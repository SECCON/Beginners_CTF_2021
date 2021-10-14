import os
import re
import time
import random
import shutil
import secrets
import datetime
from flask import Flask, render_template, session, redirect

app = Flask(__name__)
app.secret_key = secrets.token_bytes(256)


def init_userdata(user_id):
    try:
        os.makedirs(f"./users/{user_id}", exist_ok=True)
        open(f"./users/{user_id}/balance.txt", "w").write("20000")
        open(f"./users/{user_id}/noodles.txt", "w").write("0")
        open(f"./users/{user_id}/soup.txt", "w").write("0")
        return True
    except:
        return False


def get_userdata(user_id):
    try:
        balance = open(f"./users/{user_id}/balance.txt").read()
        noodles = open(f"./users/{user_id}/noodles.txt").read()
        soup = open(f"./users/{user_id}/soup.txt").read()
        return [int(i) for i in [balance, noodles, soup]]
    except:
        return [0] * 3


@app.route("/")
def top_page():
    user_id = session.get("user")
    if not user_id:
        dirnames = datetime.datetime.now()
        user_id = f"{dirnames.hour}{dirnames.minute}/" + secrets.token_urlsafe(30)
        if not init_userdata(user_id):
            return redirect("/")
        session["user"] = user_id
    userdata = get_userdata(user_id)
    info = {
        "user_id": re.sub("^[0-9]*?/", "", user_id),
        "balance": userdata[0],
        "noodles": userdata[1],
        "soup": userdata[2]
    }
    return render_template("index.html", info = info)


@app.route("/buy_noodles", methods=["POST"])
def buy_noodles():
    user_id = session.get("user")
    if not user_id:
        return redirect("/")
    balance, noodles, soup = get_userdata(user_id)
    if balance >= 10000:
        noodles += 1
        open(f"./users/{user_id}/noodles.txt", "w").write(str(noodles))
        time.sleep(random.uniform(-0.2, 0.2) + 1.0)
        balance -= 10000
        open(f"./users/{user_id}/balance.txt", "w").write(str(balance))
        return "💸$10000"
    return "ERROR: INSUFFICIENT FUNDS"


@app.route("/buy_soup", methods=["POST"])
def buy_soup():
    user_id = session.get("user")
    if not user_id:
        return redirect("/")
    balance, noodles, soup = get_userdata(user_id)
    if balance >= 20000:
        soup += 1
        open(f"./users/{user_id}/soup.txt", "w").write(str(soup))
        time.sleep(random.uniform(-0.2, 0.2) + 1.0)
        balance -= 20000
        open(f"./users/{user_id}/balance.txt", "w").write(str(balance))
        return "💸💸$20000"
    return "ERROR: INSUFFICIENT FUNDS"


@app.route("/eat")
def eat():
    user_id = session.get("user")
    if not user_id:
        return redirect("/")
    balance, noodles, soup = get_userdata(user_id)
    shutil.rmtree(f"./users/{user_id}/")
    session["user"] = None
    if (noodles >= 2) and (soup >= 1):
        return os.getenv("CTF4B_FLAG")
    if (noodles >= 2):
        return "The noodles seem to get stuck in my throat."
    if (soup >= 1):
        return "This is soup, not ramen."
    return "Please make ramen."


if __name__ == "__main__":
    app.run()
