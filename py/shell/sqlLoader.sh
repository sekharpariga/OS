#!/usr/bin/bash
###     Author  : Sekhar Pariga
###     Date    : Tue Aug 14 08:56:36 CEST 2018
###     Email   : Sekhar.Pariga@amdocs.com

#. ./conf
TGT_CONNECT_STRING=MAXIS_B2B/MAXIS_B2B@MAXATAPT02
CURPATH=${PWD}
SRCPATH=${CURPATH}
LOGPATH=${CURPATH}/loaderLogs
csvFileName=$1
CONTROLFILE=${CURPATH}/$2
PATH=$PATH:/oravl01/oracle/12.1.0.2/bin
echo "Control file : ${CONTROLFILE}"
echo "CSV file : ${csvFileName}"

echo "--------------------------------------------------------------------"
echo
echo "Program stated at : " `date`

for file in `find "$SRCPATH" -type f -name "${csvFileName}" `
do
        file1=`basename $file`
        logFile=${LOGPATH}/${file1}.log
        badFile=${LOGPATH}/${file1}.bad
        discardFile=${LOGPATH}/${file1}.dsc
        echo "File Executing : " $file1
        sqlldr userid=${TGT_CONNECT_STRING} log=${logFile}  control=${CONTROLFILE} data=${file} file=${file} bad=${badFile} discard=${discardFile} errors=100000 BINDSIZE=2000000 READSIZE=20000000 ROWS=10000000 direct=true  multithreading=true

done

echo "Program Ended at : " `date`
echo
echo "--------------------------------------------------------------------"
echo "Goodbye `whoami`"
