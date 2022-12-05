#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define NUOVO 1
#define VECCHIO 0
#define TROVA_UN_SOLO_PERCORSO 0

void stampa(char* map, int r, int c){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
        printf("%c ", map[i*c+j]);
        }
        printf("\n");
    }
}
int find_char(char* map, int size, char c_to_be_found){
    //trova la posizione di un carattere specifico all'interno della mappa
    for (int i=0; i<size; i++) if (map[i]==c_to_be_found) return i;
}

#if VECCHIO
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
    */
    if (t==0) return 1;
    if (size==0 && t>0) return 0;
    int tot=0;
    for (int n=0; n<=q[0] && t-n*c[0]>=0; n++) 
        tot += resto(c+1, q+1, size-1, t-n*c[0]); //if: se le monete sono pià del resto, non ha senso prenderle
    return tot;
}
// si può applicare al progetto?

/**
 * si, mi sto chiedendo qual è il punteggio massimo che posso fare
 * 
 * score(Lab) :
 *      posso spostarmi a N -> score(lab + posizione nord)
 *          obv devo avere degprintf("%d\n",*npassi);li if che controlli i muri.
 *      posso spostarmi a S -> score(lab + posizione sud)
 *      posso spostarmi a E -> score(lab + posizione est)
 *      posso spostarmi a O -> score(lab + posizione ovest)
 * 
 * il miglior score possibile è il max tra i 4 score.
 * 
 * i casi base: o == _    -> ritorno 1- num.passi + 10*monete
 * se numero passi > 1000 (quindi sicuramente troppo lungo) mi arrendo (posso ritornare un numero molto basso)
*/
#endif


bool punto_valido(char* map, int position){
    return map[position] != '#' && map[position] != '+';
}
int massimo(int a, int b, int c, int d){
    int max = a;
    if (b>max) max = b;
    if (c>max) max = c;
    if (d>max) max = d;
    return max;
}


#if VECCHIO
int punteggioo(char* map, int position, int fine, int c, int* npassi, int* path){
    if (punto_valido(map, position)){
        if (position==fine) {
            *path = position;
            return 1;
        }
        else {
            map[position] = '+'; //marco con un + il mio percorso
            *path = position;
            return 1+massimo(punteggioo(map, position+1,fine, c, npassi, path+1),
                        punteggioo(map, position+c,fine, c, npassi, path+1),
                        punteggioo(map, position-1,fine, c, npassi, path+1),
                        punteggioo(map, position-c,fine, c, npassi, path+1));
        }
    }
    else return 0;
}

int minimo(int* a){
    int min=a[0];
    for (int i=1; i<4; i++){
        if (a[i]<min) min=a[i];
    }
    return min;
}
#endif


#if VECCHIO
int punteggio(char* map, int position, int fine, int c, int* npassi, int* path){
    sleep(1);
    printf("position: %d\n", position);
    stampa(map, 10, c);
    map[position] = '+';
    if (position == fine) return 1;
    
    int direzioni[] = {position+1, position+c, position-c, position-1};
    int min;
    int punteggi[4];

        
    for (int i=0; i<4; i++){
        
        if (punto_valido(map, direzioni[i])){
            punteggi[i] =  1 + punteggio(map, direzioni[i], fine, c, npassi, path+1);
        }
        
    }

    return minimo(punteggi);
}
#endif
bool stuck(char *map, int c, int position){
    if ((map[position+1] == '#' || map[position+1] == '+') &&
        (map[position+c] == '#' || map[position+c] == '+') &&
        (map[position-1] == '#' || map[position-1] == '+') &&
        (map[position-c] == '#' || map[position-c] == '+')) return true;
    else return false;
}


#if VECCHIO
int punteggio(char* map, int position, int fine, int c, int* npassi){
    sleep(1);
    printf("position: %d\n", position);
    map[position] = '+';
    stampa(map, 10, c);
    int dx, sx, up, dw;
    int tot = 0;
    if (position==fine) return 1;
    if (position != fine && stuck(map, c, position)) {
        map[position] = '#';
        return 0;
    }
    else {
        //destra 
        if (punto_valido(map, position+1) && punteggio(map, position+1, fine, c, npassi) != 0) {
            
            //dx = punteggio (map, position+1, fine, c, npassi);
            tot++;
        }
        //else dx = 123456789;
        //up
        if (punto_valido(map, position-c) &&  punteggio(map, position-c, fine, c, npassi) != 0) {
            
            tot++; //up = punteggio (map, position-c, fine, c, npassi);
        }
        //else up = 123456789;
        //down
        if (punto_valido(map, position+c) &&  punteggio(map, position+c, fine, c, npassi) != 0) {
            tot++; dw = punteggio (map, position+c, fine, c, npassi);
        }
        //else dw = 123456789;
                //sinistra
        if (punto_valido(map, position-1) &&  punteggio(map, position-1, fine, c, npassi) != 0) {
            
            tot++ ;//sx = punteggio (map, position-1, fine, c, npassi);
        }
        //else sx = 123456789;
    }
    int a[]={up, dw, dx, sx};
    return tot;

}
#endif


