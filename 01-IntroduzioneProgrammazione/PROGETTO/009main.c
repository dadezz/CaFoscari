#include<stdlib.h>
#include<stdio.h>
#include"010funzioni.c"

int main(int argc, char* argv[]){
    srand(time(NULL));
    
    int default_rows = 15, default_columns = 19;
    char default_map[] =  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
                           'o',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',
                           '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','_',
                           '#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',
                           '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'};

    if (argc == 2){
        if(string_comparison(argv[1],"--challenge")) play_challenge();
    }
    else {
        int choice_mod = ask_mod();
        int choice_default = ask_default();
        if (choice_default == 1) {
            switch (choice_mod){
                case 1: 
                    mod_interactive(default_map, default_rows, default_columns, 1);
                    break;
                case 2:
                    mod_ai(default_map, default_rows, default_columns);
                    break;
            }
        }
        else {
            switch (choice_mod){
                case 1: {
                    int columns;
                    int rows;
                    printf("colonne: ");
                    scanf("%d", &columns);
                    printf("righe: ");
                    scanf("%d", &rows);
                    char* map = (char*) malloc((rows*columns)*sizeof(char));
                    if (map == NULL){
                        printf("ERRORE di allocazione memoria (malloc)");
                        exit(EXIT_FAILURE);
                    }
                    map_scan_from_input(map, rows, columns);
                    int x;
                    printf("\nci sono già bonus e imprevisti?(si=1/no=0): ");
                    do {
                        scanf("%d", &x);
                        printf("%d", x);
                    } while (x != 1 && x != 0);
                    _Bool need;
                    printf("\n fuori ciclo%d\n", x);
                    if (x == 'n') {need = 1;}
                    else need = 0;

                    mod_interactive(map, rows, columns, need);
                    break;
                }
                case 2: {
                    int columns;
                    int rows;
                    scanf("%d", &columns);
                    scanf("%d", &rows);
                    char* map = (char*) malloc((rows*columns)*sizeof(char));
                    if (map == NULL){
                        printf("ERRORE di allocazione memoria (malloc)");
                        exit(EXIT_FAILURE);
                    }
                    map_scan_from_input(map, rows, columns);
                    mod_ai(map,rows, columns);
                    break;
                }
            }
        }
    }    
    return 0;
}