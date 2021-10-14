FROM python:3.8-buster

COPY flag /flag
COPY ./src /app

RUN pip install -r /app/requirements.txt

WORKDIR /app
CMD ["uwsgi", "--ini", "uwsgi.ini"]
