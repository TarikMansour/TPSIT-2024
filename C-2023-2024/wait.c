#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int p;
int status;
int pid;
//Macro = funzione
int main(){
    
    p = fork(); 
    if(p != 0){ //padre
        printf("io sono il padre P=%d, PID= %d MIO PADRE: %d\n", p, getpid(), getppid());
        printf("aspetto la terminazione del mio figlio %d\n", wait(&status)); //restituisce la PID del figlio che ha terminato tramite risultato della wait a quale passo l'indirizzo di status 
        printf("il codice di terminazione del mio figlio risulta WEXISTATUS(status) = %d \n", WEXITSTATUS(status));
         //se PID < 0 il padre non ha piu figli vivi
        printf("aspetto la terminazione del mio figlio %d\n", wait(&status)); //restituisce la PID del figlio che ha terminato tramite risultato della wait a quale passo l'indirizzo di status 

    
    }
    else { //figlio
   printf("io sono il figlio P=%d, PID = %d, MIO PADRE: %d\n", p, getpid(), getppid());
   pid = getpid();
    exit(25);
    }
    //qui p = pid del figlio
   printf("io sono il padre e vedo ancora la PID del mio figlio %d anche se è terminato \n", p);
}