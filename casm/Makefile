all: clean build

build: main.c fact.o
	gcc -m32 main.c fact.o -o fact -g

fact.o: fact.asm
	nasm -g -f elf -o fact.o fact.asm -g

clean:
	rm -f fact
	rm -f fact.o