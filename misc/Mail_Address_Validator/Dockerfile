FROM ubuntu:18.04

ENV DEBIAN_FRONTEND nointeractive

RUN apt-get -y update --fix-missing && apt-get -y upgrade
RUN apt-get -y install xinetd ruby
RUN groupadd -r misc && useradd -r -g misc misc

ADD build/misc.xinetd    /etc/xinetd.d/misc
ADD build/init.sh       /etc/init.sh
ADD build/redir.sh      /home/misc/redir.sh
RUN chmod 550           /home/misc/redir.sh
RUN chmod 700           /etc/init.sh
RUN chmod 1733  /tmp /var/tmp /dev/shm

ADD FLAG        /home/misc/flag.txt
ADD files/main.rb /home/misc/main.rb
RUN chmod 440   /home/misc/flag.txt
RUN chmod 550   /home/misc/main.rb

RUN chown -R root:misc /home/misc

RUN ls /home/misc -lh

RUN service xinetd restart

