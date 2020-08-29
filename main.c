#include "funciones.h"

int main(int argc, char** argv){

    //getOpt
	int opt;
	int nPNG = 1;
	char* archivoConv = malloc(sizeof(char) * 40);
	int umbralClass = 0;
    int umbralBin = 0;
	int bFlag = 0;

    //OPCIONES GETOPT
	while ((opt = getopt (argc, argv, "c:m:n:u:b")) != -1)
		switch (opt){
			case 'c':
			nPNG = atoi(optarg);
			break;
			case 'm':
			strcpy(archivoConv, optarg);
			break;
			case 'n':
			umbralClass = atoi(optarg);
			break;
            case 'u':
			umbralBin = atoi(optarg);
			break;
			case 'b':
			bFlag = 1;
			break;
			case '?':
			if (optopt == 'c')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (optopt == 'm')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr,
	   			"Unknown option character `\\x%x'.\n",
	   			optopt);
			return 1;
			default:
			abort ();
	} 

    //Creacion pipe
    int *pipe1 = (int*)malloc(sizeof(int) * 2);
    if(pipe(pipe1) == -1){
        printf("Error en syscall PIPE\n");
        exit(-1);
    };

    for (int i = 0; i < nPNG; i++){
        //Proceso fork crea hijo
        int pid_read;    
        if((pid_read = fork()) == -1){
            printf("Error en syscall FORK\n");
            exit(-1);
        };
        

        if(pid_read == 0){ // Proceso del hijo
            close(pipe1[WRITE]);
            dup2(pipe1[READ], STDIN_FILENO);

            char buffIImg[10];
            char buffUmbralClass[10];
            char buffUmbralBin[10];
            char buffBflag[10];
            sprintf(buffIImg, "%d", i);
            sprintf(buffUmbralClass, "%d", umbralClass);
            sprintf(buffUmbralBin, "%d", umbralBin);
            sprintf(buffBflag, "%d", bFlag);

            char *args[]={"./read", buffIImg, archivoConv, buffUmbralBin, buffUmbralClass, buffBflag, NULL};     
            execvp(args[0],args);
        }
        else{ // Padre no hace nada
        }
    }
    // 65536 max pipe size
}