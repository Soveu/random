#!/usr/bin/python

msg = ''
with open("post", 'r') as postf:
    msg = postf.read()

payload = input()

msg += "Content-Length: " + str(len(payload)+5) + '\r\n\r\nq_id=' + payload

print(msg)
