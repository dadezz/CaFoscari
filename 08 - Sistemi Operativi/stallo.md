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
2. possesso&attesa: raccolta atomica. può aver senso, ma non si possono allocare tutte le risorse atomicamente in una volta sola. È un'idea possibile e spesso buona, ma non sempre è possibile. dipende dall'*applicazione*
3. assenza di prelazione: a farlo così a caso rischio di corrompere lo stato. fare orelazione è ok su risorse che hanno uno stato salvabile. dipende dalla *risorsa* 
4. attesa circolare: è a runtime, significa quindi prevenire l'attesa circolare. non devo fare assunzioni su risorse o applicazioni, devo trovare strategie per evitare la cosa. esiste la allocazione gerarchica

#### allocazione gerarchica
L'idea è non costringere i programmi ad allocare tutte le risorse assieme, quindi permetto possesso&attesa, ma fornisco delle policy di ordinamento che evitino l'attesa circolare. 
divido le risorse in categorie con una gerarchia.
Se un processo P richiede una risorsa R_i, essa viene concessa solo se P possiede al massimo risorse R_j, solo con j < i. 

##### esempio filosofi
dò un numero a ogni bacchetta, la gerarchia è l'indice. 
l'applicazione di fatto risulta nel filosofo mancino