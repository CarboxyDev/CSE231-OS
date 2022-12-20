CC=gcc

all: fifo sockets shm

fifo: P1-fifo.o P2-fifo.o
sockets: P1-sockets.o P2-sockets.o
shm: P1-shm.o P2-shm.o

P1-fifo.o: P1-fifo.c
	$(CC) -o P1-fifo P1-fifo.c
	
P2-fifo.o: P2-fifo.c
	$(CC) -o P2-fifo P2-fifo.c

P1-sockets.o: P1-sockets.c
	$(CC) -o P1-sockets P1-sockets.c
	
P2-sockets.o: P2-sockets.c
	$(CC) -o P2-sockets P2-sockets.c

P1-shm.o: P1-shm.c
	$(CC) -o P1-shm P1-shm.c
	
P2-shm.o: P2-shm.c
	$(CC) -o P2-shm P2-shm.c


clean:
	rm -rf P1-fifo P2-fifo P1-sockets P2-sockets P1-shm P2-shm 