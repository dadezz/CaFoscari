#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void print_lab (char x[][19], int righe, int colonne, int *punteggio){  // Funzione che mi serve per stampare la struttura del labirinto.

    for (int i=0; i<colonne*2+5; i++){
        printf("-");
    }
    printf("\n");
    for (int i=0; i<righe; i++){            // Per ogni riga, 
        printf("|  ");
        for (int j=0; j<colonne; j++){      // 
            printf("%c ", x[i][j]);         // stampa di fila ogni elemento della colonna (con uno spazio intermeio per bellezza)
        }                                   //
        printf(" |");
        printf("\n");                       // dopodiché va a capo.
    } 
    for (int i=0; i<colonne*2+5; i++){
        printf("-");
    }
    printf("\n");
    //riquadro sotto con punteggio e bonus.
    for (int i=0; i<((colonne*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("punteggio: %d", *punteggio);
        for (int i=0; i<((colonne*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("\n");
    for (int i=0; i<colonne*2+5; i++){
        printf("-");
    }
    printf("\n");
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

void controllo_input (char x[][19], int *riga_o, int *col_o, int carattere_in_input, _Bool *gioco, int *numero_dollari){
    // x -> struttura labirinto; riga_o, col_o -> coordinate attuali di 'o'; carattere in input -> inserimento utente (asdw); gioco -> booleano che falsifico quando arrivo alla fine del gioco
    
    /*
    / È il corpo vero e proprio del programma, la struttura logica che permette il movimento del pallino.
    / Commento uno solo dei caratteri, perché per gli altri la logica è la stessa, cambia solo la direzione
    / 
    / non serve controllare che lo spostamento sia all'interno del bordo superiore o inferiore del labirinto, perché quest'ultimo è 
    / delimitato sopra e sottoda # e controllo direttamente che non vada a capitare sopra un cancelletto
    */
    switch (carattere_in_input){
        case 'a':{                         // controllo qual'è il carattere  inserito (a, s, d, w)
            if ((*col_o-1)>0 && x[*riga_o][*col_o-1] != '#'){        // siccome vado a sinistra, controllo di non andare in una posizione '-1' in array (serve soltanto alla prima mossa)
                                                                     // e controllo anche che la nuova posizione dove mi dovrei spostare non sia un muro. Se entrambe le condizioni sono valide, 
                if (x[*riga_o][*col_o-1] == '$') *numero_dollari +=1 ;   //allo stesso modo, controllo se c'è un dollaro, in caso affermativo, aggiorno il contatore (per ora non ho ancora fatto che si aggiorna il punteggio)
                if (x[*riga_o][*col_o-1] == '!') *numero_dollari /= 2 ;   //allo stesso modo, controllo se c'è un !, in caso affermativo, aggiorno il contatore dei bonus
                x[*riga_o][*col_o] = ' ';                       // sostituisco la posizione dove mi trovo (che adesso è 'o' ) con uno spazio, 
                x[*riga_o][*col_o-1] = 'o';                     // e sostituisco la posizione dove devo andare (che adesso è vuoto, ovvero ' ' ) con il carattere 'o'. in questo modo, dò l'illusione di un effettivo spostamento.
                *col_o = *col_o - 1;                            // Infine, aggiorno le coordinate del mio personaggino 'o'.
            }
            else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n"); //nel caso le condizioni sopra non fossero soddisfatte (fuori dal labirinto o muro), semplicemente printo errore 
            break;
        }
        case 'd': {
            if ( (*col_o+1)<18 && x[*riga_o][*col_o+1] != '#'){
                if (x[*riga_o][*col_o+1] == '$') *numero_dollari += 1; 
                if (x[*riga_o][*col_o+1] == '!') *numero_dollari /= 2 ;
                x[*riga_o][*col_o] = ' ';
                x[*riga_o][*col_o+1] = 'o';
                *col_o = *col_o + 1;
            }
            else if((*col_o+1)==18 && x[*riga_o][*col_o+1] != '#') {                           // unica cosa in più da spiegare: se il personaggino arriva senza errori all'ultima colonna (ovvero non va su un muro dell'ultima colonna)
                printf("grandioso! hai vinto!\n");              // vince.
                *gioco = 0;                                     // di conseguenza, il gioco termina.
            }
            else {printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
            }
            break;
        }
        case 's': {
            if (x[*riga_o+1][*col_o] != '#'){
                if (x[*riga_o+1][*col_o] == '$') *numero_dollari +=1; 
                if (x[*riga_o+1][*col_o] == '!') *numero_dollari /= 2 ;
                x[*riga_o][*col_o] = ' ';
                x[*riga_o+1][*col_o] = 'o';
                *riga_o = *riga_o + 1;
            }
            else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
            break;
        }
        case 'w': {
            if (x[*riga_o-1][*col_o] != '#'){
                if (x[*riga_o-1][*col_o] == '$') *numero_dollari +=1; 
                if (x[*riga_o-1][*col_o] == '!') *numero_dollari /= 2 ;
                x[*riga_o][*col_o] = ' ';
                x[*riga_o-1][*col_o] = 'o';
                *riga_o = *riga_o - 1;
            }
            else printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
            break;
        }
    }
}


void inserisci_dollari (int bonus, char s[][19]){       //inserisce in modo casuale dei dollari (in realtà è casuale solo la prima volta perché manca i seed, poi saranno sempre nella stessa posizione)
    int i = 0, j = 0;                                   //coordinate dei futuri dollari
    srand(time(NULL));                                  //metto il seed della fuzione randomd
    while (i<bonus && j<bonus){                         //bonus è il numero di dollari che volgio inserire
        int x = (rand() % 13)+1;                        //posizione random per la riga
        int y = (rand() % 18)+1;                        // e per la colonna
        if (s[x][y] != '#') {                           //controllo che in quella posizoine non ci sia un muro
            s[x][y] = '$';                              //se è così, inserisco il dollaro
            j++;                                            
            i++;
        }
    }
}

void inserisci_imprevisti (int imprevisti, char s[][19]){   //inserisce in modo casuale dei ! (in realtà è casuale solo la prima volta perché manca i seed, poi saranno sempre nella stessa posizione)
    int i = 0, j = 0;                                       //coordinate dei futuri dollari
    while (i<imprevisti && j<imprevisti){                   //bonus è il numero di dollari che volgio inserire
        int x = (rand() % 13)+1;                            //posizione random per la riga
        int y = (rand() % 18)+1;                            // e per la colonna
        if (s[x][y] != '#' && s[x][y] != '$' && s[x][y] != 'o') {             //controllo che in quella posizoine non ci sia un muro
            s[x][y] = '!';                                  //se è così, inserisco il dollaro
            j++;                                            
            i++;
        }
    }
}