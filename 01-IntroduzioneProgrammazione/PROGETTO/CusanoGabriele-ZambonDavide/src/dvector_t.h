/**
 * @file dvector_t.h
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

void _v_check_extend(snake *v);
void _v_check_shrink(snake *v);
void _v_check_index(const snake* v, size_t index);
void _v_check_non_empty(const snake* v);
snake* v_create();
snake* v_clone(const snake *v);
void v_free(snake *v);
void v_print(const snake *v);
int v_is_empty(const snake *v);
size_t v_size(const snake *v);
position_t *v_get(const snake *v, size_t index);
void v_push_back(snake *v, vdata_t valueX);
void v_pop_back(snake *v);
