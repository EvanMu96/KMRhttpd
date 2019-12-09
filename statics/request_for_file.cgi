#!/Users/komoriii/anaconda3/bin/python

import sys, os

length = os.getenv('CONTENT_LENGTH')

if length:
    postdata = sys.stdin.read(int(length))
    print("Content-type:text/html\n")
    print('<html>')
    print('<head>')
    print('<title>TEST</title>')
    print('</head>')
    print('<body>')
    print('<h2> TEST </h2>')
    print("<li>" + postdata + "</li>")
    print ('</body>')
    print('</html>')
else:
    print ("Content-type:text/html\n")
    print('no found')