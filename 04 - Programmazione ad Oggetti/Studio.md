# teoria

## mod. accessbilità
**public**:
ccessibile da qualsiasi classe; da qualsiasi parte del programma, inclusi altri package.
**private**:
Accessibile solo all'interno della stessa classe; visibile e accessibile solo all'interno della classe in cui è dichiarato.
**default (package-private)**:
Accessibile all'interno della stessa classe e dello stesso package;
**protected**:
Accessibile all'interno della stessa classe, dello stesso package, e dalle sottoclassi (anche se si trovano in un package diverso).

## Tipi
**Tipi Statici:**
Il tipo di una variabile viene dichiarato durante la compilazione e rimane immutabile durante l'esecuzione del programma. Durante la compilazione, il compilatore esegue controlli di tipo statico per garantire che le operazioni su variabili siano compatibili con i tipi dichiarati. Se si tenta di assegnare un valore di un tipo non compatibile a una variabile, il compilatore segnalerà un errore.
**Tipi Dinamici:**
Il tipo di una variabile è associato al valore che contiene e può cambiare durante l'esecuzione del programma. La verifica del tipo avviene a runtime, quando il codice viene effettivamente eseguito, piuttosto che durante la compilazione.
**Tipizzazione Forte:**
In un linguaggio fortemente tipizzato, il sistema di tipo è rigoroso e non consente conversioni implicite tra tipi incompatibili senza una specifica conversione esplicita.
**java**
In Java, il tipaggio è sia forte che statico. Il tipaggio statico implica che il tipo di variabili ed espressioni è noto a tempo di compilazione, utilizzando tipi dichiarati e regole di inference. D'altra parte, il tipaggio forte significa che assegnazioni tra espressioni sono consentite solo se sono "compatibili", ovvero dello stesso tipo o se una è sottotipo dell'altra.
Il sottotipaggio in Java consente a un sottotipo di "sostituire" un supertipo. Le classi che estendono altre classi sono considerate sottotipi delle classi estese, mentre le classi che implementano interfacce sono sottotipi delle interfacce implementate. Questa relazione di sottotipaggio assicura la coerenza nelle assegnazioni e nell'utilizzo di oggetti.

## Override e overload
Stessa firma; ridefinizione; annotazione @override
Stesso nome; tipi o parametri diversi.
L'override di un metodo in Java avviene quando una sottoclasse fornisce una nuova implementazione per un metodo già presente nella sua superclasse. Questo comporta la stessa firma del metodo e permette alla sottoclasse di ridefinirne il comportamento. L'uso dell'annotazione @Override aiuta il compilatore a verificare la corretta sovrascrittura del metodo. 
L'overloading si verifica quando una classe ha più di un metodo con lo stesso nome ma firme diverse. Le firme diverse possono includere un numero diverso di parametri o tipi di parametri differenti. In tal modo, il compilatore e il runtime possono distinguere i metodi in base alle firme, consentendo la definizione di versioni multiple di un metodo con comportamenti diversi.

## final
**Variabili:**
valore non può essere modificato dopo la sua assegnazione iniziale.
**Metodi:**
Applicare final a un metodo impedisce alle sottoclassi di sovrascriverlo. Il metodo definito con final nella superclasse è vincolato all'implementazione fornita e non può essere modificato nelle sottoclassi.
**Classi:**
Applicare final a una classe impedisce l'estensione di quella classe. 
**Parametri:**
Applicare final a un parametro di un metodo indica che il valore del parametro non può essere modificato all'interno del corpo del metodo.

## interfacce
Un'interfaccia in Java è una collezione di metodi astratti o con implementazione di default e metodi statici. Le interfacce forniscono un modo per dichiarare contratti che le classi devono seguire senza definire una implementazione specifica. Una classe può implementare una o più interfacce, garantendo così la conformità ai contratti definiti. L'uso di interfacce favorisce il raggruppamento di comportamenti comuni e favorisce la progettazione basata su contratti.
Da Java 8 in poi, è possibile fornire un'implementazione di un metodo all'interno di un'interfaccia utilizzando la parola chiave default. Questo consente di estendere le interfacce senza rompere la compatibilità con le classi che le implementano già. Sono consentiti anche metodi statici. con l'introduzione di Java 9, è possibile dichiarare campi di istanza non finali nelle interfacce. Una classe può avere campi di istanza, mentre un'interfaccia può avere solo campi public, static, final. Le interfacce non possono avere costruttori.

