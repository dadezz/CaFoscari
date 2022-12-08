/**
 * MODIFICARE TYPES.H PER CAMBIARE TRA FLATTENED/MATRICE E PER DEBUG
*/
#ifndef _STD_LIBS_
#define _STD_LIBS_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include"types.h"
#endif //_STD_LIBS_

#include"functs.h"



int main(){
    char mappa_di_prova[] =  { '#','#','#','#','#','#',
                               'o',' ','#',' ',' ','#',
                               '#',' ','#',' ',' ','#',
                               '#','$','#',' ',' ','#',
                               '#',' ','#','#','#','#',
                               '#','T','!',' ',' ','#',
                               '#','#','#',' ','#','#',
                               '#',' ','#',' ','#','#',
                               '#',' ','$',' ',' ','_',
                               '#','#','#','#','#','#'};
    int max_p = 0;
    board_t default_map;
    // inizializzazione con valori di default, nel programma POSSONO essere presi in input 
    default_map.row = 10;
    default_map.col = 6;
    #if FLATTENED
    default_map.map = (char*) malloc((sizeof(char) * default_map.row*default_map.col));
    if (default_map.map == NULL) errore();
    for(int i=0; i<default_map.row*default_map.col; i++){
        default_map.map[i]= mappa_di_prova[i];
    }
    #endif
    #if !FLATTENED
    default_map.map = (char**) malloc((sizeof(char*) * default_map.row));
    if (default_map.map == NULL) errore();
    for(int i=0; i<default_map.row; i++){
        default_map.map[i] = (char*) malloc(sizeof(char)* default_map.col);
        if (default_map.map[i] == NULL) errore ();
        for (int j=0; j<default_map.col; j++) {
            default_map.map[i][j]= mappa_di_prova[j+i*default_map.col];
        }   
    }
    #endif

    //trovo inizio e fine. se fallisco, libero memoria allocata e esco dal programma
    position_t inizio = find_char(default_map, 'o');
    if (inizio.col == -1) {
        #if !FLATTENED
        for (int i=0; i<default_map.row; i++){
            free(default_map.map[i]);
        }
        #endif
        free(default_map.map);
        printf("inizio non trovato\n");
        exit(EXIT_FAILURE);
    }
    position_t fine = find_char(default_map, '_');
    if (fine.col == -1) {
        #if !FLATTENED
        for (int i=0; i<default_map.row; i++){
            free(default_map.map);
        }
        #endif
        free(default_map.map);
        printf("fine non trovato\n");
        exit(EXIT_FAILURE);
    }

    #if DEBUG
    printf("inizio: (%d, %d)\n", inizio.row, inizio.col);
    printf("fine: (%d, %d)\n", fine.row, fine.col);
    #if FLATTENED
    printf("inizio flattened: %d\n", inizio.row*default_map.col + inizio.col);
    printf("fine flattened: %d\n", fine.row*default_map.col + fine.col);
    #endif
    #endif



    //percorso è l'array con tutte le coordinate del percorso tentato per ogni albero
    //(quindi cambia a ogni chiamata di funzione ricorsiva)
    #if FLATTENED
    vector_t percorso;
    #endif
    #if !FLATTENED
    p_vec_t percorso;
    #endif
    percorso.size = default_map.row * default_map.col; //massima lunghezza possibile
    #if FLATTENED
    percorso.data = (int*)calloc(percorso.size, sizeof(int));
    if (percorso.data == NULL) errore ();
    #endif
    #if !FLATTENED
        percorso.col = (int*)calloc(percorso.size, sizeof(int));
    if (percorso.col == NULL) errore ();
    percorso.row = (int*)calloc(percorso.size, sizeof(int));
    if (percorso.row == NULL) errore ();
    #endif

    //path è l'array con il percorso definitivo.
    //nella funzione, quando viene trovato un percorso con punteggio maggiore del 
    //precedente, path assume i valori di percorso corrispondente
    #if FLATTENED
    vector_t path;
    #endif
    #if !FLATTENED
    p_vec_t path;
    #endif
    path.size = default_map.row * default_map.col; //massima lunghezza possibile
    #if FLATTENED
    path.data = (int*)calloc(path.size, sizeof(int));
    if (path.data == NULL) errore ();
    #endif
    #if !FLATTENED
    path.col = (int*)calloc(path.size, sizeof(int));
    if (path.col == NULL) errore ();
    path.row = (int*)calloc(path.size, sizeof(int));
    if (path.row == NULL) errore ();
    #endif


    
    //chiamata di funzione
    best_percorso(default_map, percorso, path, inizio, fine, 0, 0, 0, &max_p);
    printf("\n miglior punteggio: %d\n", max_p);

    
    //libero percorso, non mi serve più
    #if FLATTENED
    free(percorso.data);
    #endif
    #if !FLATTENED
    free(percorso.col);
    free(percorso.row);
    #endif

    //calcolo la lunghezza effettiva del path e realloco di conseguenza
    size_t size = 0;
    for (int j=0; j<path.size; j++) {
        size++;
        #if FLATTENED
        if (path.data[j] == 0) break;
        #endif
        #if !FLATTENED
        if (path.col[j] == 0 && path.row[j] == 0) break;
        #endif
    };
    path.size = size;
    #if FLATTENED
    path.data[size-1] = fine.col + fine.row*default_map.col;
    path.data = realloc(path.data, path.size*sizeof(int));
    if (path.data == NULL) errore ();
    #endif
    #if !FLATTENED
    path.col[size-1] = fine.col;
    path.row[size-1] = fine.row;
    path.col = realloc(path.col, path.size*sizeof(int));
    if (path.col == NULL) errore ();
    path.row = realloc(path.row, path.size*sizeof(int));
    if (path.row == NULL) errore ();
    #endif

    //stampo le posizioni
    printf("percorso:   ");
    for(int i=0; i<size; i++) {
        #if FLATTENED
        if (i!=size-1) printf("%d -> ", path.data[i]);
        else printf("%d", path.data[i]);
        #endif
        #if !FLATTENED
        if (i!=size-1) printf("(%d, %d) -> ", path.row[i], path.col[i]);
        else printf("(%d, %d)", path.row[i], path.col[i]);
        #endif
    }
    printf("\n");

    //stampo le mosse
    printf("mosse effettuate:   ");
    #if FLATTENED
    stampa_direzioni(path, default_map);
    #endif
    #if !FLATTENED
    stampa_direzioni(path);
    #endif
    printf("\n");


    //stampo il labirinto
    stampa_piu(default_map, path);
    
    //libero il resto
    #if FLATTENED
    free(path.data);
    #endif
    #if !FLATTENED
    free(path.col);
    free(path.row);
    for (int i=0; i<default_map.row; i++){
        free(default_map.map[i]);
    }
    #endif
    free(default_map.map);
    return 0;
}
