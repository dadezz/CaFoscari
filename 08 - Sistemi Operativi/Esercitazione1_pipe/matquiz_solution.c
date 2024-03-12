/*
 * Corso di Sistemi Operativi
 * Prima verifica: pipe
 *
 * Soluzione di Zambon Davide 898103
 * creo in sola lettura la pipe dove matquiz scrive, e in sola scrittura la pipe dove scrivo io
 * (le pipe sono create da matquiz).
 * Leggo una linea alla volta, fino a \n, poi parso la stringa ottenuta fincHé non vedo i due numeri:
 * prendo i primi 51 caratteri che sono prima dei due numeri, poi parso byte per byte il primo numero, 
 * poi la virgola e poi di nuovo byte per byte il secondo.
 * eseguo l'operazione e creo la stringa a partire dal risultato. butto in buffer della pipe il numero e poi un \n
 */
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#define PIPE_OUTPUT_NAME "/tmp/pipeOut"
#define PIPE_INPUT_NAME  "/tmp/pipeIn"


int main() {
    //////////////////////////////////////////////////////////////
    //                  inizializzazione
    //                  creazione pipe
    /////////////////////////////////////////////////////////////
    
    int fd[2];

    //printf("sto aprendo in sola lettura pipein\n");
    fd[0] = open(PIPE_OUTPUT_NAME,O_RDONLY); // apre la pipe in lettura
    //printf("sto aprendo in sola scrittura pipeout\n");
    fd[1] = open(PIPE_INPUT_NAME, O_WRONLY); //apre la pipe in scrittura

    if ( fd[0] < 0 ) { 
        perror("errore apertura pipe in sola lettura\n"); 
        exit(1);
    }
    else {
        //printf("apertura pipe in sola lettura eseguita correttamente\n");
    }

    if ( fd[1] < 0 ) { 
        perror("errore apertura pipe in sola scrittura\n"); 
        exit(1);
    }
    else {
        //printf("apertura pipe in sola scrittura eseguita correttamente\n");
    }



    //////////////////////////////////////////////////////////////
    //                  computazione
    /////////////////////////////////////////////////////////////

    int success=1; // guardia del ciclo, diventa false quando la pipe non legge più nulla
    char read_phrase[52]; // buffer per "Cortesemente, dovresti moltiplicare (x*y) i numeri "

    while(success>0){ //finché leggo
        //printf("Ciclo esterno: \n");
        
        success = read(fd[0], &read_phrase, 51); // sono 51 i caratteri prima del primo numero
        if (success<0) {
            //printf("uscita, errore lettura pipe\n");
            break;
        }
        read_phrase[51] = '\0' ;//per debug, devo stamparla
        //printf("[DEBUG]: frase letta: %s\n", read_phrase);

        int mul1, mul2; //i due fattori
        mul1 = mul2 = 0;
        char read_char; // buffer per i byte dei numeri


        //leggo il primo numero
        while (1) {
            success = read(fd[0], &read_char, 1);
            //printf("[DEBUG]: primo numero, carattere: %c\n", read_char);
            if (read_char >= '0' && read_char <= '9') {
                mul1 = mul1*10 + (read_char-'0'); // parsing del numero
                //printf("[DEBUG]: attuale mul1: %d\n", mul1);
            }
            else break; //leggo la virgola
        }
        //leggo il secondo numero 
        while (1) {
            success = read(fd[0], &read_char, 1);
            //printf("[DEBUG]: primo numero, carattere: %c\n", read_char);
            if (read_char >= '0' && read_char <= '9') {
                mul2 = mul2*10 + (read_char-'0'); // parsing del numero
                //printf("[DEBUG]: attuale mul2: %d\n", mul2);
            }
            else break; //leggo newline
        }

        mul1 = mul1 * mul2; //eseguo moltiplicazione
        //printf("[DEBUG]: risultato: %d\n", mul1);

        char pin_str[1024]; // buffer in scrittura
		snprintf(pin_str, 1024, "%d\n", mul1); // salvo il numero come stringa
        //printf("[DEBUG]: risultato as string: %s\n", pin_str);

        int len = strlen(pin_str);
        if (write(fd[1], &pin_str, len) <= 0){ // scrivo in pipe
            //printf("scrittura con errore\n");
        }
        //else printf("[DEBUG]: SCRITTO toericamente con successo\n");
    }  
    close(fd[0]);      // chiude il descrittore
    close(fd[1]);
    unlink(PIPE_OUTPUT_NAME);  // rimuove la pipe
    unlink(PIPE_INPUT_NAME);  // rimuove la pipe
    return 0;
}