/**
 * @file interactive.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section MODALITÀ_INTERATTIVA
 * Il giocatore comanda il personaggio digitando in input una delle
 * quattro direzioni proposte per muoversi : Nord, Sud, Est, Ovest. 
 * nello specifico, in input: W per Nord, S per Sud, A per Est, D per Ovest). 
 * A ogni mossa, viene, ne viene controllata la validità (celle libere, entro i bordi etc.) 
 * In caso di mossa non valida, il conteggio dei passi aumenta lo stesso, ma senza effetti nello spostamento.
 * Sono presenti celle speciali che modificano il flow del gioco, permettendo di attraversare muri, 
 * allungare e accorciare lo snake. La mappa è un vettore di caratteri monodimensionale, la
 * posizione della singola cella è rappresentata da un numero, che è l’indice dell’array. Lo
 * Snake viene rappresentato attraverso la lista delle posizioni che occupa all’interno della mappa.
 * Riteniamo che la parte più complicata da sviluppare sia stata il movimento Lo snake ha tipo vector_t
 * per semplicità di accesso tramite indice. quando si allunga o si accorcia, viene modificato il campo size.
 * Il movimento è stato fatto pensando agli effetti che deve avere graficamente all’interno del gioco. 
 * Abbiamo usato un vector_t ausiliario per memorizzare lo stato precedente dello snake, perché poi fosse facile 
 * aggiungere, togliere e modificare alementi. 
 * Quando viene incontrato un bonus ('$'), lo snake si allunga.
 * Quando viene incontrato un imprevisto ('!'), lo snake si dimezza.
*/
#ifndef _HEADERS_
#define _HEADERS_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include"types.h"
#endif //_HEADERS_

#include"dvector_t.h"

#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "func.h"
#endif //_FUNCTIONS_

/**
 * alloco memoria sufficiente per memorizzare una variabile position_t
*/
position_t* create_pos(){
    position_t *p = (position_t*) malloc(sizeof(position_t));
    if(!p) errore();
    return p;
}

/**
 * stampo la posizione
 * @param pos: posizione da stampare
*/
void print_pos(position_t *pos){
    printf("( pos : %d )\n",pos->pos);
}

/**
 * se la posizione è presente nel corpo dello snake, ritorno 1, altrmenti ritorno 0
*/
int is_in_snake(position_t *p,snake *l){
    for(size_t k = 0; k<l->size; k++){
        if(l->body->data[k] == p->pos){
            return 1;
        }
    }
  return 0;
}

/**
 * stampo la mappa con lo snake
 * @param grid: mappa da stampare
 * @param l: snake da stampare
*/
void print_grid(board_t *grid, snake* l){
    position_t *printer = create_pos();
    for(size_t j = 0; j< grid->row; ++j){
        for(size_t i = 0; i<grid->col; ++i){
            printer->pos = i + j*grid->col;
            if(is_in_snake(printer,l)){
                //se la posizione è occupata dallo snake, stampo il corpo dello snake
                if(printer->pos == l->body->data[0])
                    printf("O");
                else
                    printf("o");
            }
            else{
                //altrimenti stampo la mappa normale
                printf("%c",grid->map[i + j*grid->col]);
            }
        }
        printf("\n");
    }
             
}

/**
 * controlla se esiste una posizione uguale a quella della testa.
 * @return -1 se non esiste, la posizione se esiste
*/
int check_pos(snake *player){
    for(int i = 1; i<player->size; i++){
        if(player->body->data[i] == player->body->data[0]){
            return i;
        } 
    }
   return -1;
}

/**
 * elimina la coda dello snake, a partire da un dato indice
 * @param player snake
 * @param index la posizione dell'array dalla quale eliminare un pezzo
*/
void delete_el(snake * player, int index){
    int len_required  = index;
    while (player->size != len_required) {
        v_pop_back(player);
    }
}

/**
 * prendo la mossa in input
 * @param x il puntatore al carattere su cui viene salvato l'input
*/
void input_char(char *x) {
    do {
        scanf(" %c", x); 
        if (*x != 'w' && *x != 'a' && *x != 's' && *x != 'd')
            printf("#carattere inserito non valido...\n");
    } while (*x != 'w' && *x != 'a' && *x != 's' && *x != 'd');
}

/**
 * spostamento dello snake
 * @param player_prec snake prima della mossa successiva
 * @param player snake futuro
*/
void mov_snake(snake *player_prec,snake *player){ 
    for(int k = 1;k<player->size+1;k++){
        player->body->data[k] = player_prec->body->data[k-1]; //mi serve tutto shiftato di uno, perché la coda non occupa 
            //più la posizione precedente, e la testa occuperà la posizione successiva.
    }
}

