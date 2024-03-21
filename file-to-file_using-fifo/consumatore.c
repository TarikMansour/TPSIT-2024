#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include<sys/wait.h>
#define BUFFER_DIM 1024

int main(int argc, char *argv[]){
    FILE *file;
    int fd;
    unsigned char buffer[BUFFER_DIM];
    int n;
    if(argc != 2){
        printf("uso %s", argv[0]);
        return 0;
    }
   
    fd = open("myfifo", O_RDONLY);
    if(fd<0){
        printf("errore\n");
        
        return 0;
    }
    file = fopen(argv[1], "wb");
    if(file == NULL){
        printf("errore apertura file %s \n", argv[1]);
      
        return 0;
    }
    while(n=read(fd,buffer,sizeof(buffer))>0){
        fwrite(buffer, 1, n, file);
    }
    close(fd);
    fclose(file);
    return 1;
}