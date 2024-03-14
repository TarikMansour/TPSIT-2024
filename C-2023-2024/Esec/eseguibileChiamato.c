#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main (int argc, char *argv[]){
    printf("eseguibile esterno PID %d \n", getpid());
    printf("%s, %s \n", argv[0], argv[1]);
    //chiamo processo di linux (ls) sulla cartella bin 
    execl("/bin/ls", "-l", NULL);
    return 0;
}