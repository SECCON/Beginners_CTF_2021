import os
import random
from flask import Flask, render_template, request, session

# ====================

app = Flask(__name__)
app.FLAG = os.getenv("CTF4B_FLAG")

# ====================

class Player:
    def __init__(self):
        self.name = None
        self.color = None
        self.__role = random.choice(['VILLAGER', 'FORTUNE_TELLER', 'PSYCHIC', 'KNIGHT', 'MADMAN'])
        # :-)
        # self.__role = random.choice(['VILLAGER', 'FORTUNE_TELLER', 'PSYCHIC', 'KNIGHT', 'MADMAN', 'WEREWOLF'])

    @property
    def role(self):
        return self.__role

    # :-)
    # @role.setter
    # def role(self, role):
    #     self.__role = role


# ====================

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == 'GET':
        return render_template('index.html')

    if request.method == 'POST':
        player = Player()

        for k, v in request.form.items():
            player.__dict__[k] = v

        return render_template('result.html',
            name=player.name,
            color=player.color,
            role=player.role,
            flag=app.FLAG if player.role == 'WEREWOLF' else ''
        )

# ====================

if __name__ == '__main__':
    app.run(host=os.getenv("CTF4B_HOST"), port=os.getenv("CTF4B_PORT"))