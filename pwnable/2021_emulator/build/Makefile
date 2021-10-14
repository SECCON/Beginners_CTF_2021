all: emulator

emulator: *.c *.h Makefile
	gcc -o chall -Wall -Wextra -no-pie main.c
	cp chall ../files/
	cp chall ../solver/

clean:
	rm chall ../files/chall ../solver/chall 
