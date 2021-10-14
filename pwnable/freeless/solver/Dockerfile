FROM python:3.9-alpine

RUN pip install ptrlib

ADD libc-2.31.so .
ADD solve.py .

CMD ["python3", "solve.py"]