## Annotazioni
Un'annotazione in Java è un tipo speciale di metadato che può essere applicato a classi, metodi, campi e altri elementi del codice sorgente. Si definisce con la parola chiave @interface e può contenere elementi con valori predefiniti. Le annotazioni possono essere applicate in modo selettivo a diverse componenti del programma, come classi, campi e metodi. La visibilità di un'annotazione può essere limitata utilizzando l'elemento @Target. L'elemento @Retention definisce la visibilità durante l'esecuzione del programma, consentendo di specificare se l'annotazione sarà disponibile solo a livello di codice sorgente, bytecode o durante l'esecuzione. Le annotazioni sono utilizzate per scopi come la documentazione, la generazione di codice, la gestione della sicurezza e altro.

## Definizioni e firma
La definizione di un metodo include il suo nome, tipo di ritorno, parametri e implementazione. La firma di un metodo è una parte della definizione e comprende solo il nome e i tipi dei parametri. La firma è utilizzata per la dichiarazione e la chiamata del metodo, mentre la definizione include anche l'implementazione specifica.

## 1
Si spieghi come può essere commentato il codice Java, e qual è la differenza sintattica (ovvero su come vengono scritti all’interno del codice) e semantica (ovvero per il ruolo che ricoprono) tra commenti normali (su linea singola o multipla) e commenti che invece seguono lo standard Javadoc.

Il codice java può essere commentato su sngola linea anteponendo `//` ai commenti, o nella forma `/* ... */`. Commenti di questo tipo sono annotazioni utili a noi stessi o ad altri programmatori che lavorano sul codice, ma sono tolti al momento della compilazione e pacchettizzazione. 
I commenti Javadoc sono nella forma `/** ... */`, questi vengono tenuti come documentazione al codice in fase di release, per tutto ciò che viene commentato e ha una visiblità pubblica o anche (a seconda di come si imposta la documentazione) protetta o di package. Al loro interno possono essere inseriti dei tag che specificano il significato dei singoli campi/metodi/variabili/precodizioni/postcondizioni, oppure che aggiungono informazioni specifiche su ciò che si commenta. Ad esempio il tag `@deprecated` su un metodo invita l'utente a non usarlo, il metodo è deprecato e prima o poi verrà tolto, è lì per retrocompatiblità. I commenti Javadoc possono essere visti direttamente nell'IDE, se quest'ultimo li supporta.

• 1 punto: commenti normali con // oppure /*..*/
• 1 punto: commenti Javadoc con /** .. */
• 1 punto: i commenti normali “spariscono” dopo la compilazione
• 1 punto: i commenti Javadoc sono parte integrante delle documentazione del codice
• 1 punto: i commenti Javadoc sono strutturati e possono contenere diversi tag

uff mi son dmenticato che il javadoc si integra con html

## 2

Si spieghi che cosa significa fare l’override di un metodo. Si spieghi poi come può essere utilizzato il modificatore final in modo da limitare ciò che una sottoclasse può ridefinire della sua sovraclasse.

Fare l'override di un metodo significa implementare nella classe in cui si sta lavorando un metodo già presente nella superclasse che si sta estendendo. A seconda dell'oggetto su cui il metodo viene invocato, verrà utilizzato o il metodo della sottoclasse o quello della superclasse. Il modificatore final limita questo comportamento. Non posso estendere una classe final. Se estendo una classe normale, non posso fare l'override sui metodi che hanno questo modificatore. Diversa è la semantica nei campi, nei quali il modificatore serve a dire che non possono più cambiare il valore assegnato (tipo costanti in C).

• 1 punto: l’override si ottiene implementando un metodo con la stessa firma di un metodo
• 1 punto: override quando un metodo di una sottoclasse ridefinisce un metodo ereditato
• 1 punto: in questo contesto, final puo’ essere applicato a classi e metodi (sui campi non ha a
che vedere con l’ereditarieta’)
• 1 punto: final su una classe semplicemente impedisce che ci sia una sottoclasse
• 1 punto: final su un metodo impedisce l’override di un metodo

