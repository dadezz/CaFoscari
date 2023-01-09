#include<stdlib.h>
#include<stdio.h>

struct node {
    int value;
    struct node *next;
};


void append (struct node *list, int n){
    struct node *new;
    struct node *start = list;
    new = malloc(sizeof (struct node));

    for(; list->next; list = list->next);
    list->next = new;
    new->value = n;
    new->next = NULL;
}

void printl(struct node *list){
    printf("[ ");
    for(; list; list = list->next) printf("%d ", list->value);
    printf("]\n");
}

/**
 * eliminare tutti i nodi di una lista concatenata e rilasciarne la memoria
*/
void elimina_nodi(struct node *list){
    struct node *aux;
    for (; list && list->next;){
        aux = list->next->next;
        free(list->next);
        list->next = aux;
    }
    free(list);
}

/**
 * scrivere una funzione che restituisca il numero i volte in cui n compare nella lista.
*/
int count_occurrences(struct node *list, int n){
    int c = 0;
    for(; list; list = list->next){
        if (list->value == n) c++;
    }
    return c;
}

/**
 * scrivere una funzione che restituisca l'indirizzo dell'ultima occorrenza in cui n compare nella lista, NULL se non compare.
*/
struct node *find_last(struct node *list, int n){
    struct node *aux = NULL;
    for(; list; list = list->next) if (list->value == n) aux = list;
    return aux;
}

/**
 * modificare delete from list in modio che usi doppio puntatore per eliminare il primo elemento.
*/
void delete(struct node **list){
    struct node *aux;
    aux = *list;
    free (aux);
    *list = (*list)->next;
    
}

int main(){
    struct node *start;
    start = malloc(sizeof(struct node));
    start->value = 10;
    start->next = NULL;

    //popolo la lista
    for (int i = 2; i<10; i++){
        append(start, i*10);
    }
    printl(start);

    //esercizio 1
    elimina_nodi(start);
    printl(start);

    //esercizio2
    struct node start2 = {.value=10, NULL};
    for (int i = 2; i<10; i++) append(&start2, i*10);
    append(&start2, 10);
    printl(&start2);
    printf("%d \n", count_occurrences(&start2, 10));

    //esercizio 3
    printf("%d\n", find_last(&start2, 10));
    printf("%d\n", find_last(&start2, 12));
    struct node *lista = &start2;
    
    printl(&start2);
    delete(&lista);
    printl(lista);
    return 0;
}