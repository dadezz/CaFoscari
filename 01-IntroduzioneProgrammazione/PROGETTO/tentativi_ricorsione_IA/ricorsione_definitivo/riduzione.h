#ifndef _STD_LIBS_
#include "types.h"
#endif

#if FLATTENED

board_t copia_mappa (board_t map);
bool mappe_diverse(board_t map1, board_t map2);
bool muro(board_t map, int p);
bool vicolo_cieco (board_t map, int i);
bool angolo_libero(board_t map, int i);
bool doppia_fila(board_t map, int i);
bool muraglia(board_t map, int i);
bool adiacente_chiocciola_tre(board_t map, int i);
void stampa(board_t map);
void isola_oggetti(board_t map);
void riduci(board_t map);
void elimina_vicoli_ciechi(board_t map);
void elimina_orfani(board_t map);
void rimetti_spazi(board_t map);
void elimina_tre_inutili(board_t map);
void riduzione(board_t map);

#endif //flattened