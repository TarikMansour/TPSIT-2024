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
    //processo produttore:
    //fifo ---> creare dal terminal
    //mkfifo("sum", 0777);
    //generazione numeri
    int random[SIZE];
    for(int i = 0; i<SIZE; i++){
        random[i] = rand() % 100;
        printf("%d \n", random[i]);
    }
    //apertura fifo
    fifo = open("sum", O_WRONLY);
    if(fifo == -1){
        printf("errore \n");
        close(fifo);
        exit(-1);
    }
    //scrittura e poi chiusura fifo
    write(fifo, random, sizeof(random));
    printf("write\n");
    close(fifo);
    

    return 0;
}