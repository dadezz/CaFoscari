#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
 
///////////////////////////////
//Sezione A: voto massimo 25 //
///////////////////////////////

/**
 * Scrivere una funzione che, dati due array di interi A e B aventi la stessa lunghezza diversa da zero, resti‑
 * tuisca -1 se A[i]<=B[i] per tutte le posizioni i, restituisca 1 se A[i]>B[i] per tutte le posizioni i, e 0
 * altrimenti
*/
int es1(int a[], int b[], size_t len) {
    int minori = 1;
    if (a[0]<=b[0]) minori = -1;
    
    if (minori == -1) {
        for (int i = 1; i<len; i++) {
            if (a[i]>b[i]) {
                return 0;
            }
        }
    }
    else {
        for (int i = 1; i<len; i++) {
            if (a[i]<=b[i]) {
                return 0;
            }
        }
    }
    return minori;
}

/**
 * Scrivere una funzione che data una matrice rettangolare di interi A restituisca un nuovo vettore che in po‑
 * sizione i‑esima contenga la somma degli elementi nell’i‑esima colonna.
*/
int* isum (int* mat, int col, int row){
    int *v;
    v = malloc(sizeof(int)*row);
    for (int i = 0; i<col; i++){
        v[i] = 0;
        for(int j = 0; j<row; j++){
            v[i]+=mat[j*col + i];
        }
    }
    return v;
}

/**
 * Nell’alfabeto “minimal” al posto delle lettere maiscuole si raddoppia la corrispondente minuscola. Ad
 * esempio “WoW” diventa “wwoww”. Scrivere una funzione che data una stringa costituita solo da caratteri
 * alfabetici e spazi restituisca la stringa corrispondente in alfabeto “minimal”
*/
char* minimal(char* str){
    int contatore = 1;
    for(int i=0; i<strlen(str); i++){
        if(str[i]>='A' && str[i]<='Z') contatore += 2;
        else contatore++;
    }
    char* min = malloc(contatore);
    int  j=0;
    for(int i=0; i<strlen(str); i++){
        if (str[i]>='A' && str[i]<='Z') {
            min[j++] = str[i]+32;
            min[j++] = str[i]+32;
        }
        else min[j++] = str[i];
    }
    min[j]='\0';
    return min;
}

/**
 * Date due liste di elementi distinti, scrivere una funzione che restituisca 1 se tutti gli elementi della prima
 * lista sono inclusi nella seconda lista in qualunque ordine e 0 altrimenti. La lista è definita come segue.
*/
typedef struct list {
    int data;
    struct list *next; /* next == NULL at the end of the list */
} list_t;

int included(list_t *l1, list_t *l2){
    list_t *start2 = l2;
    for(; l1; l1 = l1->next){
        bool found = false;
        l2 = start2;
        for (; l2 && !found; l2 = l2->next){
            if (l1->data == l2->data){
                found = true;
            }
            if (!(l2->next)){
                return 0;
            }
        }
    }
    return 1;
}

/**
 * Scrivere una funzione che dato un intero n, n > 0, ed una stringa s restituisca 1 se la stringa contiene n
 * occorrenze consecutive del carattere “x”, e 0 altrimenti
*/
int consecutiveX(int n, char* str){
    for (int i = 0; i<strlen(str); i++){
        if (str[i] == 'x'){
            bool x = true;
            for(int j=0; j<n && x; j++){
                if (str[++i] != 'x') x = false;
            }
            if (x) return 1;
        }
    }
    return 0;
}

///////////////////////////////
//Sezione B: voto massimo 30L//
///////////////////////////////

/**
 * Scrivere una funzione che data una matrice di interi, restituisca una nuova matrice ottenuta replicando 4
 * volte la matrice iniziale
*/
int* repl(int* mat, int row, int col){
    int* matrepl = malloc(row*col*4*sizeof(int));
    int col2 = col*2;

    //prima meta di righe
    for(int j = 0; j<row; j++){
        for (int i = 0; i<col; i++){
            matrepl[j*col2 + i] = mat[j*col + i];
        }
        for (int i = 0; i<col; i++){
            matrepl[j*col2 + i+col] = mat[j*col + i];
        }
    }
    //seconda metà di righe
    for(int j = 0; j<row; j++){
        for (int i = 0; i<col; i++){
            matrepl[(j+row)*col2 + i] = mat[j*col + i];
        }
        for (int i = 0; i<col; i++){
            matrepl[(j+row)*col2 + i+col] = mat[j*col + i];
        }
    }
    return matrepl;
}

/**
 * La compressione ZIP usa anche la seguente intuizione. Se posso costruire una lista di sotto‑stringhe fre‑
 * quenti, allora posso comprimere un testo memorizzando solo una identificazione di queste sotto‑stringhe.
 * Implementare una funzione di decompressione ZIP con i seguenti parametri: stringa di codifica, array delle
 * posizioni iniziali, array delle lunghezze.
 * La decodifica è definita dal seguente esempio:
        char *enc_text = " over and";
        int starts[] = {1,0};
        int lens[] = {8,4};
        printf("%s \n", es6(enc_text, starts, lens, 2) );
 * output:
        over and over
 * La stringa decompressa si ottiene prendendo la sottostringa di enc_text che inizia in posizione 1 ed è
 * lunga 8 (“over and”“), e concatenandola con la sottostringa che inizia in posizione 0 ed è lunga 4 (”over“).
 * L’ultima parametro indica il numero di elementi nei vettori starts e lens.
*/
char* zip(char* enc_txt, int* starts, int* lens, int size){
    int lunghezza_decompressa = 1; //carattere terminatore
    for (int i=0; i<size; i++){
        lunghezza_decompressa += lens[i];
    }
    char* str_decompressa = malloc(lunghezza_decompressa);
    
    int i = 0;
    for(int j=0; j<size; j++){
        for(int z=0; z<lens[j]; z++){
            str_decompressa[i++] = enc_txt[starts[j]+z];
        }
    }
}

