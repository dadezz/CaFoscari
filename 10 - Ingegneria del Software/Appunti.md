# Sistema
Insieme di componeni che lavorano insieme per raggiungere un obbiettivo.
Le componenti possono anche essere indipendenti e usate per un loro obbiettivo, e la somma degli obbiettivi delle componenti non fa l'obbiettivo del sistema.
C'è una dipendenza invece dalla qualità dei singoli componenti, ma ciò che è davvero cruciale è la qualità dei singoli componenti.
## Acquisizione e sviluppo
ho due possibilità per realizzare un sistema. nel primo caso, la specifica l'ha data chi l'ha costruito, e io devo solo verificare che le mie siano compatibili, se invece faccio sviluppare il mio sistema da un'azienda sw per esempio, sono io che scelgo le specifiche.
**Acuisizione**:
* identificazione esigenze aziendali 
* ricerca e selezione fornitori
* valutazione offerte e negoziaizione contratti
* implementazione
**Sviluppo**:
* Analisi requisiti 
* Progettazione sistemma
* svilupo e codifica
* test e verifica
* manutenzione e aggiornamenti

La via di mezzo è lo sviluppo di una customizzazione di soluzioni acquisite.

## architettura di un sistema
Diagramma a blocchi in cui identifico le relaion tr i componenti

## proprietà emergenti di un sistema
* affidabilità
* manutenibilità
* resilienza

per misurarle ho bisogno di metriche e valori soglia.

# Approcci alla progettazione di un sistema
* Decomposizione strutturale: suddivisione del sistema in parti fisiche per facilitarne la progettazione. (per esempio: icaro vede le ali sugli uccelli e prova a riprodurle)
* Descomposizione funzinale: assegnazione di diverse funzioni a componenti fisiche per ottimizzare il sistema (ho bisogno di galleggiare ed andare avanti, e allora penso a fare queste funzioni)
* approccio iterativo
## Trasformazione dei bisogni in parametri del sistema
* identificazione delle esigenze
* definizione delle varie funzioni
* progettazione delle varie funzioni
* definizione dei limiti operativi el sistema
* verifica dell'allineamento dei parametri del sistema con i requisiti operativi

## Scalabilità
se aumento la numerosità dei sottosistemi, aumento la quanità di relazioni e quindi ho un problema di scalabilità

## ambiente
i sistemi non sono indipendenti, sono unifluenzati dall'ambiente circostante, che non progetto io, ma mi ci devo adattare. Devo tenere conto dell'ambiente per la progettazione.
Devo esplicitare le assudnzioni che faccio sull'ambiente.

Non progetto il dispositivo android, ma assumo che
* abbia versione superiore a x
* abbia connessione a internet
* ...

altre caratteritsiche del dispositivo, tipo il colore del telefono, sono del tutto irrilevanti.
È Importante specificare le assunzioni e i requisiti dell'ambiente in cui il sistema esiste

# Progetto
insieme di attività con inizio, fine, obiettivo, realizzato da equipe di persone, usa un insieme di risorse, non è una routine. 

Per realizzare un progetto mi serve pianificazione delle attività, gestione delle comunicazioni col team, coordinamento delle attività e monitoraggio dell'avanzamento e delle deadline, budget etc e valutazione delle performance, con continua revisione del progetto.

## Differenza tra progetto e routine
* obiettivi definiti
* qualità richiesta (nei progetti è fissata dagli obiettivi, nella routine è da standard)
* gestione del tempo
* gestione dei costi
* carattere distintivo

## Ciclo di vita
* concezione: ci penso (obiettivi e attività)
* scrivere piano di progettto, con valutazione di tempi, costi e risorse necessarie
* esecuzione e controllo
* chiusura

## organizzazione
* per funzione
* per progetto o attività
* a matrice

## tipologia team
* democratico e decentralilzzato: funziona bene per problemi difficili con team piccoli.non scala
* controllato decentralizzato: un leader conosciuto, gerarchia a piramide, ma comunicazione alla pari tra gente dello stesso livello.
* controllato centralizzato: verticalizzato e gerarchico

