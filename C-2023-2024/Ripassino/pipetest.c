#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h> //libreria errore
#include<fcntl.h> //libreria FIFO
#define MAX 3
typedef struct{
    char nome[50];
    int eta;
}persona;
int main(){
    int p;
    int status;
    int fd[2];
    if(pipe(fd)==-1){
        printf("errore creazione pipe \n");
    }
    p = fork();
    if (p>0){
        persona people[MAX];
        printf("sono il padre mio PID: %d, PID del mio figlio %d \n", getpid(), p);
        close(fd[0]);
        for(int i = 0; i<MAX; i++){
            printf("inserire %d nome \n", i+1);
            scanf("%s", people[i].nome);
             printf("inserire %d eta \n", i+1);
            scanf("%d", &people[i].eta);
        }
        for(int i = 0; i<MAX; i++){
            if(write(fd[1], people, sizeof(persona)*MAX)==-1){
                printf("errore scrittura \n");
                close(fd[1]);
            };
        }
        close(fd[1]);
        wait(&status);
    }
    else{
        persona people[MAX];
        printf("sono il figlio mio PID: %d, PID del mio padre %d \n", getpid(), getppid());
        close(fd[1]);
        int n = read(fd[0], people, sizeof(persona)*MAX);
        if(n == -1){
            printf("errore lettura \n");
            close(fd[0]);
        }
         for(int i = 0; i<MAX; i++){
            printf("nome: %s", people[i].nome);
            printf("eta: %d", people[i].eta);
        }
        close(fd[0]);
    }
    return 0;
}