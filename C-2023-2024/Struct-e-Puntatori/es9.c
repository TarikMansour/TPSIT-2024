
#include <stdio.h>
#include <stdlib.h>
//USO DELLA FUNZIONE MALLOC, LA PROPRIETA SIZEOF E FUNZIONE FREE
int main()
{

 typedef struct { //struct locale non più visibile alle funzioni
    int x;
    int y;
    int z;
} coordinate;

coordinate coord; 
coordinate *coord1 =(coordinate*)&coord; //puntatore coord1 che punta all'indirizzo di coord tramite cast (puntatore di tipo coordinate)
coord1 = malloc(sizeof(coordinate)); //malloc ritorna l'indirizzo della memoria sizeof ritorna la dimensione della struct
coord1 -> x = 50;
coord1 -> y = 50;
coord1 -> z = 50;
printf("le coordinate sono x = %d, y = %d e z = %d", coord.x, coord.y, coord.z);
free(coord1); //libero la memoria
    return 0;
}
