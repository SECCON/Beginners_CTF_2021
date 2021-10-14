from Crypto.Util.number import *
from flag import flag

flag = bytes_to_long(flag.encode("utf-8"))

p = getPrime(1024)
q = getPrime(1024)
n = p * q
e = 3

assert 2046 < n.bit_length()
assert 375 == flag.bit_length()

print("n =", n)
print("e =", e)
print("c =", pow(flag, e, n))
