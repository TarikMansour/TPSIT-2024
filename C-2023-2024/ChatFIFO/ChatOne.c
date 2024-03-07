#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main() {
    char message[100];
    char messageread[100];
    int fd0;


    //FIFO BIDIREZIONALE
    fd0 = open("shell1_fifo", O_RDWR);
    while (1) {
        //SCRITTURA SUL MESSAGE 
        printf("Shell 1 (Sender): ");
        fgets(message, sizeof(message), stdin);
        
        //SCRITTURA E LETTURA DEI MESSAGGI SULLA FIFO
        write(fd0, message, sizeof(message));
         //VERIFICA SE SHELL 1 HA SCRITTO HALT -> FERMA
        if (strcmp(message, "HALT\n") == 0) {
            printf("Shell 1 (Sender) stopping...\n");
            break;
        }
        //USO SLEEP PER DARE IL TEMPO ALLA SHELL 2 DI LEGGERE
        sleep(1);
        read(fd0, messageread, sizeof(messageread));
        //SCRIVE MESSAGGI LETTI
        printf("Shell 1 (Receiver): %s", messageread);
    }
    //CHIUSURA FIFO
    close(fd0);
    return 0;
}
