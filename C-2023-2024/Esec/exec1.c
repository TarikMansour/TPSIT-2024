#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main (int argc, char *argv[]){
    printf("processo in esecuzione PID %d \n", getpid());
    printf("chiamo un eseguibile esterno \n");
    execl("./chama", "all my homies are black as night", "white cocaine", NULL);
    //perche il codice chiamato dovrebbe sostituire al codice del chiamante  
    printf("chiamata fallita");
    /* la fork crea una copia del processo padre con la sua propria struttura
    e PID mentre la esec crea un processo che sostituisce il processo chiamante e ha il suo stesso PID */
    return 0;
}