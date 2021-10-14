FROM python:3.9.2-alpine

RUN apk --no-cache add socat
RUN adduser -D ctf

ADD writeme.py /home/ctf/writeme/writeme.py
ADD flag /home/ctf/writeme/flag
RUN chmod 500 /home/ctf/writeme/writeme.py
RUN chmod 400 /home/ctf/writeme/flag
RUN chown ctf:root /home/ctf -R

USER ctf
WORKDIR /home/ctf/writeme/
CMD socat TCP-L:27182,fork,reuseaddr EXEC:"python3 ./writeme.py",stderr