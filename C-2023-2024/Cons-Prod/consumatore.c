#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h> //libreria errore
#include<fcntl.h> //libreria FIFO
#define SIZE 5
int fifo;
int main(){
//processo consumatore:
    int numeri[SIZE];
    int somma = 0;
    fifo = open("sum", O_RDONLY);
    /* if(read(fifo, numeri, sizeof(numeri)) == -1){
        printf("errore \n");
        close(fifo);
        exit(-1);
    } */
    
    for(int i = 0; i<SIZE; i++){
        somma += numeri[i];
    }
    close(fifo);
    printf("%d", somma);
    return 0;
}