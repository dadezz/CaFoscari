#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pid,status;
    
    pid = fork();
    if ( pid < 0 ) { perror("errore fork"); exit(EXIT_FAILURE); }

    /* figlio 1: esce normalmente inviando al genitore lo stato "42" */
    if (pid == 0) {
        exit(42);
    }
    
    pid = fork();
    if ( pid < 0 ) { perror("errore fork"); exit(EXIT_FAILURE); }

    /* figlio 2: segfault, cerca di accedere alla locazione 0 */
    if (pid == 0) {
        int *tmp=0;
        int a;
        a = *tmp;
    } // segfault


    /* solo il genitore continua e attende tutti i figli ... */
    while((pid=wait(&status)) >= 0) {
        printf("ricevuta terminazione di pid=%d\n",pid);
        if (WIFEXITED(status))
            printf("OK: status = %d\n",WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("ANOMALO: status = %d\n",WTERMSIG(status));
    }
}