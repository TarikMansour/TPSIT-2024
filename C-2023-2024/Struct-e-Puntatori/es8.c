
#include <stdio.h>
//STRUCT LOCALE POPOLATA TRAMITE PUNTATORE
int main()
{

 typedef struct { //struct locale non più visibile alle funzioni
    int x;
    int y;
    int z;
} coordinate;

coordinate coord; 
coordinate *coord1 =(coordinate*)&coord; //puntatore coord1 che punta all'indirizzo di coord tramite cast (puntatore di tipo coordinate)
//COMPILO I CAMPI DELLA STRUCT
coord1 -> x = 50;
coord1 -> y = 50;
coord1 -> z = 50;
printf("le coordinate sono x = %d, y = %d e z = %d", coord.x, coord.y, coord.z);
    return 0;
}
