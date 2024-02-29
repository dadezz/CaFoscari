# Processo
## Creazione 

Questo è ciò che fa il sistema operativo

* creazione nuovo ID
* Allocazione memoria
* Allocazione altre risorse
* Gestione info sul nuovo processo
* Creazione Process Control Block: tabella che contiene le info precedenti (anche detta process descriptor)

### Focalizzazione su: Processi UNIX 
### Relazioni statiche e dinamiche

c'è una gerarchia statica di parentela. Ogni processo è creato da un altro processo con un'opportuna chiamata a sistema, fa eccezione `init` , che ha pid=1. La struttura gerarchica è ad albero: un genitore per ogni figlio.
Le relazioni dinamiche sono a runtime. Per esempio, quando s chiama `sleep`, la shell crea questo processo figlio, aspetta che esso finisca e solo dopo torna a essere disponibile come processo.
Ci sono segnali che possono essere inviati al processo. Per esempio, ctrl+C viene elaborato dalla shell, che lo gira ai figli (infatti non è che esco dalla shell con ctrl+C).
Si può anche dire esplicitamente che un processo debba essere eseguito in background, aggiungendoci una `&` alla fine. Col comando `ps`, posso vedere i processi in exec nell'istanza corrente del terminale, anche quelli in bk. con le opzioni `-o` si dice quali campi del descrittore si possono vedere (`pid,ppid,nice,comm ...` = `id, id parent, priorità, nome del comando etc`). 

### Relazioni di contenuto

nei sistemi unix, il figlio è un fork del genitore, che poi si specializza. in Win invece è un programma differente. 

#### system call FORK
Crea un processo duplicato del genitore
* condivide l'area codice del parent (reference)
* utilizza una copia dell'area dati  (copy)

Genitore e figlio vedono esattamente le stesse cose, sono due cloni. Come faccio a sapere se io, processo, sono clone o l'originale? possono interagire col OS e chiedere il PID, oppure: la fork ritorna un valore, se il valore di ritorno è <0, è errore, se è = 0 è il figlio, se è >0 è il parent (la fork ritorna il pid del figlio).

```c
pid = fork();
if (pid<0)
    perror ("fork error");
else if (pid == 0){
    // codice figlio
}
else {
    //codice genitore, pid>0
}

{
    // il codice ricordiamoci che è condiviso tra parent e child, quindi se è qui sotto lo eseguono entrambi
}
```

**esempio concreto:**

esempio 1:

```c
// Esempio di utilizzo della fork.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid;
  
  printf("Prima della fork. pid = %d, pid del genitore = %d\n",getpid(), getppid());
  
  pid = fork();
  if ( pid < 0 )
    perror("fork error"); // stampa la descrizione dell'errore
  else if (pid == 0) { 
    // figlio
    printf("[Figlio] pid = %d, pid del genitore = %d\n",getpid(), getppid());
  } else { 
    // genitore
    printf("[Genitore] pid = %d, pid del mio genitore = %d\n",getpid(), getppid());
    printf("[Genitore] Mio figlio ha pid = %d\n",pid);
    sleep(1); // attende 1 secondo
  }
  // entrambi i processi
  printf("PID %d termina.\n", getpid());
}
```
esempio 2:
```c
// visualizza l'esecuzione concorrente di genitore e figlio

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid;
  int i;
  
  pid = fork();
  if ( pid < 0 )
    perror("fork error"); // stampa la descrizione dell'errore
  else if (pid == 0) { 
    while(1) {
      for (i=0;i<10000;i++) {} // riduce il numero di printf
      printf("Figlio: pid = %d, pid del genitore = %d\n",getpid(), getppid());
    }
  } else { 
    while(1) {
      for (i=0;i<10000;i++) {} // riduce il numero di printf
      printf("genitore: pid = %d, pid di mio genitore = %d\n",getpid(), getppid());
    }
  }
}
```

non possiamo assumere nulla sullo scheduler,  i processi a volte si alternano inmodo non prevedibile, magari una stampa uno e poi 12 l'altro, la volta successiva ad alternanaza perfetta etc.

