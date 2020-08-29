#include "funciones.h"

int main(int argc, char** argv){

    //Recibe imagen mediante pipe de la etapa anterior
    JPG* img = (JPG*)malloc(sizeof(JPG));
    img->width = atoi(argv[1]);
    img->height = atoi(argv[2]);
    img->channels = atoi(argv[3]);
    img->size = atoi(argv[4]);
    img->data = (char*)malloc(sizeof(char)*img->size);
    char rBuff[1];
    int x = 0;
    while(read(STDIN_FILENO, rBuff, 1) > 0){
        img->data[x] = rBuff[0];
        x++;
    };
    
    char bufferNombre[50];
    char buffer[12];

    strcpy(bufferNombre, "imagenOut_");
    sprintf(buffer, "%d",atoi(argv[5])+1);
    strcat(bufferNombre, buffer);
    strcat(bufferNombre, ".jpg");

    escribirJPG(img, bufferNombre);

}
