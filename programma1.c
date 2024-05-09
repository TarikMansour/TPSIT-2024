#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define SIZE 1000
#define NUM 4

int arr[SIZE];

struct Parametri {
    int indice;
    int ultimo;
    int numero;
};

void riempie(int arr[SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 501;
    } 
}

void* ricerca(void* arg) {
    struct Parametri *par = (struct Parametri*)arg;
    for (int i = par->indice; i < par->ultimo; i++) { 
        if (arr[i] == par->numero) {
            printf("Numero trovato nella posizione %d dell'array\n", i+1);
        }
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));
    riempie(arr);
    int pid;
    pthread_t search[NUM];
    struct Parametri par[NUM];
    for (int i = 0; i < NUM; i++) {
        par[i].indice = (SIZE / NUM) * i;
        par[i].ultimo = (SIZE / NUM) * (i + 1);
        par[i].numero = 45;
    }
    for (int i = 0; i < NUM; i++) {
        pthread_create(&search[i], NULL, ricerca, (void *)&par[i]);
    }
    for (int i = 0; i < NUM; i++) {
        pthread_join(search[i], NULL);
    }
    return 0;
}