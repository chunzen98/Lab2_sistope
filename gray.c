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
    
    // GRAY
    JPG* imgGray = (JPG*)malloc(sizeof(JPG));
    imgGray->height = img->height;
    imgGray->width = img->width;
    imgGray->channels = img->channels == 4 ? 2 :1;
    imgGray->size = imgGray->height * imgGray->width * imgGray->channels;
    imgGray->data = (char*)malloc(sizeof(char) * imgGray->size);

    escalaGris(img, imgGray);




    //Proceso fork crea hijo
    int pid_conv;    
    if((pid_conv = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };


    if(pid_conv == 0){ // Proceso del hijo
        close(pipe1[WRITE]);
        dup2(pipe1[READ], STDIN_FILENO);

        // for (int i = 0; i < img->size; i++){printf("%d",img->data[i]);}

        char buffWidth[10];
        char buffHeight[10];
        char buffChannels[10];
        char buffSize[20];
        sprintf(buffWidth, "%d", imgGray->width);
        sprintf(buffHeight, "%d", imgGray->height);
        sprintf(buffChannels, "%d", imgGray->channels);
        sprintf(buffSize, "%d", imgGray->size);


        char *args[]={"./conv", buffWidth, buffHeight, buffChannels, buffSize, argv[5], argv[6], argv[7], argv[8], argv[9], NULL};     
        execvp(args[0],args);
    }
    else{ // Padre
        close(pipe1[READ]);
        write(pipe1[WRITE], imgGray->data, imgGray->size);
        close(pipe1[WRITE]);
        wait(NULL);
    }

    // gcc main.c -o a -lm
    // gcc read.c -o read -lm
    // gcc gray.c -o gray -lm
}