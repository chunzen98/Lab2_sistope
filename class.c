#include "funciones.h"
       
int main(int argc, char** argv){
    
    //Creacion pipe
    int *pipe1 = (int*)malloc(sizeof(int) * 2);
    if(pipe(pipe1) == -1){
        printf("Error en syscall PIPE\n");
        exit(-1);
    };

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

    //Classificacion
    int clas = clasificacion(img, atoi(argv[8]));

    if(atoi(argv[9]) == 1){
        if(atoi(argv[5]) == 0){
            printf("\n---------------------------\n");
            printf("|imagen\t\tnearly black|\n");
            printf("---------------------------\n");
        }
        if(clas == 1){
            printf("imagen_%d.jpg\t\tyes\n", atoi(argv[5]));
        }
        else if(clas == 0){
            printf("imagen_%d.jpg\t\tno\n", atoi(argv[5]));
        }
    }

    //Proceso fork crea hijo
    int pid_write;    
    if((pid_write = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };

    if(pid_write == 0){ // Proceso del hijo
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


        char *args[]={"./write", buffWidth, buffHeight, buffChannels, buffSize, argv[5], argv[6], argv[7], argv[8], argv[9], NULL};     
        execvp(args[0],args);
    }
    else{ // Padre
        close(pipe1[READ]);
        write(pipe1[WRITE], img->data, img->size);
        close(pipe1[WRITE]);
    }
}