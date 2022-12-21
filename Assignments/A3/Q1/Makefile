CC=gcc

all: a1.o a2.o b1.o b2.o

a1.o: a1.c
	$(CC) -o a1 a1.c -pthread

a2.o: a2.c
	$(CC) -o a2 a2.c -pthread

b1.o: b1.c
	$(CC) -o b1 b1.c -pthread

b2.o: b2.c
	$(CC) -o b2 b2.c -pthread

clean:
	rm a1 a2 b1 b2
