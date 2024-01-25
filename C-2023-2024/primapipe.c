#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
int main(){
//padre manda un messaggio al figlio
    int fd[2];
    char buffer[BUFFER_SIZE];
    //pipe sincronizza i due processi
    if(pipe(fd) == -1){
        printf("errore \n");
        exit(-1);
    }//viene fatta prima della fork (0 se funziona -1 sennò)

    int p = fork();
    
    if(p<0){
        printf("errore");
    }else if(p>0){
        printf("sono il padre: PID: %d PID del figlo %d \n", getpid(), p);
        close(fd[0]); //chiudo pipe di lettura
        const char* messaggio = "buona fortuna"; //puntatore che punta all'indirizzo dove si trova il messaggio
        if(write(fd[1], messaggio, strlen(messaggio)) == -1){ //scrittura + cosa scrivere + lunghezza del messaggio
            printf("errore scrittura nella pipe \n");
            close(fd[1]); //chiudo pipe di scrittura
            exit(-1);
        }
        close(fd[1]); //chiudo pipe di scrittura
        wait(); //padre attende il figlio
    }
    else{
          printf("sono il figlio: PID: %d PID del padre %d \n", getpid(), getppid());
          close(fd[1]); //chiudo pipe di scrittura
          int n = read(fd[0], buffer, BUFFER_SIZE);
          if(n ==-1){
            printf("errore \n");
            close(fd[0]);
            exit(-1);
          }
          else{
            buffer[n] = '\0'; //carattere terminatore
            printf("messaggio letto: %s ", buffer);
            close(fd[0]);

          }
    }
    return 0;
}