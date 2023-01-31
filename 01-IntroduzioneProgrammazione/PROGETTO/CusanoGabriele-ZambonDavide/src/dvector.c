/**
 * @file dvector_t.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section Libreria per il tipo "dvector_t"
 * Funzioni di libreria per la gestione del tipo dvector_t
*/
#ifndef  _HEADERS_
#define  _HEADERS_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include"types.h"
#endif // _HEADERS_
 
const size_t V_MIN_CAPACITY = 16;

/**
 * dealloca memoria
 * @param v puntatore da deallocare
*/
void v_free(snake *v){
    free(v->body->data);
    free(v->body);
    free(v);
}

/**
 * controlla che l'indice non sia oltre la size. esce dal programma in caso
 * @param v snake
 * @param index indice
*/
void _v_check_index(const snake* v, size_t index) {
    if( index >= v->size ){
        printf("Error: Index %lu out of bounds for vector of size %lu\n",
        index, v->size);
        exit(EXIT_FAILURE);
    }
}

/**
 * controllo della grandezza dello snake
 * @return 1 se è di lunghezza 0
*/
int v_is_empty(const snake *v){
    return v->size == 0;
}
 
/**
 * esco dal programma se lo snake ha lunghezza zero
 * @param v snake
*/
void _v_check_non_empty(const snake* v) {
    if( v_is_empty(v) ){
        printf("Error: Empty vector\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * size dello snake
 * @param v snake
*/
size_t v_size(const snake *v){
    return v->size;
}

/**
 * ritorna la posizione della cella occupata dallo snake in un dato indice
 * @param v snake
 * @param index indice (della lunghezza di snake)
*/
position_t* v_get(const snake *v, size_t index){
    _v_check_index(v, index);
    position_t *p;
    p->pos = v->body->data[index];
    return p;
}

/**
 * ingrandisce lo snake se serve, reallocando memoria
 * @param v snake
*/
void _v_check_extend(snake *v){
    if (v->size==v->capacity) {
        vdata_t* new_pos = (vdata_t*) realloc( v->body->data, v->capacity*2 *sizeof(vdata_t) );
        if (!new_pos) {
            v_free(v);
            printf ("Error: Failed memory allocation\n");
            exit(EXIT_FAILURE);
        }
        v->body->data  = new_pos;
        v->capacity *= 2;
    }
}

/**
 * rimpicciolisce lo snake se serve, reallocando memoria
 * @param v snake
*/
void _v_check_shrink(snake *v){
   size_t half_capacity = v->capacity/2;
   if ( half_capacity >= V_MIN_CAPACITY && v->size <= half_capacity ) {
        vdata_t* new_pos = (vdata_t*) realloc( v->body->data, half_capacity *sizeof(vdata_t) );
        if (!new_pos) {
            v_free(v); 
            exit(EXIT_FAILURE);
        }
        v->body->data  = new_pos;
        v->capacity = half_capacity;
    }
}

/**
 * creo lo snake con tutti i crismi, allocando la memoria neccessaria
 * @return il puntatore allo snake creato
*/
snake* v_create() {
    snake* v = (snake*) malloc ( sizeof(snake) );
    v->body =  (vector_t*) malloc ( sizeof(vector_t));
    v->size = 0;
    v->capacity = V_MIN_CAPACITY; /* initial capacity */
    v->body->data = (int*) malloc( v->capacity * sizeof(vdata_t) );
    if (!v->body->data) {
        printf ("Error in memory allocation\n");
        exit(EXIT_FAILURE);
    }
    return v;
}

/**
 * clono lo snake
 * @param v snake da clonare
 * @return puntatore al clone
*/
snake* v_clone(const snake *v) {
    snake* c = (snake*) malloc ( sizeof(snake) );
    c->body =  (vector_t*) malloc ( sizeof(vector_t));
    c->size = v->size;
    c->capacity = v->capacity;
    c->body->data = (int*) malloc( c->capacity * sizeof(vdata_t) );
    if (!c->body->data) {
        printf ("Error in memory allocation\n");
        exit(EXIT_FAILURE);
    }
    memcpy(c->body->data, v->body->data, v->size * sizeof(vdata_t) );
    return c;
}

/**
 * stampa a video le posizioni dello snake
 * @param  v snake
*/
void v_print(const snake *v) {
    size_t i;
    printf("[ ");
        for (i=0; i<v->size; i++){
           printf(" ( index : %ld , ",i);
           printf ("pos :  %d )", v->body->data[i]);
        }  
    printf("]\n");
}

/**
 * appende un valore
 * @param v snake
 * @param valueX valore da appendere
*/
void v_push_back(snake *v,vdata_t valueX){
    _v_check_extend(v); //vedo se serve ingrandire lo snake
    v->body->data[v->size] = valueX;
    v->size+=1;
}


/**
 * rimpicciolisco di uno lo snake
 * @param v snake
*/
void *v_pop_back(snake *v){ 
   _v_check_non_empty(v);
   v->body->data[v->size-1] = 0;
   v->size -=1;
   _v_check_shrink(v);
}



