# Pipe
la pipe è tecnicamente una porta di comunicazione. La send è asincrona e receive sincrona. Pipe significa tubo. si mandano messaggi da un lato e si ricevono dall'altro. Ce ne sono di due tipi: senza nome (solo tra processi con antenati comuni) o con nome (Tipo file speciaòle che possono usare tutti).

## Pipe senza nome
La creo direttametne da dentro il programma, con la system call `pipe(int filedes[2])`. anche la barretta `|` è una pipe senza nome che dichiaro on the fly, per esempio tra `ls` e `grep`. La shell crea due processi separati e una pipe senza nome, in cui butta tutto l'output di ls, che usa poi come input di grep. (di default, solo lo std out). Ls butta tutto in un buffer, asincronicamente, mentre grep aspetta finché non ha effettivamente qualcosa in input. La pipe è mompdorezioanle (dettoo half-duplex): esistono due distinti descrittori per legggere e scrivere. filedes[0] è la send, mentre filedes[1] è la receive. 

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main() {
    int fd[2];

    pipe(fd); /* crea la pipe */
    if (fork() == 0) {
        char *phrase = "prova a inviare questo!";

        close(fd[0]);                         /* chiude in lettura */
        write(fd[1],phrase,strlen(phrase)+1); /* invia anche 0x00 */
        close(fd[1]);                         /* chiude in scrittura */
    } else {
        char message[100];
        memset(message,0,100);
        int bytesread;

        close(fd[1]);                         /* chiude in scrittura */
        bytesread = read(fd[0],message,99);     /* di fatto è la receive */
        printf("ho letto dalla pipe %d bytes: '%s' \n",bytesread,message);
        close(fd[0]);                         /* chiude in lettura */
    }
}
```
la ram non viene condivisa, ma copiata. le risorse invece vengono condivise, quindi la pipe usata è la stessa. prima facciamo la pipe senza nome, dopodiché si fa la fork e in modo naturale la pipe viene ereditata da tutti iprocessi figli.
Creo la pipe -> faccio la fork -> pipe ereditata -> chi scrive chiude subito in lettura, scrive e chiude in scrittura -> chi legge chiude in scrittura, legge e chiude in lettura. La read è una chiamata di sistema bloccante. si azzera il buffer per assicurarsi che la stringa termini correttamente con `\0`.
Perché la chiusura etc in questo modo? ogni processo ha i processori dei file aperti. fd[0] ce l'ho in entrambi i orocessi, ho due copie. Chiudo subito quello che non mi serve, per dire al sistema operativo che non ho bisogno di leggerlo. in sto modo c'è un solo processo che legge e un solo processo che scrive. La pipe è implementata in modo trasparente al programmatore, dal sistema operativo. fd[2] viene scritto in automatico dalla pipe, con delle reference ai descrittori. si occupa di tutto l'OS. 
La chiusura è importante sia per liberare le risorse, che per avvisare il processo che legge che non ha più bisogno di scrivere.
### errori
Se facciamo una read su una pipe vuota e chiusa in scrittura, La read ritorna 0 e non viene letto nulla. Leggere da una pipe chuisa, è come essere arrivati a EOF, la read lo gestisce tornando 0 (perché ritorna il numero di byte che ha letto). 
La SIGPIPE interrompe il processo, quindi questa gestione è migliore xk non interrompe nulla. È anche per questoo che è importante chiudere il buffer, perché sennò la read continua a attendere e stare bloccata.

Se facciamo una write su una pipe chiusa il lettura, viene generato SIGPIPE e il processo viene terminato. Se il segnale viene gestito, invece di essere ammazzato, la write ritorna -1 per segnalare l'errore nella systemcall. Scrivere dei byte su una pipe chiusa in lettura è un errore grave, perché è come se buttassi via i byte, non se li leggerebbe nessuno. non è come leggere qualcosa che non c'è. È utile che di default muoua il processo per esempio quando la creo sulla shell. Se grep muore, è inutile che ls continui a scrivere sulla pipe, che tanto nessuno legge.

#### esempio: pipe di shell
```c
#include <stdio.h>
#include <unistd.h>
int main(int argc, char * argv[])
{
  int fd[2], bytesread;
  
  pipe(fd);
  if (fork() == 0)  {
    close(fd[0]);     	/* chiude in lettura */
    dup2(fd[1],1);      /* fa si che 1 (stdout) sia una copia di fd[1] */
                        /* da qui in poi l'output va sulla pipe */
    close(fd[1]);       /* chiude il descrittore fd[1] */
    execlp(argv[1],argv[1],NULL);   /* esegue il comando */
    perror("errore esecuzione primo comando");
  } else {
    close(fd[1]);       /* chiude in scrittura */
    dup2(fd[0],0);      /* fa si che 0 (stdin) sia una copia di fd[0] */
                        /* da qui in poi l'input proviene dalla pipe */
    close(fd[0]);       /* chiude il descrittore fd[0] */
    execlp(argv[2],argv[2],NULL);   /* esegue il comando */
    perror("errore esecuzione secondo comando");
  }
}
```

creo la pipe, faccio la fork, chiudoo il descrittore che non uso, duplico quello che mi interessa, chiudo quello orginale, ed eseguo il programma

¯¯¯¯¯¯¯
0: stdin
¯¯¯¯¯¯¯
1: stdout
¯¯¯¯¯¯¯
2: stderr
¯¯¯¯¯¯¯
3: inputpipe
¯¯¯¯¯¯¯
4: outpipe
¯¯¯¯¯¯¯

quello che fa `dup2` è redirezionare l'output standard in input pipe: mette l'indirizzo della pipe nell'indirizzo dello stdout, così facendo qunando scrivo sul descrittore in posizione 1 nella tabella, in realtà lìindirizzo a cui sono rediretto è quello della pipe. Chiudo poi la riga 3 della tabella (fd[0], inputpipe) così da dire al sistema operaivo (che conta quante volte una risorsa è aperta), che non ho reference aperte su quella risorsa.
*nota: l'operatore > in shell è esattamente un redirect dell'input, e funziona con dup*.

## Pipe con nome

è un file. `mkfifo mypipe`: crea un first-in-first-out file di nome mypipe. Per esempio un `cat mypipe` apre la pipe. la open è bloccante finché qualcuno non la apre in scrittura. 
```shell
# terminale1:
cat > test.txt

