#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

// codice dei thread. Notare che e' una funzione che prende 
// un puntatore e ritorna un puntatore (a void)
void * codice_thread(void * a) {
    int *num = (int *)a; 
    *num = *num * *num;

    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t tid[2];
    int somme[2];
    int i,err;
    
    for (i=0; i<2; i++){
        somme[i] = atoi(argv[i+1]);
    }

    for (i=0;i<2;i++) {
        if (err=pthread_create(&tid[i],NULL,codice_thread, (void*) &somme[i])) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }
    }

    // attende i thread. Non si legge il valore di ritorno (secondo parametro NULL)
    for (i=0;i<2;i++) {
        if (err=pthread_join(tid[i],NULL)) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE); }
    }

    int res = somme[0] + somme[1];

    printf("I thread hanno terminato l'esecuzione correttamente. Risultato: %d\n", res);
}
