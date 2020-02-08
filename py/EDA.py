# import cx_Oracle
# import pandas as pd
# import seaborn as sns

# con = cx_Oracle.connect('CNVAPPDB31/CNVAPPDB31@indlin235:1521/CNVABP31')
# query = "select * from bl1_charge_code"

# sns.set(color_codes=True)
# sns.set_palette(sns.color_palette("muted"))

# pdVar = pd.read_sql(query, con=con)
# # print(pdVar.dtypes)

# sns.distplot(pdVar["OPERATOR_ID"].dropna())

import pandas_oracle.tools as pt

query1 = "select CHARGE_CODE, count(1) as count from bl1_charge group by CHARGE_CODE order by charge_code"
query2 = "select sum(amount) as amount  from bl1_inv_charge_rel where TAX_SEQ_NO is null"

## opening conn
conn = pt.open_connection("oracleconConfig.yml")

## passing the conn object to the query_to_df
df1 = pt.query_to_df(query1, conn, 10000)

## passing the conn object to the query_to_df , without to open again
df2 = pt.query_to_df(query2, conn, 10)

# print(df1)

from pandas import DataFrame
   
Data = {'Year': [1920,1930,1940,1950,1960,1970,1980,1990,2000,2010],
        'Unemployment_Rate': [9.8,12,8,7.2,6.9,7,6.5,6.2,5.5,6.3]
       }
  
df = DataFrame(Data,columns=['Year','Unemployment_Rate'])
df.plot(x ='Year', y='Unemployment_Rate', kind = 'line')


## close connection
pt.close_connection(conn)