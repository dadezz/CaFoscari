#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#define PIPE_OUTPUT_NAME "/tmp/pipeOut"
#define PIPE_INPUT_NAME  "/tmp/pipeIn"

int main() {
    //////////////////////////////////////////////////////////////
    //                  inizializzazione
    /////////////////////////////////////////////////////////////
    
    int fd[2];

    printf("sto aprendo in sola lettura pipein\n");
    fd[0] = open(PIPE_OUTPUT_NAME,O_RDONLY); // apre la pipe in lettura
    printf("sto aprendo in sola scrittura pipeout\n");
    fd[1] = open(PIPE_INPUT_NAME, O_WRONLY); //apre la pipe in scrittura

    if ( fd[0] < 0 ) { 
        perror("errore apertura pipe in sola lettura\n"); 
        exit(1);
    }
    else {
        printf("apertura pipe in sola lettura eseguita correttamente\n");
    }

    if ( fd[1] < 0 ) { 
        perror("errore apertura pipe in sola scrittura\n"); 
        exit(1);
    }
    else {
        printf("apertura pipe in sola scrittura eseguita correttamente\n");
    }

    int success=1;
    char read_char = 0;
    char tmp;


    while(success>0){
        printf("Ciclo esterno: \n");

        success = read(fd[0], &read_char, 1);
        printf("carattere letto: %c \n", read_char);

        char chiave = 'A'-read_char;
        tmp = read_char + chiave;

        printf("chiave: %d \n", (int) chiave);
        printf("carattere corrsipondente: %c \n", tmp);


        if (write(fd[1], &tmp, 1) <= 0){
            printf("scrittura con errore\n");
        }

        while(read(fd[0], &read_char, 1)) {
            printf("Ciclo interno: \n");
            printf("carattere letto: %c \n", read_char);
            
            tmp = read_char + chiave;
            printf("carattere corrsipondente: %c \n", tmp);
            
            if (write(fd[1], &tmp, 1) <= 0){
                printf("scrittura con errore\n");
            }
            if (tmp == '#') {
                printf("sono nell'if col break\n");
                break;
            }
        }
    }
    /*while(success>0){
        printf("Ciclo esterno: \n");

        success = read(fd[0], &read_char, 1);
        printf("carattere letto: %c \n", read_char);

        char chiave = 'A'-read_char;
        printf("chiave: %d \n", (int) chiave);

        tmp = read_char + chiave;
        printf("carattere corrsipondente: %c \n", tmp);

        if (write(fd[1], &tmp, 1) <= 0){
            printf("scrittura con errore\n");
        }
        printf("l'ho scritto\n");

        while(read(fd[0], &read_char, 1)) {
            printf("Ciclo interno: \n");

            printf("carattere letto: %c \n", read_char);
            printf("chiave: %d \n", (int) chiave);

            tmp = read_char + chiave;
            printf("carattere corrsipondente: %c \n", tmp);
            
            if (write(fd[1], &tmp, 1) <= 0){
                printf("scrittura con errore\n");
            }

            printf("l'ho scritto \n");

            if (read_char == '#') {
                printf("sono nell'if col break\n");
                break;
            }
        }
    }*/
    
    /*
    printf("provo a leggere il primo byte per calcolare la chiave\n");
    read(fd[0], &first_char, 1); 
    printf("byte letto; %c \n", first_char);

    printf("calcolo chiave: \n");
    int chiave =  'A'-first_char;
    printf("chiave calcolata: %d\n", chiave);

    char tmp = first_char + chiave;
        printf("carattere in chiaro corrispondente: %c", tmp);

        printf("provo a scriverlo in pipe in scrittura\n");
        if (write(fd[1], &tmp, 1) > 0){
            printf("scrittura con successo\n");
        }
        else printf("errore in scrittura\n");



    char read_char;
    while(read(fd[0], &read_char, 1)){
        printf("sono nel while per leggere la pipe\n");
        char tmp = read_char + chiave;
        printf("carattere in chiaro corrispondente: %c\n", tmp);

        printf("provo a scriverlo in pipe in scrittura\n");
        if (write(fd[1], &tmp, 1) > 0){
            printf("scrittura con successo\n");
        }
        else printf("errore in scrittura\n");

    }
    */

   
    close(fd[0]);      // chiude il descrittore
    close(fd[1]);
    unlink(PIPE_OUTPUT_NAME);  // rimuove la pipe
    unlink(PIPE_INPUT_NAME);  // rimuove la pipe
    return 0;
}