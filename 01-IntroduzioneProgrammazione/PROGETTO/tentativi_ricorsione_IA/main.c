#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>

int max_p = 0;
struct board{
    char** map;
    int row;
    int col;
};
struct vector{
    int* data;
    size_t size;
};
struct position_vector{
    int* col;
    int* row;
    size_t size;
};
struct position{
    int row;
    int col;
};
typedef struct board board_t;
typedef struct vector vector_t;
typedef struct position_vector pvec_t;
typedef struct position position_t;


position_t find_char(board_t map, char c){
    position_t p;
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            if (map.map[i][j] == c) {
                p.row = i;
                p.col = j;
                return p;
            }
        }
    }
}
int v_size(pvec_t x){
    int size = 0;
    for (int i=0; i<x.size; i++) {
        if (x.col[i] + x.row[i] == 0) break;
        size++;
    }
    return size;
}
int max(vector_t x){
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
    int s = v_size(percorso);
    for (int i = x+1; i<s; i++) {
        percorso.col[i] = 0;
        percorso.row[i] = 0;
    }
}
void scambia_punteggio_max(int punteggio, pvec_t path, pvec_t percorso){
    if (punteggio > max_p){
        max_p = punteggio;
        for (int i = 0; i<v_size(percorso); i++) {
            path.col[i] = percorso.col[i];
            path.row[i] = percorso.row[i];
        }
    }
}
int numero_percorsi(board_t map, pvec_t percorso, pvec_t path, position_t position, position_t fine, int contatore, int bonus, int T){
    stampa_piu(map, percorso);
    printf("position: (%d, %d)\n", position.row, position.col);
    printf("max: %d ", max_p);
    printf("[ ");
    for(int i=0; i<v_size(path); i++)
        printf(" (%d, %d) ", path.row[i], path.col[i]); 
    printf(" ]\n");
    printf("size vett percorso: %d\n", v_size(percorso));
    printf("i: %d\n", contatore);
    printf("[ ");
    for(int j=0; j<v_size(percorso); j++) 
        printf(" (%d, %d) ", percorso.row[j], percorso.col[j]);
    printf(" ]\n");
    printf("numero bonus: %d\n", bonus);

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
        if (position.col++ > map.col) punteggi.data[0] = 0; //controlla meglio sta parte, che non funziona.
        else punteggi.data[0] = numero_percorsi(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.col--;
        scambia_punteggio_max(punteggi.data[0], path, percorso);
        elimina_piu(percorso, contatore);

        if (position.row++ > map.row) punteggi.data[1] = 0;
        else punteggi.data[1] = numero_percorsi(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.row--;
        scambia_punteggio_max(punteggi.data[1], path, percorso);
        elimina_piu(percorso, contatore);

        if (position.col-- < 0) punteggi.data[2] = 0;
        else punteggi.data[1] = numero_percorsi(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.col++;
        scambia_punteggio_max(punteggi.data[2], path, percorso);
        elimina_piu(percorso, contatore);

        if (position.row-- > map.row) punteggi.data[3] = 0;
        else punteggi.data[1] = numero_percorsi(map, percorso, path, position, fine, contatore+1, bonus, T);
        position.row++;
        scambia_punteggio_max(punteggi.data[3], path, percorso);
        elimina_piu(percorso, contatore);

        for (int i=0; i<4; i++) printf("punteggio %d: %d\n", i, punteggi.data[i]);
        int a = max(punteggi);
        free(punteggi.data);
        printf("massimo dei punteggi: %d", a);
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
    default_map.row = 10;
    default_map.col = 6;
    default_map.map = (char**) malloc((sizeof(char*) * default_map.row));
    if (default_map.map == NULL) exit(EXIT_FAILURE);

    for(int i=0; i<default_map.row; i++){
        default_map.map[i] = (char*) malloc(sizeof(char)* default_map.col);
        if (default_map.map[i] == NULL) {
            exit(EXIT_FAILURE);
        }
        for (int j=0; j<default_map.col; j++) {
            default_map.map[i][j]= mappa_di_prova[j+i*default_map.col];
        }   
    }
    position_t inizio = find_char(default_map, 'o');
    printf("inizio: (%d, %d)\n", inizio.row, inizio.col);
    position_t fine = find_char(default_map, '_');
    printf("fine: (%d, %d)\n", fine.row, fine.col);
    
    pvec_t percorso;
    percorso.size = default_map.row * default_map.col;
    percorso.col = (int*)calloc(percorso.size, sizeof(int));
    percorso.row = (int*)calloc(percorso.size, sizeof(int));

    pvec_t path;
    path.size = default_map.row * default_map.col;
    path.col = (int*)calloc(path.size, sizeof(int));
    path.row = (int*)calloc(path.size, sizeof(int));

    int percorsi_possibili = numero_percorsi(default_map, percorso, path, inizio, fine, 0, 0, 0);
    printf("\n percorsi possibili: %d\n", percorsi_possibili);
    
    free(percorso.col);
    free(percorso.row);
    bool f = false;
    size_t size = 0;
    for (int j=0; j<path.size && !f; j++){
        if (path.col[j] == fine.col || (path.col[j] == 0 && path.row[j]==0)) f = true;
        ++size;
    }
    path.size = size;
    path.col = realloc(path.col, path.size*sizeof(int));
    path.row = realloc(path.row, path.size*sizeof(int));
    for(int i=0; i<size; i++) printf("(%d, %d) -> ", path.row[i], path.col[i]);

    printf("\n");
    stampa_piu(default_map, path);
    free(path.col);
    free(path.row);
    return 0;
}