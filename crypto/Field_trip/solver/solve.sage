from Crypto.Util.number import *
# Chabnge the file name from "output.txt" ot "output.py"
from output import pub_key, cipher

def create_matrix(pub, c):
    N = len(pub)
    m_id = matrix.identity(N) * 2
    m = matrix(ZZ, 1, N + 1, pub[:] + [-c])
    B = m_id.augment(matrix(ZZ, N, 1, [-1] * N))
    m = m.stack(B)
    return m

def vec(matrix):
    for i in matrix.columns():
        if not(i[0]) and all([(j == -1 or j == 1) for j in i[1:]]):
            return i

M = create_matrix(pub_key, cipher)
LLL_M = M.transpose().LLL().transpose()
V = vec(LLL_M)

flag = "".join(list(map(str, V)))
flag = flag.replace("0", "")
flag = flag.replace("-1", "0")

print(long_to_bytes(int(flag, base=2)))
