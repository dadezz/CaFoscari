# Segnali
sistema più semplice di comunicazione tra processi. Tenicamente sono interruzioi software causarte da svariati evneti:
* generati da terminale (tipo ctrl+c)
* eccezioni dovute a errori a runtime (segfault, divisione per 0 ...)
* segnali esplicitamente inviati da un procelsso all'altro
* eventi asincroni che vengono notificati ai processi, esempio SIGALARM.

I segnali sono Interruzioni causate da svariati eventi. 
Il sistema posix ha una lista di segnali (macro). La SIGKILL è l'unica non gestibile. non può essere catchata né ignorata. 
azioni possibili:
* term : termina il processo
* ign : ignora il segnale
* core : core dump (comportamento di default): viene salvato l'intero stato di memoria

### Un esempio semplice: alarm

```c
#include <unistd.h>
int main() {
    alarm(3);
    while(1);
}
```

alarm manda un SIGALARM dopo n secondi (serve per dare un timeout). Il default handler termina il processo (`TERM`). La shell analizza lo stato di uscita del programma e stampa il motivo della terminazione (`"alarm clock"`). È la shell che stampa il messaggio, non il programma.

Tramite la system call `signal` è possibile cambiare il gestore dei segnali. La system call prende come parametri un segnal e e una funzione che da quel momento diventerà il nuovo gestore del segnale.

```c
#include <unistd.h>
#include <signal.h>

void AlarmHandler(){
    printf("gestito");
    alarm(3);
}
int main() {
    signal(SIGALARM, alarmHandler);
    alarm(3);
    while(1);
}
```

faccio partire il programma. setto l'handler, imposto l'alarm e inizio a ciclare. dopo 3 secondi printa gestito, ma poi l'handler reimposta l'alarm, e il programma riprende dal while, e ogni 3 sec continua a ripuntare l'allarme, senza terminare mai.

C'è un problema che la signal non è implementata in modo consistente in tutte le versioni di UNIX, per esempio per alcune versioni il gestore viene resettato. Per esempio questo lo fa la versione System V, e se si compila con `--ansi`, che è compliant con questa versione, succede così.
**NOTA**: `sigaction` rimpiazza signal con un’implementazione più stabile nelle varie versioni UNIX. Viene raccomandata se si vuole portabilità.

È possibile passare alla signal le costanti `SIG_IGN` O `SIG_DFL` al posto della funzione handler per indicare, rispettivamente:
* che il segnale va ignorato
* he l’handler è quello di default di sistema

Il valore di ritorno di signal  è:
* `SIG_ERR` in caso di errore
* l’handler precedente, in caso di successo

### Esempio: ctrl+C

Se modifichiamo il gestore del segnale `SIGINT` possiamo evitare che un programma venga interrotto tramite `ctrl-c` da terminale.

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int main() {
    void (*old)(int);
        
    old = signal(SIGINT,SIG_IGN);
    printf("Sono protetto!\n");
    sleep(3);
        
    signal(SIGINT,old);
    printf("Non sono più protetto!\n");
    sleep(3);
}
```

Notare l’uso del valore di ritorno della signal per reimpostare il gestore originale. La signal, quando va a buon fine, ritorna il gestore precedente del segnale, che salviamo nella variabile `old`. Quando vogliamo reimpostare tale gestore è sufficiente passare old come secondo parametro a signal.

Se eseguiamo il programma possiamo osservare che per 3 secondi `ctrl-c` non ha alcun effetto. Appena viene reimpostato il vecchio gestore, invece, `ctrl-c` interrompe il programma.

## System call KILL
Confonde, non manda sigkill, ma serve a mandare un segnale qualsiasi a un altro processo.

In questo esempio mostriamo come la chiamata a sistema kill possa essere utilizzata per sospendere, ripristinare e terminare un processo.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
int main(){
    pid_t pid1,pid2;
    pid1 = fork();
    if ( pid1 < 0 ) {
        perror("errore fork"); exit(EXIT_FAILURE);
    } else if (pid1 == 0)
        while(1) { // primo figlio
            printf("%d è vivo !\n",getpid());
            sleep(1);
        }   
    pid2 = fork();
    if ( pid2 < 0 ) {
        perror("errore fork"); exit(EXIT_FAILURE);
    } else if (pid2 == 0)
        while(1) { // secondo figlio
            printf("%d è vivo !\n",getpid());
            sleep(1);
        }
    // processo genitore
    sleep(2);
    kill(pid1,SIGSTOP); // sospende il primo figlio
    sleep(5);
    kill(pid1,SIGCONT); // risveglia il primo figlio
    sleep(2);
    kill(pid1,SIGINT); // termina il primo figlio
    kill(pid2,SIGINT); // termina il secondo figlio       
}
```

