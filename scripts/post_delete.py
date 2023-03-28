#!/usr/bin/env python
# coding: utf-8

import pyautogui
import time

pyautogui.PAUSE = 1.5 #1 seconds wait pert action.
deleted = 0
time.sleep(10)

try:
    while(True):
        pyautogui.click(x=496, y=393)
        pyautogui.click(x=547, y=555)
        pyautogui.click(x=832, y=503)
        deleted +=1 
        print('Deleted:', deleted, 'posts')
except KeyboardInterrupt:
    pass

