#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define SIZE 1024
unsigned char buffer[SIZE];
int n = 0;
int end;
void *lettura(void *arg){
FILE *origine = (FILE*)arg;
 while(!feof(origine)){
    n=fread(buffer, 1, SIZE, origine);
 }
 end = feof(origine);
}
void *scrittura(void *arg){
 FILE *destinazione = (FILE*)arg;
    while(!end){
   
    if(n>0){
    fwrite(buffer, 1, n, destinazione);
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