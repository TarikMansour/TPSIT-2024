#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_SLICES 16
#define SLICE_DIM 64

typedef struct
{
    unsigned char bufferInStruct[SLICE_DIM];
    int n;
}bufferStruct;

bufferStruct rBuffer[NUM_SLICES]; //zona critica
pthread_t writeTh, readTh;
FILE *fr, *fw;
pthread_mutex_t mutex;
int read_index=0;
int write_index=0;
int N_block = 0; //zona critica
int end = 0;
pthread_cond_t not_full, not_empty;
void* readFile(void* arg){
    int n; 
    while(!feof(fr)){ //loop fino alla fine del file
        pthread_mutex_lock(&mutex); //lock sezione critica
        if(N_block >= NUM_SLICES){ //se il buffer è pieno
            pthread_cond_wait(&not_full,&mutex); //aspetto che il buffer non sia pieno
            n = fread(rBuffer[write_index].bufferInStruct,1,SLICE_DIM,(FILE*)arg); //funzione lettura
            if(n>0){ //se sono riuscito a leggere continuo
                rBuffer[write_index].n  = n; //aggiorno il numero di byte letti
                write_index = (write_index+1)%NUM_SLICES; //increment + loop per spostarmi alla prossima slice
                N_block++; //num di blocchi aumenta quando leggo
            }
        }
    }
    pthread_cond_signal(&not_empty); //segno che il buffer non è vuoto
    pthread_mutex_unlock(&mutex); //sblocco sezione critica
    end = 1; //segno la fine del file
}

void* writeFile(void* arg){
    while(1){
        if(end && N_block == 0) //se il buffer è vuoto ed è la fine del file esco dal loop
        break;
        pthread_mutex_lock(&mutex); //block zona critica
        if(N_block >0){ //se il buffer non è vuoto
            fwrite(rBuffer[read_index + 1].n, 1, rBuffer[read_index + 1].n,fw); //funzione scrittura
            read_index = (read_index+1)%NUM_SLICES; //increment + loop per spostarmi alla prossima slice
            N_block--; //num di blocchi diminuisce quando scrivo
        }
        else{
            pthread_cond_wait(&not_empty, &mutex); //aspetto che il buffer non sia vuoto
        }
        pthread_cond_signal(&not_full); //segno che il buffer non è pieno
        pthread_mutex_unlock(&mutex); //sblocco sezione critica
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&mutex, NULL); 
    pthread_cond_init(&not_full, NULL); 
    pthread_cond_init(&not_empty, NULL);
    fr = fopen("input.txt", "rb"); 
    fw = fopen("output.txt", "wb"); 
    pthread_create(&readTh,NULL, &readFile,fr);
    pthread_create(&writeTh,NULL, &writeFile,fw);
    pthread_join(writeTh,NULL);
    pthread_join(readTh,NULL);
    fclose(fr); 
    fclose(fw); 
    pthread_mutex_destroy(&mutex); 
    pthread_cond_destroy(&not_full); 
    pthread_cond_destroy(&not_empty); 
    return 0;
}