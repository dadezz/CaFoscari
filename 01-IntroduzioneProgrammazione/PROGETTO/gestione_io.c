#include <stdio.h>

void print_lab (char x[][19], int righe, int colonne){

    for (int i=0; i<righe; i++){
        for (int j=0; j<colonne; j++){
            printf("%c ", x[i][j]);
        }
        printf("\n");
    } 
}

void scanf_lab (char *x){
    do {
        scanf("%c", x);
    } while( *x != 'w' && *x != 'a' && *x != 's' && *x != 'd');
}

