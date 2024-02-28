#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h> //libreria errore
#include<fcntl.h> //libreria FIFO
#define MAX 3
int fifo;
typedef struct {
    char autore[50];
    char titolo[50];
    float prezzo;
}libro;


int main()
{
	if(fifo = open("myfifo", O_RDONLY)==-1){
        printf("errore apertura fifo\n");
        exit(-1);
    }
    libro books[MAX];
    for(int i = 0; i<MAX; i++){
         if(read(fifo,&books[i],sizeof(libro)*MAX)==-1){
        printf("errore lettura fifo \n");
        close(fifo);
        }
    }
    for(int i = 0; i<MAX; i++){
       
        printf("libro %d\n:", i+1);
        printf("%s\n", books[i].autore);
        printf("%s\n", books[i].titolo);
        printf("%.2f\n", books[i].prezzo);
    }
    close(fifo);
    return 0;
}