#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
struct Parametri{
    int indice;
    int ultimo;
    int numero;
};
int arr[10] = {1,2,3,4,5,6,7,8,9,10};
void* ricerca(void* arg){
    struct Parametri *par = (struct Parametri*)arg;
    for (int i =par->indice; i<=par->ultimo;i++){
        if (arr[i] == par->numero){
            printf("prima meta dell'array: \n");
            printf("numero trovato nella posizione %d dell'array \n", i+1);
        }
    }
    pthread_exit(NULL);
}

int main(){
    struct Parametri par_1, par_2;
    par_1.indice = 0;
    par_1.ultimo = 5;
    par_1.numero = 8;
    par_2.indice = 5;
    par_2.ultimo = 10;
    par_2.numero = 8;
    pthread_t threadRicerca1, threadRicerca2;
    pthread_create(&threadRicerca1, NULL, &ricerca,&par_1);
    pthread_create(&threadRicerca2, NULL, &ricerca,&par_2);
    pthread_join(threadRicerca1, NULL);
    pthread_join(threadRicerca2, NULL);
    return 0;
}
