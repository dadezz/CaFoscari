#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>

void stampa(char* map, int r, int c){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
        printf("%c ", map[i*c+j]);
        }
        printf("\n");
    }
}
int find_char(char* map, int size, char c_to_be_found){
    //trova la posizione di un carattere specifico all'interno della mappa
    for (int i=0; i<size; i++) if (map[i]==c_to_be_found) return i;
}


bool punto_valido(char* map, int position){
    return map[position] == ' ' || map[position] == 'o' || map[position] == '_';
}

bool esiste_percorso(char* map, int position, int fine, int c, int* path){
    /**
     * per quanto concerne il path: 
     * 1 significa NORD (mi son spostato verso l'alto)
     * 2 significa EST (mi son spostato verso destra)
     * 3 significa SUD (mi son spostato verso il basso)
     * 4 significa OVEST (mi son spostato verso sinistra)
    */
    if (punto_valido(map, position)){
       
       if (position==fine) return true; //caso base
       
       map[position] = '+'; //marco con un + il mio percorso
       
       //inizio guardando a destra
       bool esiste = esiste_percorso(map, position+1, fine, c, path+1); 
       if (esiste) *path = 2;
       //se non esiste la possibilità di andare a destra, vado in basso
       if(!esiste) {
           esiste = esiste_percorso(map, position+c, fine, c, path+1);
           *path  = 3;
       }
       //se non esiste la possibilità di andare in basso, vado in alto
       if(!esiste){
           esiste = esiste_percorso(map, position-c, fine, c, path+1);
           *path = 1;
       }
       //se non esiste la possibilità di andare in alto, vado a sinistra
       if(!esiste) {
           esiste = esiste_percorso(map, position-1, fine, c, path+1);
           *path = 4;
       }

       return esiste;
    }
}



int main(){
    
    int default_rows = 10, default_columns = 7;
    char default_map[] =  {'#','#','#','#','#','#','#',
                           'o',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#','#','#','#',
                           '#',' ',' ',' ',' ',' ','#',
                           '#',' ',' ','#',' ','#','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','_',
                           '#','#','#','#','#','#','#'};
    
    stampa(default_map, default_rows, default_columns);
    int* path = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');

    int a = esiste_percorso(default_map, inizio, fine, default_columns, path);
    printf("eiste percorso: %d\n", a);
    stampa(default_map, default_rows, default_columns);

    size_t size = 0;
    for (int j=0; j<default_columns*default_rows; j++) if (path[j]!=0) ++size;
    path = realloc(path, size*sizeof(int));
    for(int i=0; i<size; i++) printf("%d -> ",path[i]);
    free(path);
    return 0;
    
}