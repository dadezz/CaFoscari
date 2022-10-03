//Dato un intero X, calcolare il suo triplo se X è pari, o il suo quadruplo se X è dispari
#include<stdio.h>

int main (){
    int intero= 425;

    if (intero%2 == 0) printf("pari, quindi il triplo: %d", intero*3);
    else printf("dispari, quindi il quadriplo: %d", intero*4);
    
    return 0;
}