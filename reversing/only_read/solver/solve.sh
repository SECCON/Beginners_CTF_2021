#!/bin/bash
objdump -M intel -j .text --disassemble=main chall |grep cmp|awk '{print $5}'|sed 's/al,//g'|xargs -I{} python3 -c 'print(chr({}), end="")'
