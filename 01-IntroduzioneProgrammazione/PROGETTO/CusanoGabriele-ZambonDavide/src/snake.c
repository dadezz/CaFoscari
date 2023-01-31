// 898103 897835
/**
 * @file snake.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @mainpage snake.c
 * @section Introduzione
 *
 * Implementazione di un gioco il cui scopo è risolvere un labirinto trovandone l’uscita. 
 * sono previste 2 modalità:
 * (1) Modalità interattiva : L’utente che si approccia al gioco ha il compito di risolvere egli
 * stesso il labirinto, muovendosi al suo interno e cercando di ottenere il punteggio migliore
 * (2) Modalità AI (intelligenza artificiale) : il programma stesso ha il compito di trovare un
 * percorso valido che risolva il labirinto e che possibilmente sia il percorso migliore,
 * ovvero quello che restituisce il punteggio finale più elevato.
 * 
 * Il programma inizia con la scelta della modalità. L’utente può decidere se utilizzare una mappa 
 * predefinita oppure una personalizzata.
 * 
 * Il punteggio si calcola come 1000 - #passi_eseguiti + 10 * #bonus_raccolti
 * 
 * @section Struttura
 * I tipi di maggior rilevanza sono le struct del campo (board_t) e quella che gestisce gli array (vector_t).
 * La prima ha come campi due variabili di tipo size_t che rappresentano rispettivamente il numero di
 * righe e di colonne e un vettore di tipo char che memorizza la mappa. La seconda ha come campi
 * un vettore di int, la variabile size che rappresenta la lunghezza del vettore stesso e
 * la variabile capacity che contiene la lunghezza massima del vettore.
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


int main(int argc, char* argv[]){

    if (argc > 1){
        if(!strcmp(argv[1],"--challenge")){
            board_t *new_map;
            new_map = malloc(sizeof(board_t));
            new_map = map_input_creation(new_map);
            mod_ai(new_map);
        }
    }
    else {
        char sample_map[] =  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
                            'o',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ','T','#',' ',' ','#',
                            '#',' ',' ','#',' ',' ','#',' ',' ','#',' ','!','#',' ',' ','#',' ',' ','#',
                            '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ','$','#',' ',' ','#',
                            '#',' ','$','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ','$','#',' ',' ','#',
                            '#',' ','!','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',
                            '#',' ','$','#',' ','$','$','$','$','#',' ',' ','#',' ',' ','#',' ',' ','#',
                            '#',' ','$','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','$',' ','#',
                            '#',' ','$','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#','$',' ','#',
                            '#',' ','T','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#','$',' ','#',
                            '#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','_',
                            '#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ','!','#',
                            '#',' ',' ',' ','!',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                            '#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                            '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'};

        board_t *default_map;
        default_map = malloc(sizeof(board_t));
        default_map->row = 15;
        default_map->col = 19;
        default_map->map = malloc(default_map->row * default_map->col);
        for (int i=0; i<default_map->row * default_map->col; i++){
            default_map->map[i] = sample_map[i];
        }

        int choice_mod = ask_mod(); // Modalità interattiva (1) o IA (0)
        int choice_default = ask_default(); //vuole inserire mappa in input: si (0), no (1)
        if (choice_default == 1) {
            /**
             * ha scelto di usare la mappa di default: il prossimo switch-case è relativo a IA o interactive
            */
            switch (choice_mod){
                case 1: 
                    mod_interactive(default_map);
                    break;
                case 2:
                    mod_ai(default_map);
                    break;
            }
        }
        else {
            /**
             * nel caso in cui avesse invece scelto di usarne una sua
            */
            board_t *new_map;
            new_map = malloc(sizeof(board_t));
            new_map = map_input_creation(new_map);
            
            switch (choice_mod){
                case 1: {
                    mod_interactive(new_map);
                    break;
                }
                case 2: {
                    mod_ai(new_map);
                    break;
                }
            }
            free(new_map);
        }
        free(default_map->map);
        free(default_map);
    }

    return 0;
}