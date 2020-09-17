CC=gcc
CFLAGS=-lm

all: main bin class conv read write gray

main: main.c funciones.h
	$(CC) funciones.c main.c -o main $(CFLAGS)

gray: gray.c funciones.h
	$(CC) funciones.c gray.c -o gray $(CFLAGS)

bin: bin.c funciones.h
	$(CC) bin.c funciones.c -o bin $(CFLAGS)

class: class.c funciones.h
	$(CC) class.c funciones.c -o class $(CFLAGS)

conv: conv.c funciones.h
	$(CC) conv.c funciones.c -o conv $(CFLAGS)

read: read.c funciones.h
	$(CC) read.c funciones.c -o read $(CFLAGS)

write: write.c funciones.h
	$(CC) write.c funciones.c -o write $(CFLAGS)