#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define SIZE 64
#define DIM 1024
struct BUFFER{
    unsigned char buffer[DIM];
    int num;
};
int n = 0;
int end;
int N_block = 0; //variabile condivisa aumenta quando leggo diminuisce quando scrivo
BUFFER ring_buffer[SIZE];
int read_index = 0;
int write_index = 0;
void *lettura(void *arg){
FILE *origine = (FILE*)arg;
 while(N_block >= SIZE){
    n=fread(ring_buffer[write_index].buffer, 1, DIM, origine);
    if(n>0){
        ring_buffer[write_index].num = n;
        write_index = (write_index+1)%SIZE;
        N_block++;
    }
 }
 end = feof(origine);
}
void *scrittura(void *arg){
 FILE *destinazione = (FILE*)arg;
    while(!end || N_block > 0){
   
    if(N_block>0){
    fwrite(ring_buffer[read_index].buffer, 1, ring_buffer[read_index].num, destinazione);
    read_index = (read_index+1) % SIZE;
    N_block--;
 }
}
 }
 
int main (int argc, char* argv[]){
    FILE *origine, *destinazione;
    pthread_t leggi, scrivi;
    if(argc != 3){
        printf("errore \n");
    }
    origine = fopen(argv[1],"rb");
    if(origine == NULL){
        printf("errore apertura file orig\n");
    }
    destinazione = fopen(argv[2], "wb");
    if(destinazione == NULL){
        printf("errore apertura file dest\n");
    }
    pthread_create(&leggi,NULL,lettura, (void*)origine);
    pthread_create(&scrivi,NULL,scrittura,(void*)destinazione);
    pthread_join(leggi, NULL);
    pthread_join(scrivi, NULL);
    fclose(origine);
    fclose(destinazione);
    return 0;
}