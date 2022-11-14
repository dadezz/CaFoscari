#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

/*
dato un array, dire se esiste una coppia di numeri la cui somma è -1
*/

/*
in questo caso uso la ricerca esaustiva
*/

bool coppia (int* v, size_t v_size){
    bool esiste = false;
    for (size_t i = 0; i<v_size && !esiste; i++){
        for (size_t j=i+1; j<v_size && !esiste; j++){
            if (v[i]+v[j]==-1) {
                esiste = true;
            }
        }
    }
    return esiste;
}

int main1(){
    int x[] = {1, 7, 3, 5, -8, 9};
    int s = coppia (x, 6);
    printf("%d\n", s);
}

/*
dato un array, dire se esiste una sottoseequenza la cui somma è 0
*/
int sottoseq_aux (int * v, size_t s, size_t l){
    int somma = 0;
    for (size_t i=0; i<l; i++) somma += v[s+i];
    return somma;
}
bool sottoseq (int* v, size_t v_size){
    bool esiste = false;
    for (size_t i=0; i<v_size-1 && esiste; i++){
        for (size_t len=1; len<v_size-i &&esiste; len++){
            if ( sum_aux(v, i, len) == 0) esiste = true;
        }
    }
    return esiste;
}

//si può fare anche, più carino:

/**
 *  int sottoseq_aux (int * v, size_t l){
 *      int somma = 0;
 *      for (size_t i=0; i<l; i++) somma += v[i];
 *      return somma;
 *  }
 * 
 *  e poi sotto  
 *  if ( sum_aux(v+i, len) == 0) esiste = true;
*/

int main2(){
    int x[] = {1, 7, 3, 5, -8, 9};
    int s = sottoseq (x, 6);
    printf("%d\n", s);
}

//////////////////////////////////////////////////////////////////////////////////////

//                                  RICORSIONE                                      //

//////////////////////////////////////////////////////////////////////////////////////


// CLASSICO ESEMPIO DI FIBONACCI

/**
 * fib (n): 1 se n = 1 o n=2;
 * in tutti gli altri casi sommo i 2 numeri precedenti della serie: fib(n-1) + fib (n-2);
*/

int fib(int n){
    if (n==1 || n==2) return 1;
    else return fib(n-1) + fib(n-2); //si può usare una funnzione non definita?
}
//si può usare una funnzione non definita?
//si, basta in realtà definire nome e tipi di in e out perché vada bene per essere chiamata, 
//percHé il compulatore è gia in grado di eseguire tutti i controlli del caso.

//chiamando fib di 5, ci sono 9 chiamate di funzione.
//ogni volta che aggiungo un cnumero, le chiamate circa raddoppiano (ogni chiamata mi fa 2 hiamate)
// il costo è circa esponeniziale ~ 2^n.
// la ricorsione è spesso più costosa  delle iterzioni(per esempio in questo caso con 2 chiamate, ce ne fosse una sarebbe lineare). 

int fib_iter(int n){
    if (n==1 || n==2) return 1;
    int fib_1 = 1;
    int fib_2 = 1;
    int fib = 1;
    for (int i=3; i<=n; i++){
        fib_1 = fib_2;
        fib_2 = fib;
        fib = fib_1 + fib_2;
    }
    return fib;
}

//in generale, tutte le ricorsive possono essere sostituite dalle iterazioni.
//la ricorsione è chiara da leggere, ma a volte più coostosa. è da decidere di volta in volta se si preferisce la chiarezza o la effcienza

int main3(){
    printf("%d\n", fib(3));
    printf("%d\n", fib(4));
    printf("%d\n", fib(5));
    printf("%d\n", fib(6));
    printf("%d\n", fib(7));
    printf("%d\n", fib(8));
    printf("%d\n", fib(9));
    printf("%d\n", fib(10));
    printf("%d\n", fib(11));
    printf("%d\n", fib(12));
    printf("%d\n", fib(13));
    printf("%d\n", fib(14));
    printf("%d\n", fib(15));
    printf("%d\n", fib(16));
    printf("%d\n", fib(17));
}
// vediamo di usare un opo' la ricorsione.
//somma elementi array

/**
 * somma = v[0] + somma(v[1]....fine])
 * se lunghezza vett == 1, la somma è v[0]
 * 
 * di conseguenza: caso base: v[0]; else: v[0] + somma (altri);
*/

int somma_ric(int * v, size_t l){
    if (l==1) return v[0];
    else return somma_ric(v+1, l-1);//la somma che inizia dall'indice 0+1, (1+1), etc, pl'inizion si sposta di uno in avanti
                                // e di lunghezza via via minore di uno
}

int main4() {
    int x[]={1, 2, 3, 4, 5};
    printf("%d\n", somma(x,5));
}

//tutti psri

/**
 * tutti pari: pari(v[0]) per l=1;
 * pari v[0] && tutti pari (v[1....tutti]) per l>1;
*/

int tutti_pari(int *v, size_t l){
}