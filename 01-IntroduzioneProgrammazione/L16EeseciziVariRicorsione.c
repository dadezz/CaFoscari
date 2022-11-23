#include<stdio.h>
/*
Scrivere una funzione ricorsiva che dato un array di interi 𝑣, restituisca la somma di tutti gli elementi
all’intero
*/
int somma(int *v, int l){
    if (l==1) return v[0];
    return somma(v, l-1) + v[l-1];
}

int main1(){
    int v[] = {1,2,3,4,5,6,7,8,9,10};
    int sum = somma(v, 10);
    printf("%d\n", sum);
    return 0;
}

/*
Scrivere una funzione ricorsiva che, dati due array di interi v1 e v2, restituisce 1 se il primo array è
uguale al secondo in ordine inverso, e 0 altrimenti.
*/
int inversi(int* v1, int* v2, int l){
    //caso base: v[+l]==v[-l];
    if (l==1) return *(v1)==v2[l-1];
    else return (*(v1)==v2[l-1] && inversi(v1+1, v2, l-1));
}
int main2(){
    int v1[] = {1,2,3,4,5,6,7,8,9,10};
    int v2[] = {10,9,8,7,6,5,4,3,2,1};
    int ris = inversi(v1, v2, 10);
    printf("%d\n", ris);
    return 0;
}

/*
Travelling Salesman Problem (TSP):
Given a set of cities and their geographic coordinates, the problem is to find the length of the shortest
possible route that visits every city exactly once and returns to the starting point. (variant: print the
shortest route)
*/
float tsp(int* x, int* y, int* r, ){

}
int main (){
    int X[] = {1,2,5,9,6};
    int Y[] = {1,3,5,4,5};
    int R[] = {1,2,3,4};
    printf("%f \n", tsp(X,Y, 0, R, 4) );
    return 0;
}