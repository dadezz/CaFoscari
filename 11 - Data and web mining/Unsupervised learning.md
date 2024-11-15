abbiamo un insieme di istanze ma non sappiamo l'etichetta. Tipicamente dobbiamo trovare gruppidi istanze omogenei tra loro

# Clustering
suddivido le istanze in modo da massimizzare la dissimilarità tra le istanze.

La difficoltà è che all'inizio non so quanti cluster ho
Una cosa importane è definire quando un cluster è buona o no (legato alla misura di similarità). Cerco di creare un clustering che crea alta similarità tra oggetti nella stessa classe e poca simlarità tra oggetti di classe diverse [in media].

Ci sono algoritmi che categorizzano in modo esclusivo e altri che permettono sfumature.
ci sono algoritmi basati sulla distenza e altri sulla contiguità/connettività in un grafo
ci sono algoritmi che hanno un singolo livello di partizionamento o un partizionamento gerarchico
ci sono algoritmi che usano tutte le feature e altri che cercano di selezionare le più rilevanti.

voglio un algo scalabile su milioni se non miliardi di istanze, vorrei gestire dati numerici, categorici etc, posso dare vincoli (tipo "queste due istanze vanno sicuramente insieme" o simili), vorrei gestire il rumore, che non sia importante l'ordine di input dei dati etc.

(tendenzialmente, lo scopo iniziale non è trovare subito il numero giusto di cluster, ma è che i cluster siano realmente cluster. ovvero conviene fare molti più cluster inizialmente e vedere quali etichette stan bene insieme. anche nel progetto, per i NaN in etichetta, posso lanciare un algo di questi unsupervisionati, per cercare di trovare similarità tra quelle cose per aiutarmi a usarle lo stesso per il training)
## K-means
ad ogni cluster è associato un centr -> ai dati sono associati dei centroidi e poi si cerca di costruire il cluster aumentando il cerchio dei dati-

Ho bisogno di stailire una misura di qualità per vedere se go sceltro dei buoni centri.
La misura d qualità in questo caso è la simma della distanza aò qiadreato di u punto e del centro di un cluster. È quindi una specie di errore quadreatico edio. In geerale voglio cercare di diminuirlo.
$$ E = \sum^k_{i=1} \sum_{p \in C_i}dist(p,c_i)^2  $$ 
Assumo però che l'utente mi dia il numero di cluster

1. prendi a caso i k centri $ c_1, ..., c_k $
2. dati sti centri, qual'è il set di cluster che minimizza l'errore E?

ora mi chiedo. i centri scelti sono i migliori? posso cambiarli? 
una volta fatto i punti 1 e 2, quindi, posso prendere la media dei cluster trovati per definire il nuovo centro, perché in sto modo sto minimizzando l'errore.

Sto algoritmo è molto veloce. il tempo dipende da numero di oggetti, di cluster e di iterazioni. lineare in tutti e 3 (solitamente il primo >> degli altri due). 

sta roba non funziona per nulla per cluster che si allontanano troppo da una forma sferica

## K-means++
i centroidi possono essere indotti in errore se vicini tra loro senza riuscire a trovare il clustering giusto.
una variante è quindi questa. aggiunge una strategia per selezionare i centroidi inizili. l'idea è di separare bene i centroidi e assicurarsi che mappino un po' tutto lo spazio. 
1. primo centroide a caso
2. ripeto:
   1. per ogni punto nel dataset calcolo la distanza dal più vicino centroide
   2. assegno ogni d(x)^2
   3. prendo un nuovo centroide random according to che above probabilities

l'errore SSE scende mano a mano che k aumenti, ma vorremmo mantenere in generale pochi cluster (ragionevolemnte). anche perché l'erore va a 0 quando ci sono tanti cluster quanti dati. allora plottiamo l'andamento di SSE al variare di k (a una forma simile a 1/x), e ci fermiamo al "gomito", cioè quando il miglioramento è marginale.

# Clustering gerarchico
livello generale in cui tutto è un unico cluster, poi via via dividi in clustering gerarchizzati finché ognuno è cluster solo.
praticamente quello che abbiamo visto il primo giorno col diagramma del dna. Nell'albero, ogni arco identifica la coppia di cluster più vicina tra loro e quanto è "alto" l'albero identifica la misura di distanza tra i due cluster.

Si basa fondamentalmente sulla matrice di similarità (almeno n^2 quindi) poi mette assieme la coppia più vicina e ricorsivamente mergio. 
posso fermarmi:
1. al raggiungimento del top
2. al raggiungimento di un certo numero di cluster
3. quando i cluster sono più lontani di una certa soglia

l'algoritmo richiede la distanza. è poblematico per vari motivi come abbiamo già visto (la euclidea?) e poi è problmentatico anche perché devo definire la distranza tra due cluster, non tra due punti. come faccio? le risposte sono banali:
* prendo i punti pià vicini dei due cluster (single linkage)
* prendo i più lontani (complete linkage)
* prendo la distanza tra la media (group average)
* distanza tra i centroidi
* ward: calcolo l'incremento di SSE

differneza particolare tra single e gli altri. basta che abbiano un punto vicino e, stando in media lontanissimi, e li considera roba unica. da un lato è uno svantaggio perché rischia di sottostimare la distanza tra cluster belli lontani. lo svantaggio è che riesco a seguire forme molto strane (risolverebbe il clustering di uno smile). favorisce classi ben separate di qualsiasi forma, sfavorisce classi poco separate.

# Density Based Clustering
anche questo dice appartiene/non appartiene, ma con la diffferenza che gestisce il rumore, ovvero può non metere qualcosa in nesssun cluster.
L'idea è che se ho una regione di spazio piena di punti, probabilmente quello è un cluster

## quando è che ho un area densa?
1. un punto è _core_ se esntro un certo raggio ho almeno _min_ punti
2. chiamo _vicini_ i punti interni al raggio
3. un punto è rumore se è fuori da tutti i raggi

i core point se sono abbastanza vicini sono _connessi_, e se sufficientemente connessi formano un cluster a loro volta.
un punto si dice raggiungibile da un alro se esiste una catena di cores in cui ogni cores è interno alla naighbour del core precedente.e l'ulitmo punto deve essere interno al neighbour, ma non deve per forza essere un core. 
sta roba però non è simmetrica (per il motivo dei core).
si risolve dicendo che due punti sono connessi (e quindi raggiungibili) se esiste un'origine da cui posso raggiungere entrambi (così rimetto la simmetria)

ma ovviamente, come faccio a trovare o parametri corretti? (definizione di core e raggio)
