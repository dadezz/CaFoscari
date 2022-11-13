#include<stdlib.h>
#include<stdio.h>
#include<time.h>

///////////////////////////////////////////////////////////////
//                      IA-CONCERNING FUNCS                  //
///////////////////////////////////////////////////////////////

int forward_IA(int position, int direction, int columns){
    switch (direction){
        case 1:
            return position - columns;
        case 2:
            return position +1;
        case 3:
            return position + columns;
        case 4:
            return position - 1;
    }
}

int right_IA(int position,int  direction, int columns){
    switch (direction){
        case 1:
            return position +1;
        case 2:
            return position + columns;
        case 3:
            return position -1;
        case 4:
            return position - columns;
    }
}

void print_IA_output(int direction){
    switch (direction){
        case 1:
            printf("N ");
            break;
        case 2: 
            printf("E ");
            break;
        case 3: 
            printf("S ");
            break;
        case 4: 
            printf("O ");
            break;
        }
}

int find_start_IA(char* map, int size){
    for (int i=0; i<size; i++) if (map[i]=='o') return i;
}

int find_direction_IA(char*map, int position, int rows, int columns){
    if (position>=0 && position < columns) return 3;
    else if (position%columns == 0) return 2;
    else if (position%columns == columns-1) return 4;
    else return 1;
}

///////////////////////////////////////////////////////////////
//                            IA MOD                         //
///////////////////////////////////////////////////////////////

void mod_ai (char* map, int rows, int columns){ 
    int position = find_start_IA(map, rows*columns);
    _Bool game = 1;
    int direction = find_direction_IA(map, position, rows, columns);
    printf("%d\n", position);
    printf("%d\n", position%columns);
    printf("%d\n", direction);
    for (int  i=0; game; i++){
        if      (map[right_IA(position, direction, columns)] == '#' && map[forward_IA(position, direction, columns)] != '#') {
            position = forward_IA(position, direction, columns);
            print_IA_output(direction);
            if((position%columns) == (columns-1)) game = 0;
        }
        else if (map[right_IA(position, direction, columns)] == '#' && map[forward_IA(position, direction, columns)] == '#') {
            direction = (direction != 1) ? (direction - 1) :  4;
        }
        else if (map[right_IA(position, direction, columns)] != '#') {
            direction = (direction != 4) ? (direction + 1) :  1;
            position = forward_IA(position, direction, columns);
            print_IA_output(direction);
            if((position%columns) == (columns-1)) game = 0;
        }
        else printf("non so cosa fare\n");
    }
} 

///////////////////////////////////////////////////////////////
//                            CHALLENGE                      //
///////////////////////////////////////////////////////////////

int string_len(char* s){
    _Bool end = 0;
    int accum = 0;
    for (int i = 0; !end; i++){
        if (s[i]!='\0') accum++;
        else end = 1;
    }
    return accum;
}

int string_comparison(char* string1, char* string2){
    _Bool equals = 1;
    if (string_len(string1) != string_len(string2)) return 0;
    for (int i=0; i<string_len(string1) && equals; i++) if (string1[i] != string2[i]) equals = 0;
    return equals;
}

void map_scan_from_input(char* map, int rows, int columns){
    for (size_t j = 0; j < rows; ++j){
        size_t i=0;
        for(;i<columns;i++){
            while ((map[(i + j*(columns))] = getchar())=='\n'); 
            // spiegazione: scanno tutte le columns per ogni riga.
            // siccome \n è un carattere che viene macinato ugualmente dallo scanf,
            // quando ciò accade si entra nel ciclo  while, che serve a sovrascrivere il carattere
            // appena ricevuto in input (l'invio) con il carattere giusto del labirinto.
        }
    }
}

void play_challenge (){
    int columns;
    int rows;
    scanf("%d", &columns);
    scanf("%d", &rows);
    char* map = (char*) malloc((rows*columns)*sizeof(char));
    if (map == NULL){
        printf("ERRORE di allocazione memoria (malloc)");
        exit(EXIT_FAILURE);
    }
    map_scan_from_input(map, rows, columns);
    mod_ai (map, rows, columns);
    free(map);
}


///////////////////////////////////////////////////////////////
//                    INTERACTIVE MOD                        //
///////////////////////////////////////////////////////////////


void ins_bonuses (int bonus, char* map, int map_size){  
    int i = 0;
    while (i<bonus){  
        int x = rand() % map_size;
        if (map[x] == ' ') {  
            map[x] = '$';                                         
            i++;
        }
    }
}

void ins_taxes (int tax, char* map, int map_size){  
    int i = 0;
    while (i<tax){  
        int x = rand() % map_size;
        if (map[x] == ' ') {  
            map[x] = '$';                                         
            i++;
        }
    }
}

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

void map_print_INTER(char* x, int rows, int columns, int* points){
    for (int i=0; i<columns*2+5; i++){
        printf("-");
    }
    printf("\n");
    for (int i=0; i<rows; i++){            // Per ogni riga, 
        printf("|  ");
        for (int j=0; j<columns; j++){      // 
            printf("%c ", x[i*columns + j]);         // stampa di fila ogni elemento della colonna (con uno spazio intermeio per bellezza)
        }                                   //
        printf(" |");
        printf("\n");                       // dopodiché va a capo.
    } 
    for (int i=0; i<columns*2+5; i++){
        printf("-");
    }
    printf("\n");
    //riquadro sotto con punteggio e bonus.
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("punteggio: %d", *points);
        for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("\n");
    for (int i=0; i<columns*2+5; i++){
        printf("-");
    }
    printf("\n");
}

void input_char_INTER(char* x){
    do {
        scanf(" %c", x);
        if (*x != 'w' && *x != 'a' && *x != 's' && *x != 'd') printf("carattere inserito non valido...\n");
    } while( *x != 'w' && *x != 'a' && *x != 's' && *x != 'd');
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
///int posizione = 1*columns + 0;        row_o*columns + col_o [i][j]=[row_o][col_o]  x[i*columns + j]     
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

void controllo_input (char* x, int *riga_o, int *col_o, int carattere_in_input, _Bool *gioco, int *numero_dollari){
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

void mod_interactive(char* map, int rows, int columns, _Bool need_bon_tax){
    
    char input_char = '0'; 
        //variabile che raccoglie il carattere in input
    int points = 1000, qt_bonuses = 10, qt_taxes = 3, bonuses = 0, taxes = 0; 
        //punti del gioco, quantità di bonus e imprevisti nel gioco, quantità di bonus e imprevisti racccolti
    int position = find_start_IA(map, rows*columns);
    int row_o = position/columns;
    int col_o = position%columns;
    _Bool game = 1;
        //sei nel gioco?

    if (need_bon_tax){
        ins_bonuses(qt_bonuses, map, columns*rows);
        ins_taxes(qt_taxes, map, columns*rows);
    }
    while(game){
        map_print_INTER(map, rows, columns, &points);
        printf("Inserisci la prossima mossa: \n");
        input_char_INTER(&input_char);
        points -= 1;
        //INTER_control(map, &riga_o, &col_o, input_char, &game, &bonuses, &taxes);
        printf("punteggio attuale: %d, \nbonus raccolti: %d\n", points, bonuses);   
    }
    printf("punteggio finale: punteggio + 10 punti per ogni bonus = %d ", 10*bonuses + points);
} 

int ask_mod(){}

