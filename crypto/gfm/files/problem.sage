
FLAG = b'<censored>'

SIZE = 8
p = random_prime(2^128)
MS = MatrixSpace(GF(p), SIZE)

key = MS.random_element()
while key.rank() != SIZE:
    key = MS.random_element()

M = copy(MS.zero())
for i in range(SIZE):
    for j in range(SIZE):
        n = i * SIZE + j
        if n < len(FLAG):
            M[i, j] = FLAG[n]
        else:
            M[i, j] = GF(p).random_element()

enc = key * M * key

print('p:', p)
print('key:', key)
print('enc:', enc)

