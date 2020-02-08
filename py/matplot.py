import numpy as np
import matplotlib.pyplot as plt
import pandas_oracle.tools as pt

# query1 = "select CHARGE_CODE, count(1) as count from bl1_charge group by CHARGE_CODE order by CHARGE_CODE"
query2 = "select RECORD_NAME,TOT_RECORD_COUNT_LEG  COUNT_LEG,  TOT_RECORD_COUNT_NEW COUNT_DOX, MATCH_CNT, MATCH_KD_CNT, MATCH_KD_DEFECT_CNT from MIR_REP_SUMMARY_DTV_B2B where RECORD_NAME <> 'TOTAL' order by to_number(TOT_RECORD_COUNT_LEG)"

# conn = pt.open_connection("oracleconConfig.yml")
conn = pt.open_connection("dtv.yml")

## passing the conn object to the query_to_df
df1 = pt.query_to_df(query2, conn, 10000)

#creating datasets
x = df1['RECORD_NAME']
y = df1['COUNT_LEG']

y2 = df1['COUNT_DOX']

y3 = df1['MATCH_CNT']

y4 = df1['MATCH_KD_CNT']

y5 = df1['MATCH_KD_DEFECT_CNT']

plt.plot(x,y, label='Legacy Record Count', color='red',linestyle='--', marker='o' )
plt.plot(x,y2,label='Amdocs Record Count',color='yellow',linestyle='--', marker='o')
plt.plot(x,y3,label='Match Count',color='green',linestyle='--', marker='o')
plt.plot(x,y4,label='Match + KD Count',color='blue',linestyle='--', marker='o')
plt.plot(x,y5,label='Match + KD + Defect Count',color='orange',linestyle='--', marker='o')
plt.xlabel("Line Of Business")
plt.ylabel("Record Count per LOB")
plt.title("Match, Match+KD, Match+KD+Defect per LOB w.r.t Received Record\n")
# axes = plt.gca()
# axes.set_ylim([3000,170000])
plt.legend()

plt.show()