## ruoli chiave nel progetto software
* project manager (pianificazione e coordinatore)
* analista dei requisiti
* sviluppatore del codice
* quality assurance
* architetto software

## comunicazione
* interna tra il team
* esterna: prof, utenti finali

# Il Piano di Progetto
* introduzione: summary. leggendo devo sapere tutte le cose salienti. vanno anche recuperati gli obbiettivi generali e le caratteristiche principali
* organizzazione: relazione tra le varie fasi
* processi gestionali: metodi per la gestione del progetto
* processi tecnici: strumenti e tecniche utilizzati nel processo di sviluppo
* pianificazione delle attività e delle risorse
* appendici

## organizzazione
1. modello del processo: waterfall? agile? ... perché?
2. struttura organizzativa: team fatto come?
3. interfacce organizzative: relazioni esterne: chi e come?
4. responsabilità: ruoli del team nel progetto (chi sviluppa? chi consegna? chi controlla la qualità?)

## processi gestionali
che scelte poss pfre per gestire il proecsso?
1. obiettivi e priorità: scadenze fisse o modulabili? qualità o efficienza?
2. assunzioni, dipendenze e vincoli: a natale lavoro?ho periodi di esami in cui non sono disponibile? quali fattori possono influenzare il processo di sviluppo?
3. gestione dei rischi: sezione più importante, vedremo.
4. meccanismi di controllo: gestione dei timesheets e dei report di lavoro. Mi serrve per controllare quante ore dedicare a tutto, quanti progetti posso fare etc
5. pianificazione dello staff: analisi degli skill presenti e richiesti.

## processi tecnici
strumenti a supporto del processo (ambiente di sviluppo, linguaggio)
1. metodi, strumenti e tecniche
2. documentazione (readme? commenti?)
3. chi controlla la qualità

## pianificazione delle attività e delle risorse
wbs, pert, gannt, allocazione risorse, costi

# Gestione dei rischi
un rischio è un fattore che determina il non raggiungimento degli obiettivi prefissati.
per ogni rischio devo stimare 
* probabilità
* impatto

Se uno si ammala per un mese, che succede?
se il gruppo si spacca? (circa 5% di prob) impatto devastante

Cause di fallimenti dei progetti:
* requisiti incompleti
* mancanza di risorse
* apsettative non realistiche
* skill non sufficienti

devo dire in anticipo cosa faccio se il rischio occorre.
quindi: identificazione, analisi, monitoraggio, mitigazione

probabilità di accadimento e di impatto hanno un livello da 1 a 4. vanno messe in una tabella dei rischi. quelli con maggior devasto sono quelli che van monitorati di più

# Stima dei costi
come faccio a valutare quanto costa un prodotto software?
prima di iniziare lo sviluppo devo fare un preventivo. ci sono 3 modi:
1. nel piano di progetto ho wbs, con una stima dei costi per ogni attivitò -> costo totale = somma di tutti i costi. Ha il problema che non è facile fare stime accurate. Se sono esperto può avere senso. Mi serve un piano di progetto affidabile
2. basasrsi sulle linee di codice. stima del prodotto in termine di dimensione del codice. In media un'app android come la mia quanto è grossa? quanto costa? È una stima bella difficile, se non sono esperto posso stimare tramite confronto con altre app
3. il più complicato  ma migliore. parte dai requisiti, ricavo gli elementi di complessità del sistema che voglio realizzare. a ogni valore di complessità, posso dare un valore monetario. A seconda di quanto presumo sia complessa la soluzione dei punti, ci dp un costo diverso

