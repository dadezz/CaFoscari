#include<stdlib.h>
#include<stdio.h>
#include<time.h>

///////////////////////////////////////////////////////////////
//                      GENERAL FUNCS                        //
///////////////////////////////////////////////////////////////

int ask_mod(){
    //stronzata: chiedo all'utente se vuole usare modalità interattiva o IA
    printf("Ciao, benvenuto nel giochino!1!1!1!1!1!1\n");
    printf("Per giocare con la modalità interattiva, premi 1 \n");
    printf("Per testare invece la modalità IA, premi 2.\n");
    int choice;
    printf("scelta: ");
    do{ //continuo a chiederlo se sbaglia input
        scanf("%d", &choice);
        if (choice!=1 && choice!=2) printf("\nSorry, scelta non valida, riprova: ");
    } while(choice!=1 && choice!=2);
    return choice;
}

int ask_default(){
    //stronzata: chiedo all'utente se vuole inserire la mappa in input o usare quella di default
    printf("Premi 1 se vuoi usare il labirinto di default\npremi 2 se vuoi inserire un labirinto custom in input.\n");
    int choice;
    printf("scelta: ");
    do{ //continuo a chiederlo se sbaglia input
        scanf("%d", &choice);
        if (choice!=1 && choice!=2) printf("\nSorry, scelta non valida, riprova: ");
    } while(choice!=1 && choice!=2);
    return choice;
}

