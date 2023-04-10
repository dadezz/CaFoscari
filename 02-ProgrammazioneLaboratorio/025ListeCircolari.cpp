/**
 * nessun puntatore a next punta a nullptr, l' "ultima" punta alla prima
 * Notiamo che il tipo è indistinguibile da una linked list normale.
*/

#include<iostream>

struct cella {
    int info;
    cella* next;
};
typedef cella* Listacirc;

void print(Listacirc l){
    if (l){
        Listacirc k = l;
        do {
            l=l->next;
            std::cout<<l->info;
        } while(l != k);
    }
}