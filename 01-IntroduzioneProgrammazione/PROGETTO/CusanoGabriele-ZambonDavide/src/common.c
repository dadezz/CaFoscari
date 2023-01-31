/**
 * @file common.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section Funzioni comuni
 * Funzioni che sono utilizzate sia nella modalità IA che in quella interattiva
*/
#ifndef  _HEADERS_
#define  _HEADERS_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include"types.h"
#endif // _HEADERS_

#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "func.h"
#endif //_FUNCTIONS_

/**
 * chiedo all'utente se vuole giocare in modalità interattiva o in modalità IA
 * @return 1 se sceglie modalità interattiva, 2 se sceglie modalità IA
*/
int ask_mod(){
    printf("Ciao, benvenuto in SNAKE\n");
    printf("Per giocare con la modalità interattiva, premi 1 \n");
    printf("Per testare invece la modalità IA, premi 2.\n");
    int choice;
    do{ //continuo a chiederlo se sbaglia input
        scanf("%d", &choice);
        if (choice!=1 && choice!=2) printf("\nSorry, scelta non valida, riprova: ");
        else printf("Ricevuto!\n");
    } while(choice!=1 && choice!=2);
    return choice;
}

/**
 * chiedo all'utente se vuole giocare con la mappa sua o con una di default
 * @return 1 se sceglie modalità interattiva, 2 se sceglie modalità IA
*/
int ask_default(){
    //stronzata: chiedo all'utente se vuole inserire la mappa in input o usare quella di default
    printf("Premi 1 se vuoi usare il labirinto di default\npremi 2 se vuoi inserire un labirinto custom in input.\n");
    int choice;
    do{ //continuo a chiederlo se sbaglia input
        scanf("%d", &choice);
        if (choice!=1 && choice!=2) printf("\nSorry, scelta non valida, riprova: ");
        else printf("Ricevuto!\n");
    } while(choice!=1 && choice!=2);
    return choice;
}

/**
 * esco dal programma in caso di problemi con malloc
*/
void errore () {
    printf("Riscontrato  problema di allocazione memoria.\n");
    exit(EXIT_FAILURE);
}

/**
 * faccio una copia della mappa
 * @param map mappa originale da copiare
 * @return la copia, con tipo board_t (non puntatore)
*/
board_t copia_mappa (board_t *map){
    board_t copia_map;
    copia_map.row = map->row;
    copia_map.col = map->col;
    copia_map.map = (char*) malloc((sizeof(char) * copia_map.row*copia_map.col));
    if (copia_map.map == NULL) exit(EXIT_FAILURE);
    return copia_map;
}

/**
 * 
 * trova la posizione di un dato carattere all'interno del labirinto.
 * @param map mappa dentro la quale cercare
 * @param c carattere da cercare
 * @return la posizione del carattere nella mappa. se non viene, restituisce -1 (in tutti i campi di position_t)
*/
position_t find_char(board_t *map, char c){
    position_t p;
    for (int i=0; i<map->row; i++){
        for (int j=0; j<map->col; j++){
            if (map->map[i*map->col + j] == c){
                p.row = i;
                p.col = j;
                p.pos = i*map->col + j;
                return p;
            }
        }
    }
    p.row = -1;
    p.col = -1;
    p.pos = -1;
    return p;
}

/**
 * prendo in input i singoli caratteri della mappa
 * @param map puntatore alla mappa (memoria già allocata) su cui salvare ciò che si prende in internet
*/
void map_scan_from_input(board_t *map){
    for (size_t j = 0; j < map->row; ++j){
        size_t i=0;
        for(;i<map->col;i++){
            while ((map->map[(i + j*(map->col))] = getchar())=='\n'); 
            // spiegazione: scanno tutte le columns per ogni riga.
            // siccome \n è un carattere che viene macinato ugualmente dallo scanf,
            // quando ciò accade si entra nel ciclo  while, che serve a sovrascrivere il carattere
            // appena ricevuto in input (l'invio) con il carattere giusto del labirinto.
        }
    }
}

/**
 * stampo il risultato finale: mosse effettuate (cioè, la direzione di ogni passo).
 * @param p: vettore del percorso
 * @param map mappa (mi serve solo per il campo "col")
*/
void stampa_direzioni(vector_t p, board_t map){
    for (int i=1; i<p.size; i++){
        if (p.data[i] - p.data[i-1] == 1) printf("E ");
        else if (p.data[i] - p.data[i-1] == -1) printf("O ");
        else if (p.data[i] - p.data[i-1] == map.col) printf("S ");
        else printf("N ");
    }
}

/**
 * controllo se sono già passato sull'attuale posizione, per evitare loop infiniti
 * @param percorso vettore col percorso esplorato finora
 * @param pos attuale posizione
 * @param map labirinto che sto usando
 * @return true se non sono già passato, false altrimenti
*/
bool not_in(vector_t percorso, position_t pos, board_t map){
    bool a = true;
    for (int i=0; i<percorso.size && a; i++)
        if (percorso.data[i] == (pos.row*map.col + pos.col))
            a = false;
    return a;
}

/**
 * stampo il labirinto, compresi i più del percorso, senza però modificare la mappa
 * @param map labirinto
 * @param percorso vettore col percorso
*/
void stampa_piu(board_t map, vector_t percorso){
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            position_t pos;
            pos.row = i;
            pos.col = j;
            if (not_in(percorso, pos, map)) printf("%c ", map.map[i*map.col + j]);
            else printf("+ ");
        }
        printf("\n");
    }
}

/**
 * prendo in input le dimensioni della mappa e la mappa stessa
 * @param map puntatore alla mappa. deve essere già allocata memoria sufficiente per i campi, mentre la memoria per i caratteri viene allocata qui
*/
board_t* map_input_creation(board_t *map){
    printf("colonne: ");
    scanf("%d", &map->col);
    printf("righe: ");
    scanf("%d", &map->row);

    map->map = malloc(map->row*map->col);
    if (!map ) errore();

    map_scan_from_input(map);
    return map;
}