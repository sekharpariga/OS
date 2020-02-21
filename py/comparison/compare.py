#Author : Sekhar
#Date   : 20th Feb, 2020

from json import load
import cx_Oracle as oracle
import pandas as pd
from datetime import datetime

global input
t1 = datetime.now()

def readFile(file, md = 'r'):
    if md == 'j':
        with open(file) as f:
            data = load(f)
    else :        
        with open(file,'r') as f:
            data = f.read()
    return data

try:
    input = readFile('source.json','j')
except:
    print("Error in reading input source Json file")

def oraConn():
    if 'ORACLE' in input['source'].upper():
        try:
            conn = oracle.Connection(input['connString'])
        except:
            print("Error in Oracle DB connection")
    return conn


legConn = oraConn()
doxConn = oraConn()
commonConn = oraConn()

def readOrapd(query):
    return pd.read_sql_query(query, oraConn())

def readOra(query):
    return commonConn.cursor().execute(query)


entitys = readOra(input['qEntity'])
legData = readOra(input['legData'])
doxData = readOra(input['doxData'])

doxColumns = {}
legColumns = {}
compkeysLeg = []
compkeysDox = []

for pos, value in enumerate(legData.description):
    legColumns[value[0]] = pos

for pos, value in enumerate(doxData.description):
    doxColumns[value[0]] = pos

for i in input['legcompkeys'].split(','):
    try:
        compkeysLeg.append(legColumns[i])
    except:
        print("error in creating compkeys positions")

for i in input['doxcompkeys'].split(','):
    try:
        compkeysDox.append(doxColumns[i])
    except:
        print("error in creating compkeys positions")






t2 = datetime.now()
print(f'Execution Duration : {t2-t1}')

'''
    TODO:
        1. NTC What is the impact of updating in the same table, match, mismatch, only as category
        2. NTC Best framework to get all the match mismatch details
'''