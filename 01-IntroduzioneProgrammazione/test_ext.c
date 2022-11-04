#include<stdio.h>
#define lunghezza 4
#define lunghezza1 4

void f(int array[lunghezza1][lunghezza]){
    for (int i =0, j=0; i<lunghezza; i++){
        printf("%d", array[i][j++]);
    }
}

