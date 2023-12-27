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
    PrimoProgetto_DnD_PrimeLezioni.characters.Fighter.number_of_instatntiated_fighters = new Random().nextInt(10);
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
* `protected` è visibile nella classe, nell package e anche nelle sottoclassi, ma non ovunque. Finché non parliamo di 
ereditarietà, è del tutto equivalente a `default`.

Con lo `static`, non cambia la visibilità, va specificata oppure rimane quella di default

***
# Appunti 11/10/2023
***

In base a dove mi trovo, ho delle cosidette "views" sulla visibilita. l'idea è di ridurre al minimo indispensabile la
visibilità pubblica degli elementi.
Anche se c'è gerarchia dei packages, non cambia nulla,sempre packages diversi sono.
In JAVA, quando dichiaro qualcosa di privato, è privato a livello di classe.. POsso accedere a un livello privato di un altro
oggetto se esso fa parte della mia stessa classe.
Ogni gruppo di classi simili va contenuto in uno specifico package. In particolare, 
è una buona idea mettere Runner nel package principale di dnd, e mettere il resto in sottopackages, 
"armors", "characters", "fight", "weapons". In questo modo non solo aumento la consistenza e la leggibilità della
struttura del codice, ma ho anche una migliore gestione della visibilità degli elementi.
Facciamo un esempio di cosa vuol dire nascondere gli elementi. Se "weapon" è pubblico, uno che ha accesso al mio
gioco -libreria- avrebbe la facoltà di creare armi a piacimento, andando a rompere il funzionamento. 
Più subdolo è il caso di `is_alive()` : quel che fa è ritornare solo un booleano a seconda dei punti vita, 
ches ono privati. ma se essi fossero pubblici, un utente potrebbe cheatare, andando a modificare direttamente il campo,
facendo personaggi che non muoiono, che risorgono, etc. non solo, se un utente costruisse un metodo che fa il check 
dei punteggi per vedere se un personaggio è morto, si troverebbe a non poter fare pià nulla nell'eventialita io cambiassi
la mia implementazione, mentre se faccio il metodo e cambio l'implementazione, la cosa è del tutto trasparente all'utilizzatore
del mio codice, permettendo cosi una buona mantenibilità e modularità.
Se voglio quindi che qualcuno possa accedere a un campo in lettura, cosa faccio? 
se mi serve`weapon.damage` , al posto di lasciare weapon pubblico, faccio campo `int get_weapon_damage()` e ho risolto
il problema. mi basta un `return this.weapon.damage` e per l'utente finale ho tolto l'accesso al campo, 
lasciando però inalterate le funzionalità progettate.
Dal punto di vista di codice conciso e di performaces, non ha alcun senso, ma è lo standars in programmazione a oggetti, 
la prassi si chiama `getters`, ed è buona prassi non esporre MAI i campi. non è neanche detto che ci siano solo i campi, 
potrebbe essere anche risultato di una computazione. Un get ci da un info sullo stato di un oggetto, ma non è per forza
un campo, può essere anche un'operazione o un numero fisso. 
Ho anche la necessità però di modificare lo stato di un oggetto. Detto fatto, l'equivalente di `get()` è `set()`.
È prolisso da impolementare, per ogni campo c'è almeno uno o due metodi, ma è una pratica essenziale per avere un codice 
robusto e leggibile.

### Documentazioni - API

la build java è un file jar, contiene tutto il bytecode con le gerarchie corrette.
Contiene classi e manifesto, con le info principali. da tante entità atomiche, si fa il pacchetto con tutto il bytecode
e la documentazione. Ma come si commenta?
i commenti servono per spiegare cosa sto facendo. I commenti interni, da standard, sono esclusivamente per il
programmatore, non per chi lo usa. 
Il Javadoc è la documentazione pubblica. Quando creo il jar, posso "compilare" anche i commnti e creare
una documentazione esterna, tipo con doxyfile - anche perché la struttura è quella che uso di base: `/** ... */` 
***
# Appunti 13/10/2023
***
## Encapsulation, Documentazione e Javadoc
Una capsula è un pezzo di codice, chiuso con gli access modifier. La capsula ci vede con l'interfaccia. A livello 
sintattico sono le firme, per sapere cosa fanno le firme si aggiungono i commenti. Al pubblico diamo il jar col 
bytecode e il manifesto.
La sintassi dei commenti è come quella di c++. la doppia `//` è commento per i programmatori, idem `/* ... */`, non viene 
nella documentazione. Lo standard JAVA per la documentazione è `/** ...*/`.
Il commento può essere strutturato: il tag @ ci permette di scrivere informazioni specifiche, per esempio:
- @param: parametri della funzione (argomenti)
- @return: cosa viene ritornato dalla funzione
- @throws: che eccezione viene lanciata in caso di errore
- @since: da che versione esiste il metodo in questione
- @author: autore
- @deprecated: il metodo esiste per retrocompatibilità, ma non si dovrebbe utilizzare e un domani potrebbe essere
anche rimosso