non ho specificatoo la stessa firma

## 3

Si spieghi come si può ottenere un oggetto di tipo Method e come questo possa essere invocato utilizzando i meccanismi di reflection di Java. Si discutano poi le tipologie di errori che si possono ottenere in seguito all’invocazione di tale metodo.

per ottenere un oggetto di tipo Method bisogna usare il metodo `getMethods()` su una classe, poi per usarlo c'è `invoke(params)`. Se il metodo non è pubblico, si può comunque ottenere con `getDeclaredMethods()`. Il meccanismo della reflection va a invalidare tutta l'encapsulation, limitatamente però al contesto di package. Lmao non so un cazzo sulla reflection

• 1 punto: tramite un oggetto Class possiamo accedere a tutti metodi della classe
• 1 punto: tramite un oggetto Class possiamo chiedere un metodo particolare specificandone la firma
• 1 punto: tramite il metodo invoke possiamo invocare un metodo
• 1 punto: tramite l’invoke dobbiamo passare tutti i parametri del metodo invocato
• 1 punto: se non abbiamo accesso al metodo o il metodo e’ astratto/non esiste, otteniamo delle eccezioni ad hoc

## 4
Si spieghi cosa sono le annotazioni in Java, come possono essere implementate, e quali caratteristiche di un’annotazione si possono definire e come.

• 1 punto: meccanismo per aggiungere informazioni alle componenti di una classe accessibili a runtime tramite reflection
• 1 punto: @interface
• 1 punto: come una classe con i propri campi/attributi
• 1 punto: target
• 1 punto: retention

## 5
Si spieghi cosa sono i metodi getter e setter. Si discuta poi quali sono i vantaggi e svantaggi di usare tali metodi rispetto ad avere campi con pari visibilità.

• 1 punto: getter ritorna il valore di un campo
• 1 punto: setter modifica il valore di un campo ricevendo tale valore come parametro
• 1 punto: potrebbero non lavorare su un campo ma sullo stato dell’oggetto
• 1 punto: il setter puo’ controllare che il valore rispetti determinate condizioni
• 1 punto: come svantaggio richiedono l’invocazione di metodi, mentre la lettura e scrittura diretta e’ computazionalmente meno costosa

## 6
Si spieghi cosa significa che un linguaggio di programmazione come Java applica un tipaggio forte (strongly) e statico (static). Si spieghi poi in cosa consiste la relazione di sottotipaggio (subtyping) e come Java permette di definire che una classe è sottotipo di un altro tipo.

• 1 punto: statico significa che il tipo di ciascuna espressione/variabile e’ noto a tempo di compilazione (tramite tipi dichiarati e regole di inference)
• 1 punto: strongly significa che un’espressione puo’ essere assegnata a un’altra solo se e’ “compatibile” (stesso tipo o sottotipo)
• 1 punto: la relazione di sottotipaggio significa che un sottotipo puo’ “sostituire” un altro
• 1 punto: una classe che estende un’altra ne e’ sottotipo
• 1 punto: una classe che implementa un’interfaccia ne e’ sottotipo

## 7
Si spieghi quali classi sono fornite da Java per poter effettuare operazioni di boxing e unboxing su valori numerici. Si spieghi poi in cosa consiste la conversione implicita di valori numerici, e quale comportamento si ha invece con valori boxed. Si individui poi un contesto in cui tale operazioni risultano essenziali

• 1 punto: una classe wrapper/mirror per ogni tipo primitivo
• 1 punto: una classe Number supertipo di tutti i numeri
• 1 punto: con la conversione implicita si puo’ assegnare il valore di un tipo primitivo a una variabile di un altro tipo
• 1 punto: non e’ pero’ possibile assegnare un tipo con “maggiore precisione” ad uno con minore (tipo un double a un float) a meno di non fare un casting/conversione esplicita
• 1 punto: con le classi wrapper/mirror non c’e’ conversione implicita da una all’altra

# Pratica
Nello svolgimento degli esercizi:
• È necessario massimizzare sempre l’information hiding,
• Le classi possono implementare metodi aggiuntivi se ritenuto utile o necessario, ma questi non devono essere visibili al di fuori della classe stessa