/**
 * calcola la posizione successiva del giocatore, modificando la lista della variabile player.
 * @param x carattere preso in input
 * @param grid mappa di gioco
 * @param player vettore con le posizioni del corpo dello snake
 * @param bonus variabile su cui tenere conto del numero di $ raccolti
 * @param taxes variabile su cui tenere conto del numero di ! raccolti
 * @param drill variabile su cui tenere conto del numero di T raccolti
*/
void input_effect(char x, board_t *grid, snake *player, int *bonus, int *taxes, int *drill){ 

    /** 
     * all'inizio della funzione vengono salvate le posizioni precedenti su player_prec
     * questo vettore poi viene copiato a partire dall'indice 1 fino a player->size + 1
     * parte da 0 quindi per passare i valori giusti è necessario considerare sempre k-1
     * e player->size  + 1
    */

    int index = 0;
    snake *player_prec = v_create();
    player_prec = v_clone(player);

    /**
     * i casi di x (carattere in input) sono 4: a, s, d, w.
     * ne commento uno solo, gli altri sono uguali di conseguenza
    */
    
    switch (x){
        case 'a':
        // caso di input a:
            if(((player->body->data[0] - 1)%grid->col) != (grid->col  - 1)){ 
                //controllo che non stia uscendo dalla mappa: sto andando verso sinistra, quindi posizione modulo colonne non 
                // può darmi colonne-1
                if(grid->map[player->body->data[0]-1] != '#'){
                    mov_snake(player_prec,player);
                    //se non vado sopra a un muro, controllo intanto se capito in una cella speciale
                    if(grid->map[player->body->data[0]-1] == 'T')
                        *drill+=3;     
                    if(grid->map[player->body->data[0]-1] == '$'){
                        *bonus+=1;
                        v_push_back(player,player_prec->body->data[player->size - 1]); //aggiungo un pezzetto di corpo
                    }
                    if(grid->map[player->body->data[0]-1] == '!'){
                        *taxes+=1;
                        *bonus /=2;
                        delete_el(player,(player->size/2)); //elimina metà del corpo
                    }
                    grid->map[player->body->data[0]] = ' '; //rendo cella calpestabile quella su cui sono appena passato 
                        //(elimino eventuali $, T, !)
                    player->body->data[0]--;     //aggiorno la mia posizione ('a' è verso sinistra, quindi posizione-1)
                }
                else{ //se vado sopra a un muro: ho il trapano?
                    if(!(*drill)){
                        printf("#non si può passare attraverso di qui,hai sprecato un punto\n");
                    }
                    else{
                        mov_snake(player_prec,player);
                        *drill-=1;
                        grid->map[player->body->data[0]] = ' ';
                        player->body->data[0]--;
                    }        
                }
            }
            else
                printf("#non puoi uscire dalla mappa : hai sprecato uno punto \n");
                break;
        case 'd':
            if(((player->body->data[0] + 1))%grid->col != 0){ 
                //controllo che non stia uscendo dalla mappa: sto andando verso destra, quindi posizione modulo colonne non 
                // può darmi 0 (perché sarebbe la prima colonna)
                if(grid->map[player->body->data[0]+1] != '#'){
                    mov_snake(player_prec,player);
                    if(grid->map[player->body->data[0]+1] == 'T')
                        *drill+=3; 
                    if(grid->map[player->body->data[0]+1] == '$'){
                        *bonus+=1;
                        v_push_back(player,player_prec->body->data[player->size-1]);
                    }
                    if(grid->map[player->body->data[0]+1] == '!'){
                        *taxes+=1;
                        *bonus/=2;
                        delete_el(player,(player->size/2)-1); 
                    }
                    grid->map[player->body->data[0]] = ' ';
                    player->body->data[0]++;
                }
                else {
                    if(!(*drill)){
                        printf("#non si può passare attraverso di qui,hai sprecato un punto\n");
                    }else{
                        mov_snake(player_prec,player);
                        *drill-=1;
                        grid->map[player->body->data[0]] = ' ';
                        player->body->data[0]++;
                    }        
                }
            }
            else
                printf("#non puoi uscire dalla mappa : hai sprecato uno punto \n");
            break;
        case 'w':
            if((player->body->data[0] - grid->col) > 0){
                //controllo che non stia uscendo dalla mappa: sto andando verso su, quindi
                //la mia posizione deve per forza rimanere positiva
                if(grid->map[player->body->data[0] - grid->col ] != '#'){
                    mov_snake(player_prec,player);
                    if(grid->map[player->body->data[0]-grid->col] == 'T'){
                        *drill+=3; 
                    }    
                    if(grid->map[player->body->data[0]-grid->col] == '$'){
                        *bonus+=1;
                        v_push_back(player,player_prec->body->data[player->size -1 ]);
                    }
                    if(grid->map[player->body->data[0]-grid->col] == '!'){
                        *taxes+=1;
                        *bonus/=2;
                        delete_el(player,(player->size/2)); 
                    }
                    grid->map[player->body->data[0]] = ' ';
                    player->body->data[0] -= grid->col;
                }
                else {
                    if(!(*drill))
                        printf("#non si può passare attraverso di qui,hai sprecato un punto\n");
                    else{
                        mov_snake(player_prec,player);
                        *drill-=1;
                        grid->map[player->body->data[0]] = ' ';
                        player->body->data[0]-= grid->col;         
                    }        
                }
            }
            else
                printf("#non puoi uscire dalla mappa : hai sprecato uno punto \n");
            break;
        case 's':
            //controllo che non stia uscendo dalla mappa: sto andando verso giù, 
            //quindi la mia posizione  non può mai superare la grandezza totale del labirinto
            if((player->body->data[0]+ grid->col ) < grid->row * grid->col){
                if(grid->map[player->body->data[0]+ grid->col] != '#'){
                    mov_snake(player_prec,player);
                    if(grid->map[player->body->data[0]+grid->col] == 'T')
                        *drill+=3;     
                    if(grid->map[player->body->data[0]+grid->col] == '$'){
                        *bonus+=1;
                        v_push_back(player,player_prec->body->data[player->size-1]);
                    }
                    if(grid->map[player->body->data[0]+grid->col] == '!'){
                        *taxes+=1;
                        *bonus/=2;
                        delete_el(player,(player->size/2));
                    }
                    grid->map[player->body->data[0]] = ' ';
                    player->body->data[0] += grid->col;    
                }
                else {
                    if(!(*drill)){
                        printf("#non si può passare attraverso di qui,hai sprecato un punto\n");
                    }else{
                        mov_snake(player_prec,player);
                        *drill-=1;
                        grid->map[player->body->data[0]] = ' ';
                        player->body->data[0] += grid->col;
                    }        
                }
            }
            else
                printf("non puoi uscire dalla mappa : hai sprecato uno punto \n");
            break;
        }
        index = check_pos(player); // controlla se esiste una posizione uguale a quella della testa.
        if(index > 0 ) // se la trova, elimina tutto il pezzo dal serpente da quel punto in poi
            delete_el(player,index);
    v_free(player_prec);     
}

