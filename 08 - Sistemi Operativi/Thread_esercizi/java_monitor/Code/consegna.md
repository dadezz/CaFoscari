Coda prioritaria

La verifica consiste nell’implementazione di un monitor CodeMonitor per la sincronizzazione di un certo numero di thread Persona.
 I thread Persona rappresentano gli utenti di un servizio con uno sportello e due code: una normale e una prioritaria. 
 Le persone, in base al proprio status (verde=prioritarie, blu=normali), si mettono in fila sulla rispettiva coda.

Gli utenti della coda prioritaria hanno la precedenza sugli altri, ma solo se sono arrivati alla fine della coda 
e sono effettivamente in attesa del servizio (se sono in movimento e si stanno accodando non hanno precedenza!).

Un thread Persona si comporta come segue:
```java
Thread Persona(boolean priority) {
    // si accoda e procede fino alla fine della coda
    // è alla fine della coda attende lo sportello
    p.attendiSportello(priority); 
    // va allo sportello e attende il servizio
    // libera lo sportello e esce
    p.liberaSportello(); 
}
```

I metodi del monitor che dovete implementare sono i seguenti:

```java
// La persona è la prossima ad essere servita e attende che si liberi 
// lo sportello. Se la persona è sulla coda prioritaria (priority è
// true) appena lo sportello si libera la persona può procedere. Se
// la persona è sulla coda normale (priority è false) la persona
// attende che non ci siano altre persone in coda prioritaria già
// in attesa e che lo sportello si liberi. In altre parole, dà 
// la precedenza a persone in attesa in coda prioritaria.
synchronized void attendiSportello(boolean priority) 
        throws InterruptedException {
    if (priority) {
        // gestione coda prioritaria
    } else {
        // gestione coda non prioritaria
    }
}

// La persona ha raggiunto lo sportello, ha fruito del servizio e ora 
// lo libera
public synchronized void liberaSportello() {    
} 
```