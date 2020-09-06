CC=gcc
CFLAGS=-c -lm -g

all: main.o bin.o class.o conv.o read.o write.o gray.o funciones.o

main.o: main.c funciones.h
	$(CC) $(CFLAGS) main.c -o main.o

bin.o: bin.c funciones.h
	$(CC) $(CFLAGS) bin.c -o bin.o

class.o: class.c funciones.h
	$(CC) $(CFLAGS) class.c -o class.o

conv.o: conv.c funciones.h
	$(CC) $(CFLAGS) conv.c -o conv.o

read.o: read.c funciones.h
	$(CC) $(CFLAGS) read.c -o read.o

write.o: write.c funciones.h
	$(CC) $(CFLAGS) write.c -o write.o

gray.o: gray.c funciones.h
	$(CC) $(CFLAGS) gray.c -o gray.o

funciones.o: funciones.c funciones.h
	$(CC) $(CFLAGS) funciones.c -o funciones.o

clean:
	rm -f main *.o