## Match
Si implementi una classe astratta Match che rappresenta un incontro sportivo. In particolare, tale classe deve memorizzare i nomi delle due squadre o persone che si sono affrontate nell’incontro (rappresentate come stringhe), e fornire un metodo che ritorna il vincitore dell’incontro o un valore null in caso di pareggio. Deve essere possibile conoscere i nomi delle due squadre esternamente.

```java 
public abstract class Match {
    private String s1;
    private String s2;
    
    public Match(String s1, String s2){
        this.s1 = s1;
        this.s2 = s2;
    }

    public abstract String getWinner();

    public final String getS1(){
        return this.s1;
    }
    public final String getS2(){
        return this.s2;
    }
}
```

• 1 punto: la classe Match ha solo due campi stringa che memorizzano i nomi delle due
squadre
• 1 punto: la classe Match ha un costruttore che inizializza in maniera appropriata i nomi delle
due squadre
• 1 punto: presenza dei getter per i metodi delle squadre, o i campi sono accessibili e final
• 1 punto: presenza di un metodo winner senza parametri che ritorna una stringa
• 1 punto: il metodo winner e’ astratto

buono

# SoccerMatch
Si implementi una classe SoccerMatch che registra, oltre alle informazioni della classe Match, anche il numero di goal segnati da ciascuna delle due squadre, e implementi in maniera adeguata il metodo che ritorna il vincitore dell’incontro.

```java
public class SoccerMatch extends Match {
    private int p1, p2;
    public SoccerMatch(String s1, String s2, int p1, int p2){
        super(s1, s2);
        this.p1 = p1;
        this.p2 = p2;
    }
    @Override
    public String getWinner(){
        if (this.p1 > this.p2) return super.getS1();
        else if (this.p1 <> this.p2) return super.getS2();
        else return  null;
    }
}
```

• 1 punto: la classe SoccerMatch estende Match
• 1 punto: la classe SoccerMatch contiene due campi interi che memorizzano il numero di goal
• 1 punto: il numero di goal non e’ esternamente accessibile
• 1 punto: il costruttore di SoccerMatch invoca il supercostruttore di Match
• 1 punto: il metodo winner e’ implementato in maniera corretta

buono

# SoccerTournament
Si implementi una classe SoccerTournament che rappresenta un torneo calcistico, e che memorizza una collezione di squadre (rappresentate come stringhe) e una collezione di Match di un torneo calcistico. Nel caso in cui la collezione di Match contenga incontri non calcistici, o di squadre non presenti nella collezione di squadre data, il costruttore deve lanciare una eccezione controllata (checked) definita appositamente. Si implementi inoltre un metodo getPoints che data una squadra, ritorna il numero di punti ottenuti da quella squadra nel torneo. Per il calcolo dei punti, dovranno essere conteggiati 3 punti per ogni vittoria, 1 punto per ogni pareggio, e 0 punti per ogni sconfitta. 

```java
public class TeamException extends Exceptions {
    String msg;
    public TeamException (String msg){
        this.msg = msg
    }
}
public class SoccerTournament throws TeamException {
    private List<String> teams = null;
    private List<? extends Match> matches = null;
    public SoccerTournament (){}

    public addTeam(String s){
        this.teams.add(s);
    }

    public addMath(Match m){
        if (!(m instanceof SoccerMatch)) 
            throw TeamException{"solo partite di calcio"}
        Bool found1 = false;
        Bool found2 = false;
        for (String s : this.teams){
            if (m.getS1().equals(s)) found1 = true;
            if (m.getS2().equals(s)) found2 = true;
        }
        if (!found1 || !found2) throw TeamException{"squadre non in torneo"};
        this.matches.add(m);
    }

    public int getPoints(String team){
        int v = 0;
        int s = 0;
        int p = 0;
        for (Match m : this.matches){
            if (m.getS1().equals(s) || m.getS2().equals(s)){
                String w = m.getWinner();
                if (w == null) p+=1;
                else if (w == team) v+=1;
                else s+=1 
            }
        }
        if (v==0 && p == 0 && s == 0) throw TeamException{"La squadra non ha giocato"}
        return v*3 + s*1;
    }
}
```