Cosa fare ora che abbiamo dei commenti javadoc? `javac` compila, `java` esegue, `javadoc` genera la documentazione.
Regola importante è mettere la documentazione in una cartella (`doc`) separata da quella del codice (`src`). Cosa viene 
generato? Un file html. Si può generare anche altro, ma HTML è la scelta migliore per come è strutturata e navigabile.
Si può creare anche la doc del package invece che solo della classe.
Solo i campi pubblici compaiono. Tutto ciò che è privato di default non viene generato (ci sono delle configurazioni 
booleane per overwriteare sta cosa). Nella documentazione della classe ci sono:
- Campi
- Costruttori
- Metodi: dei metodi, c'è prima un sommario col testo libero, la documentazione vera e propria con tutti i @ è più in
basso. Buona norma è ripetersi, e fare sommario anche del return sul testo libero.

L'IDE spesso permette di generare javadoc in modo facile a interfaccia grafica, con una marea di opzioni, tra cui la 
visiblità (public, package etc).
Se una funzione non è commentata, ho un warning in fase di creazione. Se ho caratteri speciali in html, ho errori:
in Javadoc infatti si può scrivere vero e proprio html. Esempio di html puro in javadoc: 
```
/**
 * <a "github.com/dadezz>github dell'autore</a> 
*/
```
Ci sono altri tag interni molto importanti a riguardo, degli shortcut:
* @see: link nella sezione "see also"
* @literal: scrive come codice, non interpreta come fosse html (per esempio per espressioni speciali)
* un fottio di altre robe, guardare la... documentazione xD

