/**
 * @file func.h
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section Libreria per le funzioni chiamate esternamente
 * Libreria inserita in tutti i file, con la dichiarazione della firma di tutte le funzioni 
 * dichiarate esternamente rispetto al file in cui sono usate
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

void errore ();
position_t find_char(board_t *map, char c);
bool not_in(vector_t percorso, position_t pos, board_t map);
void map_scan_from_input(board_t *map);
void stampa_direzioni(vector_t p, board_t map);
void stampa_piu(board_t map, vector_t percorso);
board_t* map_input_creation(board_t *map);
void mod_ai (board_t *map);
board_t copia_mappa (board_t *map);
void riduzione(board_t map);
void mod_interactive(board_t *grid);
int ask_mod();
int ask_default();