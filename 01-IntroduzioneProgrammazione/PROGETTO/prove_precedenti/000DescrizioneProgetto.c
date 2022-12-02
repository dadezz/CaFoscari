/*
Snake Labyrinth
###################
o     #       $   #
#     #       $   #
#     # !  #  $   #
#     #    #  $   #
#     #    #      _
#     #    #      #
#          #      #
#    $$$$  #      #
###################

La figura sopra rappresenta un labirinto dove il nostro protagonista Snake (o) deve trovare l’uscita (_). Snake
percorre il labirinto raccogliendo o evitanto gli oggetti nel piano di gioco finchè non raggiunge l’uscita. Ogni
oggetto può aumentare o diminuire il punteggio del nostro eroe. Anche la lunghezza del percorso è importante
perchè Snake vuole uscire il prima possibile.

L’obiettivo del gioco è di trovare il miglior percorso che porta all’uscita del labirinto.
Per migliore si intende il percorso che produce il punteggio più elevato. Ciò significa che il percorso
migliore non è semplicemente il più breve.

Mosse possibili
Ad ogni turno le mosse possibili sono:
• N: un passo verso l’alto (Nord)
• S: un passo verso il basso (Sud)
• O: un passo a sinistra (Ovest)
• E: un passo a destra (Est)
Ogni passo costa 1 punto.

Premi e Ostacoli
Durante il percorso Snake può incontrare:
• # pareti che non possono essere attraversate;
• $ monete, ciascuna del valore di 3 punti;
• ! imprevisti, che se incontrati dimezzano (divisione intera) il numero di monete raccolte;

Gli oggetti scompaiono dopo la prima interazione con Snake. Una volta raccolta una moneta, questa viene
rimossa dal piano di gioco e non può essere raccolta due volte. In modo simile per gli imprevisti. Snake non
può occupare una cella dove si trova una parete #, e quindi le pareti non scompaiono mai.

Una volta trovata l’uscita, il punteggio è dato dalla somma dei valori delle monete meno il numero di passi
eseguiti.

QUESTA QUA SOPRA È LA VERSIONE BASE.

Altre varianti
Durante il corso aggiungeremo nuovi oggetti e nuovi elementi al gioco che dovranno tutti essere imple-
mentati.


1:  Modalità interattiva
Viene chiesto all’utente quale sia la mossa successiva. Il piano di gioco ed il punteggio vengono aggiornati
di conseguenza.



2:  Modalità AI
Si richiede di implementare una funzione che calcoli una buona strategia di gioco.
    Strategia 1: Random 
        Nella strategia Random, Snake si muove in maniera casuale ad ogni passo finchè non viene trovata la via di
        uscita
    Strategia 2: Sempre a Destra
        Una strategia che consente di uscire sempre da qualunque labirinto é quella di appoggiare una mano su una
        parete e proseguire seguendo la parete. Sotto il percorso nel primo labirinto che si ottiene mantenendo la
        parete alla propria destra.
        ###################
        ..  #           $ #
        #.  #   ...     $ #
        #.  # ! .#.     $ #
        #.  #   .#.     $ #
        #.  #   .#.      ..
        #.  #   .#.      .#
        #.  #   .#.      .#
        #........#........#
        ###################
    Altre Strategie
        A voi piena libertà. Una opzione è una soluzione ricorsiva che implementi la ricerca del miglior percorso
        possibile.

Labirinti
Potete sperimentare il gioco con uno o più labirinti pensati da voi. Alcuni labirinti verranno pubblicati
durante il corso.

Schema di implementazione
Il programma che implementerete dovrà chiedere al giocatore quale mossa giocare, e dovrà visualizzare il
campo di gioco aggiornato (usando la funzione printf o equivalente). Dovrà verificare che la mossa scelta
sia legale (non attraversi dei muri), e dovrà aggiornare il punteggio. Questi passi si ripetono fino alla fine
della partita.

Nella modalità AI, il programma dovrà calcolare il percorso migliore, visualizzare a schermo ogni mossa con
il relativo punteggio, fino a quella finale. Infine dovrà visualizzare la stringa con tutte le mosse eseguite (es.
“NNSSONSEEE...”).

Siete liberi di sperimentare e inventare schemi di gioco o varianti a vostro piacimento, pur rispettando i
requisiti riportati più in basso in questo documento.
*/

