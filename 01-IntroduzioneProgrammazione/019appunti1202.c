/**
 * STRUCT
 * 
 * 
 * al posto di passare in funzioni l'array, le colonne e le righe, posso passare uno struct che 
 * abbia dentro tutte le informazioni relative al labirinto in questione in una sola variabile
 * 
*/


//per esempio, una funzinoe che mi iscrive un dato carattere a una data coordinata è
void plott(char* map, int x, int y, int col, char c){
    map[x+y*col] = c;
}

// si può usare una struct piuttosto. all'interno può avere il pointer ai caratteri, righe e colonne.
struct board_t{
    char* map;
    int col;
    int r;
};
//le struct sono una forma primitiva di oggetti

//ecco che ho 
void plottt(struct board_t board, int x, int y, char c){
    board.map[x + y*board.col] = c;
};

//così mi sto passando in copia 3 valori, se non volessi potrei passare solo il pointer, cosi da nondoverli copiare
void plot(struct board_t* board, int x, int y, char c){
    board->map[x + y*board->col] = c;
};

//uso typedef:
struct array_t {
    int* vett;
    int len;
};

typedef struct array_t array; //letteralmente: "array è uguale a dire struct array_t". 
// "array" è un  nome nuovo per il tipo "struct array".

int find_max(array a){
    int max = a.vett[0];
    for (int i=0; i<a.len; ++i){
        if (a.vett[i]>max) max = a.vett[i];
    }
    return max;
}
//quanto è sizeof(struct array_t)?
//int* è 8 byte; int è 4 byte. di conseguenza sizeof(array) = 12 byte.