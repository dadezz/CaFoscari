#ifndef _STD_LIBS_
#define _STD_LIBS_
#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#include"types.h"
#endif //_STD_LIBS_

position_t find_char(board_t map, char c){
    //trova la posizione di un dato carattere all'interno del labirinto
    //se non viene trovato, viene restituita la posizione (-1, -1)
    position_t p;
    bool controllo = false;
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            #if FLATTENED
            if (map.map[i*map.col + j] == c) 
            #endif
            #if !FLATTENED
            if (map.map[i][j] == c)
            #endif
            {
                p.row = i;
                p.col = j;
                controllo = true;
                return p;
            }
        }
    }
    if(!controllo) {
        p.row = -1;
        p.col = -1;
        return p;
    }
}
void errore () {
    //messaggio di errore per sbaliata allocazione in memoria con malloc
    printf("Riscontrato  problema di allocazione memoria.\n");
    exit(EXIT_FAILURE);

}
int max(vector_t x){
    //massimo elemento in un vettore di interi
    int max = x.data[0];
    for (int i=1; i<x.size; i++) if (x.data[i]>max) max=x.data[i];
    return max;
}


#if FLATTENED
void stampa_direzioni(vector_t p, board_t map)
#endif
#if !FLATTENED
void stampa_direzioni(p_vec_t p)
#endif
{
    for (int i=1; i<p.size; i++){
        #if FLATTENED
        if (p.data[i] - p.data[i-1] == 1) printf("E ");
        else if (p.data[i] - p.data[i-1] == -1) printf("O ");
        else if (p.data[i] - p.data[i-1] == map.col) printf("S ");
        else printf("N ");
        #endif
        #if !FLATTENED
        if (p.col[i] == p.col[i-1]){
            if (p.row[i] - p.row[i-1] == 1) printf("S ");
            else printf("N ");
        }
        else if(p.col[i] - p.col[i-1] == 1) printf("E ");
        else printf("O ");
        #endif
    }
}

#if FLATTENED
bool not_in(vector_t percorso, position_t pos, board_t map)
#endif
#if !FLATTENED
bool not_in(p_vec_t percorso, position_t pos)
#endif
{
    //controllo se sono già passato sull'attuale posizione
    //( => no loop infiniti )
    bool a = true;
    for (int i=0; i<percorso.size && a; i++)
        #if FLATTENED
        if (percorso.data[i] == (pos.row*map.col + pos.col))
        #endif
        #if !FLATTENED
        if (percorso.row[i] == pos.row && percorso.col[i] == pos.col)
        #endif
            a = false;
    return a;
}

#if FLATTENED
void stampa_piu(board_t map, vector_t percorso)
#endif
#if !FLATTENED
void stampa_piu(board_t map, p_vec_t percorso)
#endif
{
    //stampo il labirinto, compresi i più del percorso, senza però modificare la mappa
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            position_t pos;
            pos.row = i;
            pos.col = j;
            #if FLATTENED
            if (not_in(percorso, pos, map)) printf("%c ", map.map[i*map.col + j]);
            #endif
            #if !FLATTENED
            if (not_in(percorso, pos)) printf("%c ", map.map[i][j]);
            #endif
            else printf("+ ");
        }
        printf("\n");
    }
}

#if FLATTENED
bool punto_valido(board_t map, position_t p, vector_t percorso, int T){
    //un punto è valido se non ci sono passato sopra prima e se non è un muro    
    if (T==0) return map.map[p.row*map.col + p.col] != '#' && not_in(percorso, p, map);
    else return not_in(percorso, p, map);
}
#endif
#if !FLATTENED
bool punto_valido(board_t map, position_t p, p_vec_t percorso, int T){
    //un punto è valido se non ci sono passato sopra prima e se non è un muro    
    if (T==0) return map.map[p.row][p.col] != '#' && not_in(percorso, p);
    else return not_in(percorso, p);
}
#endif

#if FLATTENED
void elimina_piu(vector_t percorso, int x)
#endif
#if !FLATTENED
void elimina_piu(p_vec_t percorso, int x)
#endif
{
    //quando torno indietro, elimino gli ultimi passi che ho fatto dall'array, sovrascrivendoli con zeri
    int s = percorso.size;
    for (int i = x+1; i<s; i++) {
        #if FLATTENED
        percorso.data[i] = 0;
        #endif
        #if !FLATTENED
        percorso.col[i] = 0;
        percorso.row[i] = 0;
        #endif
    }
}

