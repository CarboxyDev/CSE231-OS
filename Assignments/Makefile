ASM=yasm
LINKER=gcc
DEBUG_FLAGS=-g dwarf2
LST_FLAGS=-l io.lst
LINKER_FLAGS=-m64


all: io.o

io.o: io.asm
	$(ASM) -f elf64 $(DEBUG_FLAGS) $(LST_FLAGS) io.asm
	$(LINKER) $(LINKER_FLAGS) -o io io.o

clean:
	rm io io.o io.lst