/*
#########################################

CONSEGNA

Quando? Il progetto deve essere consegnato 4 giorni prima la data di ciascun appello. E’ sempre obbligatorio
iscriversi all’appello di “Esercizi” prof. Spanò per sostenere la discussione del progetto.

Dove? Il docente abiliterà la consegna tramite Moodle secondo le scadenze previste.

Cosa? Dovrete consegnare un unico file zip contenente:
    1. Una relazione scritta di al massimo 3 pagine che descriva la struttura del vostro progetto,
        l’organizzazione del lavoro tra i componenti del gruppo, le principali diﬀicoltà incontrate. Relazioni
        più lunghe verranno penalizzate.
    2. Il codice sorgente del progetto in linguaggio C99; eventuali parti di codice scritto in altri dialetti vanno
        isolati in sorgenti separati ed il progetto dovrà compilare opportunamente.
    3. Documentazione delle funzioni, dei tipi e dei file generata con Doxygen

Librerie esterne
E’ possibile implementare l’intero gioco utilizzando semplicemente la standard library di C, usando le funzioni
di lettura dei tasti come getc() o getchar() e le funzioni di stampa come printf(). Coloro che vogliono cimen-
tarsi nell’uso di librerie esterne per dare una veste grafica ed una interazione col giocatore più accattivanti e
fluide possono farlo, tuttavia sarà propria responsabilità occuparsi degli aspetti di portabilità e compatibilità.
Il programma deve compilare e funzionare correttamente sulle 3 piattaforme (Windows, Linux, Mac); in caso
contrario, è necessario documentare e motivare opportunamente la scelta nella relazione che accompagnerà
il progetto ed in sede d’esame.

Requisiti
Per i progetti di gruppo:
    • progetto suﬀiciente se permette ad un utente di giocare inserendo le proprie mosse tramite input da
        tastiera (modalità interattiva); l’implementazione delle regole del gioco deve essere corretta.
    • progetto buono se implementa la modalità AI utilizzando un algoritmo semplice; avete piena libertà
        di definire una strategia.
    • progetto ottimo se implementa una strategia particolarmente interessante, come ad esempio un algo-
        ritmo ricorsivo, per la modalità AI;
    Tutti i membri del gruppo devono conoscere e saper leggere ogni riga del codice!

Nel caso di progetti individuali, ad esempio per studenti lavoratori:
    • progetto suﬀiciente se permette ad un utenti di giocare inserendo le proprie mosse tramite input da
        tastiera; l’implementazione delle regole del gioco può essere ragionevolmente parziale.
    • progetto buono se permette ad un utente di giocare inserendo le proprie mosse tramite input da
        tastiera; l’implementazione delle regole deve essere corretta.
    • progetto ottimo se implementa una strategia in modalità AI; avete piena libertà di definire una
        strategia.

Importante! Il progetto è di gruppo, ma la valutazione è individuale. Questo significa che i componenti
di un gruppo potrebbero ricevere un voto diverso.
Inoltre, è possibile per alcuni dei componenti presentare individualmente delle migliorie al progetto. Pos-
sibili migliorie potrebbero essere: grafica migliore, strategia di gioco più raﬀinata, menu di interazione
dell’utente più usabile, ecc.
Non ci sono limiti alle aggiunte o modifiche che vorrete fare! Quindi non ponetevi limiti!

Challenges
Durante il corso vi proporremo alcuni labirinti su cui sperimentare la vostra strategia AI.
Fisseremo 3 scadenze intermedie:
• 18 Novembre
• 2 Dicembre
• 16 Dicembre
Il vostro codice verrà testato in modo da calcolare il punteggio della vostra soluzione. Più avanti specificher-
emo cosa dovrà fare esattamente il vostro codice.
Sarà un ottimo modo per avere dei commenti sul progresso del vostro lavoro e il vostro risultato verrà preso
in considerazione nella discussione del progetto.



*/