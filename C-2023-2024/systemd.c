#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    
    //I PROCESSI HANNO MEMORIA INDIPENDENTE
    /*quanto il padre termina il figlio diventa orfano (zombie) 
    e viene assegnato a lui, dalla cpu, un padre fitizio (SYSTEMD)*/
    //ps aux | grep_'PID' --> verificare processo
    //il p del padre è uguale al PID del figlio
    //quando il figlio si sveglia, passa dal padre (6879) a systemd (1656)
    int p = fork(); //padre genera un figlio (clone del padre)
    if(p != 0){ //padre
        printf("io sono il padre P=%d, PID= %d MIO PADRE: %d\n", p, getpid(), getppid());
    }
    else { //figlio
    printf("io sono il figlio P=%d, PID = %d, MIO PADRE: %d\n", p, getpid(), getppid());
    sleep(5);
    }
    if(p == 0){
        printf("io sono il figlio P=%d, PID = %d, MIO PADRE: %d\n", p, getpid(), getppid());
    }
    return 0;
}
