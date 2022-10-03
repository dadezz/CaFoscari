#include<stdio.h>

//Verificare se l’espressione (0.1+0.1+0.1)==0.3 è vera.
 
int main(){
    if ((0.1 + 0.1 + 0.1)==0.3) printf("vero\n");     //double
    else printf ("lmao, volevi, non sono numeri rappresentabili\n");
    if ((0.1f + 0.1f + 0.1f)==0.3f) printf("vero\n"); //float
    else printf ("lmao, volevi, non sono numeri rappresentabili\n");
    return 0;
}