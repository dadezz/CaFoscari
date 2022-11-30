/**
 * voglio espandere  il concetto di array.
 * Voglio implementare funzionalità che il linguaggio non mi da, un modo aggiuntivo di gestire i dati.
*/

/////////////////////////////////////////////////
////             STRUTTURE DATI              ////
/////////////////////////////////////////////////

/**
 * Cos'è una struttura? Un modo per legare assieme dati anche di tipo diverso, dando un nome
 * 
 * Per esempio, mi serve un modo per far viaggiare sempre insieme il numero e il seme per identificare una carta
 * 
 * la struct carta che viene fuori è òun vero e proprio tipo.
 * 
 * come accedo ai due valori della carta creata? con un punto
*/
#include <stdio.h>
#include<stdlib.h>

struct carta {
    int valore; // da 1 a 10
    char seme;  // 'd', 'b', 'c, 's'
};

int main1(){
    struct carta x;
    x.valore = 7;
    x.seme = 's';

    struct carta y;
    y = x; 

    printf("%d %c \n", x.valore, x.seme);

    /**
     *  come faccio un mazzo di carte? 
     * alla fine un mazzo altro non è che un array. l'array ha tipo omogeneo, ma lo struct è a sua volta un tipo.
    */
    
    struct carta mazzo[] = {x, y};

    /**
     * come abbiamo gli arraay, possiamo avere dei puntatori
    */

    struct carta* z = &x;

    (*z).valore--;
    z->valore--; ///////// è la stessa identica cosa di quanto scritto sopra. dereferenzia il puntatore e restituisce valore
    printf("%d %c \n", x.valore, x.seme);

}


struct carta f(struct carta c){
    c.valore++;
    return c;
}

int main2(){
    struct carta x;
    x.valore = 7;
    x.seme = 's';

    struct carta y = f(x);

    /**
     * La cosa superinteressante è che posso sfruttare lo struct per ritornare più valori ad ogni funzione.
     * AL  posto dei puntatori per ritornare più cose, si torna uno struct con tante cose.
     * 
     * Non è raro in realtà che si trovino nelle librerie funzioni che ritornano valori attraverso a un puntatore allo struct, con cui passano info, 
     * e ritornano piuttosto un messaggio se è andato bene o male.
    */
}

//facciamo piccola prova

struct prova {
    int *array;
};

int main3(){
    struct prova x;
    x.array = (int*) malloc(3*sizeof(int));

    x.array[0] = 66;
   
    struct prova y = x;
    // struct prova è un puntatore a intero. quando assegno y=x, y sta puntando alla stessa cella di memoria di x.
    // se provo quindi a modificare y, siccome modifico direttamente la stessa cella di memoria, modifico anche x

    // il meccanismo si chiama shallow copy, ed è fonte frequente di errori.
    // si contrappone al deep copy, che però non è supportato da C.

    y.array[1] = 99;

    printf("%d \n", y.array[0]); //66
    printf("%d \n", x.array[1]); //99
     
    return 0;
}


/**
 * Obbiettivo: creare nuovo tipo di vettore che posso usare per avere dimensione dinamica (della serie "aggiungi elemento in coda")
*/

struct vector {
    size_t len; //numero di elementi nel vettore
    int *data;
};

void v_push_back(struct vector *x, int val){
    //aggiungi val in coda a x
    x->data =  realloc (x->data, (x->len+1)*sizeof(int));
    x->data[x->len] = val;
    x->len++;
}

struct vector * v_create(){
    struct vector *v = (struct vector *) malloc(sizeof(struct vector));
    v->len = 0;
    return v;
}

int main(){
    struct vector v;
    v.len = 0;
}