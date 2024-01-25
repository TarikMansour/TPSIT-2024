#include <stdio.h>

int main(int argc, char* argv[])
{
    //RIPASSO ARGC E ARGV ARGC = ARGUMENT COUNTER ARGV = ARGUMENT VECTOR 
    printf("ciao \n");
    printf ("%d \n",argc);
    //se scrivo 3 parole spazate saranno 3 argumenti contati se le metto tra doppia appici conterà come una singola stringa 
    //quindi solo uno argomento
    for (int i = 0; i<argc; i++){
        printf("%s \n", argv[i]);
    }
    return 0;
}