/*
guardo al primo taglio. quali opzioni mi apre? in questo caso ne posso prendere 0,1,2,3,4,5,6,7. 
     * se ne prendo 0, devo costruire il resto con monete da 3, 7, 12. =>  resto (c+1, q+1, t, size-1)
     * se ne prendo 1, devo costruire il resto-1 con monete da 3, 7,12 e così via. =>  resto (c+1, q+1, t-1, size-1)
     * se ne prendo 2, devo costruire il resto-2 con monete da 3, 7,12 e così via. =>  resto (c+1, q+1, t-2, size-1)

*/

#if NUOVO
int numero_percorsi(char* map, int position, int fine, int c){
    sleep(1);
    printf("position: %d\n", position);
    
    stampa(map, 10, c);
    if (position==fine) return 1;
    if (position != fine && stuck(map, c, position)) {
        //map[position] = '#';
        return 0;
    }


    if (punto_valido(map, position)){
        int tot=0;
        int direzioni[] = {position+1, position+c, position-c, position-1};
        map[position] = '+';
        for (int i = 0; i<4; i++){
            tot += numero_percorsi(map, direzioni[i], fine, c);
            for (int i=position+1; i<10*c; i++) if (map[i] == '+') map[i] = ' ';
        }
        printf("percorsi trovati finora: %d\n", tot);
        return tot;
    }
    else return 0;
}
#endif














#if TROVA_UN_SOLO_PERCORSO
bool esiste_percorso(char* map, int position, int fine, int c, int* path){
    /**
     * per quanto concerne il path: 
     * 1 significa NORD (mi son spostato verso l'alto)
     * 2 significa EST (mi son spostato verso destra)
     * 3 significa SUD (mi son spostato verso il basso)
     * 4 significa OVEST (mi son spostato verso sinistra)
    */
    if (punto_valido(map, position)){
       
       if (position==fine) return true; //caso base
       
       map[position] = '+'; //marco con un + il mio percorso
       
       //inizio guardando a destra
       bool esiste = esiste_percorso(map, position+1, fine, c, path+1); 
       if (esiste) *path = 2;
       //se non esiste la possibilità di andare a destra, vado in basso
       if(!esiste) {
           esiste = esiste_percorso(map, position+c, fine, c, path+1);
           *path  = 3;
       }
       //se non esiste la possibilità di andare in basso, vado in alto
       if(!esiste){
           esiste = esiste_percorso(map, position-c, fine, c, path+1);
           *path = 1;
       }
       //se non esiste la possibilità di andare in alto, vado a sinistra
       if(!esiste) {
           esiste = esiste_percorso(map, position-1, fine, c, path+1);
           *path = 4;
       }

       return esiste;
    }
}
#endif


int main(){
    
    int default_rows = 10, default_columns = 6, npassi = 0;
    char default_map[] =  {'#','#','#','#','#','#',
                           'o',' ','#',' ',' ','#',
                           '#',' ','#',' ',' ','#',
                           '#',' ','#',' ',' ','#',
                           '#',' ','#','#','#','#',
                           '#',' ',' ',' ',' ','#',
                           '#',' ','#',' ','#','#',
                           '#',' ','#',' ','#','#',
                           '#',' ',' ',' ',' ','_',
                           '#','#','#','#','#','#'};
    
    stampa(default_map, default_rows, default_columns);
    //int* path = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');
    //int a = esiste_percorso(default_map, inizio, fine, default_columns, path);
    int punt = numero_percorsi(default_map, inizio, fine, default_columns);
    stampa(default_map, default_rows, default_columns);

    size_t size = 0;
    //for (int j=0; j<default_columns*default_rows; j++) if (path[j]!=0) ++size;
    //path = realloc(path, size*sizeof(int));
    //for(int i=0; i<size; i++) printf("%d -> ",path[i]);
    printf("\npunti: %d\n", punt);
    printf("npassi: %d\n", npassi);
    //free(path);
    return 0;
    
}