ASM=yasm
LINKER=ld
DEBUG_FLAGS=-g dwarf2
LST_FLAGS=-l io.lst



all: io.o

io.o: io.asm
	$(ASM) -f elf64 $(DEBUG_FLAGS) $(LST_FLAGS) io.asm
	$(LINKER) -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o io io.o -lc

clean:
	rm io io.o io.lst