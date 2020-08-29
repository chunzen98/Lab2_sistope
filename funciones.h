#ifndef funciones_h
#define funciones_h

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/wait.h>
#include <sys/socket.h>

#define READ 0
#define WRITE 1

typedef struct JPG{
    int width;		//img->data px width
    int height;		//img->data px height
    int channels;	//img->data canales (si es 3 no tiene Alpa)
    int size;		//img->data Total de px
    char* data; 	//NO USAR plox
} JPG;

 JPG* leerJPG(char* nombreArchivo);
void escribirJPG(JPG* imagen, char* nombreArchivo);
void escalaGris(JPG* img, JPG* imgGray);
void filtro(JPG* img, JPG* imgMask, char* maskName);
void binarizacion(JPG* img, JPG* imgBin, int umbral);
int clasificacion(JPG* img, int umbral);

#endif