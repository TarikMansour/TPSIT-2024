#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//il p di un processo è come il suo codice fiscale (process id)
//tutti i processi hanno un padre tranne il processo iniziale (init) che viene lanciato dal kernel per avviare la macchina 
//il padre del padre è il terminale
int p; /* permette di gestire il padre e figlio p nel padre = p figlio p nel figlio = 0*/
int main()
{
    //il p del padre è uguale al PID del figlio
    p = fork(); //padre genera un figlio (clone del padre)
    if(p != 0){ //padre
        printf("io sono il padre P=%d, PID= %d MIO PADRE: %d\n", p, getpid(), getppid());
    }
    else { //figlio
   printf("io sono il figlio P=%d, PID = %d, MIO PADRE: %d\n", p, getpid(), getppid());
    }
    return 0;
}