import os
import socket
import re

def recvuntil(s, delim=b'\n'):
    buf = b''
    while delim not in buf:
        buf += s.recv(1)
    return buf


if __name__ == '__main__':
    host = os.getenv('CTF4B_HOST')
    port = os.getenv('CTF4B_PORT')

    if not host:
        host = 'localhost'

    if not port:
        port = '1337'

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, int(port)))

    print(recvuntil(s, b'>').decode())
    s.send(b'3\n')
    print(recvuntil(s, b'>').decode())
    s.send(b'4690bcdd9077065bf5f52712003dd51060d56314d465f7bf6dd0279e1b95f9511416d2af204cbdd814a9fc126b4889742e348d960da74ebe98c2f8096ad2438060d56314d465f7bf6dd0279e1b95f951f46e71373d85fcc3bf4c2b07aa496b19\n')

    print(recvuntil(s, b'>').decode())
    s.send(b'5\n')
    output = recvuntil(s, b'>').decode()
    print(output)

    print(re.findall('ctf4b\{.*?\}', output)[0])
