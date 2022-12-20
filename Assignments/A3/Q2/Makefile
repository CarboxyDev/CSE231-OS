CC=gcc

all: fifo sockets shm

fifo: P1-fifo.o P2-fifo.o
#sockets: P1-sockets.o P2-sockets.o
#shm: P1-shm.o P2-shm.o

P1-fifo.o: P1-fifo.c
	$(CC) -o P1-fifo P1-fifo.c
	
P2-fifo.o: P2-fifo.c
	$(CC) -o P2-fifo P2-fifo.c

clean:
	rm -rf P1-fifo P2-fifo