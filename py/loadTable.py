#Author :Sekhar Pariga
#Date 	:Fri Feb 28 14:58:56 MYT 2020

import argparse, cx_Oracle, os, subprocess

parser = argparse.ArgumentParser(description="loades csvfile into Oracle DB")
parser.add_argument('-f', '--file', type = str, metavar = '', required = True, help = "CSV File name")
parser.add_argument('-t', '--table', type = str, metavar = '', required = True, help = "Oracle Table name")
parser.add_argument('-d', '--delimitor', type = str, metavar = '', required = False, help = "csv file delimitor")

args = parser.parse_args()

fileName = args.file
oraTable = args.table.upper()
delimitor = ',' if args.delimitor == None else args.delimitor 

print 'delimitor : ' + delimitor
print fileName, oraTable, "\n\n"

with open(fileName, 'r') as f:
	csvHeader = f.readline().strip()

csvCols = csvHeader.split(delimitor)
control = "options (skip=1) \n\nLOAD DATA\nTRUNCATE INTO TABLE " + oraTable + "\n"
control += "FIELDS TERMINATED BY '" + delimitor + "'\n" + "TRAILING NULLCOLS \n("
control += (delimitor + "\n").join(csvCols)  + " )\n"

conn = cx_Oracle.connect('MAXIS_B2B/MAXIS_B2B@kpb2bdbn03:1521/MAXATAPT02')
cur = conn.cursor()

try:
	cur.execute("SELECT 1 FROM USER_TABLES WHERE TABLE_NAME = '" + oraTable + "'")
	tableExistFlag = cur.fetchall()[0][0]
except:
	tableExistFlag = 0

if tableExistFlag == 1 :
	# print oraTable + " Table Exist in DB"
	cur.execute("select * from " + oraTable + " where 1 = 2")
	curCols = [i[0] for i in cur.description]
	alterSet = set(csvCols) - set(curCols)
	if len(alterSet) > 0:
		cur.execute("truncate table " + oraTable)
		cur.execute("commit")
		for col in alterSet:
			cur.execute("alter table " + oraTable + " add " + col + " varchar2(4000)")
else:
	# print oraTable + " Table Not exist DB"
	createTable = "create table " + oraTable + " (" + " varchar2(4000), ".join(csvCols) + " varchar2(4000))"
	cur.execute(createTable)

with open(oraTable + '.ctl', 'w') as f:
	f.write(control)

subprocess.call(["./sqlLoader.sh",str(fileName), str(oraTable + '.ctl')])