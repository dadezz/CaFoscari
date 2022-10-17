/*
17 ottobre 2022: fine cicli e puntatori
*/

/*
dati int A, B, calcolare la somma dei numeri da A a B inclusi
*/

#include <stdio.h>

#define DEBUG  0

#if DEBUG
int func_somma_compresi (int A,int B){
    int somma_parziale = A;

    if (A<B) for (int i=A; i<=B; i++) somma_parziale += i;
    else for (int i=B; i<=A; i++) somma_parziale += i;

    return somma_parziale;
}

int main1 (){

    printf("%d\n", func_somma_compresi(0,12));
    return 0;
}

/*
PUNTATORI

celle di memoria:
una cella di memoria ha un suo numero che lo identifica, come abbiamo imparato ad architettura.
Si richiama una specifica cella di memoria  con la lettera &
*/

int main2 (){
    int a = 10;

    printf("%p\n", &a); //mi stampa l'indirizzo di memoria corrispondente alla variabile a
    return 0;
}

void incrementa1(int *x){
    x = x+1; //Sto facendo "incrementa di uno l'indirizzo di memoria". non sto incrementando a (10)
    //x punta sempre alla cella di memoria di a.
    printf("%p\n", x);
}

int main3 (){
    int a = 10;
    int *b = &a; //voglio per b l'indirizzo di memoria, non il valore di a
    //il puntatore è un tipo.
    incrementa1 (b); //ecco che per la funzione, ho bisogno del tipo puntatore, non int

    printf("%p\n", b); 
    printf("%p\n", &a); 
    return 0;
}


void incrementa(int *x){
    x+1; //qui sto sommando uno alla cella di memoria (x è un puntatore int)
    *x+1; //ora invece sto "dereferenziando" il puntatore, ovvero torno al tipo int e leggo 
          //cosa c'è scritto in quella cella di memoria.
          //si può vedere come un "vai a vedere il valore puntato e modifica quello che c'è scritto"
    
    printf("%p\n", x);
}

int main4 (){
    int a = 10;
    int *b = &a; //voglio per b l'indirizzo di memoria, non il valore di a
    //il puntatore è un tipo.
    incrementa (b); //ecco che per la funzione, ho bisogno del tipo puntatore, non int


    //la & commerciale chiede l'indirizzo della variabile.
    //siccome b ha tipo puntatore intero, la sua cella di memoria è quella a cui punta.

    printf("%p, %d, %p", b, *b, &b); //avrò in stampa: l'indirizzo di memoria di a, il valore di a e di nuovo l'indirizzo di a
    
    //ugualmente, posso scrivere
    int **c = &b; //ottengo a
    /*il puntatore intero significa: se io punto a un indirizzo, ottengo un intero. 
    scrivere quindi int *c = &b è sbagliato, perché non ottengo un intero ma un puntatore*/

    /*non posso invece chiedere l'indirizzo di un indirizzo: se ho &b, chiedo l'indirizzo di b. una volta
    ottenuto, è un numero tipo 0x74875b o simile. che non è una variabile, quindi non posso chiedere di darmi l'indirizzo di questa
    cosa.*/
    printf("%p\n", &a); 
    return 0;
}

/*
i puntatori sono delicati, perché possono cambiare qualsiasi posizione di memoria.
se si guarda, il puntatore x punta alla a del main, senza return, quindi riesce a vedere anche oltre lo 
scope: il puntatore vede qualsiasi cella, anche quella fuori dalla sua funzione.
*/


/*
proviamo un esercizio
dati A, B, restituire somma e prodotto dei numeri tra A e B compresi.
NON USARE FUNZIONI CON RETURN; VOGLIO UN VOID.
*/

void f (int A, int B, int *somma, int *prodotto){ //"a e b sono i dati che mi dai, poi dammi un posto dove scrivere somma e prodotto e io lo faccio"
    *somma = 0;
    *prodotto = 1;
    for (int i=A; i<=B; i++){
        *somma += i;
        *prodotto *= i;
    }
//riesco così a modificare una cella di memoria non appartenente allo scope della funzione quindi senza ritornare nulla
}

int main5 (){
    int sum, prod; //devo quindi creare prima della funzione le celle di memoria su cui memorizzare i risultati
    
    f(10, 12, &sum, &prod);
    printf ("%d, %d\n", sum, prod);

    return 0;
}

//il concetto di puntatore è quello che ci serve pure per mettere valori in input

int main6(){
    int sum, prod;
    int a, b;
    printf ("inserisci a: ");
    scanf("%d", &a);
    printf ("inserisci b: ");
    scanf("%d", &b);
    //scanf usa il valore che l'utente mette nel segnapoto %d e lo inserisce nella cella di memoria in cui è salvata la variabile a
    //scaf quindi è un puntatore alla cella di memoria e ne modifica il contenuto.

    f(a, b, &sum, &prod);
    printf ("%d, %d\n", sum, prod);

    return 0;
}
#endif 

///////////////////////
//     ESERCIZIO     //
///////////////////////


/*
scrivere una func cje legge N numeri interi da imput e restituisce 1 se la sequenza è crescente, 0 atrimenti.
anche N è da input.
*/

int funzione_esercizio (){
    int N;
    _Bool crescente = 1;
    int num_ins_prec;
    int num_ins;

    
    printf("inserisci N: ");
    scanf("%d", &N);

    if (N>1){
        printf("inserisci il numero in posizione 1: ");
        scanf("%d", &num_ins_prec);

        for (int i=2; i<=N; i++){
            printf("inserisci il numero in posizione %d: ", i);
            scanf("%d", &num_ins);
            if (num_ins < num_ins_prec) crescente = 0;
            num_ins_prec = num_ins;
        }
    }
    else printf("vabbe\n");
    return crescente ? 1 : 0;
}

int main (){
    int a = funzione_esercizio();
    printf("%d\n", a);
    return 0;
}