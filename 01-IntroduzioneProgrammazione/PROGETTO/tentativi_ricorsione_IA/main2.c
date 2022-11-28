#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

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





int main (){
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
}