#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
#define DEBUG 0

int max_p = 0; //variabile globale col punteggio migliore

struct board{
    /**
     * array bidimensionale per la mappa
     * numero di righe e colonne
    **/
    char** map;
    int row;
    int col;
};
struct vector{
    /**
     * vettore normale:
     * si porta dietro array e dimensione
    */
    int* data;
    size_t size;
};
struct position_vector{
    /**
     * vettore di posizioni:
     * si porta dietro i due array per le due coordinate
     * e la dimensione
    */
    int* col;
    int* row;
    size_t size;
};
struct position{
    /**
     * punto sulla mappa
     * due coordinate
    */
    int row;
    int col;
};
typedef struct board board_t;
typedef struct vector vector_t;
typedef struct position_vector pvec_t;
typedef struct position position_t;

void stampa_direzioni(pvec_t p){
    for (int i=1; i<p.size; i++){
        if (p.col[i] == p.col[i-1]){
            if (p.row[i] - p.row[i-1] == 1) printf("S ");
            else printf("N ");
        }
        else if(p.col[i] - p.col[i-1] == 1) printf("E ");
        else printf("O ");
    }
}
position_t find_char(board_t map, char c){
    //trova la posizione di un dato carattere all'interno del labirinto
    //se non viene trovato, viene restituita la posizione (-1, -1)
    position_t p;
    bool controllo = false;
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            if (map.map[i][j] == c) {
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
bool not_in(pvec_t percorso, position_t pos){
    //controllo se sono già passato sull'attuale posizione
    //( => no loop infiniti )
    bool a = true;
    for (int i=0; i<percorso.size && a; i++) 
        if (percorso.row[i] == pos.row && percorso.col[i] == pos.col) 
            a = false;
    return a;
}
void stampa_piu(board_t map, pvec_t percorso){
    //stampo il labirinto, compresi i più del percorso, senza però modificare la mappa
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            position_t pos;
            pos.row = i;
            pos.col = j;
            if (not_in(percorso, pos)) printf("%c ", map.map[i][j]);
            else printf("+ ");
        }
        printf("\n");
    }
}
bool punto_valido(board_t map, position_t p, pvec_t percorso, int T){
    //un punto è valido se non ci sono passato sopra prima e se non è un muro    
    if (T==0) return map.map[p.row][p.col] != '#' && not_in(percorso, p);
    else return not_in(percorso, p);
}
void elimina_piu(pvec_t percorso, int x){
    //quando torno indietro, elimino gli ultimi passi che ho fatto dall'array, sovrascrivendoli con zeri
    int s = percorso.size;
    for (int i = x+1; i<s; i++) {
        percorso.col[i] = 0;
        percorso.row[i] = 0;
    }
}
void scambia_punteggio_max(int punteggio, pvec_t path, pvec_t percorso){
    //cambio la variabile globale punteggio_max ogni volta che trovo un 
    //percorso migliore del migliore precedentemente trovato
    if (punteggio > max_p){
        max_p = punteggio;
        for (int i = 0; i<percorso.size; i++) {
            path.col[i] = percorso.col[i];
            path.row[i] = percorso.row[i];
        }
    }
}
int best_percorso(board_t map, pvec_t percorso, pvec_t path, position_t position, position_t fine, int contatore, int bonus, int T){
    //funzione effettiva
    #if DEBUG
    sleep(1);
    stampa_piu(map, percorso);
    printf("position: (%d, %d)\n", position.row, position.col);
    printf("max: %d ", max_p);
    printf("[ ");
    for(int i=0; i<path.size; i++)
        printf(" (%d, %d) ", path.row[i], path.col[i]); 
    printf(" ]\n");
    printf("size vett percorso: %d\n", percorso.size);
    printf("i: %d\n", contatore);
    printf("[ ");
    for(int j=0; j<percorso.size; j++) 
        printf(" (%d, %d) ", percorso.row[j], percorso.col[j]);
    printf(" ]\n");
    printf("numero bonus: %d\n", bonus);
    #endif

    //Caso base
    if (position.col == fine.col && position.row == fine.row) return 1000-contatore+10*bonus;
    if (punto_valido(map, position, percorso, T)){
        if (map.map[position.row][position.col] == '$') bonus++;
        if (map.map[position.row][position.col] == '!') bonus = bonus/2;
        if (map.map[position.row][position.col] == 'T') T+=3;
        if (map.map[position.row][position.col] == '#') T-=1;
        percorso.col[contatore] = position.col;
        percorso.row[contatore] = position.row;
        vector_t punteggi;
        punteggi.size = 4;
        punteggi.data = calloc(sizeof(int), punteggi.size);
        /**
         * 0: vado a destra (col+1)
         * 1: vado giu (riga+1)
         * 2: vado a sinistra(col-1)
         * 3: vado su (riga-1)
        */
        if (++position.col >= map.col) punteggi.data[0] = 0;
        else punteggi.data[0] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.col--;
        scambia_punteggio_max(punteggi.data[0], path, percorso);
        elimina_piu(percorso, contatore);

        if (++position.row >= map.row) punteggi.data[1] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.row--;
        scambia_punteggio_max(punteggi.data[1], path, percorso);
        elimina_piu(percorso, contatore);

        if (--position.col < 0) punteggi.data[2] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.col++;
        scambia_punteggio_max(punteggi.data[2], path, percorso);
        elimina_piu(percorso, contatore);

        if (--position.row < 0) punteggi.data[3] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.row++;
        scambia_punteggio_max(punteggi.data[3], path, percorso);
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
    board_t default_map;
    // inizializzazione con valori di default, nel programma POSSONO essere presi in input 
    default_map.row = 10;
    default_map.col = 6;
    default_map.map = (char**) malloc((sizeof(char*) * default_map.row));
    if (default_map.map == NULL) errore();
    for(int i=0; i<default_map.row; i++){
        default_map.map[i] = (char*) malloc(sizeof(char)* default_map.col);
        if (default_map.map[i] == NULL) errore ();
        for (int j=0; j<default_map.col; j++) {
            default_map.map[i][j]= mappa_di_prova[j+i*default_map.col];
        }   
    }

    //trovo inizio e fine. se fallisco, libero memoria allocata e esco dal programma
    position_t inizio = find_char(default_map, 'o');
    if (inizio.col == -1) {
        for (int i=0; i<default_map.row; i++){
            free(default_map.map[i]);
        }
        free(default_map.map);
        printf("inizio non trovato\n");
        exit(EXIT_FAILURE);
    }
    position_t fine = find_char(default_map, '_');
    if (fine.col == -1) {
        for (int i=0; i<default_map.row; i++){
            free(default_map.map[i]);
        }
        free(default_map.map);
        printf("fine non trovato\n");
        exit(EXIT_FAILURE);
    }

    #if DEBUG
    printf("inizio: (%d, %d)\n", inizio.row, inizio.col);
    printf("fine: (%d, %d)\n", fine.row, fine.col);
    #endif
    

    //percorso è l'array con tutte le coordinate del percorso tentato per ogni albero
    //(quindi cambia a ogni chiamata di funzione ricorsiva)
    pvec_t percorso;
    percorso.size = default_map.row * default_map.col; //massima lunghezza possibile
    percorso.col = (int*)calloc(percorso.size, sizeof(int));
    if (percorso.col == NULL) errore ();
    percorso.row = (int*)calloc(percorso.size, sizeof(int));
    if (percorso.row == NULL) errore ();

    //path è l'array con il percorso definitivo.
    //nella funzione, quando viene trovato un percorso con punteggio maggiore del 
    //precedente, path assume i valori di percorso corrispondente
    pvec_t path;
    path.size = default_map.row * default_map.col; //massima lunghezza possibile
    path.col = (int*)calloc(path.size, sizeof(int));
    if (path.col == NULL) errore ();
    path.row = (int*)calloc(path.size, sizeof(int));
    if (path.row == NULL) errore ();
    
    //chiamata di funzione
    best_percorso(default_map, percorso, path, inizio, fine, 0, 0, 0);
    printf("\n miglior punteggio: %d\n", max_p);
    
    //libero percorso, non mi serve più
    free(percorso.col);
    free(percorso.row);

    //calcolo la lunghezza effettiva del path e realloco di conseguenza
    bool f = false;
    size_t size = 0;
    for (int j=0; j<path.size && !f; j++) {
        size++;
        if (path.col[j] == 0 && path.row[j] == 0) break;
    };
    path.size = size;
    path.col[size-1] = fine.col;
    path.row[size-1] = fine.row;
    path.col = realloc(path.col, path.size*sizeof(int));
    if (path.col == NULL) errore ();
    path.row = realloc(path.row, path.size*sizeof(int));
    if (path.row == NULL) errore ();

    //stampo le posizioni
    printf("percorso:   ");
    for(int i=0; i<size; i++) {
        if (i!=size-1) printf("(%d, %d) -> ", path.row[i], path.col[i]);
        else printf("(%d, %d)", path.row[i], path.col[i]);
    }
    printf("\n");

    //stampo le mosse
    printf("mosse effettuate:   ");
    stampa_direzioni(path);
    printf("\n");


    //stampo il labirinto
    stampa_piu(default_map, path);
    
    //libero il resto
    free(path.col);
    free(path.row);
    for (int i=0; i<default_map.row; i++){
        free(default_map.map[i]);
    }
    free(default_map.map);
    return 0;
}