#include<stdio.h>
#include "test_ext.c"

#define lunghezza 4
#define lunghezza1 4

extern void f(int array[lunghezza1][lunghezza]);
int main(){
    int prova[][lunghezza] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};

    f(prova);

    return 0;

}