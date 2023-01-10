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
 * Scrivere una funzione che, data una lista definita come segue, restituisca 1 se la lista è palindroma e 0 altri‑
 * menti
*/
int palindrome(list_t list){
    
}



int main(){
    
    return 0;
}