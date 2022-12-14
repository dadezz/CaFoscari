/**
 * standard per la documentazione:
 * 
 * come si commenta un codice? esiste strumento doxygen:
 * riceve in input codice commentato a dovere (forma /** /)
 * 
 * i commmenti hanno parole chiave tipo @param, @return (per esempio i parametri di una funzione
 * o cosa ritorna una funzione)
*/

//appello 17 giugno  (o 6 settembre) 2022 esercizio 1 funzione euclidean

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<math.h>

typedef struct list{
    int data;
    struct  list *next;
} list_t;

float euclidean (float* a, int a_size, float *b, int b_size){
    float sum = 0.0f;
    for (int i=0; i<a_size; i++){
        sum += (a[i]-b[i])*(a[i]-b[i]);
    }
    return sum;
}

//stesso appello, matrice incrociata

int incrociata(int *m, int n_rows, int n_cols){
    for (int i=0; i<n_rows; i++)
        if (m[i*n_cols + i] != m[i*n_cols + (n_cols-1)-i]) 
            return 0;
    return 1;
}

//stesso appello, "asterisco"

char* asterisco(char*s){
    int contatore = 0;
    for (int i = 0; i<strlen(s); i++){
        if (s[i] == ' ') contatore +=2;
        else contatore++;
    }
    char* s2 = malloc(contatore + 1); //manca il sizeof perhché il char ha misura 1. il +1 serve al \0
    if(!s2) exit(EXIT_FAILURE);
    
    int j=0;
    for (int i = 0; i<strlen(s); i++){
        if (s[i] == ' ') {
            s2[j] = '*';
            s2[++j] = '*';
        }
        else s2[j] = s[i];
        j++;
    }
    s2[j] = '\0';
    return s2;
}

// stesso appello esercizio merge
list_t* merge(list_t*a, list_t* b){
    list_t* c = NULL;
    while(a || b){
        if (a==NULL) //inserisco solo gli elementi di b, idem viceversa.
        if (a<b) ;//inserisci a in c, a = a->next;
        else ; //viceversa 
    }
}
int main(){
    float a[] = {1.0f, 2.0f, 4.0f, 8.0f};
    float b[] = {1.0f, 1.0f, 4.0f, 4.0f};

    printf("%f\n", euclidean(a, 4, b, 4));

    char* s = "ciao a tutti";
    char* s2 = asterisco(s);
    printf("%s\n", s2);
    free(s2);
    return 0;

}