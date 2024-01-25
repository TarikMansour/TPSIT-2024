#include <stdio.h>
#include <stdlib.h>
#define MAX 4
#define LETTERE 20 
//tutto ciò che viene scritto viene trattato come un codice in esadecimale
int main (){
    FILE *nomi; //puntatore al file
    char arr[LETTERE];
    char c;
    nomi = fopen("nomi.txt", "r"); //nome e estensione del file, w per write (overwrites), a per add (aggiunge), r per read (lettura) --> se esiste lo apre senno lo crea
    
    if(nomi == NULL){
        printf("file non aperto: errore \n");
        exit(1); //funzione exit = true
    }
    printf("ok, file aperto\n"); //creato un file nomi.txt
    do{
        c=fgetc(nomi); //dentro c metto i caratteri di nomi.txt
        putchar(c); //stampo i caratteri di nomi.txt
    }while(c != EOF); //END OF FILE (carattere nascosto che indica il fine del file --> non stampa piu)
   
   /*  for (int i = 0; i<MAX; i++){
        printf("inserire il %d nome \n", i+1);
        scanf("%s", arr);
        fputs(arr, nomi); //funzione che mette dentro nomi i nomi inseriti
        fputc('\n', nomi); //funzione che mette dentro un spazio tra i nomi inseriti
    } */

    fclose(nomi); //funzione che chiude il file e lo salva, liberando anche memoria
    return 0;
}