## functions point
parametri:
* internal logical file (file interni all'app)
* external interface file (file esterni)
* external input (attività elementari di input)
* external output (attività elementari di output)
* external inquiry (attività elementari di interrograzione)

faccio la tabella dei alori unadjusted, poi controllo le 14 caratteristiche quanto sono rilevanti e calcolo gli adjusted function points

# documento dei requisiti
È la base dl contratto, se è fatto bene è improbabile ci siano contenziosi in tribunale.
Il documento va organizzato in sezioni.
L'attività di raccolta dei requisiti deve avere delle robe preliminari, che possono essere brainstorming, interviste, osservazioni, questionari etc -> docuemntate nell'introduzione; più lìidentificazione di scenari specifici di utilizzo del sistema (use cases per ogni servizio).
Tutto ciò serve ad avere chiaro quali sono le funzionalità essenziali.
posso poi procedere sia bottomup che topdown.  
1. top-down: questo sistema come posso organizzarlo in macroservizi che poi si dettagliano in funz più piccole?
2. bottom-up: le funzionalità comeposso strutturarle in un sistema coeso?

dove scrivo che scelta ho fatto? una possibilità è in introduzione, oppure anche nel piano di progetto (si modifica nelle versioni successive).

## uml
linguaggio di modellazione. Un modello è un'astrazione della realtà. UML è un tenativo di unificare dei modelli embrionali di progettazione software. 

### diagramma d'uso
mi concentro sulla visione del sistema come scatola nera che offre servizi ad attori esterni. Dimentico gli aspetti non funzionali.
- attore: esprimo i diversi ruoli che le entità esterne possono avere verso il sistema. rappresentato con un omino a livello grafico. È possibile definire gerarchie tra attori
- caso d'uso: modo in cui il sistema interagisce con gli attori esterni. rappresentato mediante un ellisse etichettata
- scenario: insieme di casi d'uso che coinvolgono gli stessi attori.

per ognuno dei casi d'uso corrisponde un template
- nome
- goal
- attori
- precondizioni
- trigger
- descrizione
- alternative (cosa succede nel caso in cui ci sia condiione particolari)
- postcondizioni 

relazioni tra casi d'uso: inclusione
dietro un servizio si nascondono altri servizi che vengono chiamati. (tipo funzione rincipale con altre chiamate a funzione). ni questo caso la relazione di dice di inclusione. 

per esempio i casi d'uso prelevare e visualizzare saldo del conto, in un bancomat, includono entrambi il servizio "identificazione utente"

generalizzazione: altra relazione. se effettuo ordine libro o effettuo ordine cd, sono due casi d'uso diversi, generalizzabili in "effettuo ordine".

estensione: in corrispondenzaz di un certo punto d'estensione (alternativa), questo servizio ne chiama un altro. "per realizzare questo servizio, quando questa condizione è verificata, allora devo fare anche questa cosa". ricorda un po' la gestione delle eccezioni.

### specifica dei requisiti
descrizione precisa e dettagliata di ciascuno dei requisiti funzionali del sistema. serve come base da una parte per il contratto e dall'altra per la progettazione e lo sviluppo. il punto di partenza sono itemplate dei casi d'uso. per la specifica dei requisiti vengono utilizzate form strutturate.

### Matrice di tracciabilità dei requisiti
evidenzia la correlazione tra requisiti. presupponde che ogni requisito sia univocamente individualivle tramite un codice. la matrice non è simmetrica -> serve specificare come leggerla

## da cui
1. introduzione: descirve le funzinoalità generali del sistema e le modalità di coinvolgimento degli stakeholderls
2. modelli del sistema: mostra gli use case, gli attori, i servizi e le relazioni. per ognuno degli usecase compilo il template
3. definizione dei requisitii funzionali: elenca i servizi offerti dal sistema, ordina i requisiti in base alla priorità (prima quelli core). per ogni requisito indica la motivazione; inddica possibili evoluzione del sistema
4. def dei requiisiti non funzionali (proprietà e vincoli sul sutema e sul processo di sviluppo - tipo versione di android supportate)
5. specifica dei requisiti funzionali. form semi strutturato per la specifica dei servizi. è tipo la specifica di un esrcizio di programmazione. ti dico quali sono gli input, cosa mi aspetto che faccia e qualieoutput voglio.

a chi è destinato il documento dei requisiti? business manager, project manager, architetti di sistema, sviluppatori (non è quindi necessario mettere nel glossario linguaggio specifico se ci si aspetta che il destinatario lo conosca)