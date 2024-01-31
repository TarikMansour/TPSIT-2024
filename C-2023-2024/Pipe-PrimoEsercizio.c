#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define BUFFER_SIZE 1024


int main()
{

	int p;
	int fd[2];
	int n;
	int status;
	if(pipe(fd) == -1) 
	{
		printf("\nErrore creazione pipe");
		exit(-1); 
	}

	p=fork(); 
	if (p<0)
	{
		printf("\nErrore generazione figlio");
	}

	if(p>0) 
	{
	    int buffer[5];
	    int numero;
		printf("\nSono il padre: il mio PID=%d, mio figlio ha PID=%d\n", getpid(), p);
		close(fd[1]); 
		n=read(fd[0], buffer, sizeof(buffer));
		if(n==-1)
		{
			printf("\nErrore nella lettura della pipe");
			close(fd[0]); 
			exit(-1);
		}
		else 
		{
			printf("inserire numero \n");
			scanf("%d", &numero);
			for(int i = 0; i<5; i++){
			    buffer[i] *= numero;
			    printf("%d", buffer[i]);
			}
			close(fd[0]);
		}
	
		wait(&status);
	}
	else 
	{
		int numeri[5];
	
		printf("\nSono il figlio: il mio PID=%d, mio padre ha PID=%d\n", getpid(), getppid());
		close(fd[0]);
		printf("Inserire numeri\n");
		for(int i = 0; i<5; i++){
		    scanf("%d", &numeri[i]);
		}
		if( write(fd[1], numeri,  sizeof(numeri)) == -1)
		{
			printf("\nErrore di scrittura nella pipe");
			close(fd[1]);
			exit(-1);
		}
		close(fd[1]);
		
	}

	return 0;
}