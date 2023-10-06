# Appunti 4.10.2023

*****
### Come funzia il costruttore
La new del bytecode fa l'alloc di C, ovvero alloca la memoria.
in Java è inizializzata tutta a 0. Dopodiché duplica l'indirizzo appena creato, 
mette sullo stack i parametri passati, ed esegue il costruttore.

I campi sono tutti sempre inizializzati all'interno del costruttore, in maniera esplicita

***
### 'This'
In Java non esistono procedure, tutti i metodi devono essere definiti
su una classe, e invocati su un oggetto, chiamato "receiver".
All'interno dei metodi, se non specificato, il metodo viene invocato sull'
oggetto corrente. Si può anche rendere esplicito il tutto, usando la keyword "This".
```
this.MetodoInvocato()
```
This è un puntatore all'oggetto corrente. Nel contesto di DnD, posso anche fare una roba del tipo:
``` 
void autodestroy(){
    while(this.isAlive());
    this.fight(this);
}
```
This può anche esere usato per invocare un costruttore da un altro costruttore,
come nome di un metodo, che permette di non scrivere esplicitamente una duplicazione di codice.
This non può mai essere assegnato obv.

***
### Modificatori
A classi, campi e oggetti, si possono aggiungere i modificatori.
I modificatori di Accesso permettono di restringere i permessi di accesso al codice
##### static
Voglio fare qualcosa che non sia per forza attaccato a un'istanza della classe (un oggetto).
Ecco la keyword `static`. Un campo statico appartiene alla classe. Non c'è da creare un oggetto e invocarlo
su esso, mi basta il nome della classe. Il campo non appartiene all'oggetto ma alla classe (come fosse una
var globale).

La memoria per il campo statico viene allocata all'iniziio dell'exec, non ogni volta che istanzio
un oggetto. 
Come il campo statico, un metodo statico non ha bisogno di istanziare la classe.
Non esiste quindi l'oggetto corrente -> non esiste `this`. 
Un metodo che non opera sullo stato corrente dell'oggetto, è buona norma metterlo esplicitamente
statico (per esempio, se un metodo modifica un campo statico o fa un print, mettilo statico) -> ecco
spiegato il `public static void main()`.
Un campo statico si può usare per esempio come campo locale riferito a tutte le istanze. Per esempio, 
nel nostro contesto: `fighter` può avere come campo `max_point`, ovvero un campo non riferito all'oggetto
ma alla classe, che tiene conto del massimo punteggio mai raggiunto da un fighter.
Se fosse relativo a un oggetto, verrebbe eliminato ogni fine vita (scope) -> variabile globale.

Posso scrivere un pezzo di codice così: 
```
static{
    PrimoProgetto_DnD_PrimeLezioni.Fighter.number_of_instatntiated_fighters = new Random().nextInt(10);
}
```
Questo costruttore statico viene eseguito all'inizio dell'esecuzione (o meglio, quando la classe viene caricata
dalla JAVA virtual machine), e può accedere a ogni campo e metodo statico.
#### final
è praticamente un const. è un campo che non posso modificare. Non compila se non viene inizializzato, deve per forza
stare all'interno del costruttore, e poi mai più modificato.
Si può usare insieme a static: `static final MAX_ID = 100`: variabile globale e const.

***

# Appunti 06/10/2023
***
### References and values types
Possiamo dividere i tipi di java in 2 categorie: 
* Valore (primitivo: int, long, float, double, char, bool)
* Rererence Type: oggetti, array etc

In Java non ci sono puntatori, quando abbiamo reference type è di fatto un puntatore, 
ma a noi è del tutto trasparente, si occupa il linguaggio della gestione della memoria.
Reference type sono i tipi definiti dalla classe del programma. Iniziano con la lettera maiuscola.
Si noti che, essendo reference values, quindi puntatori, se modifico un campo dentro a uno scope, lo modifico ovunque.
Non vale sta cosa invece per i value types, che sono interni allo scope (perché appunto sono valori, non puntatori).
```
if (new Random().nextBoolean()>0.95){
    System.out.print("Increasing damage");
    w1.damage = w1.damage*2;
    w2.damage = w2.damage*2;
```
***
### Aliasing
Conflitti sul nome delle classi, va a rompere il concetto di modularità.
***
### Packages
Ho una directory con tutto quanto dentro. Voglio strutturare il codice in modo più intelligente, strutturandolo in directory.
Il cambiamento delle directory richiede una modifica del codice, Come prima riga bisogna mettere `package path_directory`.
Chiamando il package con i punti (`.`) si costruiscono dei sotto-packages, o sotto directory, come i `/` in github.
JAVA ha scelto come standard di fare i package come fossero domini, il nome del package deve rispecchiare la struttura delle
directory.

Per importare delle sottoclassi, si usa la keyword `import`.
```
import path.path.sottodirectory.Armor
import path.path.sottodirectory.Weapon
```

C'è un modo di importare tutte le classi di una directory
```
import path.path.sottodirectory.*
```
È però poco utilizzata e anche un po' deprecata, perché 
* "tanto gli ide fan tutto": l'IDE vede già tutte le classi disponibili e suggerisce le azioni necessarie
* se importo una singola classe, ci possono essere ottimizzazioni

***
### Encapsulation
Abbiamo una capsula, entità a sé stante, in cui si nasconde l'impostazione interna. La classe weapon ha un damage, 
ma per modificarlo dobbiamo da un altra classe accedere alla classe weapon e modificare il campo, che non è la migliore 
delle cose. Voglio garantire la consistenza dello stato computazionale senza rivelare i dettagli implementativi e 
proteggendo i campi.
* `private` è una keyword che fa sì che il metodo o il campo possano essere visti solo dalla classe a cui appartiene.
* `public` tutti lo vedono
* `se non scrivo nulla` -> la visibilità di default è del package. le classi nello stesso package lo possono vedere

