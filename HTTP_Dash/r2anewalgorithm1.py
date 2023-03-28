# -*- coding: utf-8 -*-
"""
@author:
Grupo 4
Luiz Felipe Almeida Silva - 18/0023098
Lucas Resende Silveira Reis - 18/0144421
Leonardo de Oliveira Costa - 17/0015599

@description: Class for SARA (Segment Aware Rate Adaptation Algorithm 
for Dynamic Adaptive Streaming Over HTTP) implementation.
"""
import time

from abc import ABCMeta, abstractmethod
from base.message import Message, MessageKind, SSMessage
from base.whiteboard import Whiteboard
from player.parser import *

from r2a.ir2a import IR2A


class r2anewalgorithm1(IR2A):
    def __init__(self, id):
        IR2A.__init__(self, id)
        self.Whiteboard = Whiteboard.get_instance() #Pega a instancia do whiteboard para obter seus dados
        self.qi = [] #Bitrates
        self.time = 0 #Parametro do SARA para estimar tempo
        self.quality = 0 #ID da qualidade escolhida (altera durante todo o funcionamento)
        self.currquality = 0 #ID da qualidade atual (altera durante todo o funcionamento) 
        self.wait = 0 #Tempo de espera para baixar o proximo segmento
        self.qindex = 0 #Index de qualidades

    def SARA(self, msg):
        self.Bcurr = Whiteboard.get_amount_video_to_play(self.Whiteboard) #Pega o tamanho do buffer

        if(self.Bcurr <= self.I): #Inicio rapido
            print('--------------------Red Zone: Fast Start--------------------')
            return self.qi[0] #Retorna a menor qualidade se o buffer esta na zona vermelha
        else:
            if(self.time > float(self.Bcurr-self.I)): #Se o tempo pra baixar o proximo e maior que a diferenca em relacao a I
                print('--------------------Yellow Zone: Filling Buffer--------------------')
                self.quality = int(max(self.time, float(self.Bcurr-self.I))) #Maior qualidade entre os dois

                if(self.quality > self.currquality): #Se a qualidade for maior
                    return self.qi[self.currquality] #Nao aumenta pra nao exaurir o buffer

                return self.qi[self.quality] #Aumenta pois ha banda
            elif(self.Bcurr <= self.Ba): #Aumento gradual zona amarela
                if(self.time < float(self.Bcurr-self.I)): #Se o tempo de espera estimado cabe dentro do threshold
                    print('--------------------Yellow Zone: Gradual Increase--------------------')
                    self.quality = self.currquality+1 #Aumenta 1 na qualidade
                    if(self.quality > self.qindex): #Nao deixa passar do indice da lista
                        self.quality = self.qindex

                    return self.qi[self.quality]
                else:
                    return self.qi[self.quality] #Nao muda a qualidade se o tempo e maior
            elif(self.Bcurr <= self.Bb): #Zona verde, mudanca agressiva
                print('--------------------Green Zone: Agressive Switching--------------------')
                if(int(max(self.time, float(self.Bcurr-self.I))) >= self.currquality): #Se o tempo pra baixar ou o espaco entre o threshold inferior for maior que a qualidade atual
                    self.quality = int(max(self.time, float(self.Bcurr-self.I))) #Escolhe a melhor qualidade pra banda atual

                    if(self.quality > self.qindex): #Nao deixa passar do indice da lista
                        self.quality = self.qindex

                    if(self.quality < self.currquality):
                        self.quality = self.currquality #Nao muda se a qualidade for menor

                    return self.qi[self.quality]
                else:
                    return self.qi[self.currquality] #Nao muda caso contrario
            elif(self.Bcurr > self.Bb): #Download adiado, zona roxa
                if(int(max(self.time, float(self.Bcurr-self.Ba))) >= self.currquality): #Se o tempo pra baixar ou o espaco entre o threshold medio for maior que a qualidade atual
                    self.quality = int(max(self.time, float(self.Bcurr-self.Ba))) #Escolhe a melhor qualidade pra banda atual
                    
                    if(self.quality > self.qindex): #Nao deixa passar do indice da lista
                        self.quality = self.qindex

                    if(self.quality < self.currquality):
                        self.quality = self.currquality #Nao muda se a qualidade for menor

                print('--------------------Purple Zone: Waiting to download:', int(self.Bcurr - self.Bb), 's--------------------')
                self.wait = int(self.Bcurr-self.Bb) #Calcula tempo de espera baseado no threshold superior
                time.sleep(self.wait) #Espera pra baixar
                return self.qi[self.quality] #Retorna para o pedido
            else:
                return self.qi[self.currquality] #Nao muda se nao for nenhum dos casos

    def media(self, msg):
        bitsize = Message.get_bit_length(msg) #Pega tamanho do segmento em bits
        downloadrate = SSMessage.get_quality_id(msg) #Pega o bitrate do segmento
        self.num += bitsize #Calcula somatorio wi adicionando o tamanho do segmento atual com os anteriores
        self.den += bitsize/downloadrate  #Calcula wi/di e adiciona com o do passado
        self.H = self.num/self.den #Calcula a media harmonica atual
        print('-----Mean:', self.H, '-----')

    def handle_xml_request(self, msg):
        self.send_down(msg) #Envia pra baixo (pedido)
        pass

    def handle_xml_response(self, msg):
        descritor = parse_mpd(msg.get_payload()) #Pega descritor
        self.qi = descritor.get_qi() #Pega as qualidades
        self.qindex = len(self.qi)-1
        self.send_up(msg) #Envia pra cima (resposta)
        pass

    def handle_segment_size_request(self, msg):
        msg.add_quality_id(self.SARA(msg)) #Escolhe qualidade do proximo usando a saida do SARA
        self.send_down(msg) #Envia pra baixo (pedido)
        pass

    def handle_segment_size_response(self, msg):
        self.media(msg) #Calcula a media apos receber segmento
        self.time = Message.get_bit_length(msg)/self.H #Calcula tempo pra pegar o segmento
        self.currquality = SSMessage.get_quality_id(msg) #Pega o bitrate atual

        for i in range(0, self.qindex+1): #Converte o bitrate para o seu id na lista
            if(self.currquality <= int(self.qi[i])):
                self.currquality = i
                break

        self.send_up(msg) #Envia pra cima (resposta)
        pass
    
    def initialize(self):
        self.I = 5 #Parametros algoritmo (threshold I)
        self.Ba = 15 #Balpha
        self.Bb = 35 #Bbeta
        self.Bmax = 40 #Bmax
        self.Bcurr = 0 #Bcurr

        self.H = 0 #Parametros media (media)
        self.num = 0.0 #Numerador media
        self.den = 0.0 #Denominador media
        IR2A.initialize(self)
        pass

    def finalization(self):
        IR2A.finalization(self)
        pass
