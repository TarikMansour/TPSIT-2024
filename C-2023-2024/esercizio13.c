#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define DIM 64

struct BUFFER { //struct contiene i parametri del ring buffer
    int n;
    unsigned char buffer[DIM];
};
struct Parametri{ //struct contiene la quantità di numeri da inserire nell'array
    int N;
};
struct BUFFER buffer_ring; //creo ring buffer
pthread_mutex_t buffer_mutex; //creo mutex per bloccare e sbloccare l'accesso al ring buffer
void*casual(void*arg){ //thread produttore 
    struct Parametri *par = (struct Parametri*)arg;
    int size = par->N;
    int numeri[size];
    for (int i = 0; i<size; i++){
        numeri[i] = rand() % size + 1;
        pthread_mutex_lock(&buffer_mutex);
        buffer_ring.buffer[i] = numeri[i];
        pthread_mutex_unlock(&buffer_mutex);
    }
    buffer_ring.n = size;
    return NULL;
}
void *show(void*arg){ //thread consumatore
    pthread_mutex_lock(&buffer_mutex);
    for (int i = 0; i<buffer_ring.n; i++){
        printf("il numero [%d] del ring buffer è: %d \n" ,i+1, buffer_ring.buffer[i]);
    }
    pthread_mutex_unlock(&buffer_mutex);
    return NULL;
}
int main(int argc, char*argv[]){
    struct Parametri Parametri;
    pthread_t produttore, consumatore;
    Parametri.N = (atoi)(argv[1]); //quantità di numeri da inserire specificata dall'utente
    if(argc != 2){
        printf("errore di inserimento\n");
    }

    pthread_create(&produttore, NULL, casual, (void*)&Parametri); //creo le thread
    pthread_create(&consumatore, NULL, show, NULL);
    pthread_join(produttore, NULL); //aspetto la conclusione del thread produttore per poi avviare il thread consumatore
    pthread_join(consumatore, NULL);
    pthread_mutex_destroy(&buffer_mutex); //distruggo il mutex alla fine del programma
    return 0;
}