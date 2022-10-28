/*
esercitazioni spano pointer
*/

#include <stdio.h>
#include<stdlib.h>


void print_array_float(float *a, size_t len){
    printf("[len: %d][ ", len);
    for (unsigned short i=0u; i<len; i++){
        printf("%.1f, ", a[i]);
    }
    printf(" ]\n");
}

/*
lettere suffisso dei numeri:
u -> unsigned
s -> short
f -> float
l -> long

*/

int main1 (){
    float a[10] = {1.1, 1.3, 1.4, 1.6}; //il tipo della variabile è float*. non esiste tipo degli array, ma solo pointer
    int b[30];
    print_array_float(a, 10);

    return 0;
}

/*a cosa punta il pointer di a?
al primo elemetno della serie di 4.

se distruggo l'array, continua a puntare? */


int* crea_array_vuoto(){
    int p[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    return p;
}

int main2 (){
    float a[10] = {1.1, 1.3, 1.4, 1.6}; //il tipo della variabile è float*. non esiste tipo degli array, ma solo pointer
    int* b = crea_array_vuoto();
    print_array_float(a, 10);

    int n = b[0]; //segmentation fault

    return 0;
}

//il p a riga 40 a cosa punta? al primo elemento dell'array.
// dereferenziando p, cosa tiro su? il primo zero

/* alla fine dello scope , che fine fa p? 
vengono distrutte le variabili (la lista di 10 zeri). 
se all'uscita della funzione distruggo l'array, ma ritorno comuque la posizione del primo, mi dà problemI?
si. perché per puntare alla memoria, punti alla memoria, ma quando esci la deallochi, e la chiamata diventa errore a runtime, access violation

segmentation fault non è un errore di compilazione, ma errore di esecuzione. dal pov del compilatore, i tipi son tutti a posto.
é un errore che ritorna il sistema operativo. è un crash del programma che fa un accesso "illegale" a una memoria a cui non ha accesso.

L'accesso alla memoria che non è tua produce un kill immediato del programma da parte del sistema operativo.
*/

/*esempio stuido di seg fault*/

int x(){
    int x = 5;
    int *u = &x;
    int y = u[1];  
}

/* sta roba compila, ma si cerca di andare in un posto della memoria che  non ci appartiene 
tipo: x è nella cella di memoria 123 e contiene il numero 5. u punta al posto 123.
y guarda la memoria 124: non è legale. 

sarebbe stato uguale scrivere int y = *(u+1)
piccola parentesi: p[n] = *(p+n)

 */

/* come posso quindi creare un array in uno scope che rimanga anche dopo?
devo allocare un toco di memoria. Ecco che uso malloc.
la riga 39 non chiede al sistema operativo di allocare una memoria, malloc fa proprio questo.
crea un array non nello stack, ma "chiede un favore all'OS".
quel pezzo di memoria non viene mai eliminato finché non lo si elimina automaticamente 

*/

int * crea_array_vuoto2(unsigned int len){
    int * p = (int*)malloc(len); 
    //la malloc non pulisce la memoria, quindi in realtà non è "vuoto".

    //per pulirla:
    for (int i=0; i<len/4; i++){
        p[i] = 0;
    }

    // è più bello comunque dare all'utenete la possibilità di dire quanti interi vuole, invece di quanti byte.
    // conseguentemente:

    int * p1 = (int*)malloc(len*sizeof(int));
    // in questo caso, len non è la lunghezza dei byte, am il  numero di int
    // il for quindi diventa
    for (int i=0; i<len; i++){
        p1[i] = 0;
    }

    //questo, ricordiamo, è percHé un int misura 4 byte
    return p1;
}

/*numeri casuali:
facile fuznionetta se vogio avere numeri casuali tra a e b*/

int rnd(int a, int b){
    int n = rand() % (a-b) + a;
    return n;
}

/*utlizzo srand.
i rand sono pseudocasuali, ma sono sempre gli stessi. per farla sempre diversa, si usa una funzione gemella di rand: srand.
dato un seed, la sequesnza sarà sempre la stessa. il trucco è dare un seed differente.
una soluzione spesso usata è dargli l'ora corrente.
srand si chiama una volta sola per inizializzare il genreatore*/

# include <time.h>

float * create_filled_float_array(unsigned int n){
    
    int * p1 = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++){
        p1[i] = 0;
    }
    return p1;
}
void print_array_float(){}

float * filter_array1(float *a, unsigned int len, float threshold){
    int contatore = 0;
    for (int i =0; i<len; ++i){
        if (a[i] >= threshold) contatore++;
    }
    float * r = (float*)malloc(contatore*sizeof(float));
    for (int i =0, j =0 ; i<len; ++i){
        if (a[i] >= threshold) r[j++]=a[i];
    }
    return r;
}

//al ritorno, dove c'è scrttto quanto è grande r?
//serve un modo per tornare due cose, che in c non si può.
//come facciamo?

/*si passa l'info extra come pointer e la si setta dentro alla func*/

float * filter_array(float *a, unsigned int len, float threshold, unsigned int * outlen){
    int contatore = 0;
    for (int i =0; i<len; ++i){
        if (a[i] >= threshold) contatore++;
    }
    float * r = (float*)malloc(contatore*sizeof(float));
    for (int i =0, j =0 ; i<len; ++i){
        if (a[i] >= threshold) r[j++]=a[i];
    }
    *outlen = contatore;
    return r;
}



int main3(){
    srand(time(NULL));   //time(NULL) mi dice che ora è adesso.


    float *a = create_filled_float_array(30);
    print_array_float(a, 30);

    int outlen;
    float *b = filter_array(a, 30, 0.0, &outlen);

}