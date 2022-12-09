#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    char* map;
    int row;
    int col;
} board_t;

void stampa(board_t map) {
    //stampo il labirinto, compresi i più del percorso, senza però modificare la mappa
    for (int i=0; i<map.row; i++){
        for (int j=0; j<map.col; j++){
            printf("%c ", map.map[i*map.col + j]);
        }
        printf("\n");
    }
}

bool mappe_diverse(board_t map1, board_t map2){
    for (int i = 0; i<map1.col*map2.row; i++){
        if (map1.map[i] != map2.map[i]){
            return true;
        }
    }
    return false;
}

bool muro(board_t map, int p){
    if (map.map[p] == '#' || map.map[p] == '3' || map.map[p] == '@')
        return true;
    else return false;
}

bool vicolo_cieco (board_t map, int i){
    if (muro(map, i+1) && muro(map, i+map.col) && muro(map, i-1) && !muro(map, i-map.col) ||
        muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && muro(map, i-map.col) ||
        muro(map, i+1) && !muro(map, i+map.col) && muro(map, i-1) && muro(map, i-map.col) ||
        !muro(map, i+1) && muro(map, i+map.col) && muro(map, i-1) && muro(map, i-map.col)){
        return true;
    }
    else return false;
}

bool angolo_libero(board_t map, int i){
    if ( (muro(map, i+1) && muro(map, i-map.col) && !muro(map, i-1) && !muro(map, i+map.col) && !muro(map, i+map.col-1)) ||
         (muro(map, i-1) && muro(map, i-map.col) && !muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i+map.col+1)) ||
         (muro(map, i-1) && muro(map, i+map.col) && !muro(map, i+1) && !muro(map, i-map.col) && !muro(map, i-map.col+1)) ||
         (muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && !muro(map, i-map.col-1))   ){
            return true;
         }
    else return false;
}

bool doppia_fila(board_t map, int i){
    if (muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && muro(map, i+1+map.col) && !muro(map, i+map.col-1) && !muro(map, i-1-map.col) && muro(map, i-map.col+1) ||
        !muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i-1) && muro(map, i-map.col) && !muro(map, i+1+map.col) && !muro(map, i+map.col-1) && muro(map, i-1-map.col) && muro(map, i-map.col+1) ||
        !muro(map, i+1) && !muro(map, i+map.col) && muro(map, i-1) && !muro(map, i-map.col) && !muro(map, i+1+map.col) && muro(map, i+map.col-1) && muro(map, i-1-map.col) && !muro(map, i-map.col+1) ||
        !muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && muro(map, i+1+map.col) && muro(map, i+map.col-1) && !muro(map, i-1-map.col) && !muro(map, i-map.col+1) ){
        return true;
    }
    else return false;
}

void isola_oggetti(board_t map){
    for (int i=map.col; i<map.col*map.row-map.col; i++){
        if (map.map[i] != '#' && map.map[i] != ' ' && map.map[i] != '2'){

            if(map.map[i+1] == ' ') map.map[i+1] = '2';
            if(map.map[i+map.col] == ' ') map.map[i+map.col] = '2';
            if(map.map[i+1+map.col] == ' ') map.map[i+1+map.col] = '2';
            if(map.map[i+map.col-1] == ' ') map.map[i+map.col-1] = '2';
            if(map.map[i-1] == ' ') map.map[i-1] = '2';
            if(map.map[i-map.col] == ' ') map.map[i-map.col] = '2';
            if(map.map[i-1-map.col] == ' ') map.map[i-1-map.col] = '2';
            if(map.map[i-map.col+1] == ' ') map.map[i-map.col+1] = '2';
        }
    }
}


void riduci(board_t map){
    stampa(map);
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if (angolo_libero(map, i)) {
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if (doppia_fila(map,i)) { 
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
        stampa(map);
    }
}

void elimina_vicoli_ciechi(board_t map){
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if(vicolo_cieco(map, i)){
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
        stampa(map);
    }
}

void rimetti_spazi(board_t map){
    for (int i = 0; i<map.row*map.col; i++){
        if (map.map[i] == '2') map.map[i] = ' ';
    }
}

bool muraglia(board_t map, int i){
    if (muro(map, i+1) && 
        muro(map, i-1) && 
        muro(map, i+map.col) && 
        muro(map, i-map.col) && 
        muro(map, i+1+map.col) && 
        muro(map, i-1-map.col) && 
        muro(map, i+map.col-1) && 
        muro(map, i-map.col+1)){
            return true;
    }
    else return false;
}

void elimina_tre_inutili(board_t map){
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == '3' || map.map[i] == '#'){
                if(muraglia(map, i)){
                    map.map[i] = '@';
                    trovato = true;
                }
            }
        }
        stampa(map);
    }
}

board_t copia_mappa (board_t map){
    board_t copia_map;
    copia_map.row = map.row;
    copia_map.col = map.col;
    copia_map.map = (char*) malloc((sizeof(char) * copia_map.row*copia_map.col));
    if (copia_map.map == NULL) exit(EXIT_FAILURE);
    return copia_map;
}

int riduzione(board_t map){
    
    isola_oggetti(map);
    board_t copia_map = copia_mappa(map);
    do {
        for(int i=0; i<copia_map.row*copia_map.col; i++){
            copia_map.map[i] = map.map[i];
        }
        riduci(map);
        elimina_vicoli_ciechi(map);
        riduci(map);
    } while(mappe_diverse(map, copia_map));
    free(copia_map.map);
    elimina_tre_inutili(map);
    rimetti_spazi(map);
    stampa(map);
    return 0;
}