C++ doc usa doxygen, non ci sono particolari differenze con javadoc, è lo standard per c++, supporta comunque i commenti
javadoc, ma produce la documentazione esternamente rispetto al codice sorgente, ovvero non è integrato con gli IDE.
Quando javadoc documenta un metodo, sull'IDE sfiorando il metodo viene mostrata la documentazione, con doxygen no.
(Utile x es l'autocompletamento).

Qual è il problema dei commenti? sono informali, non verificati, ambigui. Come posso risolvere?
### -> design by contracts
Diritti e doveri delle due parti: chi sviluppa la libreria offre dei servizi, con un agreement su come sono usate le
librerie etc. Il contratto contiene le firme (basico) e i commenti + precodindizioni, postcondizioni e invarianti
***
# Appunti 27/10/2023
## Design by contracts
Il commento diviene a tutti gli effetti parte dell'interfaccia pubblica. Questo approccio by contracts non è ampiamente 
diffuso a livello commerciale. Il contratto più standard è: tu mi dai un servizio e io pago, spesso è molto leggero come
conseguenze da parte del software: aggiornamenti per ban funzionali gratuiti è lo standard, difficile sia altro. Doveri 
per l'utente? Usare il codice come fa documentazione: rispettare la sintassi (il codice non compila, lol) e la semantica.
gli argomenti delle funzioni per esempio devono rispondere a dei prerequisiti (precondizioni) and so on [madonna che
palle ste robe]. Le precondizioni si scrivono in javadoc con `@requires`, tipo `@requires i > 0`. Postcondizione:  ti
garantisco che dopo avermi usato lascio l'oggetto in uno specifico stato. Si indica con `@ensures`. Se il contratto è
rispettato in ogni caso, ovvero non ci sono precondizioni, si usa `@requires true`.Il problema di `@ensures` è che 
praticamente esplode subito. Tutti i casi vanno riportati e difatti è una quasi riscrittura del codice. Ultima 
roba su cui ragionare sono i campi. In particolare, gli invarianti: `@invariant experience_point >= 0 && 
experience_point >= pre(experience_point)`. Si possono usare gli invarianti anche come check per capire se il codice che 
stiamo scrivendo ha senso. Ogni volta che invoco il metodo, l'invariante è vero prima, durante e dopo l'esecuzione.
Permette in qualche modo di ragionare in maniera modulare e "matematica" sul nostro codice. Sti @tag non sono parte del 
core di javadoc, ma sono parte di JML: Java Modeling Language. Problema successivo per la verifica della correttezza dei
programmi: un invariante di ciclo per ogni loop
## Ereditarietà
Un fighter è uno degli Nmila personaggi a cui si può pensare. Prendiamo un wizard. Non c'è una weapon, c'è la magia,
il get_damage è diverso, è uno dei personaggi più distanti.
Notiamo subito però che `private int experience_point;` va copincollato da fighter. Idem altre cose. Poi ci sono alcune 
cose da aggiungere su wizard che non ci sono su fighter, come ad esempio tutta la parte magica. Poi ci sono alcune
robe che non tornano. Per esempio, `defeated` in un fighter presuppone che sia stato un altro fighter a sconfiggerlo.
Ci serve una cosa che, al posto di prendere ogni singola combinazione tra tutti i tipi di personaggi, permetta di
racchiudere tutti i casi in un colpo.
Ed ecco che sorge un altro problema. Anche il package Weapon non è adatto, è da aggiungere un altro package: Magic, 
pure questa con moltissime robe identiche a Weapon, ma altre diverse. 
Stiamo riscrivendo un fottio di codice come copincolla, nammerda.
***
# Appunti 3/11/2023
## ereditarietà e polimorfismo
Fighter e wizard hanno cose in comune e alcune differenze. Si può pensare di fare un personaggio base e poi specializzarlo
Sta roba ci perterà al principio di sostituzione: se ho un oggett di una classe, posso sostituirlo con un oggetto di un
altra classe, a patto che essa mi dia tutte le stesse caratteristiche della classe originale. È la base del 
polimorfismo. 
### aggregazione
Verbo avere. Ho qualcosa: un oggetto ha un riferimento ad un altro oggetto. può essere in condivisione con altri. Per esempio, un 
fighter ha un weapon e un armor. 
### ereditarietà
Verbo essere. un oggetto estende le funzionalità di un altro. riusa il codice specializzandolo, aggiunge funzionalità 
a una classe già definita. Un fighter **è** un personaggio. Un wizard **è** un personaggio. 
La macchina è un veicolo -> estende le informazioni del veicolo. La sintassi che si usa è:
`class Fighter extends Figure`.
Tutti i metodi come `getID` e gli attributi come `NumberOfIStanciedCharacters` posso metterli nella classe esterna.
Parlando di danno e difesa, lo abbiamo fatto in termini specifici per le varie armi. Voglio avere invece un concetto generico
In generale, le classi sono estendibili quanto si vuole, anche svariate volte.
Abbiamo in JAVA ereditarietà singola, ovvero una classe ne può estendere solo una. La classe generale si chiama superclasse.
Costruttori: nella classe, ho un puntatore alla superclasse, `super`, ovvero un modo per interfacciarmi solo con la superclasse.
In particolare, nel costruttore, come prima cosa devo invocare il costruttore della superclasse. 
Per esempio, per il costruttore di wizard:
```java
class Wizard {
    Wizard (int exp, int life, Weapon w1, armor a1) {
        super(exp, life);   //costruttore superclasse
        this.weapon = w1;
        this.armor = a1;
    }
}
```
Come `this`, anche `super.` mi permette di interfacciarmi con la superclasse (metodi e attributi). 
#### Access Modifiers: protected
protected è visibile dal package, dalle sottoclassi, ma non da ovunque.
È il livello più vicino al public. Nel progetto mi aspetto che altri user estendano la mia classe? sì -> lo includo nel 
javadoc come intefaccia pubblica; no -> non lo metto come interfaccia, dipende quindi da scopo e struttura di 
ciò che stiamo facendo.

Importante: `abstract` : la classe non può essere istanziata. Si può anche mettere relativo al metodo, e va a sigificare
che il metodo esiste ma non è definita un'implementazione. Il metodo abstract deve appartenere per forza a una classe 
abstract (altrimenti posso istanziare la classe, e con essa posso invocare il metodo, senza però che esso sia definito).
Il viceversa non è vero. Posso infatti avere una classe abstract con dei metodi implementati all'interno. Perché dò piene
funzionalità ma non voglio che la superclasse possa essee istanziata. Nel momento in cui eredito un metodo astratto, 
eredito l'obbligo di implementarlo, altrimenti devo anche io mettere la mia classe come abstract. 


***
#### mancano le interfacce, ma vabbe
# Appunti 25/11/2023 (Lecture 14 + 15)

## Fine polimorfismo
Come vengono considerati i tipi delle variabili nelle chiamate delle funzioni?
* Metodi degli oggetti:
    * il tipo dell'oggetto ricevente viene calcolato a runtime, per garantire polimorfismo.
      Non c'è quindi necessità di castare esplicitamente l'oggetto:
      ```Java
      Figure f1 = new Wizard;
      ((Wizard) f1).metodo(); // non è necessario.
      ```
    * il tipo degli argomenti di funzione viene calcolato a compilation time, quindi se si vuole specificamente chiamare un metodo più preciso, c'è bisogno di cast esplicito.
* Metodi Statici:
    * L'oggetto ricevente deve essere una classe, cioè, può essere anche un oggetto, ma non sarebbe proprio proprio corretto. Oltretutto, il tipo del ricevente viene calcolato a compilation time (da qui "tipo statico"),  quindi non c'è polimorfismo, e si rischiano atteggiamenti inaspettati qualora si chiamasse una funzione statica su un oggetto con tipo dinamico, in quanto verrebbe eseguita la funzione della superclasse.
    * statici, a compilation time.

Cosa significa che il tipo degli argomenti, nel caso dei metodi, viene calcolato staticamente?
QUando il metodo viene chiamato, comincia dalla classe dell'oggetto (dinamico) ricevente, per poi salire di superclasse in superclasse finché non trova un metodo con la firma che combaci con quello che serve. Anche i tipi degli argomenti vengono estesi verso l'esterno, ciò però comporta un vincolo di ambiguità:
```Java
public void foo (Wizard f1, Figure f2);
public void foo (Figure f1, Fighter f2);
```
L'esistenza di due firme del genere, non viene permessa, il codice non compila, ciò perché la distanza delle due funzioni dalla superclasse è uguale, quindi se in runtime si trovasse a "salire di un livello" e chiamare la funzione su due figure, non saprebbe quale dei due invocare.

## Templates e tipi generici
### Tipi come argomenti

A una vista esterna, i tipi generici di Java sono esattamente identici a i templates di c++. Questi ultimi però duplicano il codice per ogni tipo su cui sono definiti. In Java sta cosa non accade, in quanto esistono realmente tipi "generici".

Ho una classe che riceve come parametri dei tipi. I tipi generici sono stati introdotti in Java 1.5, molto dopo i template di c++. Il tipo generico può essere messo come classe o nei singoli metodi

```Java
public class AlmostEmpty{
    public <T> identity(T param){
        return param;
    }
    public void foo(){
        AlmostEmpty obj = new AlmostEmpty();
        AlmostEmpty obj2 = obj.<AlmostEmpty>identity(new AlmostEmpty());
    }
}
```

Come viene compilato in bytecode? identity ha un tipo generico, ma non esistono a livello di bytecode. Prendo un `Object` e ritorno un Object. (Quest'ultimo è l'istanza della classe che sta sopra a tutte). Viene poi fatto un cast dinamico del tipo, da object al tipo passato come parametro. Dicevamo, si può parametrizzare la classe intera, tipo le liste:
```Java
public class List<T> {
    private T[] elements = null;
        // non posso fare new T[], tipo new String[]
        // perché obv non si sa la memoria da allocare. va quindi messo a null e creato in un altro modo (sotto, in add)
    public T get (int inde){
        return elements[index];
    }
    public int lenght(){
        return elements.length;
    }
    public void add(T el){
        if (elements == null){
            // spiegheremo più avanti
            ArrayList<T> list = new Arraylist<>();
            list.add(el);
            elements = list.toArray(elements);
        }
        elements = Arrays.copyOf(elements, newLength: elements.length +1);
        elements[elements.length-1] = el;
    }
}
```
Quando estendiamo la classe che prende un generico, possiamo estenderla passando tipi specifici. I tipi generici sono invarianti però. A una lista di `Figures` posso assegnare o dei `Figures` o dei `Wizard` (sottotipo), ma non entrambi. Negli array sta roba si può fare e causa problemi in runtime: se il tipo non è dinamicamente compatibile, crasha. 

### Bounded generics
voglio una classe che non riceve qualsiasi tipo, ma solo per esempio dei sottotipi di qualcosa.
```Java
public class ListFigure<T extends Figure> extends List <t>{
}
ListFigure<Wizard> = new ListFigure<>; // works
ListFigure<String> = new ListFigure<>; // doesn't work
```

### Wildcards

Solo accennata, in quanto soluzione sbagliata a problema giusto:

passare <?> invece di un generico type
`List<?>` supertype of `List<T>` for any T

```Java
    List<Figure> f = new List<Figure>();
    List<?> listBoh = f;
    String s1 = listBoh.get(0); //non compila perché non èuna stringa
    Figure s2 = listBoh.get(0); // non compila uguale
    Object s3 = listBoh.get(0); // unica roba che compila
    listBoh.add("pippo"); // per lo stesso motivo, non funziona
```
Stiamo definendo una lista che è supertipo di qualsiasi altra lista, non possiamo farci praticamente nulla. Possiamo però aggiungerci dei bounds, da `extend`. La wildcard funziona bene lì dove la covarianza funziona bene, sul tipo di ritorno. Con i Wildcard, i genereici non sono più covarianti.La variabile con la wildcard però diventa un po' inutilizzabile percHé non definita correttamente al passaggio del valore.

In definitiva, Java è tra i linguaggi OOP mainstream che gestisce nel modo peggiore i tipi generici.

# Appunti 20/12/2023 (lecture 16 + 17)
```Java
this.defensiveMagic = new DefensiveBag<Magic>();
this.defensiveMagic.add(m1);
this.offensiveMagic = new OffensiveBag<Magic>();
this.offensiveMagic.add(m1);
```
Qui ho aliasing, ma stavolta sono io che voglio averlo. La magia è sia difesa che attacco, può andare sia in una che nell'altra bag. Mi serve che lo stesso oggetto sia riferito da entrambe le classi, così da mantenere ilcontrollo sull'evoluzione, usandolo prima in un modo e poi nell'altro.

## Java in Action
**Object**: superclasse di tutto. Nella gerarchia delle classi, ogni classe estede la radic di tutto, che è `object`.
Non estende nessun'altra classe. Ha una serie di metodi già implementati. Una volta esistva il metodo finalize, che era un distruttore.
Il problema è che in java c'è il garbage collector, ma è indefinito quando verrà effettivamente chiamato,, quindi è deprecato e non viene usato.
Poi ci sono alcuni metodi (notify, wait etc) che sono inerenti a multithreading e concorrenza. Poi c'è `getclass()`, che pero vedremo più avanti con la reflection. I metodi che ci interessano sono:
### Equals
In Java non esistono gli operatori come in C++. Per l'operatore ==  esiste `equals` object riceve un altro object. Restituisce True se i due oggettisono ugualli.
Ma qual è la definizione di uguaglianza? 

L'operatore == controlla solo il puntatore all'oggetto, non controlla la semantica dell'operatore. Java ci dà l'override, in cui bisogna metterci il controllo `istance of`.
#### proprietà
La classe è di fatto un insieme, per cui deve rispondere alle stesse regole che esistono in matematica discreta:
* riflessiva
* simmetrica
* commutativa
* transitiva

È figo che l'IDE permette di generarlo in automatico, dicendogli quali campi controllare.


### Clone
fa esattamente quello che pensi. SI puo scegliere di non clonare gli oggetti. in generale è protected. POsso farla anche public, per principio di sostituzione. Non tutti gli oggetti sono clonobli, si può anche specicifare. Clone è protected, deve fornire anche questo una serie di garanzie:
* le due copie devono essere `equals` (uguali semanticamente)
* le due copie devono essere oggetti diversi (separati in memoria)
* il tipo dei due cloni deve essere uguale

Per come è definito il metodo clone, non è una deep copy.

### Hashcode
Ci servono conoscere le tabelle Hash (mappe). 
Se gli oggetti sono ugual, l'hascode deve necessariamente essere uguale.

```Java
public int HashCode(){
    return 0;
}
```

Tecnicamente questa implementazione è corretta. Ha poco senso però. Posso pensare un `return id;`, o un `return id%50`. Sono un peogrammatore ad oggetti, uso le librerie. `return hash(id)`.

## String
È una classe che si trova subito sotto a object ed è `final`. Quando si assegna una stringa ("vdf") viene presa come valore costante nel bytecode. 

```Java
String a = "pippo";
String b = "pippo";
a.equals(b); // True
a == b; // True
```
a e b sono lo stesso oggetto! se cambio a modifico b come side effect?
La classe stringa ha la particolarità di essere immutabile. se si usa il replace, si crea un'altra stringa. 
Altra caratteristica è un'eccezione sugli operatori. il `+` concatena due stringhe. Il metodo si chiama concat, ma è l'unico che ammette l'uso di un operatore, (appunto, il `+`). Una volta il + non era ammesso, ora esistono entrambi,hanno la stessa semantica, ma si comportano in modo diverso. Il concat è costoso perché ogni volta invoca costruttore e mette costante in stack etc, il + ha delle ottimizzazioni a livello di bytecode che permettono di bypassare l'immutabilità delle stringhe (non entriamo nel dettaglio).

### ToString (classe object)
Mostra l'oggetto in forma di stringa. Il default richiama un po' i file json, ma si può modificare a piacimento. A livello di debug, è utile perché è il meotodo usato per mostrare dinamicamente le info dell'oggetto a runtime.Altra funzione utile è per il logging. QUando si concatena una stringa con un oggetto, sullìoggeto viene inovocato a sua volta il ToString().

# Appunti 27/12/2023 (Lecture 18)

Nelle gerarchie delle strutture dati, la root è interafccia iterable, che fornisce iteratori, sotto c'è uinterfaccia Collection. da qui si estendono tre interdfacce: set, List e Queue e una classe Astratta: Abstract Collection.
Quest a sono la base su cui si bassano tutte le altre.

## Set

Interfaccia che eestende l'interfaccia `Collection`. È un insieme matematico. Tanti elementi delo stesso tipo, ogni elemento può coparire al più una volta. Vediamo subito qualche roba ereditata da Object. Per esermpio `equals`. Per come è definito, dati due oggetti del set,`obj1.equals(obj2)` ritorna falso per ogi obj1 e obj2.

Un Hashset è una classe che implementa Set e estende HashTable.

Si può iterare nella forma 
```JAVA
iterator<T> it  = this.iterator();
while(it.HasNext()){
    T current = it.next();
    if (current.getInfoDamage() > result.getInfoDamage()){
        result = current;
    }
    return result.
}
```

Oppure, Java offre i cicli for-each:
```JAVA
iterator<T> it  = this.iterator();
T result = null;
for (T el : this){
    /* if ... */
}
```
Come viene compilato il ciclo foreach? esattamente come sopra. prende l'iterator, guarda se has next etc. Meglio la seconda versione convenzionalmente.
Quando itero non ho garanzie in un hashset sull'ordine ritornato. L'hashtable non ci dà garanzie sull'ordine degli elementi. Un codice deve essere deterministico. Il `TreeSet` invece è un implementazione di `Set` che dà questa garanzia. Il treeset richiede l'implementazione del metodo `compareTo()`. Più si va avanti con classi e strutture dati, più i problemi di ereditarietà multipla si fanno sentire. 
Una cosa molto noiosa è fare una serie immensa di `if ... istanecof ...`. Nelle ultimissime versioni di Java si possono fare dei switch-case statement con espressioni invecedi costanti, tra cui anche dei switch sui tipi. Non vedremo sta cosa xk troppo recente (madonna che reottua di coglioni).

## Tipi Primitivi
`int, double, float, char, long...` etc. Abbiamo visto che Object è il supertipo di tutti i tipi, tranne i tipi primitivi. Per esempio non esiste non esiste la List<int>. i tipi generici non possono essere tipi primitivi. Però esistono una serie di classi che estendono object che rappresentano i tipi primitivi.
Per esempio, posso creare qualcosa del tipo 
```JAVA
int i = 12;
Object o = i;
```
Creo un oggetto, in particolare di tipo `Integer` (la maiuscola lo differenzia dal tipo primitivo), che rappresenta sotto forma di oggetto il tipo primitivo intero.

Il cast contrario è qualcosa del tipo:
```JAVA
Object obj = 5; // obj is an Integer object

    // Cast obj to an int using the intValue() method
    int x = ((Integer) obj).intValue();
    System.out.println(x); // prints 5
```