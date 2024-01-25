#include <stdio.h>

//struct = dati caratterizzati da campi che definisco io 
struct s_punto{
    int x, y, z;
}punto1; //definisco una variabile di tipo struct

//stampa coordinate
void stampa_punto (struct s_punto p1){
    printf("X: %d Y: %d Z: %d", p1.x, p1.y, p1.z);
}
//passaggio per valore 
struct s_punto mod_punto (struct s_punto p1){
    p1.x += 1;
    p1.y += 1;
    p1.z += 1;
    return p1;
}
int main(int argc, char*argv[]){
    punto1.x = 5;
    punto1.y = -2;
    punto1.z = 7;
    stampa_punto(punto1);
    struct s_punto punto2 = mod_punto(punto1);
    return 0;
}