## Mascherare i segnali

A volte risulta utile bloccare temporaneamente la ricezione dei segnali per poi riattivarli. Tali segnali non sono ignorati ma solamente ‘posticipati’.

*NOTA: POSIX non specifica se più occorrenze dello stesso segnale debbano essere memorizzate (accodate) oppure no. Tipicamente se più segnali uguali vengono generati, solamente uno verrà “recapitato” quando il blocco viene tolto.*

È molto più comune mascherare un segnale che non ignorarlo. è utile per esempio se sto facendo operazioni delicate in memoria, che rischio di mandare in vacca in caso di interferenze.
La chiamata a sistema `sigprocmask(int action, sigset_t *newmask, sigset_t *oldmask)` compie azioni differenti a seconda del valore del primo parametro `action`:

* `SIG_BLOCK`: l’insieme dei segnali newmask viene unito all’insieme dei segnali attualmente bloccati, che sono restituiti in oldmask;
* `SIG_UNBLOCK`: l’insieme dei segnali newmask viene sottratto dai segnali attualmente bloccati, sempre restituiti in oldmask;
* `SIG_SETMASK`: l’insieme dei segnali newmask sostituisce quello dei segnali attualmente bloccati (oldmask)

Per gestire gli insiemi di segnali (di tipo sigset_t) si utilizzano:
* `sigemptyset(sigset_t *set)` che inizializza l’insieme set all’insieme vuoto
* `sigaddset(sigset_t *set, int signum)` che aggiunge il segnale signum all’insieme set

L’esempio mostra come bloccare SIGINT e poi ripristinarlo.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    sigset_t newmask,oldmask;

    sigemptyset(&newmask);          // insieme vuoto
    sigaddset(&newmask, SIGINT);    // aggiunge SIGINT alla "maschera"
    // setta la nuova maschera e memorizza la vecchia
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("errore settaggio maschera"); exit(1); 
    }

    printf("Sono protetto!\n");
    sleep(3);

    // reimposta la vecchia maschera
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("errore settaggio maschera"); exit(1); 
    }
    printf("Non sono piu' protetto!\n");
    sleep(3);
}
```

### Attesa tramite `pause`

Negli esempi abbiamo sempre usato while(1){} per attendere un segnale (busy-waiting). La system call pause() attende un segnale senza consumare tempo di CPU. Vediamo un esempio:

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarmHandler()
{
    printf("questo me lo gestisco io!\n");
}

int main()
{
    signal(SIGALRM, alarmHandler);
    alarm(3);
    pause();
    printf("termino!\n");
}
```

## Interferenze e funzioni safe
L’uso della `printf` nell’handler è rischioso perché usa strutture dati condivise dai diversi processi: Se anche il programma interrotto stava facendo I/O i due potrebbero interferire! printf non è “safe”. Facendo `man 7 signal` (in sistemi Linux recenti), troviamo la lista di funzioni safe che sicuramente non creano problemi di interferenza:
Il seguente esempio cerca di far interferire le printf aggiungendo nel ciclo while la stampa di una stringa. Se il programma viene interrotto proprio durante la stampa, la printf del gestore potrebbe interferire con quella del programma.
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarmHandler();    // gestore
static int i=0;     // contatore globale `volatile'

int main() { 
    signal(SIGALRM, alarmHandler);
    alarm(1);
    while(1){
        printf("prova\n");
    }
}
void alarmHandler()
{
    printf("questo me lo gestisco io %d!\n",i++);
    alarm(1);   // ri-setta il timer a 1 secondo
}
```

Tipicamente le stampe sono troncate o mischiate. In alcuni casi si possono addirittura perdere alcune printf (e/o alcuni a-capo) perché eseguite a metà di un’altra printf. In casi estremi può accadere che il programma vada in errore e si blocchi.

*NOTA è necessario eseguire il comando con in coda “ | grep io” per evitare di osservare tutte le stampe “prova”. Il comando 'grep' stampa solo le linee contenenti la stringa “io” (che compare in “questo me lo gestisco io”). la pipe ‘|’ fa si che l’output del comando venga reindirizzato al comando successivo come input (è un modo per creare ‘al volo’ un canale di comunicazione message passing tra due processi, che approfondiremo la prossima volta).*