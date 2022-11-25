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

    if (argc > 1){
        if(string_comparison(argv[1],"--challenge")) play_challenge();
    }
    else {
        int choice_mod = ask_mod(); // Modalità interattiva (1) o IA (0)
        int choice_default = ask_default(); //vuole inserire mappa in input: si (0), no (1)
        if (choice_default == 1) {
            switch (choice_mod){
                case 1: 
                    mod_interactive(default_map, default_rows, default_columns);
                    break;
                case 2:
                    mod_ai(default_map, default_rows, default_columns);
                    break;
            }
        }
        else {
            switch (choice_mod){
                case 1: {
                    int rows, columns;
                    char* map = map_input_creation(&rows, &columns);
                    do_you_need_bonuses(rows*columns, map);
                    mod_interactive(map, rows, columns);
                    free(map);
                    break;
                }
                case 2: {
                    int rows, columns;
                    char* map = map_input_creation(&rows, &columns);
                    do_you_need_bonuses(rows*columns, map);
                    mod_ai(map, rows, columns);
                    free(map);
                    break;
                }
            }
        }
    }    
    return 0;
}