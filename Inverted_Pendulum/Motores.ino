// Pinos do motor A
int ENA = 3;    //velocidade
//polos
int mA1 = 5;
int mA2 = 4;
// Pinos do motor A
int ENB = 9;    //velocidade
//polos
int mB1 = 10;
int mB2 = 11;

void inicializar_motores(){
  
  // configura os pinos dos motores como saída
  pinMode(ENA, OUTPUT);   
  pinMode(mA1, OUTPUT);
  pinMode(mA2, OUTPUT);
  pinMode(ENB, OUTPUT);   
  pinMode(mB1, OUTPUT);  
  pinMode(mB2, OUTPUT); 

  //mantem as direções dos motores como não definida
  digitalWrite(mA1,HIGH); 
  digitalWrite(mA2,HIGH); 
  digitalWrite(mB1,HIGH); 
  digitalWrite(mB2,HIGH); 
  
}


void Saida_motores(double saida){
  
  // configurar direções
  if (saida > 0){              // para frente
    digitalWrite(mA1,HIGH);
    digitalWrite(mA2,LOW);
    digitalWrite(mB1,LOW);
    digitalWrite(mB2,HIGH);
  }
  if(saida < 0){                     // para trás
    digitalWrite(mA1,LOW);
    digitalWrite(mA2,HIGH);
    digitalWrite(mB1,HIGH);
    digitalWrite(mB2,LOW);
  }
  byte vel = abs(saida);    //valor absoluto de velocidade
  
  // mantem a velocidade entre os valores maximos e minimos de saída
  if (saida > 255) vel=255;
  if (saida < -255) vel = 0;
  
  // envia o sinal PWM 
  analogWrite(ENA,vel);
  analogWrite(ENB,vel);
  
}

