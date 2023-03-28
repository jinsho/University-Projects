#!/usr/bin/env python
# coding: utf-8
import camelot.io as c
import pandas as pd

MI = 0
MM = 0
MS = 0
SS = 0
prog = 0
total = 0

#Takes all tables, export to a csv file.
#file = c.read_pdf('hr2.pdf', pages = 'all')
#file.export("1.csv", f="csv")

#Tables with the scores.
page1 = pd.read_csv('1-page-1-table-1.csv')
page2 = pd.read_csv('1-page-2-table-1.csv')

for i in range(1, len(page1["Nota"])):
    #print(page1["Nota"][i])
    if(page1["Nota"][i] == 'MI'):
        MI += 1
    elif(page1["Nota"][i] == 'MM'):
        MM += 1
    elif(page1["Nota"][i] == 'MS'):
        MS += 1
    elif(page1["Nota"][i] == 'SS'):
        SS += 1
    else:
        prog += 1
    total += 1

for j in range(len(page2["Nota"])):
    #print(page2["Nota"][j])
    if(page2["Nota"][j] == 'MI'):
        MI += 1
    elif(page2["Nota"][j] == 'MM'):
        MM += 1
    elif(page2["Nota"][j] == 'MS'):
        MS += 1
    elif(page2["Nota"][j] == 'SS'):
        SS += 1
    else:
        prog += 1
    total += 1    

total = total-prog-MI
print('MI:', MI, '\nMM:', MM, '\nMS:', MS, '\nSS:', SS, '\nCursando:', prog, '\nTotal:', total)
