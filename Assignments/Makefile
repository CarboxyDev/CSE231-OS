ASM=yasm
LINKER=ld
DEBUG_FLAGS=-g dwarf2
LST_FLAGS=-l io.lst


all: io.o

io.o: io.asm
	$(ASM) -f elf64 $(DEBUG_FLAGS) $(LST_FLAGS) io.asm
	$(LINKER) -o io io.o

clean:
	rm io io.o io.lst