#!/usr/bin/env python
# coding: utf-8

import pyautogui
import pyperclip
import time

#Parameters
pyautogui.PAUSE = 1.5 #1 seconds wait pert action.
kanji = '気'
reading = 'き'
translation = 'Mind, Spirit, Energy'
sentence = 'やる気がないね...'
s_translation = 'I don\'t feel like doing it...'
kanjin = 19

def canva():
    time.sleep(10) #Acessing canva
    pyautogui.hotkey("ctrl", "t")
    pyperclip.copy('https://www.canva.com/')
    pyautogui.hotkey("ctrl", "l")
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.press("enter")
    time.sleep(10)

def kanji_dir():
    pyautogui.click(x=96, y=432) #Kanji directory
    time.sleep(5)
    pyautogui.click(x=1255, y=734)
    pyautogui.press("down")
    pyautogui.press("down")
    pyautogui.click(x=1218, y=728)
    pyautogui.click(x=367, y=443) #Kanji folder

def copy(kanjin):
    time.sleep(3)
    pyautogui.click(x=495, y=428) #1 copy
    pyautogui.click(x=521, y=284)
    time.sleep(3)
    pyautogui.click(x=343, y=612)
    pyperclip.copy(f'kanji{kanjin}') #Renaming
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")

def make_en(kanji, reading, translation, sentence, s_translation, kanjin):
    #EN
    time.sleep(3)
    pyautogui.click(x=400, y=496)
    time.sleep(15)
    pyautogui.PAUSE=0.5
    pyautogui.click(x=900, y=416)
    pyautogui.click(x=900, y=416)
    pyautogui.click(x=900, y=416)
    pyautogui.hotkey("end")
    pyautogui.hotkey("shift", "home")
    pyperclip.copy('Daily Kanji') #Daily Kanji
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=894, y=506, clicks=3)
    pyperclip.copy(kanji) #Daily Kanji
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    time.sleep(3)
    pyautogui.scroll(-6) #Scroll to Kanji part
    pyautogui.click(x=992, y=426, clicks=2)
    pyautogui.hotkey("shift", "home")
    pyperclip.copy(kanji) #Copy Kanji
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=1151, y=410)
    pyautogui.click(x=888, y=532, clicks=2)
    pyautogui.press("home")
    pyautogui.hotkey("shift", "end")
    pyperclip.copy(translation) #Copy Translation
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=1004, y=593, clicks=2)
    pyautogui.press("backspace", 2)
    pyperclip.copy(f'{kanjin}') #Copy Translation
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    time.sleep(3)
    pyautogui.scroll(-6) #Scroll to Kanji part
    pyautogui.click(x=992, y=426, clicks=2)
    pyautogui.hotkey("shift", "home")
    pyperclip.copy(kanji) #Copy Kanji
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=1151, y=410)
    pyautogui.click(x=888, y=532, clicks=2)
    pyautogui.hotkey("ctrl", "a")
    pyperclip.copy(translation) #Copy Translation
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.press("enter")
    pyperclip.copy(reading) #Copy Reading
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    time.sleep(3)
    pyautogui.scroll(-6) #Scroll to Kanji part
    pyautogui.click(x=895, y=463, clicks=2)
    pyautogui.press("home")
    pyautogui.hotkey("shift", "end")
    pyperclip.copy(sentence) #Copy Sentence
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    time.sleep(3)
    pyautogui.scroll(-6) #Scroll to Kanji part
    pyautogui.click(x=898, y=357, clicks=3)
    pyperclip.copy('Example') #Copy Sentence
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=893, y=402, clicks=3)
    pyperclip.copy(sentence) #Copy Sentence
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=895, y=448, clicks=3)
    pyperclip.copy(s_translation) #Copy Translation
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")
    pyautogui.click(x=898, y=493, clicks=3)
    pyperclip.copy(f'{kanji} {reading} {translation}') #Copy Vocab
    pyperclip.paste()
    pyautogui.hotkey("ctrl", "v")

canva()
kanji_dir()
copy(kanjin)
make_en(kanji, reading, translation, sentence, s_translation, kanjin)

