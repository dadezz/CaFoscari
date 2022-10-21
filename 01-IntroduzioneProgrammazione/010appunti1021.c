#include<stdio.h>

int main (){

    //come togliersi il problema degli array non dinamici?
    /*
    soluzione brutta: farlo sicuramente più grande di quanto serve
    oppure, leggermente più elegante ma comunque motlo brutto, farlo comunque di una misura grande e
    dare un limite all'utente.

    In termini di memoria, si crea un array enrome, srecando memoria. infatti, array di 1024 sono 4kb.
    Oggigiorno, un pc di oggi non sente la differenza, non è nulla, quindi se dovesse servire non è sto gran
    problema. 
    Ad ogni modo, c'è un metodo migliore, usando malloc, ma ne parleremo più avanti.

    Sta cosa comunque c'è su C99, alcuni dialetti più nuovi compilano anche array di misura del tipo
    
    int n;
    scanf("%d", &n);
    int array[n];

    C99 non accetta questa scrittura, perché al momento della compilazione ha bisogno di sapere quanta memoria
    allocare. in questo caso, invece, la variabile n prende valore solo dopo lo scan (quindi ovviamente dopo la 
    compilazione).

    
    */

    return 0;
}