#include <stdlib.h>
#include<stdio.h>

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
   
    printf("%d\n", inizio);
    map[inizio]='+';
    stampa(map, r, c);
    printf("\n%d\n    ", path[1]);
    if (inizio==fine) return inizio;
    if (map[inizio+1] != '#' && map[inizio+1] != '+')
        path[1] = risoluzione_ricorsiva(map, path+1, c, r, inizio+1, fine, lunghezza_path-1);
    if (map[inizio+c] != '#' && map[inizio+c] != '+')
        path[1] = risoluzione_ricorsiva(map, path+1, c, r, inizio+c, fine, lunghezza_path-1);
    if (map[inizio-c] != '#' && map[inizio-c] != '+')
        path[1] = risoluzione_ricorsiva(map, path+1, c, r, inizio-c, fine, lunghezza_path-1);
    if (map[inizio-1] != '#' && map[inizio-1] != '+')
        path[1] = risoluzione_ricorsiva(map, path+1, c, r, inizio-1, fine, lunghezza_path-1);

    return inizio;
}





























int soluzione_easy(char* map, int *path, int inizio, int fine, int lunghezza_path, int c, int r){
    sleep(1);
    map[inizio]='+';
    stampa(map, r, c);
    if (inizio==fine) return inizio;
    path[1] = soluzione_easy(map, path+1, inizio+1, fine, lunghezza_path-1, c, r);
    return inizio;
}


int main(){
    int c=4, r=3;
    char map[] = {'#','#','#','#',
                  'o',' ',' ','_',
                  '#','#','#','#',
                };
    stampa(map, r, c);
    int* path = (int*) calloc(c, sizeof(int));
    int inizio = find_char(map, c*r, 'o');
    int fine = find_char(map, c*r, '_');
    path[0] = soluzione_easy(map, path, inizio, fine, c, c, r);
    for(int i=0; i<c; i++) printf("%d\n",path[i]);
}








int main1(){
    
    int default_rows = 10, default_columns = 7;
    char default_map[] =  {'#','#','#','#','#','#','#',
                           'o',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ',' ',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','_',
                           '#','#','#','#','#','#','#'};
    
    stampa(default_map, default_rows, default_columns);
    int* path = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');


    path[0] = risoluzione_ricorsiva(default_map, path, default_columns, default_rows, inizio, fine, default_columns*default_rows);
    for(int i=0; i<default_columns*default_rows; i++) printf("%d\n",path[i]);

    return 0;
}