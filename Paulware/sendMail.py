from email.header    import Header
from email.mime.text import MIMEText
from getpass         import getpass
from smtplib         import SMTP_SSL
import sys
import urllib


print '<br><h1>sendMail.py</h1><br>\n'
print '<h2>sys.argv:</h2><br>\n' 
print str(sys.argv) + '<p>\n' 

Username = sys.argv[1]
Subject = sys.argv[2]
Body = sys.argv[3]

login, password = 'richardspaulr1@gmail.com', 'hello?6ch'
recipients = [Username]
   
message = "From: richardspaulr1@gmail.com\n"  
message = message + "To: " + Username + "\n"
message = message + "Subject: " + Subject.strip() + "\n" 
message = message + Body

# send it via gmail
s = SMTP_SSL('smtp.gmail.com', 465, timeout=30)
s.set_debuglevel(1)
print message
try:
    s.login(login, password)
    s.sendmail(login, recipients, message)
except Exception as inst:
    print 'Exception: ' + str(inst)
finally:
    s.quit()