/**
 * Scrivere una funzione che, data una lista, restituisca 1 se la lista è palindroma e 0 altri‑
 * menti
*/
//queste due funzioni mi servivano solo a crearmi una lista di prova e vedere la correttezza
void printl(list_t *list){
    printf("[ ");
    for(; list; list = list->next) printf("%d ", list->data);
    printf("]\n");
}
list_t *append (list_t *lista, int n){
    list_t *aux = malloc(sizeof(list_t));
    aux->data = n;
    aux->next = lista;
    return aux;
}
int palindrome(list_t *lista){
    if (!lista) return 0; //se la lista è vuota, non ha senso dire che è palindroma
    if (!lista->next) return 1; //se la lista ha un solo nodo, è per forza palindroma

    /**
     * l'idea è che a una lista si può appendere in coda o in testa. per cui, 
     * se lista procede #0# -> #1# -> #2# -> #NULL#
     * posso creare nodo #NULL# e poi aggiungerci in testa il nodo #0#
     * e quindi diventa #0# -> #NULL#
     * poi aggiungerci in testa il nodo #1#
     * e quindi diventa #1# -> #0# -> NULL
    */
    
    list_t *rovescia;
    rovescia = NULL;

    list_t *start;
    start = lista; //tengo traccia del primo elemento della lista

    for (; lista; lista = lista->next){
        list_t *aux = malloc(sizeof(list_t));
        aux->data = lista->data;
        aux->next = rovescia;
        rovescia = aux;
    }

    printl(start);
    printl(rovescia);

    lista = start;
    for(; lista; lista = lista->next, rovescia = rovescia->next){
        if(lista->data != rovescia->data) return 0;
    }
    return 1;
}

/**
 * La rana Fred deve percorrere esattamente 𝑛 metri (𝑛 ≥ 0) e può moversi a salti di 1, 2 o 3 metri con un vincolo:
 * non può mai fare due salti consecutivi della stessa lunghezza. Scrivere una funzione ricorsiva che dato 𝑛
 * calcoli il numero di modi possibili in cui è possibile percorrere esattamente gli 𝑛 metri senza superarli.
 * Esempio:
 * • 𝑛 = 0. Esiste un solo modo: stare fermo perché siamo già a destinazione.
 * • 𝑛 = 2. Esiste un solo modo con un salto lungo 2. Non è possibile fare 2 salti consecutivi lunghi 1.
 * • 𝑛 = 4. : Ci sono 3 modi: (1, 2, 1), (1, 3), (3, 1)
*/
/**
 * @param n: metri da percorrere
 * @param salto: lunghezza salto appena effettuato. alla prima chiamata inserire numero diverso da 1, 2, 3.
*/
int numero_modi(int n, int salto){
    if (n<0) return 0;
    if (n == 0) return 1;
    if (salto == 1){
        return numero_modi(n-2, 2) + numero_modi(n-3, 3);
    }
    else if (salto == 2){
        return numero_modi(n-1, 1) + numero_modi(n-3, 3);
    }
    else if (salto == 3){
        return numero_modi(n-2, 2) + numero_modi(n-1, 1);
    }
    else{
        return numero_modi(n-2, 2) + numero_modi(n-3, 3) + numero_modi(n-1, 1);
    }
}

/**
 * Chiamiamo “x‑𝑛‑x” la stringa fatta da una “x”, 𝑛 volte “o” e di nuovo “x”. Ad esempio “x‑4‑x” è la stringa
 * “xoooox”. Scrivere una funzione che data una stringa 𝑠 restituisca il valore di 𝑛, 𝑛 > 0, più grande per cui
 * esiste in 𝑠 la sottostringa “x‑𝑛‑x”. La funzione restituisce 0 se la sottostringa non viene mai trovata
*/
int xnx (char* str){
    int cont = 0;
    bool o = false;
    for(int i=1; i<strlen(str)-1; i++){
        if(str[i] == 'o' && str[i-1] == 'x'){
            int cont_aux = 0;
            for (int j=i; j<strlen(str)-1; j++, i++){
                if(str[j] == 'o'){
                    if (j == strlen(str)-2 && str[j+1] != 'x'){
                        cont_aux = 0;
                    }
                    else cont_aux++;
                }
                else{ 
                    if (str[j] != 'x'){
                        cont_aux = 0;
                    }
                    break;
                }
            }
            if (cont_aux > cont){
                cont = cont_aux;
            }
        } 
    }
    return cont;
}



int main(){
    printf("prova: %d\n", numero_modi(0, 0));    
    printf("prova: %d\n", numero_modi(2, 0));    
    printf("prova: %d\n", numero_modi(4, 0));    

    printf("%d \n", xnx("oxoxoooxoxo") );
    printf("%d \n", xnx("ooxxxxoo") );
    return 0;
}