# Appunti 4.10.2023

***
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
