#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
struct studente{
    char nome[20];
    char cognome[20];
    float media;
    char classe[4];
};
void* inserimento(void *arg){
    struct studente* student = (struct studente*)arg;
    printf("inserire nome \n");
    scanf("%s", student ->nome);
    printf("inserire cognome \n");
    scanf("%s", student ->cognome);
    printf("inserire media \n");
    scanf("%f", &student ->media);
    printf("inserire classe \n");
    scanf("%s", student ->classe);
    pthread_exit(NULL);
}
//Versione senza puntatore usando la struttura
/* typedef struct{
    char nome[20];
    char cognome[20];
    float media;
    char classe[4];
}studente;
void* inserimento(void *arg){
    studente student = *(studente*)arg;
    printf("inserire nome \n");
    scanf("%s", student.nome);
    printf("inserire cognome \n");
    scanf("%s", student.cognome);
    printf("inserire media \n");
    scanf("%f", &student.media);
    printf("inserire classe \n");
    scanf("%s", student.classe);
    pthread_exit(NULL);
} */
void* stampa(void *arg){
    struct studente* student = (struct studente*)arg;
    printf("nome: %s \n", student ->nome);
    printf("cognome: %s \n", student ->cognome);
    printf("media: %f \n", student ->media);
    printf("classe: %s \n", student ->classe);
    pthread_exit(NULL);
}
void* salva(void *arg){
    struct studente* student = (struct studente*)arg;
    FILE *file = fopen("log.txt", "w");
    if (file == NULL) {
        pthread_exit(NULL);
    }
    fprintf(file, "nome: %s \n", student ->nome);
    fprintf(file, "cognome: %s \n", student ->cognome);
    fprintf(file, "media: %f \n", student ->media);
    fprintf(file, "classe: %s \n", student ->classe);
    fclose(file);
    pthread_exit(NULL);
}
int main(){
    struct studente student;
    pthread_t threadInserimento, threadStampa, threadSalva;
    pthread_create(&threadInserimento, NULL, &inserimento,(void*)&student);
    pthread_join(threadInserimento, NULL);
    pthread_create(&threadStampa, NULL, &stampa, (void*)&student);
    pthread_join(threadStampa, NULL);
    pthread_create(&threadSalva, NULL, &salva, (void*)&student);
    pthread_join(threadSalva, NULL);
}
