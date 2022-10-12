/*
12 ottobre 2022
continuiamo a parlare di cicli
*/
#include <stdio.h>
int main1 (){
    for (;0;){
        //in questo caso il ciclo non viene mai eseguito, dal momento che la condizione è sempre falsa
    }

    for(int i=0; i<10; i++){
        //classica forma del ciclo.
        //il for è di norma usato per cicli di cui si sa già il numero di iterazioni previsto.
        //da stare attenti agli estremi (se <10, il 10 non viene eseguito).
    
    }

}


/*dato N, scrivere una func che stampi tutti i numeri interi strettamente positivi, multipli di 3 e minori di N*/

void interi (int N){
    for (int i=3; i<N; i+=3){
        printf ("%d\n", i);
    }
}

int main2(){
    interi(30);
    return 0;
}

/*
dato N, scirvere una func che stampi tutte le coppie di numeri (a, b) interi positivi minori di N, t.c. a^2 + b^2 = 25
*/

void funzione (int N){
    for(int a = 1; a<N && a<25; a++){
        for(int b = a; b<N && b<25; b++){
            if ((a*a + b*b) == 25){
                printf("(%d, %d)\n", a, b);
            }
        }
    }
}

//una cosa interessante è che lo statement può essere scritto in linea, se non è compound, non servono le graffe
void funzione2 (int N){
    for(int a = 1; a<N && a<25; a++) for(int b = a; b<N && b<25; b++) if ((a*a + b*b) == 25) printf("(%d, %d)\n", a, b);
}


int main3 (){
    funzione2(30);
    return 0;
}

/*
scrivere una funzione che calcli la radice di uno z applicando il metodo di erone per 10 iterazioni. data una stima iniziale x0, l regola di aggiornamento della stima è
x_{i+1} =  1/2 * (x_i + z/x_i) con 10 iterazioni
*/

float radice (float z, int iterazioni){
    float stima = z/2.0; //x0 (stima)
    for(int i = 0; i<iterazioni; i++) stima = ((stima + z/stima)/2.0);
    return stima;
}

//voglio ora un modo per non avere bisogno di un numero di iterazioni, ma capire automaticamnte quando fermarmi, a seconda della precisione di quanto trovato.

float radice_nn (float z){
    float stima_precedente = z; //x0 (stima) precendete 144/2 = 72
    float stima_finale = stima_precedente/2; 
    for (; stima_precedente-stima_finale>0.000002;){
         stima_precedente = stima_finale;
         stima_finale = ((stima_precedente + z/stima_precedente)/2.0);
    }
    return stima_finale;
}

//ha senso usare un for senza il contatore? no, esiste indatti il while:

float radice_n (float z, float tolerance){
    float stima_precedente = z; //x0 (stima) precendete 144/2 = 72
    float stima_finale = stima_precedente/2; 
    while(stima_precedente-stima_finale>tolerance){
         stima_precedente = stima_finale;
         stima_finale = ((stima_precedente + z/stima_precedente)/2.0);
    }
    return stima_finale;
}

int main3 (){
    float z = 143.0f;
    float tolerance = 0.00000001;
    //int iterazioni = 10;
    printf("%.8f\n", radice_n(z, tolerance));
}

//piccolo appunto: per uscire precocemente da un ciclo si può usare break, ma se il programma è complicato è preferibile non farlo, in quanto non si è sicuri della
//delle variabili.

/*dati A e B, caloclare la soma dei numeri interi da A e B inclusi*/

int f(int A, int B){
    return 0;
}

int main(){
    int a = 10, b = 12;
    int somma = (a, b);
    return 0;
}