#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global;
int global2 = 520;
int main(){
    /*numeri esadecimali ettichetta stack -> intervallo dove esiste lo stack
    stack overflow se andiamo oltre all'intervallo -> quando si chiamano tante funzioni
    */
    int local;
    int *p;
    p = (int*)malloc(local); 
    while(1){
        printf("%p\n", p); //l'indirizzo del puntatore è nello stack ma il suo contenuto che punto allo heap
        printf("%p\n", &local);
        printf("%d\n", getpid());
        sleep(1);
    }
    free(p); //libera lo spazio allocato
    return 0;
}