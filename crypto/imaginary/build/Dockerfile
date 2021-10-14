FROM python:3.9.4-alpine

WORKDIR /usr/src/app
COPY . .
RUN apk add gcc g++ make libffi-dev openssl-dev git
RUN pip install -r requirements.txt

ENV CTF4B_HOST "0.0.0.0"
ENV CTF4B_PORT "1337"

CMD ["python", "./app.py"]
