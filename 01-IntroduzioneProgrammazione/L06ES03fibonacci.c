/*
Dato un intero N, calcolare l’N-esimo elemento della successione di Fibonacci
*/
#include<stdio.h>

int main (){
    int numero = 2;
    int fibonacci_prec = 0;
    int fibonacci = 1;
    int temp = fibonacci_prec;
    
    if (numero != 1){
        for (int i = 1; i < numero; i++){
            temp = fibonacci;
            fibonacci += fibonacci_prec;
            fibonacci_prec = temp;
        }
        printf("il %d-esimo numero della successione di fibonacci è: %d\n", numero, fibonacci);
    }
    else printf("il primo numero della successione di fibonacci è: %d\n", fibonacci);



    return 0;
}