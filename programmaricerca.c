#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
int arr[10] = {1,2,3,4,5,6,7,8,9,10};
void* ricerca1(void* arg){
    int* array = (int*)arg;
    for (int i =0; i<5;i++){
        if (array[i] == 8){
            printf("prima meta dell'array: \n");
            printf("numero trovato nella posizione %d dell'array \n", i+1);
        }
    }
    pthread_exit(NULL);
}
void* ricerca2(void* arg){
    int* array = (int*)arg;
    for (int i =5; i<10;i++){
        if (array[i] == 8){
            printf("seconda meta dell'array: \n");
            printf("numero trovato nella  posizione %d dell'array \n", i+1);
        }
    }
    pthread_exit(NULL);
}
int main(){
    pthread_t threadRicerca1, threadRicerca2;
    pthread_create(&threadRicerca1, NULL, &ricerca1,(void*)arr);
    pthread_create(&threadRicerca2, NULL, &ricerca2, (void*)arr);
    pthread_join(threadRicerca1, NULL);
    pthread_join(threadRicerca2, NULL);
    return 0;
}