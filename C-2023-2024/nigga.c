#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//POSIX
void* stampaBuongiorno(void* par){
    printf("buongiorno\n");
}
void* stampaBuonasera(void* par){
    printf("buonasera\n");
}
void* stampaBuonanotte(void* par){
    printf("buonanotte\n");
}
int main(){
    pthread_t threadGiorno, threadSera, threadNotte;
    printf("ciao\n");
    
    pthread_create(&threadGiorno, NULL, &stampaBuongiorno,NULL);
    pthread_create(&threadSera, NULL, &stampaBuonasera, NULL);
    pthread_create(&threadNotte, NULL, &stampaBuonanotte, NULL);
    pthread_join(threadGiorno, NULL);
    pthread_join(threadSera, NULL);
    pthread_join(threadNotte, NULL);
}