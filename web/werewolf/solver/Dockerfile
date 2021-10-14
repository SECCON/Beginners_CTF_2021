FROM python:3.7-alpine

ENV CTF4B_HOST=0.0.0.0
ENV CTF4B_PORT=80

RUN pip install requests beautifulsoup4

COPY ./solver.py /solver.py

CMD ["python",  "/solver.py"]