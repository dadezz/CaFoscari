/*
 * COMMENTO GENERALE (necessario per la sufficienza!):
 *
 * - Come si è arrivati a scegliere le strutture dati utilizzate per la 
 *   sincronizzazione
 *
 * Per la sincronizzazione utilizziamo:
 *
 * 1. un booleano 'occupato' che tiene traccia dello stato di occupazione 
 *    dello sportello. Il booleano è inizializzato a false per indicare 
 *    che lo sportello è libero;
 * 2. un booleano 'p_attende' che tiene traccia se una persona è in attesa 
 *    sulla coda prioritaria. Il booleano è inizializzato a false per 
 *    indicare che nessuna persona inizialmente è in attesa sulla coda 
 *    prioritaria.
 *
 * - Come funziona, intuitivamente, la sincronizzazione
 *
 * la funzione 'attendiSportello' si comporta diversamente a seconda che la 
 * coda sia prioritaria o meno:
 *
 * 1. Coda prioritaria: la persona attende solo se lo sportello è 'occupato'.
 *    Tuttavia, è necessario porre 'p_attende' a true prima di entrare nel
 *    nel ciclo while in modo da segnalare una potenziale attesa prioritaria.
 *    La variabile 'p_attende' viene rimessa a false dopo l'uscita dal while.
 *    In questo modo le persone in coda non prioritaria potranno dare la
 *    precedenza a quelle in coda prioritaria.
 * 2. Coda non prioritaria: la persona attende se c'è qualcuno già in attesa
 *    in coda prioritaria oppure se lo sportello è occupato. In questo modo
 *    viene data la precedenza alla coda prioritaria.
 *
 * La persona che va allo sportello lo occupa settando 'occupato' a true e
 * poi ponendolo a false nella funzione 'liberaSportello'.
 *
 * - Come sono state utilizzate le wait e le notify / notifyAll
 *
 * La wait viene usate in 'attendiSportello' nel caso che 
 *
 * - la persona è sulla coda prioritaria e lo sportello è occupato
 *   ('occupato' è true)
 * - la persona è sulla coda non prioritaria e c'è una persona in attesa 
 *   sulla coda prioritaria oppure lo sportello è occupato ('p_attende' || 
 *   'occupato')
 *
 * La notifyAll viene fatta su 'liberaSportello' dopo che lo sportello è
 * stato liberato ('occupato' è posto a false). E' necessaria la notifyAll
 * per svegliare le persone in entrambe le code.
 * Le wait sono racchiuse in un while in modo da ri-verificare la 
 * condizione di bloccaggio. Se venisse sbloccato erroneamente un thread
 * questo non sarebbe un problema perché si ribloccherebbe autonomamente.
 *
 */
public class CodeMonitor {    
    Boolean occupato = false; // lo sportello è occupato? 
    Boolean in_attesa = false; // c'è qualcuno nella coda prioritaria?


    // La persona è la prossima ad essere servita e attende che si liberi 
    // lo sportello. Se la persona è sulla coda prioritaria (priority è
    // true) appena lo sportello si libera la persona può procedere. Se
    // la persona è sulla coda normale (priority è false) la persona
    // attende che non ci siano altre persone in coda prioritaria già
    // in attesa e che lo sportello si liberi. In altre parole, dà 
    // la precedenza a persone in attesa in coda prioritaria.
    synchronized void attendiSportello(boolean priority) throws InterruptedException {
        if (priority) {
            while(occupato) {
                in_attesa = true;
                wait();
            }
            in_attesa = false;
        } else {
            while(occupato || in_attesa) wait();
        }
        occupato = true;
    }

    // La persona ha raggiunto lo sportello, ha fruito del servizio e ora 
    // lo libera
    public synchronized void liberaSportello() {   
        occupato = false;
        notifyAll(); 
    } 
}
