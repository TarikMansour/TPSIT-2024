#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//i processi vengono gestiti dal kernel
//p vale sempre il PID del processo figlio
/* i processi non sono sincronizzati: il figlio e padre contano insieme, 
il figlio termina il suo conteggio e il padre continua fino ad arrivare alla fine */
/*quanto il padre finisce il conteggio per primo il figlio diventa orfano (zombie) 
e viene assegnato a lui, dalla cpu, un padre fitizio */
int main()
{
    //qui nasce il padre con il main
    int p = fork(); 
    int contapadre, contafiglio;
    if(p < 0) //errore p = -1
    {
        printf("il figlo non è nato \n");
        exit(1);
    }
    else if (p > 0) //p del padre =  PID del figlio (> 0) , p del figlio = 0
    {
        printf("io sono il padre. il mio PID = %d, il PID del mio padre = %d, il PID del mio figlio = %d \n", getpid(), getppid(), p);
        for(contapadre = 0; contapadre <=50; contapadre++){
            printf("conto del padre: %d \n", contapadre);
        }
    }
    else {
        printf("io sono il figlio. il mio PID = %d, il PID del mio padre = %d, il PID del mio figlio = %d \n", getpid(), getppid(), p);
        for(contafiglio = 0; contafiglio <=55; contafiglio++){
            printf("conto del figlio: %d \n", contafiglio);
        }
    }
    
    return 0;
}
