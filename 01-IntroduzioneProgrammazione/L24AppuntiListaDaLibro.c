#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// GLI APPUNTI SONO NEL MAIN

struct node{
    int value; //dato contenuto nel nodo
    struct node *next; //puntatore al nodo successivo
};

struct node *add_to_list(struct node *list, int n){
    // la funzione dovrà restituire un puntatore ovviamente. prende come argomenti l'intero da aggiungere e il puntatore al primo nodo della
    // vecchia lista

    struct node *new_node; // creo il nuovo nodo che deve essere aggiunto alla lista
    new_node = malloc(sizeof(struct node)); //alloco la memoria necessaria per il nuovo nodo (manca controllo malloc NULL)

    new_node->value = n; //il valore del nuovo nodo
    new_node->next = list; //il nuovo nodo in questo modo diventa il primo della lista, perché ha "next" che punta a list.

    return new_node;
}

struct node *search_list(struct node *list, int n){
    struct node *p;
    for (p = list; list != NULL; p = p->next){
        if (p->value == n) return p;
    }
    return NULL;
}

struct node *delete_from_list(struct node *list, int n){
    struct node *aux, *start;
    start = list;
    if (list->value == n){ //caso in cui l'elemento da eliminare sia nel primo posto della lista
        aux = list->next;
        free(list);
        return aux;
    }
    for (; list && list->next; list = list->next){
        if (list->next->value == n){
            aux = list->next->next;
            free(list->next);
            list->next = aux;
        }
    }
    return start;
}

void print_list (struct node *list){
    printf("[ ");
    for (; list; list = list->next){
        printf("%d ", list->value);
    }
    printf("]\n");
}

struct node *add_ordinato (struct node *list, int n){
    /**
     * idea: scorro la lista, controllando il valore del nodo attuale e del successivo. 
     * se sono uno maggiore e uno minore del numero che si cerca, lo si inserisce lì in mezzo.
     * si può trasformare la funzione perché vada bene sia per le liste ordinate in modo crescente che per quelle decrescenti,
     * basta fare un controllo sui primi due elementi e comportarsi di conseguenza. non lo faccio in sto caso per semplicità
    */
    struct node *aux, *start;
    aux = malloc(sizeof(struct node));
    start = list;
    //mi serve come prima cosa controllare che non vada inserito all'inizio.
    if (list->value < n){
        aux->value = n;
        aux->next = list;
        return aux;
    }
    //controllo poi la lista generale
    for (; list && list->next; list = list->next){
        if (list->value > n && list->next->value < n){
            aux->value = n;
            aux->next = list->next;
            list->next = aux;
            return start;
        }
    }
    //se non l'ho mai aggiunto, lo attacco in coda (list sarà arrivato alla fine della lista)
    aux->value = n;
    list->next = aux;
    aux->next = NULL;
    return start;
}



int main(){
    // dichiarata la struttura, mi serve tener traccia del punto di inizio della lista
    // ovvero serve una variabile che punti sempre al primo nodo.

    struct node *first = NULL; //ovvero la lista è vuota.

    /**
     * è quindi necessario creare nu nodo che contegna qualcosa.
     * Creare un nodo richiede rte passi:
     * 1. allocare memoria per il nodo,
     * 2. salvare i dati nel nodo;
     * 3. inserire il nodo nella lista.
    */

    struct node *new_node;
    new_node = malloc(sizeof(struct node)); //ho allocato la memoria necessaria, ora new_node punta a un elemento di memoria grande a sufficienza
                                         //per contenere un nodo
    // IMPORTANTE se si usasse sizeof (new_node), si allocherebbe memoria sufficiente solo a contenere un puntatore, non un nodo.

    (*new_node).value = 10; // metodo scomodo di assegnamento
    new_node->value = 10; // metodo comodo
    
    
    //notare che new node NON è un nodo allinterno della mia lista, non è ancora concatenato a nulla, devo metterlo da qualche parte.


    // uno dei vantaggi delle liste è che i nodi possono essere aggiunti in qualsiasi punto dela lista. l'inizio è il punto più semplice,
    // quindi vedremo quest per primo

    // new_node è un puntatore e punta al nodo che deve essere inserito.
    // ugualmente, first punta al primo elemento della lista (che ricordiamo essere al momento vuota).

    new_node->next = first; //ora il next di new_node punta a first,diventando quindi il primo elemento della lista.
    first = new_node; //first ricordiamo essere solo un segnaposto che punta al pirmo elemento. quindi dobbiamo farlo puntare al nuovo primo
                // elemento, che è new_node
    // ora a cosa punta new_node->next? a NULL. quindi la lista finisce lì correttamente

    // l'inserimento di un nodo al'inizio di una lista è un operaizione così comune che necessita di una funzione dedicata: add_to_list

    first = add_to_list(first, 20); //il nuovo nodo che creo diventa direttamente il primo della lista.

    first = add_to_list(first, 30);

    // la lista ora risulta essere: [ 30 20 10 ].

    /**
     * una volta creata la lista, potremmo aver bisongo di cercare elementi all'interno della stessa
     * si può usare la forma in ciclo while: finché il puntatore non è NULL, continua a scorrere la lista.
     * 
     * for però è molto flessibile, e piò risultare utille anche in questo frangente, nella forma:
    */

    for (struct node *p = first; p != NULL; p = p->next);
    
    print_list(first);
    // vediamo per esempio la funzione search_list. restituisce un puntatore al nodo che contiene l'elemtno cercato.

    /**
     * eliminare un nodo: 
     * 1. localizzare il nodo da eliminare
     * 2. alterare il next del nodo precedente in modo da saltare quello da eliminare
     * 3. liberare la memoria allocata
     * 
     * il passo 1 non è così facile, perché avremo il puntatore al nodo attuale, non a quello precedente (di cui dobbiamo modificare il next)
     * come ritorno, ho sempre il primo elemento della lista
    */

    first = delete_from_list(first, 10);
    print_list(first);


    /**
     * LISTE ORDINATE :
     * Una lista ordinata è più efficiente ma presenta delle difficoltà in più per quanto riguarda la programmazione.
     * Risulta evidente l'utilità. permette di avere un database dinamico e sempre ordinato, senza tutte le limitaioni legate 
     * all'utilizzo degli array. 
    */

    //vediamo come aggiungere un elemento all'interno di una lista, non all'inizio né alla fine
    //la nostra lista attuale è 30 -> 20 e basta. aggiungiamo un 25 in mezzo

    first = add_ordinato(first, 25);
    print_list(first);
    first = add_ordinato(first, 15);
    print_list(first);
    first = add_ordinato(first, 15);
    print_list(first);
    first = add_ordinato(first, 16);
    print_list(first);
    first = add_ordinato(first, 40);
    print_list(first);
    first = add_ordinato(first, 1);
    print_list(first);
    return 0;
}