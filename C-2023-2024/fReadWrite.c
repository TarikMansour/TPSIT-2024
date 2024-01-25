#include <stdio.h>
#include <stdlib.h>
#define BUFFER_DIM 1024
//PROGRAMMA CHE COPIA CONTENUTI DI UN FILE DENTRO UN'ALTRO TRAMITE UN BUFFER
int main (int argc, char *argv[]){
    FILE *origine, *destinazione;
    int n;
    unsigned char buffer[BUFFER_DIM]; 
    if(argc < 3){ //CONTROLLO 
        printf("inserire corretamente i parametri \n");
        exit(1);
    }
    origine = fopen(argv[1], "r"); //SI APRE IL FILE DATO COME ARG. NELLA COMPILAZIONE
    if(origine == NULL){ //SE IL FILE NON ESISTE CI DA ERRORE
         printf("errore apertura file origine \n");
        exit(1);
    }
    destinazione = fopen(argv[2], "w"); //CREA O APRE FILE DESTINAZIONE
    if(destinazione == NULL){ //CONTROLLLO ERRORE
         printf("errore apertura file destinazione \n");
        exit(1);
    }
    while (!feof(origine)){ //WHILE FINCHE NON ARRIVE ALLA FINE DEL FILE ORIGINE
        n=fread(buffer, 1, BUFFER_DIM, origine); //LEGGO UN BYTE ALLA VOLTA DA ORIGINE TRAMITE BUFFER 
        if(n>0){ //SE CI RITORNA VALORE MAGGIORE DI 0 SIGNIFICA CHE STA ANCORA LEGGENDO 
            fwrite(buffer, 1, n, destinazione); //SCRIVO UN BYTE ALLA VOLTA DA ORIGINE A DESTINAZIONE TRAMITE N
        }
    }
    //CHIUSURA DEI FILE
    fclose(origine);
    fclose(destinazione);
    return 0;
}