all: chall

chall: src.c Makefile
	gcc src.c -no-pie -fno-stack-protector -o chall -Wall -Wextra

clean:
	rm -f chall