/**
 * @param steps passi eseguiti
 * @param bonus $ raccolti
 * @return punteggio finale
*/
int point_sum(int steps,int bonus){
    return 1000-steps + 10*bonus;
}

/**
 * funzione che sviluppa il gioco interattivo
 * @param grid mappa su cui si vuol giocare
*/
void mod_interactive(board_t *grid){

    position_t *start; //variabile su cui salvo la cella di entrata nel labirinto
    position_t *end; //variabile su cui salvo la cella di uscita dal labirinto
    start = malloc(sizeof(position_t));
    if (!start) errore();
    end = malloc(sizeof(position_t));
    if (!end) errore();
    *start = find_char(grid, 'o');
    *end = find_char(grid, '_');

    int bonus = 0;  //variabile che tiene conto dei $ raccolti
    int taxes = 0;  //variabile che tiene conto dei ! raccolti
    int drill = 0;  //variabile che tiene conto dei T raccolti

    snake* player = NULL; //puntatore all'array che contiene il corpo dello snake

    //CONTROLLI RISPETTO ALL'INIZIO E ALLA FINE DELLA MAPPA
    if (start->pos == -1 || end->pos == -1) {
        free(grid->map);
        printf("inizio o fine non trovati\n");
        exit(EXIT_FAILURE);
    }

    //creo la lista del giocatore  
    player = v_create(); 
    v_push_back(player,start->pos); //la testa dello snake è la cella iniziale
        
    //effettivo inizio del gioco
    bool in_game = true;    //booleano che serve per uscire dal gioco quando arriviamo alla fine
    int counter = 0;    //variabile che conta i passi fatti
    char  x;    //variabile su cui viene memorizzato il carattere in input ad ogni mossa

    while (in_game){
        /**
         * finché non arrivo alla fine:
         * prendo in input la mossa da fare, 
         * calcolo la nuova situazione di gioco,
         * conto un passo in più
         * stampo il labirinto (+ lo snake)
         * stampo un resoconto su punti.
         * se arrivo alla fine, esco dal gioco e stampo il punteggio totale
        */
        print_grid(grid,player);
        printf("(?)inserisci la prossima mossa : ");
        input_char(&x);
        printf("\n");
        input_effect(x, grid, player, &bonus, &taxes, &drill);
        counter++;
        printf("(s)PASSI      : %d\n", counter);
        printf("($)bonus      : %d\n", bonus);
        printf("(!)imprevisti : %d\n", taxes);
        printf("(T)trivella   : %d\n", drill);
        if(player->body->data[0] == end->pos){
            printf("(F)HAI VINTO!!!\n");
            printf("(F)PUNTI TOTALI : %d\n",point_sum(counter, bonus));
            in_game = false;
        }
    }
    

    //libero le varie memorie allocate, che non mi servono più
    v_free(player);
    free(end);
    free(start);

}