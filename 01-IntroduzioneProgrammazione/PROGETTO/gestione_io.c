#include <stdio.h>
#include<stdlib.h>

void print_lab (char x[][19], int righe, int colonne){  // Funzione che mi serve per stampare la struttura del labirinto.

    for (int i=0; i<righe; i++){            // Per ogni riga, 
        for (int j=0; j<colonne; j++){      // 
            printf("%c ", x[i][j]);         // stampa di fila ogni elemento della colonna (con uno spazio intermeio per bellezza)
        }                                   //
        printf("\n");                       // dopodiché va a capo.
    } 
}

void scanf_lab (char *x){   // Funzione che mi serve per prendere in input il carattere
    do {
        scanf(" %c", x);    // scan il carattere,
        if (*x != 'w' && *x != 'a' && *x != 's' && *x != 'd') printf("carattere inserito non valido...\n"); //se non è valido printa errore
    } while( *x != 'w' && *x != 'a' && *x != 's' && *x != 'd'); //e se non è valido lo riscanna.
}


/*
* per quanto riguarda il carattere_in_input, vengono usati i classici comandi da gioco:
* 'a' = sinistra
* 's' = giù
* 'd' = destra
* 'w' = su
* In particolare:
*   - se l'utente vuole spostarsi verso su (w), significa che la coordinata riga deve decrementare di 1
*   - se l'utente vuole spostarsi verso giu (s), significa che la coordinata riga deve incrementare di 1
*   - se l'utente vuole spostarsi verso sinistra (a), significa che la coordinata colonna deve decrementare di 1
*   - se l'utente vuole spostarsi verso destra (d), significa che la coordinata colonna deve incrementare di 1
*/


void controllo_input (char x[][19], int *riga_o, int *col_o, int carattere_in_input, _Bool *gioco){
    // x -> struttura labirinto; riga_o, col_o -> coordinate attuali di 'o'; carattere in input -> inserimento utente (asdw); gioco -> booleano che falsifico quando arrivo alla fine del gioco
    
    /*
    / È il corpo vero e proprio del programma, la struttura logica che permette il movimento del pallino.
    / Commento uno solo dei caratteri, perché per gli altri la logica è la stessa, cambia solo la direzione
    / 
    / non serve controllare che lo spostamento sia all'interno del bordo superiore o inferiore del labirinto, perché quest'ultimo è 
    / delimitato sopra e sottoda # e controllo direttamente che non vada a capitare sopra un cancelletto
    */
    if (carattere_in_input == 'a'){                         // controllo qual'è il carattere  inserito (a, s, d, w)
        if ( (*col_o-1)>0 && x[*riga_o][*col_o-1] != '#'){  // siccome vado a sinistra, controllo di non andare in una posizione '-1' in array (serve soltanto alla prima mossa)
                                                            // e controllo anche che la nuova posizione dove mi dovrei spostare non sia un muro. Se entrambe le condizioni sono valide, 
            x[*riga_o][*col_o] = ' ';                       // sostituisco la posizione dove mi trovo (che adesso è 'o' ) con uno spazio, 
            x[*riga_o][*col_o-1] = 'o';                     // e sostituisco la posizione dove devo andare (che adesso è vuoto, ovvero ' ' ) con il carattere 'o'. in questo modo, dò l'illusione di un effettivo spostamento.
            *col_o = *col_o + 1;                            // Infine, aggiorno le coordinate del mio personaggino 'o'.
        }
        else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n"); //nel caso le condizioni sopra non fossero soddisfatte (fuori dal labirinto o muro), semplicemente printo errore 
    }
    else if (carattere_in_input == 'd'){
        if ( (*col_o+1)<18 && x[*riga_o][*col_o+1] != '#'){
            x[*riga_o][*col_o] = ' ';
            x[*riga_o][*col_o+1] = 'o';
            *col_o = *col_o + 1;
        }
        else if((*col_o+1)==18) {                           // unica cosa in più da spiegare: se il personaggino arriva senza errori all'ultima colonna (ovvero non va su un muro dell'ultima colonna)
            printf("grandioso! hai vinto!\n");              // vince.
            *gioco = 0;                                     // di conseguenza, il gioco termina.
        }
        else {printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
           //printf("\033[%dm", 40 + 1);
        }
    }
    else if (carattere_in_input == 's'){
        if (x[*riga_o+1][*col_o] != '#'){
            x[*riga_o][*col_o] = ' ';
            x[*riga_o+1][*col_o] = 'o';
            *riga_o = *riga_o + 1;
        }
        else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
    }
    else { //non serve l'if, perché il controllo del carattere c'è già nello scanf
        if (x[*riga_o-1][*col_o] != '#'){
            x[*riga_o][*col_o] = ' ';
            x[*riga_o-1][*col_o] = 'o';
            *riga_o = *riga_o - 1;
        }
        else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
    }
}