#if FLATTENED
void scambia_punteggio_max(int punteggio, vector_t path, vector_t percorso, int* max_p)
#endif
#if !FLATTENED
void scambia_punteggio_max(int punteggio,  p_vec_t path, p_vec_t percorso, int* max_p)
#endif
{
    //cambio la variabile globale punteggio_max ogni volta che trovo un 
    //percorso migliore del migliore precedentemente trovato
    if (punteggio > *max_p){
        *max_p = punteggio;
        for (int i = 0; i<percorso.size; i++) {
            #if FLATTENED
            path.data[i] = percorso.data[i];
            #endif
            #if !FLATTENED
            path.col[i] = percorso.col[i];
            path.row[i] = percorso.row[i];
            #endif
        }
    }
}


#if FLATTENED
int best_percorso(board_t map, vector_t percorso, vector_t path, position_t position, position_t fine, int contatore, int bonus, int T, int* max_p)
#endif
#if !FLATTENED
int best_percorso(board_t map, p_vec_t percorso, p_vec_t path, position_t position, position_t fine, int contatore, int bonus, int T, int* max_p)
#endif
{
    //funzione effettiva
    #if DEBUG
    sleep(1);
    stampa_piu(map, percorso);
    #if FLATTENED
    printf("position: %d\n", position.row*map.col + position.col);
    #endif
    #if !FLATTENED
    printf("position: (%d, %d)\n", position.row, position.col);
    #endif
    printf("max: %d ", max_p);
    printf("[ ");
    for(int i=0; i<path.size; i++)
        #if FLATTENED
        printf(" %d ", path.data[i]); 
        #endif
        #if !FLATTENED
        printf(" (%d, %d) ", path.row[i], path.col[i]); 
        #endif
    printf(" ]\n");
    printf("size vett percorso: %d\n", percorso.size);
    printf("i: %d\n", contatore);
    printf("[ ");
    for(int j=0; j<percorso.size; j++) 
        #if FLATTENED
        printf(" %d", percorso.data[j]);
        #endif
        #if !FLATTENED
        printf(" (%d, %d) ", percorso.row[j], percorso.col[j]);
        #endif
    printf(" ]\n");
    printf("numero bonus: %d\n", bonus);
    #endif


    //Caso base
    #if FLATTENED
    if (position.col == fine.col && position.row == fine.row) return 1000-contatore+10*bonus;
    #endif
    #if !FLATTENED
    if (position.col == fine.col && position.row == fine.row) return 1000-contatore+10*bonus;
    #endif

    if (punto_valido(map, position, percorso, T)){
        #if FLATTENED
        if (map.map[position.row*map.col + position.col] == '$') bonus++;
        if (map.map[position.row*map.col + position.col] == '!') bonus = bonus/2;
        if (map.map[position.row*map.col + position.col] == 'T') T+=3;
        if (map.map[position.row*map.col + position.col] == '#') T-=1;
        percorso.data[contatore] = position.row*map.col + position.col;
        #endif
        #if !FLATTENED
        if (map.map[position.row][position.col] == '$') bonus++;
        if (map.map[position.row][position.col] == '!') bonus = bonus/2;
        if (map.map[position.row][position.col] == 'T') T+=3;
        if (map.map[position.row][position.col] == '#') T-=1;
        percorso.col[contatore] = position.col;
        percorso.row[contatore] = position.row;
        #endif
        vector_t punteggi;
        punteggi.size = 4;
        punteggi.data = calloc(sizeof(int), punteggi.size);
        
        /**
         * punteggi.data:
         * 0: vado a destra (col+1)
         * 1: vado giu (riga+1)
         * 2: vado a sinistra(col-1)
         * 3: vado su (riga-1)
        */
        if (++position.col >= map.col) punteggi.data[0] = 0;
        else punteggi.data[0] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, max_p);
        position.col--;
        scambia_punteggio_max(punteggi.data[0], path, percorso, max_p);
        elimina_piu(percorso, contatore);

        if (++position.row >= map.row) punteggi.data[1] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, max_p);
        position.row--;
        scambia_punteggio_max(punteggi.data[1], path, percorso, max_p);
        elimina_piu(percorso, contatore);

        if (--position.col < 0) punteggi.data[2] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T,max_p);
        position.col++;
        scambia_punteggio_max(punteggi.data[2], path, percorso, max_p);
        elimina_piu(percorso, contatore);

        if (--position.row < 0) punteggi.data[3] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, max_p);
        position.row++;
        scambia_punteggio_max(punteggi.data[3], path, percorso, max_p);
        elimina_piu(percorso, contatore);

        #if DEBUG
        for (int i=0; i<4; i++) printf("punteggio %d: %d\n", i, punteggi.data[i]);
        #endif

        int a = max(punteggi);
        free(punteggi.data);

        #if DEBUG
        printf("massimo dei punteggi: %d", a);
        #endif

        return a;
    }
    else return 0;
}