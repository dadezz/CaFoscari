/*
19 ottobre 2022

ARRAY

un array è una sequenza (contigua in memoria) di n elementi dello stesso tipo (in C)
Tutti gli elementi hanno un nome dentro l'array, e l'array intero ha un nome suo e può essere gestito come oggetto unico.
*/
#include<stdio.h>

int main (){
    float my_array[4] = {0.0f, 1.0f, 2.0f, 3.0f} ;//si inizializza con gli elementi tra parentesi graffe

    int a[]={1, 2, 3, 4, 5}; //se inizializzo senza dimensione, il linguaggio conta gli elementi e lo crea di conseguenza

    int b[4] = {1, 2}; //se dò meno valori di quelli dichiarati, quelli mancanti (in coda) sono azzerati.

    float elemento =  my_array[3]; //per specificare che voglio l'elemento 4, metto il 4 come parametro delle quadre
    printf("%f\n", elemento);

    //  IMPORTANTE: GLI INDICI PARTONO DA 0
    // se chiedo una posizione troppo alta, non mi stampa errore. accede alla posizione di memoria corrispondente alla
    // posizione che avrebbe un array di quella linghezza. 
    // è un errore problematico, perché in quella cella potrebbe esserci qualunque cosa e non ci sono warnings.

    //l'accesso è sia in lettura che in scrittura

    my_array[1] = 123.0f; //sto scrivendo 123 nella seconda poszione delll'array.

    /*
    gli array sono in quasi tutte le situazioni intercambiabili coi puntatori. in un certo senso, il nome è un sinonimo della poszione
    in memoria.
    POsso fare:
    */
    float *x = my_array;
    //cosa succede: ho l'array da 4 elementi, poi creo x che è un puntatore al float (primo elemento dell'array). controllo:

    printf("%f\n", my_array[0]);
    printf("%f\n", *x); //saranno uguali.

    //la dereferenziazione obv vale anche in scrittura


    *x = 33.0f;

    printf("%f\n", my_array[0]);
    printf("%f\n", *x); //saranno uguali. (=33)

    float *y = &my_array[2];

    *y = 66.0f;

    printf("%f\n", my_array[2]);
    printf("%f\n", *y); //saranno uguali. (=33)

    // l'operatore [] si applica anche ai puntatori

    printf("%f\n", x[2]); // "vai alla posizione di cella di x, e aggiungi 2 celle" 

    //è esattamente quello che fa un array. 

    // anche in scrittura. 

    x[2] = 45.0f; //ricordiamo che x è di tipo puntatore float, non array.

    // una cosa che non si uò fare è:

    // float array_2[4] = my_array;     (commentato perché sbagliato). non posso copiare un array su un altro.
    // copiabile solo elemento per elemento


    return 0;
}

//come fare funzioni che lavorino su array? (la funzione va sopra al main, ma vabbe)

void f(float x[4]){ //non per forza devo specificare la dimensione, perché
    //passare per argomento un array viene interpretato come passare un puntatore al primo elemento dell'array

    x[1] = 33.0f;

}

// è in generale preferibile la scrittura

void f(float *x){

    x[1] = 33.0f;

}