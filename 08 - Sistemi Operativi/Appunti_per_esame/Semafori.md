```c
struct semaphore {
   int valore;
   thread *queue;
}
```
S.valore > 0: il semaforo è verde. Il valore indica il numero di accessi consentiti prima che il semaforo diventi rosso;
S.valore <= 0: il semaforo è rosso. Il valore (tolto il segno) indica il numero di thread in attesa sulla coda del semaforo.


P(S) o wait(S): decrementa il valore del semaforo S. Se il semaforo era rosso già prima del decremento il thread attende sulla coda associata al semaforo;
V(S) o post(S): incrementa il valore del semaforo S. Se ci sono thread in attesa sul semaforo, viene sbloccato il primo della coda.

## sezione critica coi semafori
```c
thread T {
  ...
  P(mutex);
  < Sezione critica >
  V(mutex);
  ...
}
```

## Altro uso dei semafori: attendere un altro thread
Esistono altri utilizzi dei semafori, oltre alla realizzazione della sezione critica.
Supponiamo che T2, prima di eseguire la porzione di codice < D > debba attendere che T1 abbia eseguito il codice < A >. Possiamo realizzare questa semplice sincronizzazione con un semaforo S inizializzato a 0 come segue:

```
semaphore S=0;

T1 {                    T2 {
< A >                    < C >
V(S) ------------------> P(S)
< B >                    < D >
}                       }
```

poiché S è inizializzato a 0 (rosso) la P(S) di T2 sarà bloccante e di conseguenza il codice < D > sarà eseguito necessariamente dopo < A >. Quindi, < A > e < C > possono andare in parallelo. Lo stesso vale per < B > e < D >. Anche < B > e < C > possono andare in parallelo in quanto la V(S) non è mai bloccante. Notare che se la V(S) è eseguita prima della P(S) il semaforo diventerà 1 (verde) e la successiva P(S) non sarà bloccante.

Questo semplice esempio ricorda la sincronizzazione che si ottiene nello scambio di messaggi: la V(S) è come una send asincrona mentre la P(S) come una receive sincrona. Abbiamo evidenziato questa analogia con una freccia dalla V(S) alla P(S).

## regolare accesso alle risorse
Abbiamo visto che un semaforo inizializzato a 1 può essere utilizzato per regolare l’accesso alla sezione critica. In generale, un semaforo iniziato a MAX permette MAX accessi prima di diventare bloccante. Possiamo quindi dare la seguente interpretazione alle operazioni P e V:

    P(S): richiesta di risorsa: se ce ne è almeno una disponibile viene assegnata, altrimenti si attende;
    V(S): rilascio di risorsa: se ci sono thread in attesa il primo viene sbloccato.

Ad esempio se abbiamo 3 stampanti possiamo usare S inizializzato a 3 e quando i primi 3 thread eseguiranno P(S) per allocarsi una stampante, il semaforo diventerà rosso bloccando eventuali altri thread che desiderino stampare. Finita la stampa, l’esecuzione di V(S) sbloccherà il primo thread in attesa. 

# Produttore Consumatore
/* 
La soluzione è di usare due semafori distinti che regolano l’accesso a risorse: 
vuote inizializzato al numero MAX di celle inizialmente vuote e 
piene inizializzato a 0 in quanto inizialmente non abbiamo celle piene.
*/

semaphore_t piene=0; 
semaphore_t vuote=MAX;

Produttore {
    while(1) {
        // < produce d >
        P(vuote); // richiede una cella vuota
        buffer[inserisci] = d;
        inserisci = (inserisci+1) % MAX;
        V(piene); // rilascia una cella piena
    }
}
 
Consumatore {
    while(1) {
        P(piene); // richiede una cella piena
        d = buffer[preleva];
        preleva = (preleva+1) % MAX:
        V(vuote); // rilascia una cella vuota
        < consuma d >
    }
}

/*
Cosa accade se abbiamo tanti produttori e tanti consumatori?
Potrebbero esserci interferenze in scrittura e lettura sul buffer. 
Ad esempio due produttori potrebbero scrivere sulla stessa cella buffer[inserisci], 
sovrascrivendosi l’uno con l’altro, e poi entrambi incrementare inserisci. 
Oppure potrebbero interferire sull’incremento di inserisci, come abbiamo discusso nelle lezioni precedenti.
La soluzione è di proteggere il codice che aggiorna variabili condivise con una sezione critica. 
Ecco la soluzione con tanti produttori e tanti consumatori utilizzando un semaforo mutex inizializzato a 1:
*/
semaphore piene=0, vuote=MAX, mutex=1;

Produttore {
  while(1) {
    < produce d >
    P(vuote); // richiede una cella vuota
    P(mutex); // entra in sezione critica
    buffer[inserisci] = d;
    inserisci = (inserisci+1) % MAX;
    V(mutex); // esce dalla sezione critica
    V(piene); // rilascia una cella piena
  }
}
 
Consumatore() {
  while(1) {
    P(piene); // richiede una cella piena
    P(mutex); // entra in sezione critica
    d = buffer[preleva];
    preleva = (preleva+1) % MAX:
    V(mutex); // esce dalla sezione critica
    V(vuote); // rilascia una cella vuota
    < consuma d >
  }
}


# Posix

I semafori POSIX si utilizzano tramite le seguenti strutture dati e funzioni, definite nella libreria semaphore.h:

`sem_t sem_name`: dichiara una variabile di tipo semaforo;
`int sem_init(sem_t *sem, int pshared, unsigned int value)` inizializza il semaforo sem al valore value. la variabile pshared indica se il semaforo è condiviso tra thread (uguale a 0) o processi (diverso da 0), lo useremo quindi sempre con 0.
`int sem_wait(sem_t *sem)` esegue una P(sem);
`int sem_post(sem_t *sem)`esegue una V(sem);
`int sem_getvalue(sem_t *sem, int *val)` legge il valore del semaforo e lo copia in val;
ATTENZIONE: in alcune implementazioni il semaforo rosso è 0, in altre è negativo (e indica il numero di processi in attesa);
`sem_destroy(sem_t *sem)` elimina il semaforo. Da NON usare se ci sono processi in attesa sul semaforo (comportamento non specificato).
