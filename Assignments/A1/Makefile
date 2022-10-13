CC=gcc
BINPATH=./cmdbin/

all: unix-shell.o bin

unix-shell.o: unix-shell.c
	$(CC) -o unix-shell unix-shell.c

bin: cat.o ls.o date.o

cat.o:
	$(CC) -o $(BINPATH)cat $(BINPATH)cat.c

ls.o:
	$(CC) -o $(BINPATH)ls $(BINPATH)ls.c

date.o:
	$(CC) -o $(BINPATH)date $(BINPATH)date.c

clean:
	rm unix-shell unix-shell.o $(BINPATH)cat $(BINPATH)ls $(BINPATH)date $(BINPATH)cat.o $(BINPATH)ls.o $(BINPATH)date.o
