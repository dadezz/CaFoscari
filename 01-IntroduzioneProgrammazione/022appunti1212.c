#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct vector{
    int* data;
    int size;
};
typedef struct vector vector_t;

typedef
struct list{

    int data; //int ma potrebbe esserequalsiasi cosa
    struct list* next;

} list_t;

list_t* l_create(int x){
    list_t* l = malloc(sizeof(l));
    if(!l) exit(EXIT_FAILURE);
    l->data = x;
    l->next = NULL;
    return l;
}

void l_print(list_t* l){
    printf("{");
    while (l) {
        printf(" %d", l->data);
        l = l->next;
    }
    printf(" }\n");
}

void l_append(list_t ** l_orig, int x){
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

/*
 * come si libera la memoria di una lista?
*/
void l_free(list_t * l){
    while(l){
        list_t *succ = l->next;
        free(l);
        l = succ;
    }
}

/**
 * dato un vettore di elementti, creo una lista con gli stessi elementi
*/

list_t * array_to_list1 (int* v, size_t v_size){
    list_t* new_list = NULL;
    for (size_t i=0; i<v_size; i++){
        l_append(&new_list, v[i]);
    }
    return new_list;
}

// se volesi crearlo da 0 senza append?

list_t * array_to_list (int* v, size_t v_size){
    list_t* new_list = NULL; //primo elemento
    list_t* tail = NULL; // ultimo elemento

    for (size_t i=0; i<v_size; i++){
        if (new_list == NULL) {
            list_t* new_elem = l_create(v[i]);
            new_list = new_elem;
            tail = new_elem;
        }
        else {
            list_t* new_elem = l_create(v[i]);
            tail->next = new_elem;
            tail = tail->next;
        }
    }
    return new_list;
}

/**
 * dire se l'elemento èpresente nella lista
*/
bool l_is_in(list_t *l, int x){
    while(l){
        if (l->data == x);
            return true;
        l = l->next;
    }
    return false;
}
//ricorsivo
bool l_is_in_rec(list_t *l, int x){
    if (l == NULL) return false;
    return l->data == x || l_is_in_rec(l->next, x);
}

int main(){
    int vettore[] = {1, 10, 100,  50};
    list_t* lista = array_to_list1(vettore, 4);
    printf("elemnto 100 in lista: %d\n", l_is_in_rec(lista, 100));
    l_print(lista);
    return 0;
}

/**
 * scrivere una f che data una lista di interi restiuirsc auna nuova lista (fatta di nuovi nodi) 
 * con soli gli elementi distinti della prima (in altre parole, tolti i duplicati)
*/

list_t* l_unique(list_t* l){
    list_t* uniq;
    for (; l; l = l->next){
        if (!l_is_in(uniq, l->data)) 
            l_append(&uniq, l->data);
    }
    return uniq;
}

list_t* l_unique_rec(list_t* l){
    list_t * new_l = NULL;
    list_t * head = l;
    list_t* uniq_other =l_unique_rec(l->next);
    if (l_is_in(uniq_other, head->data)) new_l = uniq_other;
    else {
        list_t* new_elem = l_create(head->data);
        new_elem->next = uniq_other;
        new_l = new_elem;
    }
    return new_l;
}

/**
 * scrivere una funzione che restituisca una lista inversa a quella data
*/

