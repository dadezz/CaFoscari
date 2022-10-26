/*reversed: restituisce l'array a ordine inverso*/
#include<stdio.h>
#include<stdlib.h>
void print_array(int* a, int len){
    for (int i = 0; i<len; i++){
        printf("%d", a[i]);
    }
}
int * reversed (int * A, int N){

    int * REV = (int*) malloc (N *sizeof(int));//riservami N per 4 byte ocnsecutuvi co puntatore alla prima pos
    for (int i=0; i<N; i++){
        REV[i] = A[N-i-1];
    }
    return REV; // è un puntstore a un'area di memoria grande N
}

//malloc sopravvive agli scope.
//esiste la funzione free che serve proprio a deallocare la memoria (importante operazione di pulizia)
//idem realloc, posso prendere un vecchio puntatore malloc e reallocare la memoria

int main (){

    int A[] = {1,2, 3, 4, 5};
    print_array(A, 5);

    int *B = reversed(A, 5);
    print_array(B, 5);
    free(B); //obv non si può più usare dopo.
}

/*
la fuznione è scritta in maniera corretta, ma crea un po' di confusione, percHé non si sa di chi è la responsabilità
della memoria. nel senso che quando il codice diventa compleso, vorrei che se la fnzione gestisce la memroai se la deallocasse da sola.
si immagini per esempio una f che chiama una f che ne chiama un altra etc etc. chi e come gestisce la memoria?
ci sono delle convenzioni.
quella usata in questo esempio è la cosiddetta CALLEE: chiamato crea memoria e chiamante la dealloca, ovvero la funzoine crea la memoria, ma è
 che chi chiama la funzione diventa responsabile di quella memoria (in questo caso main)
c'è invece la caller ownership, isola ogni blocco, ovvero che la memoria non viene creata dalla funzione ma fal chiamante, che ne è pienamente responsabile.
*/

//in sto caso sarbbe 
void reversed (int * A, int N, int *REV){
    for (int i=0; i<N; i++){
        REV[i] = A[N-i-1];
    }
}


int main1(){
    int * REV = (int*) malloc (N *sizeof(int));//riservami N per 4 byte ocnsecutuvi co puntatore alla prima pos
}



//la funzione exit causa la terminazione del programma. tipicamente, 0 significa che è andato tutto bene, altri numeri sono codici di errori che possono essere gestiti e personalizzati

//il tipo di size_of non è int, ma size_t, che è sinonimo di un altro tipo, deciso dal compilatore.tipicamente unsigned int