# send/receive
la send di solito è asincrona (buffer), la receive di solito è sincrona (potrebbe non esserlo con un polling).

# fork
processo duplicato del genitore. ritorno = 0 -> figlio, >0 -> genitore (ritorna pid del figlio)

# exec
sostituisce codice e dati -> fa partire un programma diverso.
copy-on-write : l'os non fa effettivamente copia di nulla se la fork è subito seguita da un exec (per evitare inefficienze).

invocazioni:
`execl ("/path/command", lista di arg (tra cui command), NULL)`
`execlp ("command", lista di arg (tra cui commmand), NULL)`
`execv ("/path/command", array di char*)`
`execvp ("command", array di char*)`

la exec ritorna **solo** in caso di errore

-> come gestre la terminazione?
`exit(status)` termina il processo
`wait()` attende terminazione del figlio
    `pid = wait(int &stato)` ritorna pid e stato del figlio che ha terminato

lo stato ritornato da wait si gestisce con macro.
1. WIFEXITED(status) == true <=> figlio uscito con exit()
2. wifsignaled(status) == true <=> terminato in modo anomalo
   * WTERMSIG(status) ritorna il segnale cheha causato la term

# Signal
`signal(SIG, *f())` cambia il gestore del segnale. Eventualmente, al posto della f() si possono mettere delle macro pre-esistenti: SIG_IGN (ignora il segnale), SIG_DFL (usa il gestore di default dell'os)

# Pipe
`pipe (int filedes[2])` restituisce in filed[0] il descrittore in lettura e in filedes[1] quello in scrittura.

per redirectare lo stdout al pipe (idem lo stdin), `dup2(fd[1], 1)`: fd[1] è il descrittore in scrittura, 1 è lo stdout
`mkfifo` MyPipe crea pipe con nome

# Sezione critica
parte di codice in cui si accede a dati condivisi, creando quindi interferenze con altre esecuzioni concorrenti

# Thread POSIX
`pthread_create(pthread_t *thread, NULL, f(), void arg*)`
`pthread_exit(void *retval)`
`pthread_join(pthread_t thread, void **thread_return)`
`pthread_t pthread_self()` ritorna l'id del thread DELLA LIBRERIA

# Semaforo
contatore con lista d'attesa
```c
struct S {
    int val; // maggiore di 0 -> verde; minore o uguale di 0 -> rosso, numero di thread in attesa prima di te
    thread_t *queue;
}
```

* P(S) o WAIT(S) decrementa il valore e se necessario aggiunge un thread alla coda (una macchina sta arrivando al semaforo -> lo occupa, non lo libera)
* V(S) o POST(S) incrementa il valore e, se necessario, elimina un thread dalla coda

```c
thread() {
    // ...
    P(SEMAFORO);
    // sezione critica;
    V(SEMAFORO);
    // ...
}
```