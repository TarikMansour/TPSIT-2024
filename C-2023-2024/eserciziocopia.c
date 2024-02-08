#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define DIM 1024

int p;

int main(int argc, char* argv[])
{
    FILE *file; //puntatore file
    unsigned char buffer[DIM]; //buffer di apoggio usato per lettura e scrittura
    int fd[2]; //canale di communicazione per la pipe
    int status, n; //n -> contiene valore della fread che serve per sapere esattamente la dimensione, status -> variabile usata per la wait
    int cont = 0; //conta lettere
    char c; //contiene la lettera ricercata

    if (argc != 4) //controllo inserimento dei 2 file e una lettera
    {
        printf("Inserire correttamente i file di origine e destinazione\n");
        exit(-1);
    }

    if (pipe(fd) < 0) //controllo pipe
    {
        printf("Errore creazione pipe\n");
        exit(-1);
    }

    p = fork(); //padre crea figlio

    if (p < 0) //se p<0 errore -> chiudo i due end di communicazione
    {
        printf("Errore creazione figlio\n");
        close(fd[0]);
        close(fd[1]);
        exit(-1);
    }
    if (p > 0) //padre
    {
        p = fork(); //crea un secondo figlio dentro il proprio processo padre

        if (p < 0) //se p<0 errore -> chiudo i due end di communicazione
        {
            printf("Errore creazione figlio\n");
            close(fd[0]);
            close(fd[1]);
            exit(-1);
        }
        if (p == 0) //figlio apre il file origine e non usa la pipe
        {
            close(fd[0]);
            close(fd[1]);
            file = fopen(argv[1], "r");
            if (file == NULL)
            {
                printf("Errore nell'apertura del file\n");
                close(fd[1]);
                wait(&status);
                exit(-1);
            }
            else
            {
                //verifica di quante volte appare il carattere
                do 
                {
                    c = fgetc(file);
                    if (argv[3][0] == c)
                    {
                        cont++;
                    }
                } while (c != EOF);
                printf("Il carattere [%c] è presente %d volte nel file\n", argv[3][0], cont);
                fclose(file);
            }
        }
        //padre apre il file di testo e scrive nella pipe 
        close(fd[0]); //chiudo lettura
        file = fopen(argv[1], "r"); //apro file origine
        if (file == NULL)
        {
            printf("Errore nell'apertura del file\n");
            close(fd[1]);
            wait(&status);
            exit(-1);
        }
        else
        {
            while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0) //mentre n > 0 leggo i contenuti dal file origine facendo uso di un buffer di apoggio 
            {
                write(fd[1], buffer, n); //scrivo nel canale di communicazione facendo uso del buffer usando n perche solo n conosce la lunghezza del file
            }
            fclose(file); //chiudo file origine
            close(fd[1]); //chiudo scrittura
            wait(&status); //aspetto il processo 
        }
    }
    else //figlio che copia il file leggendo dalla pipe
    {
        close(fd[1]); //chiudo scrittura

        file = fopen(argv[2], "w"); //creo file destinazione dove verra copiato i contenuti di origine

        if (file == NULL)
        {
            printf("Errore nell'apertura del file\n");
            close(fd[0]);
            exit(-1);
        }
        else
        {
            while ((n = read(fd[0], buffer, sizeof(buffer))) > 0) //qui uso n per leggere dalla pipe utilizzando lo stesso principio
            {
                fwrite(buffer, 1, n, file); //dopo che leggo copio i contenuti del buffer di apoggio usando sempre n come parametro di lunghezza 
            }
            fclose(file); //chiudo file destinazione
            close(fd[0]); //chiudo lettura
            wait(&status); //aspetto processo
        }
    }
    return 0;
}