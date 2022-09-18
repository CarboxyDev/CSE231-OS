ASM=yasm
LINKER=gcc


all: io.o

io.o: io.asm
	$(ASM) -f elf64 -g dwarf2 -l io.lst io.asm
	$(LINKER) -o io io.o

clean:
	rm io io.o io.lst