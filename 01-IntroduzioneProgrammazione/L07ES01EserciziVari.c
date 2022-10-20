#include<stdio.h>
#define DEBUG  0


//Scrivere una funzione che riceve in input 3 parametri “int A, int B, int* max” e
//che memorizzi nella locazione riferita da max, il valore del massimo tra A e B
void f(int A, int B, int* max){  //non mi viene mai passato il valore di max, ma la sua locazione in memoria
    if (A>B) *max = A; //nella cella di memoria di maxmetto il contenuto di A
    else *max = B; 
}

//Scrivere una funzione che riceve in input 2 parametri “int *A, int *B” e che
//scambi i valori nelle locazioni riferite dai due puntatori
void f2(int *A, int *B){
    int temp = *A; //nella temporanea metto il contenuto di a
    *A = *B; //nel contenuto di A metto il contenuto di B
    *B = temp; //nel contenuto di B metto temp
}

/*Scrivere una funzione che legge da input un intero N, e dopo aver letto altri N
//numeri interi, restituisca la somma degli N numeri interi*/
#if DEBUG
int f3(void) {
    int N;
    int n;
    int somma;
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%d", &n);
        somma += n;
    }
    return somma;
}
#endif 

//Come sopra, scrivere una funzione che dato un intero N e tre puntatori a
//intero, legga N numeri interi da input e usi i tre puntatori per memorizzare
//min, max e media
void f4(int N, int* a, int* b, int* c){
    
    do scanf("%d", &N); while(N<=1);
    
    int immesso;
    scanf("%d", &immesso);
   
    *a = immesso;
    *b = immesso;
    *c = immesso;
    
    for (int i=2; i<=N; i++){
        scanf("%d", &immesso);
        *c += immesso;
        if (immesso > *a) *a = immesso;
        else if (immesso < *b) *b = immesso;
    }
    *c = (float)*c/(float)N;
}

//Scrivere una funzione che legge N numeri interi positivi da input e restituisce
//1 se sono tutti pari o 0 altrimenti
int f5(int N){
    _Bool pari = 1;
    int n;
    for (int i=1; i<=N; i++){
        scanf("%d", &n);
        if (n % 2 == 1) pari = 0;
    }
    return pari;
}

//Scrivere una funzione che legge N numeri interi da input e restituisce 1 se la
//sequenza è crescente e 0 altrimenti
int f5(int N){
    _Bool crescente = 1;
    
    int n_prec;
    scanf("%d", &n_prec);
    
    int n;
    for (int i=2; i<=N; i++){
        scanf("%d", &n);
        if (n < n_prec) crescente = 0;
        n_prec = n;
    }
    return crescente;
}

//Scrivere una funzione che legge al massimo N numeri interi da input e
//restituisce 1 se sono tutti pari o 0 altrimenti, ma smette di chiedere ulteriore
//input non appena legge un numero negativo
int f5(int N){
    _Bool pari = 1;
    int n;
    for (int i=1; i<=N; i++){
        scanf("%d", &n);
        if (n % 2 == 1) {pari = 0;
            break;
        }
    }
    return pari;
}

//Scrivere una funzione che legga da input numeri interi finché l’utente non
//specifica un numero negativo. Letto il numero negativo, la funzione smette di
//chiedere ulteriore input e restituisce la media dei valori positivi letti
int f6(void){
    int immesso, somma = 0;
    int contatore = 0;
    do{
        scanf("%d", &immesso);
        if (immesso>0){
            somma += immesso;
            contatore++;
        }
    } while (immesso>0);

    return (somma == 0) ? 0 : somma/contatore;
}

int main (){
    int a = 2;
    int b = 6;
    int max = 8;
    int somma;

    f(a, b, &max);
    printf("%d\n", max);

    f2(&a, &b); //passo la posizione delle celle di memoria di a e b
    printf("%d\n", a);
    printf("%d\n", b);

    int maxx, min, media;
    f4(12, &min, &maxx, &media);
    printf("%d, %d, %d\n", maxx, min, media);
    
    return 0;
}
