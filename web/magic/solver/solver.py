import requests
from bs4 import BeautifulSoup
import time
import os
import json


def crawl(url):
    try:
        # ログインページを表示
        res = requests.get(
            url + "/login",
            timeout=5,
        )
        res.raise_for_status()
        if "You don't have an account" not in res.text:
            print("Failed to post login")
            return 1
        soup = BeautifulSoup(res.text, "html.parser")
        csrf = soup.find("input", attrs={"name": "_csrf"}).get("value")
        cookies = res.cookies

        # ログイン
        res = requests.post(
            url + "/login",
            {
                "username": os.getenv("CTF4B_REPORT_USER"),
                "password": os.getenv("CTF4B_REPORT_PASS"),
                "_csrf": csrf,
            },
            cookies=cookies,
            timeout=5,
        )
        res.raise_for_status()
        if "Hello" not in res.text:
            print("Failed to post login")
            return 1

        # レポートページを表示
        res = requests.get(
            url + "/report",
            cookies=cookies,
            timeout=5,
        )
        res.raise_for_status()
        if "admin will check" not in res.text:
            print("Failed to get report")
            return 1
        soup = BeautifulSoup(res.text, "html.parser")
        csrf = soup.find("input", attrs={"name": "_csrf"}).get("value")

        # レポート送信
        res = requests.post(
            url + "/report",
            {
                "path": os.getenv("CTF4B_EXPLOIT"),
                "_csrf": csrf,
            },
            cookies=cookies,
            timeout=5,
        )
        res.raise_for_status()
        if "OK. Admin will check the URL you sent." not in res.text:
            print("Failed to post report")
            return 1

        print("[*] crawl requested")

        # クロール待ち
        time.sleep(30)

        # XSS checkサーバーへ疎通確認
        res = requests.get(
            os.getenv("CTF4B_CHECKER_URL") + "/ping",
            timeout=5,
        )
        res.raise_for_status()
        if "pong" not in res.text:
            print("Failed to connect check server")
            return 1

        # XSS checkサーバーに問い合わせ
        res = requests.get(
            os.getenv("CTF4B_CHECKER_URL"),
            headers={"X-API-KEY": os.getenv("CTF4B_CHECKER_KEY")},
            timeout=5,
        )
        res.raise_for_status()
        data = json.loads(res.text)

        # XSS checkサーバーがフラグを受け取ったのが直近60秒以内か確認
        time_check = int(data["time"])
        time_now = int(time.time()) - 60
        if time_check > time_now:
            print(data["flag"])  # フラグを標準出力
            return 0
        else:
            print("XSS check is too old", time_check, time_now)
            return 1

    except Exception as e:
        print(e)
        return 2


if __name__ == "__main__":
    # ローカル環境
    # os.environ["CTF4B_REPORT_USER"] = "96qmzCV67UFnqdfD"
    # os.environ["CTF4B_REPORT_PASS"] = "88YuKvwwMpdJtnyR"
    # os.environ["CTF4B_EXPLOIT"] = "magic?token=643984ee-3cfd-416f-ad00-3067143357e9"
    # os.environ["CTF4B_CHECKER_URL"] = "http://192.168.0.222:8080"
    # os.environ["CTF4B_CHECKER_KEY"] = "cdSBQ6z9CKsazrT4"
    print(crawl("https://{}:{}".format(os.getenv("CTF4B_HOST"), os.getenv("CTF4B_PORT"))))
