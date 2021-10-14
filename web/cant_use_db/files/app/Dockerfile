FROM python:3.9.2-alpine

RUN mkdir /var/www
WORKDIR /var/www

COPY requirements.txt ./

RUN apk add gcc build-base linux-headers && \
      pip install -r requirements.txt

CMD ["uwsgi","--ini","/var/www/uwsgi.ini"]