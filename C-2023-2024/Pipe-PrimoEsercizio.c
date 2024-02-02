#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 5


int main()
{
    //read e write sono sincrone ma la pipe no quindi si usa la wait cosi il padre aspetta la terminazione del figlio altrimenti
    //diventa un figlio zombie 
	int status;
    int fd[2];
    int p;
    //PIPE 
    if(pipe(fd) == -1){
        printf("errore \n");
        exit(-1);
    }
    //FORK 
    p = fork();
    if(p<0){
        printf("errore \n");
        exit(-1);
    }
    //PADRE
    if (p > 0){
        int numero;
        int buffer[BUFFER_SIZE];
        wait(&status); //SISTEMA IL PROBLEMA DI ASINCRONIZZAZIONE
        printf("\nSono il padre: il mio PID=%d, mio figlio ha PID=%d\n", getpid(), p); //IDENTIFICAZIONE
        close(fd[1]); //CHIUDE SCRITTURA
        printf("inserire numero \n");
        scanf("%d", &numero);
        if(read(fd[0], buffer, sizeof(int)*BUFFER_SIZE) == -1){ //LEGGE 
            printf("errore \n");
        }
        for(int i = 0; i< BUFFER_SIZE; i++){ //FA LA MOLTIPLICAZIONE
            printf("%d \n", buffer[i]*numero);
        }
        close(fd[0]); //CHIUDO LETTURA
    }
    //FIGLIO
    else{
        int numeri[BUFFER_SIZE];
        printf("\nSono il figlio: il mio PID=%d, mio padre ha PID=%d\n", getpid(), getppid()); //IDENTIFICAZIONE
        close(fd[0]); //CHIUDO LETTURA
        for (int i = 0; i< BUFFER_SIZE; i++){ //RIEMPE ARRAY
            printf("inserire %d numero", i+1);
            scanf("%d", &numeri[i]);
        }
        if(write(fd[1], numeri, sizeof(numeri)) == -1){ //SCRITTURA ARRAY
            printf("errore \n");
            close(fd[1]); //CHIUDO SCRITTURA
            exit(-1);

        }
        close(fd[1]); //CHIUDO SCRITTURA
    }
	return 0;
}
