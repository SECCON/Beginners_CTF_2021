all: chall

CC=tigress # https://tigress.wtf/
CFLAGS+= --Environment=x86_64:Linux:Gcc:10.2.0
CFLAGS+= --Seed=42
CFLAGS+= --Transform=Flatten
CFLAGS+= --Functions=main
CFLAGS+= --FlattenDispatch=switch
CFLAGS+= --FlattenObfuscateNext=false
CFLAGS+= --FlattenRandomizeBlocks=true
CFLAGS+= --FlattenConditionalKinds=branch,compute,flag
CFLAGS+= --FlattenImplicitFlowNext=true
CFLAGS+= --Transform=EncodeArithmetic
CFLAGS+= --Functions=main
CFLAGS+= --EncodeArithmeticKinds=integer
CFLAGS+= --out=src_obfuscated.c
CFLAGS+= -o chall

chall: src.c Makefile
	$(CC) $(CFLAGS) src.c
	cp chall ../files/
	cp chall ../solver/

clean: chall
	rm chall
	rm src_obfuscated.c
