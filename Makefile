all: lab
lab:
		gcc main.c funciones.c -o main -lm
		gcc read.c funciones.c -o read -lm
		gcc gray.c funciones.c -o gray -lm
		gcc conv.c funciones.c -o conv -lm
		gcc bin.c funciones.c -o bin -lm
		gcc class.c funciones.c -o class -lm
		gcc write.c funciones.c -o write -lm		

