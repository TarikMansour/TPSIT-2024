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
	if((fifo = open("myfifo", O_WRONLY))==-1){
        printf("errore apertura fifo\n");
        exit(-1);
    }
    libro books[MAX];
    for(int i = 0; i<MAX; i++){
        printf("inserire autore \n");
        scanf("%s", books[i].autore);
        printf("inserire titolo \n");
        scanf("%s", books[i].titolo);
        printf("inserire prezzo\n");
        scanf("%f", &books[i].prezzo);
      
    }
    for(int i = 0; i<MAX; i++){
       if(write(fifo,&books[i],sizeof(libro)*MAX)==-1){
        printf("errore scrittura fifo \n");
        close(fifo);
    };
    }
      
    close(fifo);
    return 0;
}