#include "funciones.h"

int main(int argc, char** argv){

    char bufferNombre[50];
    char buffer[12];
    //Nombre de imagen
    strcpy(bufferNombre, "imagen_");
    sprintf(buffer, "%d",atoi(argv[1])+1);
    strcat(bufferNombre, buffer);
    strcat(bufferNombre, ".jpg");

    JPG* img = (JPG*)malloc(sizeof(JPG));
    img = leerJPG(bufferNombre);

    //Creacion pipe
    int *pipe1 = (int*)malloc(sizeof(int) * 2);
    if(pipe(pipe1) == -1){
        printf("Error en syscall PIPE\n");
        exit(-1);
    };
    //Proceso fork crea hijo
    int pid_gray;    
    if((pid_gray = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };



    if(pid_gray == 0){ // Proceso del hijo
        close(pipe1[WRITE]);
        dup2(pipe1[READ], STDIN_FILENO);

        // for (int i = 0; i < img->size; i++){printf("%d",img->data[i]);}

        char buffWidth[10];
        char buffHeight[10];
        char buffChannels[10];
        char buffSize[20];
        sprintf(buffWidth, "%d", img->width);
        sprintf(buffHeight, "%d", img->height);
        sprintf(buffChannels, "%d", img->channels);
        sprintf(buffSize, "%d", img->size);


        char *args[]={"./gray", buffWidth, buffHeight, buffChannels, buffSize, argv[1], argv[2], argv[3], argv[4], argv[5], NULL};     
        execvp(args[0],args);
    }
    else{ // Padre
        close(pipe1[READ]);
        write(pipe1[WRITE], img->data, img->size);
        close(pipe1[WRITE]);
    }
}