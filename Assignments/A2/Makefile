CC=gcc

all: threadSched.o

threadSched.o: threadSched.c
	$(CC) -o threadSched threadSched.c -pthread

clean:
	rm threadSched threadSched.o
