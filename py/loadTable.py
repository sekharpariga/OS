#Author :Sekhar Pariga
#Date 	:Fri Feb 28 14:58:56 MYT 2020

import argparse
import cx_Oracle
import os
import subprocess

parser = argparse.ArgumentParser(description="loades csvfile into Oracle DB")
parser.add_argument('-f', '--file', type = str, metavar = '', required = True, help = "CSV File name")
parser.add_argument('-t', '--table', type = str, metavar = '', required = True, help = "Oracle Table name")
parser.add_argument('-d', '--delimitor', type = str, metavar = '', required = False, help = "csv file delimitor")

args = parser.parse_args()

fileName = args.file
oraTable = args.table.upper()
delimitor = ',' if args.delimitor == None else args.delimitor 

print "\n\n", "Input provided"
print 'delimitor : ' + delimitor
print fileName, oraTable, "\n\n"

conn = cx_Oracle.connect('MAXIS_B2B/MAXIS_B2B@kpb2bdbn03:1521/MAXATAPT02')
cur = conn.cursor()

cur.execute("SELECT 1 FROM USER_TABLES WHERE TABLE_NAME = '" + oraTable + "'")

try:
	tableExistFlag = cur.fetchall()[0][0]
except:
	tableExistFlag = 0

if tableExistFlag == 1 :
	print oraTable + " Table Exist in DB"
	cur.execute("select * from " + oraTable + " where 1 = 2")
	curCols = [i[0] for i in cur.description]
else:
	print oraTable + " Table Not exist DB"
	curCols = []

with open(fileName, 'r') as f:
	csvHeader = f.readline().strip()

csvCols = csvHeader.split(delimitor)

if tableExistFlag == 0:
	createTable = "create table " + oraTable + " (" + " varchar2(4000), ".join(csvCols[:-1]) + " varchar2(4000), " + csvCols[-1] + " varchar2(4000))"
	cur.execute(createTable)
	cur.execute("commit")
	print "\n", createTable, "\n"

control = "options (skip=1) \n\nLOAD DATA\nTRUNCATE INTO TABLE " + oraTable + "\n"
control += "FIELDS TERMINATED BY '" + delimitor + "'\n"
control += "TRAILING NULLCOLS \n("
control += (delimitor + "\n").join(csvCols)  + " )\n"

alterSet = set(csvCols) - set(curCols)
print "number of columns to alter ", len(alterSet)

if tableExistFlag == 1 and len(alterSet) > 0:
	cur.execute("truncate table " + oraTable)
	cur.execute("commit")
	for col in alterSet:
		cur.execute("alter table " + oraTable + " add " + col + " varchar2(4000)")
	cur.execute("commit")
else:
	print "No Missing columns to alter in " + oraTable
try:
	os.remove(oraTable + '.ctl')
except:
	print oraTable + '.ctl', " File not found"

with open(oraTable + '.ctl', 'w') as f:
	f.write(control)

subprocess.call(["./sqlLoader.sh",str(fileName), str(oraTable + '.ctl')])
