all: chall

chall: src.c Makefile
	gcc src.c -no-pie -fno-stack-protector -o chall -Wall -Wextra
	cp chall ../solver/chall
	cp chall ../files/chall

clean:
	rm -f chall ../solver/chall ../files/chall

