import json
import os
from socketserver import ThreadingTCPServer, BaseRequestHandler
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from secret import flag, key


class ImaginaryService(BaseRequestHandler):
    def handle(self):
        try:
            self.request.sendall(b'Welcome to Secret IMAGINARY NUMBER Store!\n')
            self.numbers = {}

            while True:
                num = self._menu()
                if num == 1:
                    self._save()
                elif num == 2:
                    self._show()
                elif num == 3:
                    self._import()
                elif num == 4:
                    self._export()
                elif num == 5:
                    self._secret()
                else:
                    break

        except Exception as e:
            try:
                self.request.sendall(f'ERR: {e}\n'.encode())
            except Exception:
                pass

    def _menu(self):
        self.request.sendall(b'1. Save a number\n')
        self.request.sendall(b'2. Show numbers\n')
        self.request.sendall(b'3. Import numbers\n')
        self.request.sendall(b'4. Export numbers\n')
        self.request.sendall(b'0. Exit\n')
        self.request.sendall(b'> ')
        try:
            return int(self.request.recv(128).strip())
        except ValueError:
            return 0

    def _save(self):
        try:
            self.request.sendall(b'Real part> ')
            re = int(self.request.recv(128).strip())

            self.request.sendall(b'Imaginary part> ')
            im = int(self.request.recv(128).strip())

            name = f'{re} + {im}i'
            self.numbers[name] = [re, im]
        except ValueError:
            pass

    def _show(self):
        self.request.sendall(b'-' * 50 + b'\n')
        for name in self.numbers:
            re, im = self.numbers[name]
            self.request.sendall(f'{name}: ({re}, {im})\n'.encode())
        self.request.sendall(b'-' * 50 + b'\n')

    def _import(self):
        self.request.sendall(b'Exported String> ')
        data = self.request.recv(1024).strip().decode()
        enc = bytes.fromhex(data)
        cipher = AES.new(key, AES.MODE_ECB)
        plaintext = unpad(cipher.decrypt(enc), AES.block_size)

        self.numbers = json.loads(plaintext.decode())
        self.request.sendall(b'Imported.\n')
        self._show()

    def _export(self):
        cipher = AES.new(key, AES.MODE_ECB)
        dump = pad(json.dumps(self.numbers).encode(), AES.block_size)
        self.request.sendall(dump + b'\n')
        enc = cipher.encrypt(dump)
        self.request.sendall(b'Exported:\n')
        self.request.sendall(enc.hex().encode() + b'\n')

    def _secret(self):
        if '1337i' in self.numbers:
            self.request.sendall(b'Congratulations!\n')
            self.request.sendall(f'The flag is {flag}\n'.encode())


if __name__ == '__main__':
    host = os.getenv('CTF4B_HOST')
    port = os.getenv('CTF4B_PORT')

    if not host:
        host = 'localhost'

    if not port:
        port = '1337'

    ThreadingTCPServer.allow_reuse_address = True
    server = ThreadingTCPServer((host, int(port)), ImaginaryService)

    print(f'Start server at {host}:{port}')
    server.serve_forever()
