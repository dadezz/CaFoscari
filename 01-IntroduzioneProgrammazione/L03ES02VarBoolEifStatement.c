#include<stdio.h>

int main1(){
    int a=10, b=43, c=278; 

    // && è l'operatore logico "e"
    if (a>b && a>c) printf("%d", a);
    else if (b>a && b>c) printf("%d", b);
    else printf("%d", c);

    return 0;
}

/* Gli operatori logici sono:
< minore
> maggiore
== uguale
!= diverso
! not
&& e
& e bit per bit
|| or
*/

int main2(){
    // un metodo un fià più facile da leggere per far la stessa cosa, senza troppi if:
    int a=10, b=43, c=278;
    int max = a;

    if (b>max) max = b;
    if (c>max) max = c;
    printf("%d", max);

    return 0;
}

//BOOLEANI

int main3 (){
    _Bool falso = 0;
    _Bool vero = 1;
    _Bool nuovamenteVero = 34568752;
    // per il linguaggio c, un valore == 0 è identificato come falso.
    // qualsiasi altro valore ha significato logico "vero".
}

#include<stdbool.h>

/* libreria molto easy per quello che ci serve. Aggiunge il tipo bool come sinonimo di Bool
e le parole "true" e "false" ad indicare i valori 1 e 0. 
Se si stampa una variabile booleana vera, si ottiene sempre il valore 1
*/

int main (){
    bool vero = true;
    int veron = 1343;
    bool falso = false;
    int falson = 0;
    if (1) printf ("vero con 1\n");
    else printf("errore");
    if (2) printf ("vero con 2\n");
    else printf("errore");
    if (true) printf ("vero con ture\n");
    else printf("errore");
    if (vero) printf ("vero con variabile true\n");
    else printf("errore");
    if (veron) printf ("vero con variabile intera diversa da 0\n");
    else printf("errore");
    if (!falso) printf("vero con negazione del falso in var bool\n");
    else printf("errore");
    if (!false) printf ("vero con negazione del falso in bool\n");
    else printf("errore");
    if (!0) printf("vero con !0\n");
    else printf("errore");
    if (!falson) printf ("vero con !variabile intera = 0\n");
    else printf("errore");

    return 0;
}