#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define NUM 10
struct Parametri{
    int var;
    int numeroThread;
};
void*thread(void*arg){
    struct Parametri *par = (struct Parametri*)arg;
    int var = 0;
    par->var = var;
    int num = par->numeroThread;
    for(int i = 0; i< 10; i++){
        num++;
        var = var + num;
    }
    par->var = var;
}

int main(){
    pthread_t search[NUM];
    struct Parametri par;
    for (int i = 0; i < NUM; i++) {
        pthread_create(&search[i], NULL, thread, (void *)&par);
    }
    for (int i = 0; i < NUM; i++) {
        pthread_join(search[i], NULL);
    }
    printf("variabile %d", par.var);
    return 0;
}