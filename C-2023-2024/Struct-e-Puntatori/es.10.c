#include <stdio.h>
#include <stdlib.h>
#define MAX 3
//ESERCIZIO USANDO ARRAY DI PUNTATORI DI STRUCT, TYPEDEF, MALLOC, FREE E STAMPA DEGLI INDIRIZZI
//struct creo nuovo tipo di variabile (typedef)
typedef struct {
    char cognome[50];
    char nome[50];
    float media;
} student_t;

void inserimento (student_t *studenti[]){
 //inserimento dati
 for(int i = 0; i<MAX; i++){
        printf("Inserisci il cognome del %d studente : ", i + 1);
        scanf("%s", studenti[i]->cognome);
        
        printf("Inserisci il nome del %d studente: ", i + 1);
        scanf("%s", studenti[i]->nome);
        
        printf("Inserisci la media del %d studente: ", i + 1);
        scanf("%f", &studenti[i]->media);
    }
}
void visualizza (student_t *studenti[]){
 //contenuto array puntatori
    for (int i = 0; i < MAX; i++) {
        printf("Dati dello studente %d:\n", i + 1);
        printf("Cognome: %s\n", studenti[i]->cognome);
        printf("Nome: %s\n", studenti[i]->nome);
        printf("Media: %f\n", studenti[i]->media); //uso float 
    }  
}
void visualizzaInd (student_t *studenti[]){
   //stampa indirizzi di memoria dell'array usando %p
    printf("Indirizzi di memoria degli studenti:\n");
    for (int i = 0; i < MAX; i++) {
        printf("%p\n", studenti[i]);
    }
}
int main() {
    // dichiarazione di un array di puntatori student_t
    struct student_t* studenti[MAX];
    
    for (int i = 0; i < MAX; i++) {
        // allocazione della memoria per la struct student_t
        studenti[i] = (student_t*)malloc(sizeof(student_t)); //funzione malloc (memory 	allocation) assegna un blocco della memoria della dimensione (usando sizeof) della struct
    }
    inserimento(studenti);
    visualizza(studenti);
    visualizzaInd(studenti); 
        
    //liberazione della memoria per ogni elemento dell'array 
    for (int i = 0; i < MAX; i++) {
        free(studenti[i]);
    }
    
    return 0;

}
