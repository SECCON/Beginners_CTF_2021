all: chall

chall: src.c Makefile
	gcc -Wl,-z,lazy,-z,relro src.c -o chall -fno-stack-protector -no-pie

clean:
	rm -f chall
