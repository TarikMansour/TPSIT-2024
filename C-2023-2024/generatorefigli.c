#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
    //PADRE CHE GENERA DUE FIGLI
    int p = getpid();
    printf("io sono il padre P=%d, MIO PADRE: %d\n", p, getppid()); 
    for(int i = 0; i<3; i++){
        if(p!=0){
            p=fork();
            if(p==0){
                printf("io sono il figlio %d  P=%d, PID = %d, MIO PADRE: %d\n", i+1, p, getpid(), getppid());
            }
        }
    }
    //SE FACCIO UN'ALTRO FORK NASCONO ALTRI 3 FIGLI (1 PER PADRE , 1 PER FIGLIO 1 E 1 PER FIGLIO 2)
   
    return 0;
}
