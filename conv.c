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

    // MASK
    JPG* imgMask = (JPG*)malloc(sizeof(JPG));
    imgMask->height = img->height;
    imgMask->width = img->width;
    imgMask->channels = img->channels == 4 ? 2 :1;
    imgMask->size = imgMask->height * imgMask->width * imgMask->channels;
    imgMask->data = (char*)malloc(sizeof(char) * imgMask->size);

    filtro(img, imgMask, argv[6]);



    // stbi_write_png("testasd.jpg", imgMask->width, imgMask->height, imgMask->channels, imgMask->data, imgMask->width * imgMask->channels);

    //Proceso fork crea hijo
    int pid_bin;    
    if((pid_bin = fork()) == -1){
        printf("Error en syscall FORK\n");
        exit(-1);
    };

    if(pid_bin == 0){ // Proceso del hijo
        close(pipe1[WRITE]);
        dup2(pipe1[READ], STDIN_FILENO);

        // for (int i = 0; i < img->size; i++){printf("%d",img->data[i]);}

        char buffWidth[10];
        char buffHeight[10];
        char buffChannels[10];
        char buffSize[20];
        sprintf(buffWidth, "%d", imgMask->width);
        sprintf(buffHeight, "%d", imgMask->height);
        sprintf(buffChannels, "%d", imgMask->channels);
        sprintf(buffSize, "%d", imgMask->size);


        char *args[]={"./bin", buffWidth, buffHeight, buffChannels, buffSize, argv[5], argv[6], argv[7], argv[8], argv[9], NULL};     
        execvp(args[0],args);
    }
    else{ // Padre
        close(pipe1[READ]);
        write(pipe1[WRITE], imgMask->data, imgMask->size);
        close(pipe1[WRITE]);
    }
}