#terminale 2:
cat test.txt
```
il secondo terminale è bloccato in attesa, ogni volta che scrivo qualcosa nel primo e ci metto `\n`, compare nel secondo. La pipe è un file.

## Esercizio:

Consideriamo un processo lettore (destinatario) che accetta, su una pipe con nome, messaggi provenienti da più scrittori (mittenti). Gli scrittori mandano 3 messaggi e poi terminano. Quando tutti gli scrittori chiudono la pipe il lettore ottiene 0 come valore di ritorno dalla read ed esce. Lettori e scrittori sono processi distinti lanciati indipendentemente (non necessariamente parenti).

### Lettore

(`mkfifo` è anche una syscall che posso usare in C).

```c
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#define PNAME "/tmp/aPipe"
int main() {
    int fd;
    char leggi;

    mkfifo(PNAME,0666); // crea la pipe con nome, se esiste gia' non fa nulla
    fd = open(PNAME,O_RDONLY); // apre la pipe in lettura
    if ( fd < 0 ) { 
        perror("errore apertura pipe"); 
        exit(1);
    }
    while (read(fd,&leggi,1)) { // legge un carattere alla volta fino a EOF
        if (leggi == '\0'){
        printf("\n"); // a capo dopo ogni stringa
        } else {
        printf("%c",leggi);
        }
    }
    close(fd);      // chiude il descrittore
    unlink(PNAME);  // rimuove la pipe
    return 0;
}
```
## Atomicità

se si scrivono messaggi sotto il limite di dimensione PIPE_BUF (definito dal OS, tipicamente 4096 byte), le scritture sono atomiche, mentre non è garantita sta cosa per stringhe più lunghe, possono creare interferenze