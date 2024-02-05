#include <stdio.h>
#include <stdlib.h>
void conta (char stringa[], int *vocali, int *consonanti){
    for (int i = 0; stringa[i] != 0; i++){
        if (stringa[i] == 'a' || stringa[i] == 'e' || stringa[i] == 'i' ||stringa[i] == 'o' || stringa[i] == 'u'){
            (*vocali)++;
        }
        else {
            (*consonanti)++;
        }
    }
}
int main (int argc, char*argv[]){
    int consonanti = 0, vocali = 0;
    if (argc < 2){
        printf("errore argomenti");
        return -1;
    }
    conta(argv[1], &vocali, &consonanti);
    printf("ci sono %d vocali e %d consonanti", vocali, consonanti);
    return 0;
}