• 1 punto: la classe SoccerTournament memorizza squadre e match in campi privati e il
costruttore inizializza tali campi correttamente
• 1 punto: c’e’ la definizione di una classe che definisce l’eccezione ad hoc e il costruttore
dichiara che lancia tale eccezione
• 1 punto: il costruttore controlla tramite instanceof che tutte le istanze delle classe siano
SoccerMatch
• 1 punto: il costruttore controlla che entrambe le squadre siano all’interno della collection
che contiene i nomi delle squadre
• 1 punto: il calcolo dei punti e’ corretto

sbagliato definizione e lancio eccezione, sbagliato == invece di equals; sbagliato uso collections.

**exception**
```java
class TournamentException extends Exception {
    public TournamentException(String message) {
        super(message);
    }
}
/*...*/
throw new TournamentException("Lorem ipsum");
/*anche i metodi hanno throws*/
```
**costruttore con collections**
```java
    public SoccerTournament(List<String> teams, List<Match> matches) throws TournamentException {
        this.teams = new ArrayList<>(teams);
        this.matches = new ArrayList<>(matches);
        /*ArrayList<> ha .contains() per verificare "is in"*/
    }
```
**inizializzazione collections**
```java
public static void main(String[] args) {
    List<String> teams = List.of("TeamA", "TeamB", "TeamC");
    List<Match> matches = new ArrayList<>();
    matches.add(new SoccerMatch("TeamA", "TeamB", 2, 1));
    matches.add(new SoccerMatch("TeamB", "TeamC", 1, 1));

    SoccerTournament tournament = new SoccerTournament(teams, matches);
}
```
## Submarine 
Si implementi una classe Submarine che rappresenta un sottomarino. In particolare, tale classe deve memorizzare il nome del sottomarino, la profondità massima a cui può andare il sottomarino, e la profondità attuale. Il livello di profondità è espresso in metri con un valore numerico floating point. Tali informazioni devono essere inizializzate durante la costruzione dell’oggetto, devono essere esternamente accessibili ma non modificabili. Si implementi poi un metodo immersione che riceve un valore floating point che rappresenta di quanto il sottomarino si deve immergere. Nel caso in cui tale valore sia compatibile con la profondità massima, questo metodo deve aggiornare la profondità coerentemente e ritornare un valore true, o in caso contrario non deve modificare la profondità ritornando false.

```java
public class Submarine{
    public final String nome;
    public final float prof_max;
    private float prof_att;
    public Submarine (String nome, float prof_max, float prof_att){
        this.nome = nome;
        this.prof_max = prof_max;
        if (prof_att >= 0 && prof_att <= prof_max) {
            this.prof_att = prof_att;
        } else {
            throw new IllegalArgumentException("La profondità iniziale deve essere compresa tra 0 e prof_max");
        }
    }
    public boolean immersione(float imm){
        if (imm + this.prof_att > this.prof_max) return false;
        this.prof_att += imm;
        return true;
    }
    public float getProfAttuale(){
        return this.prof_att;
    }
}
```

## PoweredSubmarine
Si estenda la classe Submarine con una classe PoweredSubmarine che rappresenta una sottomarino motorizzato. In particolare, il PoweredSubmarine contiene un valore numerico floating point che rappresenta di quanto il sottomarino si immerge quando il motore è acceso, e un flag booleano che è true se il motore è accesso. Si implementino poi due metodi pubblici per accendere e spegnere il motore, e un metodo step() che se il motore è acceso lo fa scendere della profondità attesa, e che ritorna true se e solo se alla fine del metodo il sottomarino è sceso della profondità attesa.

```java
public class PoweredSubmarine extends Submarine{
    private float imm_motore;
    private boolean motore;

    public PoweredSubmarine (String nome, float prof_max, float prof_att, float immersione_motore_acceso){
        super(nome, prof_max, prof_att);
        this.imm_motore = immersione_motore_acceso;
        this.motore = false;
    }
    
    public void accendi(){
        this.motore = true;
    }
    public void spegni(){
        this.motore = false;
    }

    public boolean step() {
        if (this.motore) {
            // Se il motore è acceso, immerge il sottomarino della profondità attesa
            if (super.immersione(this.imm_motore)) {
                return true; // Il sottomarino è sceso della profondità attesa
            }
        }
        return false; // Il sottomarino non è sceso della profondità attesa
    }
}
```
## rescueSubmarine
Si implementi un metodo statico rescueSubmarine che riceve una collezione di Submarine. Per ciascun sottomarino all’interno della collezione, controlla se la profondità attuale del sottomarino è maggiore di quella massima, e in tal caso crea un PoweredSubmarine che può raggiungere tale profondità con il motore acceso.

