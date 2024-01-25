
#include <stdio.h>

int main()
{
//RIPASSO CICLI 
   //dichiarazione variabili
    int limite1 = 0, limite2 = 0;
    int numeri = 0, somma = 0;

   //inserimento dei limiti e controllo 
   //do while: controllo in coda   while: controllo in testa
    do{
    printf("inserire i due limiti compresi tra 30 e 50 \n");
    scanf("%d%d", &limite1, &limite2);
    if (limite1 < 30 || limite1 > 50 ){
        printf("limite1 fuori range! \n");
    }
    else if (limite2 < 30 || limite2 > 50){
        printf("limite2 fuori range! \n");
    }
    }while (limite1 < 30 || limite1 > 50 || (limite2 < 30 || limite2 > 50)); //condizione dei limiti se 
    //il limite è minore di 30 o maggiore di 50 il controllo continua

    //ciclo for per inserire i 5 numeri compresi tra i limiti
    printf("inserire 5 numeri compresi tra %d e %d \n", limite1, limite2);
    for (int i = 0; i<5; i++){
        printf("inserire il %d numero \n", i+1);
        scanf("%d", &numeri);
    //se il numero inserito risulta compreso tra i limiti allora lo aggiungo alla somma
        if (numeri >= limite1 && numeri <= limite2){
            somma += numeri;
        }
   //senno lo scarto 
        else {
            numeri = 0;
        }
    }
 //output
    printf ("la somma dei numeri compresi tra %d e %d: %d", limite1, limite2, somma);
    return 0;
}


