#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#define MAX 3
#define BUFFER_SIZE 1024
/*Creare un programma C dove il padre passa due variabili di tipo libro (STRUCT: titolo,autore e prezzo) al processo figlio che stampa i dati così ricevuti.*/
struct libro {
    char autore[50];
    char titolo[50];
    float prezzo;
};


int main()
{
	//dichiarazione var
	int p;
	int fd[2];
	//char buffer[BUFFER_SIZE];
	int n;
	int status;
    
	if(pipe(fd) == -1) //N.B. La pipe e' SINCRONA !!!
	{
		printf("\nErrore creazione pipe");
		exit(-1); //esco dal prg
	}

	p=fork(); //padre genera figlio
	if (p<0)
	{
		printf("\nErrore generazione figlio");
	}

	if(p>0) //padre
	{
        struct libro libri[MAX];
		printf("\nSono il padre: il mio PID=%d, mio figlio ha PID=%d\n", getpid(), p);
		close(fd[0]); //padre chiude pipe in lettura (output pipe)
		
                          for(int i = 0; i<MAX; i++){
        printf("Inserisci il titolo del %d libro : ", i + 1);
        scanf("%s", libri[i].titolo);
        
        printf("Inserisci il nome del %d libro: ", i + 1);
        scanf("%s", libri[i].autore);
        
        printf("Inserisci il prezzo del %d libro: ", i + 1);
        scanf("%f", &libri[i].prezzo);
        }
        if(write(fd[1], libri, sizeof(struct libro) * MAX) == -1) //La chiamata alla funzione di scrittura dovrebbe utilizzare la dimensione della struttura moltiplicata per il numero di elementi da scrivere.
		{
			printf("\nErrore di scrittura nella pipe");
			close(fd[1]); //bisogna sempre chiudere il fd
			exit(-1);
		}
		close(fd[1]);
		wait(&status); /*padre attende la terminazione figlio 
		                 altrimenti rimarrebbe un figlio zombie*/
    
                        
    }
	
	else //figlio
	{
		struct libro buffer[MAX];

		printf("\nSono il figlio: il mio PID=%d, mio padre ha PID=%d\n", getpid(), getppid());
		close(fd[1]);
		n=read(fd[0], buffer, sizeof(struct libro) * MAX); //La chiamata alla funzione di lettura dovrebbe utilizzare la dimensione della struttura moltiplicata per il numero di elementi da scrivere.
		if(n==-1)
		{
			printf("\nErrore nella lettura della pipe");
			close(fd[0]); //bisogna sempre chiudere il fd
			exit(-1);
		}
		for(int i = 0; i<MAX; i++){ 
            printf("Libro %d:\n", i + 1);
            printf("Titolo: %s\n", buffer[i].titolo);
            printf("Autore: %s\n", buffer[i].autore);
            printf("Prezzo: %.2f\n", buffer[i].prezzo);
            printf("\n");
        }
	}
}