```java
public class SubmarineRescuer {
    public static void rescueSubmarine(Collection<Submarine> submarines) {
        for (Submarine sub : submarines) {
            if (sub.getProfAttuale() > sub.prof_max) {
                PoweredSubmarine poweredSubmarine = new PoweredSubmarine(
                    sub.nome + "_rescue", 
                    sub.prof_max, 
                    sub.getProfAttuale(), 
                    sub.getProfAttuale() - sub.prof_max
                );
                poweredSubmarine.accendiMotore();
            }
        }
    }
}

```

## Flight
Si implementi una classe Flight che rappresenta un volo aereo. In particolare, tale classe deve memorizzare la città di partenza e di arrivo (rappresentate da stringhe), l’orario di partenza e di arrivo (rappresentati come oggetti istanza di java.util.Date), e il numero del volo (che è un valore numerico intero compreso tra 0 e 9999). Una volta inizializzate, queste informazioni non possono più essere modificate, ma deve essere possibile leggerle esternamente. Il costruttore controlla che l’orario di partenza sia prima di quello di arrivo. Per fare ciò, si possono usare i metodi after e before della classe java.util.Date. Nel caso in cui l’orario di partenza sia dopo quello dell’arrivo, il costruttore deve lanciare un’istanza della seguente eccezione. public class FlightException extends Exception {}

```java
public class FlightException extends Exception {
    public FlightException() {
        super("Errore: l'orario di partenza deve essere prima di quello di arrivo.");
    }
}

public class Flight throws FlightException {
    private final String cityDeparture;
    private final String cityArrival;
    private final Date departureTime;
    private final Date arrivalTime;
    private final int flightNumber;

    public Flight(String cityDeparture, String cityArrival, Date departureTime, Date arrivalTime, int flightNumber)
            throws FlightException {
        if (departureTime.after(arrivalTime)) {
            throw new FlightException();
        }
        this.cityDeparture = cityDeparture;
        this.cityArrival = cityArrival;
        this.departureTime = departureTime;
        this.arrivalTime = arrivalTime;
        this.flightNumber = flightNumber;
    }

    public String getCityDeparture() {
        return cityDeparture;
    }

    public String getCityArrival() {
        return cityArrival;
    }

    public Date getDepartureTime() {
        return new Date(departureTime.getTime()); // Return a defensive copy of Date object
    }

    public Date getArrivalTime() {
        return new Date(arrivalTime.getTime()); // Return a defensive copy of Date object
    }

    public int getFlightNumber() {
        return flightNumber;
    }
}
```
## Airplane
Si implementi una classe astratta Airplane che contenga un elenco di voli che un aeromobile percorre. Ciascuna tratta è un’istanza della classe Flight definita nell’esercizio 1. L’elenco dei voli deve essere inizialmente vuoto, e deve essere visibile solamente dallo stesso package e dalle sottoclassi. La classe Airplane deve implementare poi un metodo per aggiungere un volo all’elenco. Nel caso in cui il volo aggiunto abbia un orario di partenza precedente all’orario di arrivo dell’ultimo volo in elenco, tale metodo deve lanciare una FlightException (definita nel testo dell’esercizio 1)

```java
import java.util.ArrayList;
import java.util.List;
public abstract class Airplane {
    // Elenco dei voli percorribili dall'aeromobile
    protected List<Flight> flights;
    public Airplane() {
        this.flights = new ArrayList<>();
    } 

    protected void addFlight(Flight flight) throws FlightException {
        if (!flights.isEmpty()) {
            
            Flight lastFlight = flights.get(flights.size() - 1);
            if (flight.getDepartureTime().before(lastFlight.getArrivalTime())) {
                throw new FlightException("Errore: l'orario di partenza del nuovo volo precede l'orario di arrivo dell'ultimo volo.");
            }
        }

        flights.add(flight);
    }
}
```

