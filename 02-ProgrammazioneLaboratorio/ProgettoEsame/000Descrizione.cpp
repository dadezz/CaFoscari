/**
 * GOAL:
 * scrivere un parser di file in formato json (semplificato) e un oggetto che lo memorizzi. Simile a XML. (specifiche su github)
 * Il container deve permettere l'accesso tramite iteratori e overloading di operatori.
 * I file json sono degli alberi (grammatiche context free), possiamo avere sia liste di valori che dizionari.
 * 
 * FORMATOJSON:
 * 
 *      LISTE:
 * aperte da parentesi quadre e contengonoo altri json separati da virgole.i jso n possono essere o json a loro volta (liste), o dizionari, 
 * o stringhe tra doppi apici, o booleani, o double, o Null. I separatori (\n, \t, etc) vanno ignorati. 
 * l'unica eccezione ovviamente sonogli spazi nelle stringhe tra virgolette.
 * nota sulle stringhe: possono contenere carattere escape. nel nostro caso li ignoreremo, escluso 
 * il carattere \" (vanno estratti sia \ che ", senza far finire la stringa).
 * 
 *      DIZIONARI:
 * insieme di coppie "chiave: valore". è racchiuso tra graffe. le chiavi sono stringhe (semplificazione rispetto al json originale).
 * poi ci sono i due punti, a destra possono esserci ricorsivamente file json, quindi o tipi base o altre liste / dizionari. 
 * Ogni coppia è separata da virgole. I dizionari associano a una chiave un valore, sono come le map in cpp.
 * 
 * CONTAINER:
 *      
 *      CLASSE:
 * Si trova la dichiarazione in json.hpp (sempre su github). c'è libertà sul tipo di strutture dati da usare, infatti si usa il sistema pimpl.
 * volendo, nella struct pimpl si possono aggiungere metodi, ma non dovrebbe essere necessario. NON è classe templatizzata.
 * cosa devo mettere in json impl? è una struct, che deve contenere 6 tipi: null, double, bool, string, list(di json), 
 * un dizionario (un insieme di coppie <stringa, json>). Abbastanza naturale che saranno 6 variabili. 
 * un oggetto json userà solo una di queste variabili (soluzione sporca, vedremo l'ereditarietà prossimo anno, a OOP).
 * La classe contiene dei tipi: json::impl, json::list_iterator, json::dictionary_iterator (e i relativi const degli ultimi due). 
 * 
 *      ECCEZIONI:
 * Nel file json è contenuta la struttura json_exception. si lancia l'eccezione con un messaggio qualsiasi da noi scelto. 
*/

//metodi pubblici: costruttori (default, copy, move, ~), assegnamenti (copy e move). Il costruttore di default deve costruire un oggetto json di tipo null

bool is_null(); //deve restituire true quando viene lanciato il costruttore.
// distruttore ~json(); //attenzione ai memory leaks
bool is_list(); bool is_dictionary(); // etc, come is null. SOLO UNO di questi metodi alla volta deve restituire true.
//metodi per accedere al container dall'esterno
//operator[](); deve funzionare solo sui dizionari. Se is_dictionary è false, lancio eccezione.
// devo mettere nell'operatore quadre la stringa chiave del dizionario, e ottenere una reference all'oggetto json che contiene il valore.
/**
 * un dizionario può essere una lista che contiene le coppie chiave:json. Le quadre scorrono tutta la lista finché non trovano la chiave corretta.
 * Non ci sono problemi di efficienza a scorrere tutta la lista. se il dizinoario non contiene la chiave cercata, chiamare j["stringa"] deve costruire la
 * coppia stringa:null (null xk è costruttore di default). l'ordine non è importante (i dizionari non sono ordinati).
 * 
 * Le liste possono essere navigate solo con gli iteratri, senza []. i membri della lista sono oggetti json. L'ordine degli elementi di una lista
 * deve essere lo stesso del file
 * se is_list restituisce false, l'iteratore begin list chiama eccezione.
 * 
*/

//la specifica delle altre funzioni è defiita su github.

/**
 * il costruttore di default fa oggetto null.
 * viene modificato con i vari set(): rendi il json di tipo voluto, cancelli gli altri dati (deallocando anche la memoria)
 * 
 * ci sono anche push_front, push_back e insert (per liste i primi due e dizionari il terzo). devono impiegare tempo costante.
 * 
 * overloading IO :
 * se scriviamo l'oggetto json su un file di testo, deve essere un formato valido.
 * il metodo di lettura da stream  è quello che lancia il paser.
 * 
 * 
 * Le eccezioni devono rilevare file json scritti in formato non valido.
*/

/**
 * SUGGERIMENTI:
 * prima fare grammatica context free, poi fare una funzione per ogni non terminale, poi ogni funzione deve restituire un jsonz
*/























