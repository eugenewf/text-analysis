CC = gcc
CFLAGS  = -ansi -pedantic -Wall

all: getandprint.o
	$(CC) $(CFLAGS) -o getandprint getandprint.o

getandprint.o: getandprint.c
	$(CC) $(CFLAGS) -c getandprint.c 
	
clean:
	rm *.o getandprint
