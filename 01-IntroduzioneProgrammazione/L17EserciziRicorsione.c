/**
 * 28 novembre 2022
 * 
 * Continuazione esercizi ricorsione
 * 
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

/**
 * Dobbiamo dare un resto a un cliente.
 * Dato un insieme di monete di diverso taglio, dire in quanti modi è possibile dare il resto.
*/

int resto(int* c, int* q, size_t size, int t){
    /**
     * guardo al primo taglio. quali opzioni mi apre? in questo caso ne posso prendere 0,1,2,3,4,5,6,7. 
     * se ne prendo 0, devo costruire il resto con monete da 3, 7, 12. =>  resto (c+1, q+1, t, size-1)
     * se ne prendo 1, devo costruire il resto-1 con monete da 3, 7,12 e così via. =>  resto (c+1, q+1, t-1, size-1)
     * se ne prendo 2, devo costruire il resto-2 con monete da 3, 7,12 e così via. =>  resto (c+1, q+1, t-2, size-1)
     *      .
     *      .
     *      .
     * se ne prendo q[0] (in sto caso 7), devo costruire il resto-7 con monete da 3, 7,12 e così via. =>  resto (c+1, q+1, t-2, size-1)
     * 
     * in sto modo ho: numero di conf possibili prendendo 1 del primo tagli, num di conf poss prendendo 2 del primo taglio ... num di conf poss prendendo q[0] del primo taglio.
     * se ho tutte le conf possibili, per sapere quante sono, se le sommo le trovo tutte.
     * 
     * ora,se il resto è 0, ho una configurazione possibile da dare.
     * se ho 10 monete da 1 e devo dare 7 di resto, non devo cercare tutto ma solo fino a 7. se il target è negativo, non devo prendere nulla.
     * 
     * quali sono le grandezze che cambiano? c (e q, perché cambiano uguali) e target, perchétolgo qualcosa finché diventa 0
     * 
     * quindi, casi base:
     * se t== 0, ho dato il resto: ok(restituisco 1, perché ho trovato un modo)
     * se ho finito le monete ma il resto è ancora maggiore di 0, ritorno 0 perché nonposso darti alccun resto
     * 
     * 
     * 
    */

    if (t==0) return 1;
    if (size==0 && t>0) return 0;
    int tot=0;
    for (int n=0; n<=q[0] && t-n*c[0]>=0; n++) 
        tot += resto(c+1, q+1, size-1, t-n*c[0]); //if: se le monete sono pià del resto, non ha senso prenderle
    return tot;
}

int main(){
    int c[] = {1, 3, 4, 12} ;//monete da 1, 3, 7, 12 fiorini
    int q[] = {7, 1, 1, 1}; //7 monete da un fiorino, una moneta per ogni altro tipo

    int t = 7; //resto che devo dare

    //la mia funzione deve dare risposta 3, perché ci sono 3 modi possibili per dare il resto:
    // 1 da 7;      1 da 3 e 1 da 4;     7 da 1

    int possibilità = resto(c, q, t, 4);
    printf("%d\n", possibilità);
    return 0;
}

// si può applicare al progetto?

/**
 * si, mi sto chiedendo qual è il punteggio massimo che posso fare
 * 
 * score(Lab) :
 *      posso spostarmi a N -> score(lab + posizione nord)
 *          obv devo avere degli if che controlli i muri.
 *      posso spostarmi a S -> score(lab + posizione sud)
 *      posso spostarmi a E -> score(lab + posizione est)
 *      posso spostarmi a O -> score(lab + posizione ovest)
 * 
 * il miglior score possibile è il max tra i 4 score.
 * 
 * i casi base: o == _    -> ritorno 1- num.passi + 10*monete
 * se numero passi > 1000 (quindi sicuramente troppo lungo) mi arrendo (posso ritornare un numero molto basso)
 * 
 * 
*/

//// ricerca binaria
/**
 * prendo v ordinato in modo crescente. come faccio a sapere in modo veloce se un numero x è presente nell'array?
 * 
 * search(v, n) :
 *      se il mio elemento è maggiore dell'elemento che sta a metà dell'array, posso dimezzare la dimensione dell'array e guardare solo la metà più grande.
 *      ugualmente, se il mio elemento è minore dll'elemento a metà, posso dimezzare guardando la metà inferiore
*/

bool find(int* v, size_t v_size, int m) {
    if (v_size == 1 && v[0] == m) return true;
    if (v_size == 1 && v[0] != m) return false;
    if (v[(v_size/2)]==m)return true;
    if (v[(v_size/2)]<m) return v_size%2==0 ? find(v+(v_size/2), v_size/2, m) : find(v+(v_size/2), v_size/2+1, m);
    if (v[(v_size/2)]>m) return v_size%2==0 ? find(v, v_size/2, m): find(v, v_size/2+1, m);
}