## Boeing747
Si implementi una classe Boeing747 che estende Airplane. La classe Boeing747 deve implementare un metodo che esegue il primo volo dell’elenco. Tale metodo deve controllare che la data attuale (ottenibile istanziando la classe java.util.Date senza passare alcun parametro al costruttore) sia successiva alla data di partenza del volo (usando i metodi after e before specificati nell’esercizio 1), e levare il primo volo dall’elenco. Nel caso in cui una delle condizioni elencate non sia validata, il metodo deve lanciare una FlightException (definita nell’esercizio 1). In caso di successo, tale metodo deve ritornare l’orario di arrivo previsto del volo.

```java
import java.util.Date;
public class Boeing747 extends Airplane {
    public Boeing747() {
        super();
    }

    // Metodo per eseguire il primo volo dell'elenco
    public Date executeFirstFlight() throws FlightException {
        if (flights.isEmpty()) {
            throw new FlightException("Errore: non ci sono voli disponibili per l'esecuzione.");
        }

        Flight firstFlight = flights.get(0);

        Date currentDate = new Date();
        if (currentDate.before(firstFlight.getDepartureTime())) {
            throw new FlightException("Errore: la data attuale è antecedente alla data di partenza del primo volo.");
        }
        flights.remove(0);
        return firstFlight.getArrivalTime();
    }
}
```


# Code Snippsets vari
## Annotations

Esempio basico con annotation su classe
```java
// dichiarazione della annotazione (in sto caso senza campi)
@Target(ElementType.CLASS /*oppure, un array {type, type}*/)
@Retention(RetentionPolicy.RUNTIME /*source, class, runtime. runtime permette l'accesso in runtime tramite reflection*/)
public @interface VeryImportant{}

// uso con reflection (la classe Cat ha l'annotaione @VeryImportant)
public class AnnotationExample {
    public static void main(String[] args){
        Cat myCat = new Cat("micio");
        /*accessing a annotation through reflection*/
        if (myCat.getClass().isAnnotationPresent(VeryImportant.class)){
            System.out.println("this thing is very important");
        }
        else {
            System.out.println("this thing is not very important");
        }
    }
}
```

esempio basico con annotation su metodi. Il metodo "meow" della classe Cat ha l'annotazione @RunImmediately
```java
public @interface RunImmediately{
    int times() default 1; // ha le parentesi ma è un campo
}

@VeryImportant
public class Cat{
    @RunImmediately(times = 4);
    public void meow(){
        System.out.println("Meow!");
    }
}

public class AnnotationExample {
    public static void main(String[] args){
        Cat myCat = new Cat("micio");
        
        if (myCat.getClass().isAnnotationPresent(VeryImportant.class)){
            System.out.println("this thing is very important");
        }
        else {
            System.out.println("this thing is not very important");
        }

        for (Method method : myCat.getClass().getDeclaredMethods()){
            if (method.isAnnotationPresent(RunImmediately.class)){
                RunImmediately annotation = method.getAnnotation(RunImmediately.class)
                for (int i = 0; i<annotation.times(); i++){
                    method.invoke(myCat);
                }
            }
        }

    }
}
```

## Hash, Equals, ToString

```java
import java.util.Objects;
public class SampleClass {
    private int id;
    private String name;

    public SampleClass(int id, String name) {
        this.id = id;
        this.name = name;
    }
    // Metodo equals
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        SampleClass other = (SampleClass) obj;
        return id == other.id && Objects.equals(name, other.name);
    }
    // Metodo hashCode
    @Override
    public int hashCode() {
        return Objects.hash(id, name);
    }
    // Metodo toString
    @Override
    public String toString() {
        return "SampleClass{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
    public static void main(String[] args) {
        SampleClass obj1 = new SampleClass(1, "Object 1");
        SampleClass obj2 = new SampleClass(1, "Object 1");

        // Test dell'override di equals e hashCode
        System.out.println("Equals: " + obj1.equals(obj2)); // Dovrebbe stampare true
        System.out.println("HashCode Obj1: " + obj1.hashCode());
        System.out.println("HashCode Obj2: " + obj2.hashCode());

        // Test dell'override di toString
        System.out.println("ToString: " + obj1); // Dovrebbe stampare "SampleClass{id=1, name='Object 1'}"
    }
}
```