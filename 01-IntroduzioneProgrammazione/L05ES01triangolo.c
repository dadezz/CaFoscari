/*
Scrivere una funzione che dati 3 lunghezze che restituisca 1 se possono
essere i lati di un triangolo e 0 altrimenti
*/

#include<stdio.h>

int triangolo (float a, float b, float c){
    if (((a+b)>c) && ((a+c)>b) && ((c+b)>a)) return 1;
    else return 0;
}
