
#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include<sys/wait.h>
#define BUFFER_DIM 1024
#define PROGRAM "./esecuzione"

int spawn(char program[], char*argument[]){
    int p;
    p = fork();
    if (p == -1){
        return -1;
    }
    if (p >0){
        return 0;
    }
    execv(program, argument); //equivalente a ("./esecuzione,"testo2.txt", NULL)
                                /*execl("percorso", "nome del file", "stringa di ingresso", "numero di ingresso");
                                char *mioarray[];
                                mioarray[0] = "finestra";
                                mioarray[1] = "ciaociao";
                                mioarray[2] = "4";
                                mioarray[3] = NULL;
                                execv("percorso", mioarray); */
    abort();
}
int main(int argc, char *argv[]){
    FILE *file;
    int fd;
    unsigned char buffer[BUFFER_DIM];
    int n;
    char *arg[3]; 
    if(argc != 3){
        printf("uso %s", argv[0]);
        return 0;
    }

    arg[0] = (char*)malloc(strlen(PROGRAM)+1); 
    strcpy(arg[0], PROGRAM); //presente il nome del programma
    arg[1] = (char*)malloc(strlen(argv[2])+1); 
    strcpy(arg[1], argv[2]); //terzo parametro di argv: file di destinazione
    arg[2] = NULL; 
    if(spawn(PROGRAM,arg) <0){
        printf("errore creazione processo \n");
        free(arg[0]);
        free(arg[1]);
        return 0;
    }
    fd = open("myfifo", O_WRONLY);
    if(fd<0){
        printf("errore\n");
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    file = fopen(argv[1], "rb");
    if(file == NULL){
        printf("errore apertura file %s \n", argv[1]);
        free(arg[0]);
        free(arg[1]);
        return 0;
    }

    while(n=fread(buffer,1,sizeof(buffer),file)>0){
        write(fd, buffer, n);
    }
    fclose(file);
    close(fd);
    free(arg[0]);
    free(arg[1]);
    return 1;
}

