from Crypto.Util.number import *
from random import getrandbits
from flag import flag


flag = bytes_to_long(flag.encode("utf-8"))
flag = bin(flag)[2:]
length = len(flag)

A = []
a, b = 0, 0
for _ in range(length):
    a += getrandbits(32) + b
    b += a
    A.append(a)

p = getStrongPrime(512)
q = getStrongPrime(512)

assert q > sum(A)

pub_key = [a * p % q for a in A]
cipher = sum([int(flag[i]) * pub_key[i] for i in range(length)])

f = open("output.txt", "w")
f.write("pub_key = " + str(pub_key) + "\n")
f.write("cipher = " + str(cipher) + "\n")
f.close()

