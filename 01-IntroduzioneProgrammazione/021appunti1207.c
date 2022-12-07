#include <stdio.h>
#include<stdlib.h>
/**
 * ho un array (in struct tipo len+data). voglio inserire un valore in una data posizione.
*/
struct vector{
    int* data;
    int size;
};

typedef struct vector vector_t;

void insert_at(vector_t v, int val, int pos){
    // la classica funzione di alloca/copia non è una buona soluzione nel caso di un vettore molto dinamico o molto grande.

    /**
     * malloc dimensione +1
     * copio elementi fino a posizione
     * aggiungo elemento
     * copio elementi mancanti shiftati di una posizione
     * aggiusto il puntatore alla nuova memeoria
     * libero la memoria precedente
    */
}


/**
 * Ecco che ci viene in aiuto una nuova struttura dati.
 * è una scorciatoia: non tocco gli elementi vecchi del vettore, ma quando arrivo alla posizione, 
 * dico "ora leggi il valore che devo inserire" e poi riprende a leggere la lista di prima.
 * 
 * ogni nodo della lista incapsula un elemento e racchiude in sé l'informazione su chi sia il prossimo elemento della lista
 * 
 * (data1 = 66, next = puntatore al prossimo elemento), -> (data2 = 99, next = puntatore non valido (così codifico la fine della lista), NULL)
 * 
 * è quindi molto utile in strutture molto dinamiche (e magari che occupano molto spazio), per cui non voglio continuamente allocare memoria o copiare dati
 * 
 * in generale, la struttura viene chiamata o lista o nodo. 
*/

typedef
struct list{

    int data; //int ma potrebbe esserequalsiasi cosa
    struct list* next;

} list_t;

/**
 * operazione base: create. 
 * funz che mi crea una nuova lista e ci inserisce un elemento.
 * la funz restituirà un puntatore alla lista
*/
list_t* l_create(int x){
    //creo il mio nodo 
    list_t* l = malloc(sizeof(l));
    if(!l) exit(EXIT_FAILURE);
    //ci inserisco i dati
    l->data = x;
    //il prossimo nodo non c'è
    l->next = NULL;
    //restituisco un puntatore alla struttura dati appena creata
    return l;
}

int main1(){
    list_t* lista = l_create(10);
    printf("%d\n", lista->data);
    return 0;
}

/**
 * proviamo a farla crescere
*/

void l_append(list_t* l, int v){
    //alloco nuova memoria per il prox nodo
    list_t* nuovo = malloc(sizeof(l));
    //la inizializzo
    nuovo->data = v;
    nuovo->next = NULL;
    //cambio il puntatore del nodo precedente
    l->next = nuovo;
}

int main2(){
    list_t* lista = l_create(10);
    l_append(lista, 11);
    printf("%d\n", lista->data); //contenuto del nodo 1
    printf("%d\n", lista->next); //dove punta il nodo 1?
    printf("%d\n", lista->next->data); //contenuto del nodo 2
    printf("%d\n", lista->next->next); //dove punta il nodo 2?

    return 0;
}
/**
 * chiaro che una stampa del genere è un dito in culo.
 * mi creo un'utility di stampa, tramite le chiamate dei puntatori
*/

void l_print(list_t* l){
    printf("{");
    // stampare un elemento è cosi: printf(" %d", l->data);
    //l->next è il puntatore al secondo elemento. devo ripetere  la stampa sul nuovo puntatore
    /*
    while (l->next != NULL) {
        printf(" %d", l->data);
        l = l->next;
    }
    printf(" %d", l->data);

    così è davvero brutto.
    */
    while (l) {
        printf(" %d", l->data);
        l = l->next;
    }
    //meglio: all'ultima iterazione, l stesso diventa null, e non viene quindi più stampato nulla
    printf(" }\n");
}

//alternativa ricorsiva
void l_print_aux(list_t* l){
    if (l==NULL) return;
    else {
        printf(" %d", l->data);
        l_print_aux(l->next);
    }
}
void l_print_rec(list_t* l){
    
    printf("{");
    l_print_aux(l);
    printf(" }");
}

/**
 * IN GENERALE, VEDREMO CHE DI NORMA LE OPERAZIONI SULLE LISTE SONO PIÙ FACILI DA
 * IMPLEMENTARE RICORSIVAMENTE
*/

//append anche se la lista ha più elementi (assumo ne abbia almeno uno):
void l_append_1 (list_t* l, int v){
    list_t *nuovo = malloc(sizeof(nuovo));
    if(!nuovo) exit(EXIT_FAILURE);
    nuovo->data = v;
    nuovo->next = NULL;

    while(l->next){
        l = l->next;
    }
    //aggangio la vecchia lista al nuovo elemento
    l->next = nuovo;
}
//vara che figo:
void l_append_2(list_t *l, int v){
    while(l->next){
        l = l->next;
    }
    l->next = l_create(v);
}

//se la lista è vuota, come funziona l'append?
list_t * l_append_3(list_t*l_orig, int v){
    if (l_orig==NULL){
        return l_create(v);
    }
    list_t *l = l_orig;
    while(l->next){
        l = l->next;
    }
    l->next = l_create(v);
    return l_orig;
}

void l_append_4(list_t ** l_orig, int x){
    if (!l_orig){
        *l_orig = l_create(x);
    }
    else{
        list_t*l = *l_orig;
        while(l->next){
            l=l->next;
        }
        l->next = l_create(x);
    }

}

int main(){
    list_t* lista = l_create(10);
    if(!lista) exit(EXIT_FAILURE);
    l_append(lista, 11);
    l_print(lista);
    lista = l_append_3(lista, 12);  //l'append non è più void, ma restituisce un puntatore-
    //un altro modo è chiedere un puntatore alla memoria, così da poter continuare a usare un void. 
    l_print_rec(lista);
    l_append_4(&lista, 13);
    l_print_rec(lista);
    return 0;
}