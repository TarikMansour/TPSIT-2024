#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define DIM 1024
int main() {
    char arr1[DIM];
    char arr2[DIM];
    int fd;
    int p;
    p = fork();
    if (p == -1){
        return -1;
    }
    if (p >0){
        fd = open("fifone", O_WRONLY);
        while(1){
            fgets(arr2,DIM,stdin);
            write(fd, arr2, strlen(arr2)+1);
        }
        close(fd);
    }
    else{
        fd = open("fifone2", O_RDONLY);
        while(strcmp(arr1,"HALT\n")){
           read(fd, arr1, sizeof(arr1));
           printf("chat2 : %s", arr1);
        }
        close(fd);
    }
    return 0;
}