**fallimento della fork**
in che senso può fallire? se non ci sono risorse disponibili da allocare. 

```c
// fork bomb
int main() {
    while (1) {
        if (fork()<0){
            perror ("errore fork");
        }
    }
}
```

### processi orfani e zombie
Se il genitore termina prima, si dice che il figlio diventa orfano. In tal caso viene adottato da `init` (genitore di tutti i processi di sistema), o da `upstart`. Interessante sapere che un processo orfano non biene terminato da ctl-C. 
Il processo zombie sono terminati ma in attesa che il genitore rilevi il loro stato di terminazione.

### tricky

Qual è l'output di questo programma? 

```c
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t f1,f2,f3;
  
  f1=fork();
  f2=fork();
  f3=fork();

  printf("%i%i%i ", (f1 > 0),(f2 > 0),(f3 > 0)); 
}
```

Alla fine ci sono 8 processi, quindi sicuramente 8 printf, perché dopo la prima fork, il `f2=fork()` è fatto da entrambi i branch, e così vale per i 4 che vengono creati poi. Cosa contengono le printf? tutte le permutazioni dei 3 valori 0/1. In che ordine? non si può sapere, non è sotto il nostro controllo, dipende dallo scheduler.
Interessante è che la shell può promptare anche in mezzo alle printf, questo è dovuto al fatto che la shell aspetta il primo genitore, i fork figli vanno in background e alla shell non fotte un cazzo di aspettarli, quindi capita che i due processi utilizzino lo stesso stdout a video contemporaneamente, sovrapponendo le scritte.

## Esecuzione e terminazione

### System Call exec

Come si fa a eseguire un programma diverso da quello che ha effettuato la fork?
esiste una chiamata apposita: `exec`. Questa sostituisce codice e dati di un process con quelli del programma che si vuole eseguire.

***copy-on-write*** che senso ha copiare i dati nella fork se se poi li butto via subito? sta cosa permette di fare una copia virtuale dei dati (quindi senza scrivere realmente in memoria fisica): crea una copia della page table, flaggandole come read only. in pratica è memoria condivisa in lettura, che poi viene copiata solamente se utilizzata realmente in scrittura. Quanodo si prova a scirvere su mem read only, viene lanciata un interrupt, il controllo torna al kernel, che sa che che l'interrupt è stata lanciata in modo controllato per fare sta cosa del coppy on write, quindi crea effettivamente la copia per il processo forkato, rimette quella originale in mod anche scrittura e poi rifà continuare il processo.
Con un piccolo overhead nel caso di fork con scrittura, si permettte di evitare la copia in tutti i casi in cui si lancia un exec di un prog diverso.
Cosa accade quando il programma eseguito con exec termina l'esecuzione?
Il processo termina e il codice dopo la exec non viene mai eseguito. L'unico caso in cui la exec ritorna è se va in errore. questo perché il programma viene completamente rimpiazzato. **SI INTENDE IL CODICE FORKATO, NON IL GENITORE**.

**sintassi** 
La exec ha diverse varianti che si differenziano in base al:
* formato degli argomenti (lista o array argv[])
* utilizzo o meno del path della shell
  
```c
execl("/bin/ls", arg(), arg1, ..., NULL);
execlp("ls", arg0, arg1, ..., NULL);
execv("/bin/ls", argv);
execvp("ls", argv);
```
Le prime due varianti prendono una lista di argomenti terminata da NULL. Le altre due, invece, prendono i parametri sotto forma di un array di stringhe (puntatori a char), sempre terminato da NULL. La presenza della ‘p’ nel nome della exec indica che viene utilizzato il path della shell (quindi, ad esempio, non è necessario specificare /bin perché già nel path).

***NOTA***: Per convenzione, il primo argomento contiene il nome del file associato al programma da eseguire. Ad esempio:

```c
#include <stdio.h>

int main(int argc, char * argv[]) {
    int i;
    for(i=0;i<argc;i++) {
        printf("arg %d: %s\n",i,argv[i]);
    }
}

```

Dà il seguente output:

```
$ ./argv prova 1 2 3
arg 0: ./argv
arg 1: prova
arg 2: 1
arg 3: 2
arg 4: 3
```

#### Valore di ritorno
La exec ritorna solamente in caso di errore (-1). In caso di successo, il vecchio codice è completamente sostituito dal nuovo e non è più possibile tornare al programma originale.


#### Shell

Prototipo di shell:

```C
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    pid_t esito=1,i;
    char comando[128], *argv[128], *pch;
    while(1) {
        printf("myshell# "); // il prompt dei comandi
        // il codice che segue separa gli argomenti e
        // salva i puntatori in argv[]
        fgets(comando, 128, stdin);  // legge l'input dell'utente
        pch = strtok (comando," \n"); // "parsa" il primo argomento
        for (i=0; pch != NULL && i < 127; i++) {
            argv[i] = pch;
            pch = strtok (NULL, " \n"); // "parsa" gli argomenti successivi
        }
        argv[i] = NULL; // termina l'array argv con NULL
        if (argv[0] != 0) { // comando vuoto, ignora
            esito=fork(); // crea un processo figlio
            if (esito < 0)
                perror("fallimento fork");
            else if (esito == 0) {
                execvp(argv[0],argv); // esegue il comando!
                perror("Errore esecuzione");
                exit(EXIT_FAILURE);
            }
        }
    }   // il processo genitore (shell) torna a leggere un altro comando
}
```

se lancio un po' di roba, dopo con `ps` vedo un sacco di processi zombies. Vorrei che la protoshell appena fatta possa raccogliere le terminazioni.
Un'altra differenza con una shell vera è che non aspetta il programma figlio, infatti viene printato `myshell# ` anche durante l'exec. Per esempio, se chiamo la sleep in realtà posso continuare a usarla...

## Terminazione di un processo

La terminazione di un processo rilascia le risorse allocate dal SO al momento della creazione (ad esempio la memoria e i file aperti) e “segnala” la terminazione al genitore: alcune informazioni di stato vengono messe a disposizione al processo genitore e devono rimanere memorizzate finché non vengono processate. Parte della informazioni contenute nella PCB vengono quindi mantenute dopo la terminazione, finché il processo genitore non ha eventualmente letto tali informazioni.

Il sistema mantiene almeno:

* il PID,
* lo stato di terminazione;
* il tempo di CPU utilizzato dal processo.


### System call Exit e Wait

* exit: termina il processo (già usata negli esempi per i casi di errore);
* wait: attende la terminazione di un figlio (se uno dei figli è uno zombie ritorna subito senza bloccarsi).

Sintassi

* `exit(int stato)`: termina il processo ritornando lo stato al genitore; Si usano le costanti EXIT_FAILURE e EXIT_SUCCESS che normalmente sono uguali ad 1 e 0 rispettivamente;
* `pid = wait(int &stato)`: ritorna il pid e lo stato del figlio che ha terminato. Si invoca wait(NULL) se non interessa lo stato. Se non ci sono figli ritorna -1.

wait va gestito con una macro:


* `WIFEXITED(status)==true` se il figlio è uscito normalmente con una `exit`. `WEXITSTATUS(status)` ritorna gli 8 bit di stato passati dalla exit.Esempio di codice:
  ```c
  if (WIFEXITED(status))
      printf("OK: status = %d\n",WEXITSTATUS(status));
  ```

* `WIFSIGNALED(status)==true` se il figlio è stato terminato in maniera anomala.  ' ritorna il “segnale” che ha causato la terminazione.Esempio di codice:
  ```c
  if (WIFSIGNALED(status))
      printf("ANOMALO: status = %d\n",WTERMSIG(status));
  ```
* macro analoghe per stop/resume, utili per il tracing dei processi (`WIFSTOPPED`, `WSTOPSIG`, `WIFCONTINUED`).