void map_scan_from_input(char* map, int rows, int columns){
    //prendo in input i singoli caratteri della mappa
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

void random_ins_chars (int N, char* map, int map_size, char c){  
    //inserimento casuale di N caratteri nella mappa
    int i = 0;
    while (i<N){  
        int x = rand() % map_size;  //posizione casuale nell'array
        if (map[x] == ' ') {        //inserisco negli spazi vuoti
            map[x] = c;                                         
            i++;
        }
    }
}

int char_counter (char* map, int map_size, char c){
    //conto gli spazi vuoti della mappa
    int counter = 0;
    for (int i=0; i<map_size; i){
        if (map[i] == c) counter++;
    }
    return counter;
}

void do_you_need_bonuses(int map_size, char* map){
    //chiedo se sono da inserire i $ e !, in caso li inserisco.
    int bonuses_needed;
    
    printf("\nserve inserire casualmente bonus e imprevisti?(si=1/no=0): ");
    do {
        scanf("%d", &bonuses_needed);
    } while (bonuses_needed != 1 && bonuses_needed!= 0); 
    if (bonuses_needed) {
        int qt;
        do { // ci sono abbastanza spazi vuoti nel labirinto per inserire quel numero di $?
            printf ("quanti $ ti servono? ");
            scanf("%d", &qt);
        } while (qt < char_counter(map, map_size, ' ')); 
        random_ins_chars(qt, map, map_size, '$');
        do{
            printf ("quanti ! ti servono? ");
            scanf("%d", &qt);
        } while (qt < char_counter(map, map_size, ' '));
        random_ins_chars(qt, map, map_size, '!');
    }
}

char* map_input_creation(int *rows, int *columns){
    //prendo in input dimensioni e mappa
    printf("colonne: ");
    scanf("%d", columns);
    printf("righe: ");
    scanf("%d", rows);
    char* map = (char*) malloc((*rows*(*columns))*sizeof(char)); //scelta:
        //uso array monodimensionale per facilità d'uso
    if (map == NULL){
        printf("ERRORE di allocazione memoria (malloc)");
        exit(EXIT_FAILURE);
    }
    map_scan_from_input(map, *rows, *columns);
    return map;
}

int find_char(char* map, int size, char c_to_be_found){
    //trova la posizione di un carattere specifico all'interno della mappa
    for (int i=0; i<size; i++) if (map[i]==c_to_be_found) return i;
}

///////////////////////////////////////////////////////////////
//                      IA-CONCERNING FUNCS                  //
///////////////////////////////////////////////////////////////

int forward_IA(int position, int direction, int columns){
    // qual'è la posizione "davanti" a me?
    // rircordo che posizione 1=N, 2=W, 3=S, 4=E
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
    // qual'è la posizione "alla mia destra"?
    // rircordo che posizione 1=N, 2=W, 3=S, 4=E
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

int find_start_direction_IA(char*map, int position, int rows, int columns){
    // trovo la direzione di partenza 
    // a seconda del bordo in cui sono, so dove girarmi.
    if (position>=0 && position < columns) return 3;
    else if (position%columns == 0) return 2;
    else if (position%columns == columns-1) return 4;
    else return 1;
}

void print_IA_output(int direction){
    // stampo a video i passi usati per la soluzione
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

///////////////////////////////////////////////////////////////
//                            IA MOD                         //
///////////////////////////////////////////////////////////////

void mod_ai (char* map, int rows, int columns){ 
    int position = find_char(map, rows*columns, 'o'); //posizione di inizio
    int end = find_char(map, rows*columns, '_');        //posizione di fine
    int game = 1; //diventerà 0 quando arrivo alla fine
    int direction = find_start_direction_IA(map, position, rows, columns);
    
    while(game) {
        /**
         * logica interna: tengo sempre un muro sulla destra. 
         * se mi trovo un muro davanti, mi giro verso la mia sinistra, in modo da averlo a destra
         * se ho la destra libera, mi giro e mi spost verso destra
        */
        if (map[right_IA(position, direction, columns)] == '#' && map[forward_IA(position, direction, columns)] != '#') {
            position = forward_IA(position, direction, columns);
            print_IA_output(direction);
            if(position == end) game = 0;
        }
        else if (map[right_IA(position, direction, columns)] == '#' && map[forward_IA(position, direction, columns)] == '#') {
            direction = (direction != 1) ? (direction - 1) :  4;
        }
        else if (map[right_IA(position, direction, columns)] != '#') {
            direction = (direction != 4) ? (direction + 1) :  1;
            position = forward_IA(position, direction, columns);
            print_IA_output(direction);
            if(position == end) game = 0;
        }
        else printf("non so cosa fare\n");
    }
} 

///////////////////////////////////////////////////////////////
//                            CHALLENGE                      //
///////////////////////////////////////////////////////////////

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


void map_print_INTER(char* x, int rows, int columns, int* points, int* bonuses, int*taxes, int*drill){
    //stampa labirinto
    for (int i=0; i<columns*2+5; i++){
        printf("-");                        // riga superiore del riquadro che contiene il labirinto
    }
    printf("\n");
    for (int i=0; i<rows; i++){             // Per ogni riga, 
        printf("|  ");                      // muro laterale del riquadro
        for (int j=0; j<columns; j++){      // 
            printf("%c ", x[i*columns + j]);         // stampa di fila ogni elemento della colonna (con uno spazio intermeio per bellezza)
        }                                   //
        printf(" |");                       //muro laterale del riquadro
        printf("\n");                       // dopodiché va a capo.
    } 
    for (int i=0; i<columns*2+5; i++){
        printf("-");                        //riga inferiore del riquadro
    }
    printf("\n");
    //riquadro sotto con punteggio e bonus.
    //riga punteggio
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("punteggio: %d", *points);
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    //riga bonus
    printf("\n");
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("Bonus: %d", *bonuses);
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    //riga imprevisti
    printf("\n");
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("imprevisti: %d", *taxes);
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    //riga trapani
    printf("\n");
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("Trapani: %d", *drill);
    for (int i=0; i<((columns*2+5)-13)/2; i++){
        printf(" ");
    }
    printf("\n");
    for (int i=0; i<columns*2+5; i++){
        printf("-");                        //fine riquadro punteggio
    }
    printf("\n");
}

void input_char_INTER(char* x){
    //prendo in input il carattere per spostarmi
    do {
        scanf(" %c", x);
        if (*x != 'w' && *x != 'a' && *x != 's' && *x != 'd') printf("carattere inserito non valido...\n");
    } while( *x != 'w' && *x != 'a' && *x != 's' && *x != 'd');
}

int next_position_INTER (int input_char, int position, int columns){
    //posizione successiva a seconda del carattere in input
    switch (input_char){
        case 'a':
            return position-1;
        case 'd':
            return position+1;
        case 'w':
            return position-columns;
        case 's':
            return position+columns;
    }
}

void INTER_control (char* x, int rows, int columns, int *position, int input_char, int *game, int* bonuses, int* taxes, int* drill){
    //logica effettiva del gioco: ci sono muri? posso spostarmi? bonus? etc etc
    int ok = 1;
    switch(input_char){
        //controllo che non si possa uscire dai bordi delle pareti
        case 'w':{
            if (next_position_INTER(input_char, *position, columns)<0) {
                printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
                ok = 0;
            }
            break;
        }
        case 'a':{
            if (next_position_INTER(input_char, *position, columns)%columns == (columns-1)){
                printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
                ok = 0;
            }
            break;
        }
        case 's':{
            if (next_position_INTER(input_char, *position, columns)>rows*columns) {
                printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
                ok = 0;
            }
            break;
        }
        case 'd':{
            if (next_position_INTER(input_char, *position, columns)%columns == 0) {
                printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
                ok = 0;
            }
        }
    }
    if (ok){
        //controllo che non ci si scontri con le pareti
        if (x[next_position_INTER(input_char, *position, columns)] == '#'){
            if (!*drill){
                printf("Mi spiace, di qua non puoi andare, hai sprecato un punto...\n");
                ok = 0;
            }
            if (*drill) *drill -=1;
        }
        else if (x[next_position_INTER(input_char, *position, columns)] == '_'){
            
            printf("Grandioso, hai vinto!\n");
            *game = 0;
        }
        else if (x[next_position_INTER(input_char, *position, columns)] == '$') *bonuses += 1;
        else if (x[next_position_INTER(input_char, *position, columns)] == '!') {
            *taxes += 1;
            *bonuses = *bonuses/2;
        }
        else if (x[next_position_INTER(input_char, *position, columns)] == 'T') *drill += 3;
        if (ok){
            x[*position] = ' ';
            *position = next_position_INTER(input_char, *position, columns);
            x[*position] = '.';
        }
    }
}

void mod_interactive(char* map, int rows, int columns){
    //contenitore della parte interattiva, come fosse main
    char input_char = '0'; 
        //variabile che raccoglie il carattere in input
    int points = 1000, bonuses = 0, taxes = 0, drill = 0; 
        //punti del gioco, quantità di bonus e imprevisti nel gioco, quantità di bonus e imprevisti racccolti
    int position = find_char(map, rows*columns, 'o');
    int game = 1;
        //sei nel gioco
    map_print_INTER(map, rows, columns, &points, &bonuses, &taxes, &drill);
    while(game){
        printf("Inserisci la prossima mossa: \n");
        input_char_INTER(&input_char);
        points -= 1;
        INTER_control(map, rows, columns, &position, input_char, &game, &bonuses, &taxes, &drill);
        map_print_INTER(map, rows, columns, &points, &bonuses, &taxes, &drill);
           
    }
    printf("bonus risultanti: %d.\npunteggio finale:\npunteggio + 10 punti per ogni bonus  = %d ", bonuses, 10*bonuses + points);
} 