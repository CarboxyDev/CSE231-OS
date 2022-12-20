CC=gcc

all: a1.o a2.o b.o

a1.o: a1.c
	$(CC) -o a1 a1.c -pthread

a2.o: a2.c
	$(CC) -o a2 a2.c -pthread

b.o: b.c
	$(CC) -o b b.c -pthread

clean:
	rm a1 a2 b
