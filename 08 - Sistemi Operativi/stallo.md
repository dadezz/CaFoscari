# Stallo 
**definizione**: un insieme S di processi/thread è in stallo se tutti i processi/thread di S attendono un evento che può essere effettuato solo da altri processi/thread in S

## Condizioni necessarie per lo stallo
* **mutua esclusione**: senza mutua esclusione non c'è attesa
* mancato rilascio delle risorse:
  * bug: dimenticanza da parte del programmatore
  * bug: loop infiito prima del rilascio
  * bug: condizioni sbagliate
  * **hold and wait:** errore logico: modlità di allocazione risorse (atomica o sequenziale). per esempio raccogliendo le bacchette dei filosofi insieme sono tranquillo, se invece prima chiedo la dx e poi la sx rischio lo stallo -> usare le risorse una alla volta è rischioso
* **assenza di prelazione**: non si può forzare il rilascio di una risorsa
* **attesa circolare** 


le prime tre sono statici, non dipendono dall'esecuzione, o ci sono o no. l'ultima è dinamica, a runtime.

## Evitare lo stallo
* **prevenire**: meglio che curare, se lo preveniamo dopo non dobbiamo più curarcene
* **controllo**: monitoraggio, cerco di reagire a runtime, prima che lo stallo effettivamente avvenga (monitoro le risorse per capire se sono a rischio stallo) 
* **riconoscimento**: lo stallo già c'è. me ne accorgo. resetto (utile ma muoio), oppure rollbaccko (utile ma non sempre e potrei morire uguale)

### prevenzione
provo a far sì che una delle 4 condizioni necessarie siano false. me ne basta una.
1. mutua esclusione: non ha senso negarla se necessaria, dipende dalla *risorsa*
2. possesso&attesa: raccolta atomica. può aver senso, ma non si possono allocare tutte le risorse atomicamente in una volta sola. È un'idea possibile e spesso buona, ma non sempre è possibile. dipende dall'*applicazione*. RIschio di starvation
3. assenza di prelazione: a farlo così a caso rischio di corrompere lo stato. fare orelazione è ok su risorse che hanno uno stato salvabile. dipende dalla *risorsa* 
4. attesa circolare: è a runtime, significa quindi prevenire l'attesa circolare. non devo fare assunzioni su risorse o applicazioni, devo trovare strategie per evitare la cosa. esiste la allocazione gerarchica

#### allocazione gerarchica
L'idea è non costringere i programmi ad allocare tutte le risorse assieme, quindi permetto possesso&attesa, ma fornisco delle policy di ordinamento che evitino l'attesa circolare. 
divido le risorse in categorie con una gerarchia.
Se un processo P richiede una risorsa R_i, essa viene concessa solo se P possiede al massimo risorse R_j, solo con j < i. 

##### esempio filosofi
dò un numero a ogni bacchetta, la gerarchia è l'indice. 
l'applicazione di fatto risulta nel filosofo mancino

### Controllo

Non faccio qualcosa che mi escluda a priori lo stallo, ma controllo la situazione ed evito lo stallo indipendentemente da come è fatto il codice. il controllo può farlo il OS, la JVM, in generale lo strato al di sotto del mio programma.
Lo svantaggio è che ovviamente il controllo non è gratis, c'è overhead, sia in termmini di complessità (di scrittura), che di tempo->gli os generalisti non hanno questi meccanismi, che si possono invece trovare in sistemi embedded. 
Per evitare gli stalli, si usa un grafo di assegnazione (2 tipi di nodi: processi e risorse) che tiene conto di (3tipi di archi):
1. quali risrse sono assegnate a quali processi/thread, (da una risorsa a un processo, assegnamento)
2. quali processi richiedono quali risorse (da un processo a una risorsa, richiesta effettiva)
3. quali processi potrebbero rihiedere quali risorse (da un processo a una risorsa, richiesta possibile)

Per poter usare questo algoritmo, in particolare il punto 3, bisogna assumere che i processi dichiarino inizialmente quali risorse potrebbero utilizzare (assunzione bella forte).

Se arrivo in una situazione in cui ho dei "punti 3" che creano uno stallo se diventano effettivi, è già troppo tardi, devo evitare anche che lo stallo ci sia in potenza (stallo se le frecce tratteggiate fossero continue).

se ho p3 in attesa di p1 e p1 in attesa di p2, che però non aspetta nessuno, ho una **sequenza di terminazione**, o **sequenza sicura** -> < p2, p1, p3 > 

#### Algoritmicamente parlando

Dato un grafo di assegnazione, come si fa a decidere se c'è uno stallo? 
1. 1 sola istanza per risorsa -> lo stallo c'è se e solo se è presente un ciclo
2. più istanze per risorsa -> lo stallo implica il ciclo, ma non viceversa. La non-esistenza di una sequenza sicura implica lo stallo.

L'algoritmo generale si chiama **Algoritmo del banchiere**
partenza: P richiede istanza di R
 * se R non è disponibile, P attende 
 * se R è disponibile, non la concedo immediatamente ma faccio partire una simulazione: simulo l'assegnamento sul grafo.
   * se sul grafo (in cui considero anche le richieste future) individuo lo stallo, metto in attesa P. Sì, anche se la risorsa è effettivamente disponibile
   * altrimenti la assegno

Trovare un ciclo è facile. Come faccio a vedere se c'è una sequenza sicura? 

1. prendo tutte le risorse trateggiate e le trasformo in richieste, e guardo se c'è un processo che ha già tutte le risorse disponibili.
2. aggiungo questo processo alla sequenza sicura e simulo una terminazione -> simulo la liberazione delle risorse che al momento gli sono assegnate
3. torno a 1, finché non ho finito i processi
Se terminano tutti, faccio l'output della sequenza sicuras 