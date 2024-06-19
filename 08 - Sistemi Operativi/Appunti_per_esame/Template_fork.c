#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void fork_ () {
    pid_t pid = fork();
    if (pid == 0){
        // codice processo figlio
    }
    else if (pid > 0){
        // codice processo genitore
    }
    else {
        // pid < 0: fork non riuscita, errore
    }

    // qua sotto c'è codice comune. da usare con cautela!
}