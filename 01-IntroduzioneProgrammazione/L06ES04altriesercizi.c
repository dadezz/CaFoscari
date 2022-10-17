#include <stdio.h>
#include <math.h>


    /*
    * Scrivere una funzione che restituisca 1 se e solo se esistono 2 interi positivi
    * tali a,b tali che 𝑎2 +𝑏2 =25, e che restituisca 0 altrimenti.7
    */
int venticinque (){
    _Bool esistono = 0;
    for (int i=0; i<25 && !esistono; i++){
        for (int j=i; j<25 && !esistono; j++){
            if (i*i + j*j == 25) esistono = 1; 
        }
    }
    return esistono;
}

    /*
    *Scrivere una funzione che restituisca 1 se e solo se esistono 3 interi positivi
    *tali a,b,c minori di 100 e tali che 𝑎4 +𝑏3 =𝑐2 , e 0 altrimenti
    */

int congettura (){
    _Bool esistono = 0;
    for (int i=0; i<100 && !esistono; i++){
        for (int j=i; j<100 && !esistono; j++){
            for (int z=j; z<100 && !esistono; z++)
                if (pow(i,4) + pow(j,3) == pow(z,2)) esistono = 1; 
        }
    }
    return esistono;
}

    /*
    * dato un numero N in input 
    * scrivere una funzione che dia il seguente ourput (N righe)
    * +
    * ++
    * +++
    * ++++
    * +++++
    * ++++++
    * etc
    */

void piramide (){
    int N;
    printf("inserisci numero: ");
    scanf("%d", &N);

    for (int i=1; i<=N; i++){
        for (int j=1; j<=i; j++){
            printf("+");
        }
        printf("\n");
    }
}

int main(){
    /*
    * Scrivere un programma che visualizzi tutti i numeri tra 2000 e 2200 (estremi
    * inclusi) che sono divisibili per 7 ma che non sono multipli di 5
    */
    
    for (int i = 2000; i<=2200; i++){
        if (i%7 == 0 && i%5 != 0){
            printf("%d\n", i);
        }
    }
    
    return 0;
}