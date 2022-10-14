CC=gcc
BINPATH=./cmdbin/

all: unix-shell.o bin

unix-shell.o: unix-shell.c
	$(CC) -o unix-shell unix-shell.c -pthread

bin: cat.o ls.o date.o mkdir.o rm.o

cat.o:
	$(CC) -o $(BINPATH)cat $(BINPATH)cat.c

ls.o:
	$(CC) -o $(BINPATH)ls $(BINPATH)ls.c

date.o:
	$(CC) -o $(BINPATH)date $(BINPATH)date.c

mkdir.o:
	$(CC) -o $(BINPATH)mkdir $(BINPATH)mkdir.c

rm.o:
	$(CC) -o $(BINPATH)rm $(BINPATH)rm.c

clean:
	rm unix-shell unix-shell.o $(BINPATH)cat $(BINPATH)ls $(BINPATH)date $(BINPATH)rm $(BINPATH)mkdir $(BINPATH)*.o
