#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

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

int risoluzione_ricorsiva(char* map, int *path, int c, int r, int inizio, int fine, int lunghezza_path){
    /**
     * se inizio coincide con la fine, ritorno la mia attuale posizione come elemento di path
    */

    //appunto sul path: in questo caso registravo le posizioni invece degli spostamenti, ma il succo non cambia 

    //printf("%d\n", inizio);
    //sleep(1);
    map[inizio]='+';
    stampa(map, r, c);

    path[0] = inizio;
    if (*path==fine) return inizio;
    if (map[inizio+1] != '#' && map[inizio+1] != '+')
        inizio = risoluzione_ricorsiva(map, path+1, c, r, inizio+1, fine, lunghezza_path-1);
    if (map[inizio+c] != '#' && map[inizio+c] != '+')
        inizio = risoluzione_ricorsiva(map, path+1, c, r, inizio+c, fine, lunghezza_path-1);
    if (map[inizio-c] != '#' && map[inizio-c] != '+')
        inizio = risoluzione_ricorsiva(map, path+1, c, r, inizio-c, fine, lunghezza_path-1);
    if (map[inizio-1] != '#' && map[inizio-1] != '+')
        inizio = risoluzione_ricorsiva(map, path+1, c, r, inizio-1, fine, lunghezza_path-1);
    return inizio;
}

int main(){
    
    int default_rows = 10, default_columns = 7;
    char default_map[] =  {'#','#','#','#','#','#','#',
                           'o',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#','#','#','#',
                           '#',' ',' ',' ',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','_',
                           '#','#','#','#','#','#','#'};
    
    stampa(default_map, default_rows, default_columns);
    int* path = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');

    risoluzione_ricorsiva(default_map, path, default_columns, default_rows, inizio, fine, default_columns*default_rows);

    size_t size = 0;
    for (int j=0; j<default_columns*default_rows; j++) if (path[j]!=0) ++size;
    path = realloc(path, size*sizeof(int));
    for(int i=0; i<size; i++) printf("%d -> ",path[i]);
    free(path);
    return 0;
    
}
