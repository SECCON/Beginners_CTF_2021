FROM python:3.9.2-alpine

ENV CTF4B_HOST=0.0.0.0
ENV CTF4B_PORT=31415

WORKDIR /app
ADD . /app

RUN pip install -r requirements.txt

CMD ["python3", "/app/solver.py"]