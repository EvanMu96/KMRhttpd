#!/Users/komoriii/anaconda3/bin/python

import sys
import os
import psycopg2

length = os.getenv('CONTENT_LENGTH')

"""
username(str)
hashval(str)
"""
def check_user(username, hashval):
    conn = psycopg2.connect("dbname=User user=postgres")
    cur = conn.cursor()
    cur.execute("select Count(*) from login where username=\'" + username + "\' and authcode=\'" + hashval + "\'")
    res = cur.fetchone()
    if(res[0] == 1):
        return True
    else:
        return False


"""
data(str)
"""
def res_handler(data):
    print("Content-type:text/html\n")
    print('<html>')
    print('<head>')
    print('<title>TEST</title>')
    print('</head>')
    print('<body>')
    print(data)
    print('</body>')
    print('</html>')



def req_handler(length):
    if length:
        postdata = sys.stdin.read(int(length))
        datalist = postdata.split("&")
        varlist = [d.split("=") for d in datalist]
        print(varlist[0][1])
        print(varlist[1][1])
        return varlist[0][1], varlist[1][1]
    
if length:
    username, hashval = req_handler(length)
    if check_user(username, hashval):
        res_handler("welcome")
    else:
        res_handler("not a valid user")


