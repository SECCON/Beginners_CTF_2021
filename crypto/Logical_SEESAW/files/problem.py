from Crypto.Util.number import *
from random import random, getrandbits
from flag import flag

flag = bytes_to_long(flag.encode("utf-8"))
length = flag.bit_length()
key = getrandbits(length)
while not length == key.bit_length():
    key = getrandbits(length)

flag = list(bin(flag)[2:])
key = list(bin(key)[2:])

cipher_L = []

for _ in range(16):
    cipher = flag[:]
    m = 0.5
    
    for i in range(length):
        n = random()
        if n > m:
            cipher[i] = str(eval(cipher[i] + "&" + key[i]))
            
    cipher_L.append("".join(cipher))


print("cipher =", cipher_L)
