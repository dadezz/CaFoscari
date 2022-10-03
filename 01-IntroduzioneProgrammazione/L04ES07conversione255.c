#include<stdio.h>
#include<math.h>

int main (){
    // Dato in input un numero intero <=255, visualizzare la sua rappresentazione binaria
    // Il metodo migliore in questo caso penso sia la conversione tramite sottrazioni
    int intero = 37;

    if (intero<=255){
        for (int i=7; i>=0; i--){
            int potenza = pow(2,i);
            if (potenza<=intero){
                printf("%d",1);
                intero -= potenza;
            } 
            else printf("%d",0);
        }
    }
    else {
        printf ("goldonasso, go dito minore di 256!");
        return 0;
    }
    
    return 0;
}