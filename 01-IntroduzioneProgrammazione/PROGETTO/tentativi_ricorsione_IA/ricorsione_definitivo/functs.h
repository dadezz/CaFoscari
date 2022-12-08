
#ifndef _STD_LIBS_
#include "types.h"
#endif


position_t find_char(board_t map, char c);
void errore ();
int max(vector_t x);

#if FLATTENED
void stampa_direzioni(vector_t p, board_t map);
bool not_in(vector_t percorso, position_t pos, board_t map);
void stampa_piu(board_t map, vector_t percorso);
bool punto_valido(board_t map, position_t p, vector_t percorso, int T);
void elimina_piu(vector_t percorso, int x);
void scambia_punteggio_max(int punteggio, vector_t path, vector_t percorso, int* max_p);
int best_percorso(board_t map, vector_t percorso, vector_t path, position_t position, position_t fine, int contatore, int bonus, int T, int* max_p);
#endif

#if !FLATTENED
void stampa_direzioni(p_vec_t p);
void elimina_piu(p_vec_t percorso, int x);
bool not_in(p_vec_t percorso, position_t pos);
void stampa_piu(board_t map, p_vec_t percorso);
bool punto_valido(board_t map, position_t p, p_vec_t percorso, int T);
void scambia_punteggio_max(int punteggio,  p_vec_t path, p_vec_t percorso, int*max_p);
int best_percorso(board_t map, p_vec_t percorso, p_vec_t path, position_t position, position_t fine, int contatore, int bonus, int T, int*max_p);
#endif
