# Grafo
il grafo è una relazione cartesiana

## Grafo Orientato
È una relazione binaria G=(V,E), V={1, 2, .., n}; E sottoinsieme di VxV. L'insieme E è detto insieme degli archi (edge), l'insieme V invece è detto insieme dei vertici. *Notazione*: n tipicamente identifica il numero di vertici, m il numero di archi

**esempio**: V={1, 2, 3, 4} E = {(1,2), (1,4), (2, 2), (3,1), (4,3), (2,4)}.
Raramente useremo questa rappresentazione formale, di norma useremo rappresentazione con cerchi (vertici) e frecce orientate. Gli archi che partono e arrivano sullo stesso vertice sono detti cappi o self-loop.

Qusto è deto grafo orientato percHé la relazione non è simmetrica. Non è detto che se un vertice I ha un arco con il vertice J, anche il vertice J abbia un arco col vertice I. 

Quant'è il massimo numero di archi al'interno di un grafo orientato con N vertici? Lo ho quando E non è un sottinsieme di VxV, ma coincide. da cui => su un grafo con N vertici posso avere al più N^2 archi.

## Grafo non orientato
Grafo G dove vale:
$$ (i,j) \in E \iff (j,i) \in E, \forall i,j \in V $$
In alcuni libri viene rappresentato E come sottoinsieme delle combinazioni di due elementi di V (coefficiente binomiale tra V e 2). È equivalente. Gli archi vengono raèèresentati senza frecce, sollo con segmenti. NOn ci sono cappi.

Quant'è il massimo numero di archi al'interno di un grafo non orientato con N vertici? Cardinalità di E è il coeff binom tra la cardinalità di V e 2: n(n-1)/2.

## Classificazione
* Un grafo è **sparso** se il numero di archi è approssimativamente il numero di vertici. Non è una definizione formale, ma serve a livello intuitivo.
* Un grafo è **denso** se il numero di archi è nell'ordine di n^2 (vicino al massimo numero di archi).

La densità è definita come 
$$ \delta = \frac{E}{|V|^2} $$ in caso di grado orientato, o $$ \delta = \frac{E}{\frac{n(n-1)}{2}} $$
Di conseguenza è sempre un numero compreso tra 0 e 1

## Rappresentazione di grafi su macchina
1. Lista di adiacenza
2. matrice di adiacenza
3. matrice di incidenza

### Lista di adiacenza
La lista di adiacenza ha un vettore di puntatori con tanti elementi quanti sono i vertici del grafo. Da ciascuno dei puntatori parte una linked list degli archi che partono da quel vertice

v={1, 2, 3, 4} E = {(1,2), (1,3), (1,4), (2,2), (2,3), (3,2), (3,4), (4,2)}

|1| -> 2 -> 3 -> 4
|2| -> 2 -> 3
|3| -> 2 -> 4
|4| -> 1

In pratica, nel vettore (prima colonna) ci vanno i primi elementi di ogni tupla, quindi i vertici, nelle righe ci vanno i secondi elementi di ogni tupla

**vantaggi o svantaggi**
tutte le volte che un algoritmo vuole sapere se du vertici sono adiacenti, deve scorrere una lista concatenata (tenendo conto che i vertici possono essere tantissimi, è inefficiente). L'occupazione spaziale è invece molto buona: Theta(n+m). È una rappresentazione che nella pratica si usa in presenza di grafi sparsi. Sicuramente non in presenza di grafi sparsi

### Matrice di adiacenza
sia n il numero di vertici. La matrice è quadrata nxn. È una matrice binaria: troveremo solo zeri e uni. è definita come 
$$ a_{ij} = 1 \iff \exists (i \rightarrow j) $$

Nel grafo visto sopra, 

V | 1   2   3   4
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
1 | 0   1   1   1
2 | 0   1   1   0
3 | 0   1   0   1
4 | 1   0   0   0

è una rappresentazione molto buona per i grafi densi. In tempo costante riesco sempre a sapere se esiste un arco tra i e j. Ovviamente è la soluzione giusta per i grafi densi.
Si noti che ha un proprietà implortante: la matrice è simmetrica in caso di grafi **non orientati**. 

### Matrice di incidenza.
La matrice di incidenza è nxm. (n vertici e m archi). 
**orientati**: la matrice contiene 0, -1, +1. Ogni colonna rappresenta un arco. Se esiste l'arco, scriviamo +1 se l'arco entra, o -1 se l'arco esce. 0 altrimenti. Può essere una buona rappresentazione quando il grafo è sparso. 

## Grafi pesati
Finora abbiamo visto grafi non pesati. 
* G=(V, E, w), grafo pesato sui vertici: ci sono numeri assegnati a ciascun vertice. w è una funzione che assegna a ciascun vertice un numero reale
* G=(V, E, w), grafo pesato sugli archi: ci sono numeri assegnati a ciascun arco. w è una funzione che assegna a ciascun arco un numero reale
* G=(V, E, w1, w2), grafo pesato su arhi e vertici
  
# Sottografo
Supponiamo di avere un grafo G=(V, E). Un sottografo G'=(V', E') è un altro grafo tale che V' è sottinsieme di V, ed E' è sottinsieme di E (in particolare, del sottoinsieme V'xV').
Possono anche mancare gli archi, non è che se prendo 3 vertici su 4 del grafo originale devo prendere tutti gli archi che colegano quei 3 vertici, basta che ne prendo un sottinsieme (volendo anche vuoto).

## Sottografo indotto
il sottografo indotto da V' si definisce come G' = (V', E') -> gli archi sono tutti gli archi possibili tra i vertici presi, quindi in E' al posto di sottinsieme c'è la relazione di uguaglianza. La notazione che si usa per i sottografi indotti è G=[V'].

# Cammino
Abbiamo u, v due vertici di G. Un cammino tra u, v è una sequenza di vertici x_i con le seguenti condizioni:
* $$ x_0 = u $$
* $$ x_q = v $$
* $$ (x_i, x_{i+1}) \in E \forall i = 0, .. , q-1 $$

La lunghezza di un cammino è il numero di ARCHI del cammino (non il numero di vertici). Un cammino si dice ***non semplice*** se contiene vertici ripetuti. Se non ne contiene si dice ***semplice***.

## Ciclo
Un ciclo è un cammino in cui x_0 e x_q coincidono. 
**NB:** se G è non orientato, ci devono essere almeno tre vertici per definire un ciclo. Sta cosa non vale in caso di grafi orientati (anzi, un cappio è un ciclo).

# Nozioni varie sui grafi (non orientati)
## Tipi
* aciclico: se non esistono cicli. Chiamato anche foresta
* connesso: se non esistono vertici irraggiungibili. Un grafo è connesso se, comunque io prenda due vertici distinti, esiste sempre un cammino tra i due vertici. 
* Albero libero: Grafo connesso e aciclico. Ha proprietà interessanti. Per esempio, il numero di arhi coincide con il numero di vertici -1. O anche, il cammino è sempre unico. Studieremo approfonditamente.

## Componente connessa 
Possiamo vedere un grafo non connesso come la somma di grafi distitnti. Questi grafi distinti vengono detti componenti connesse.
* La componente connessa è un sottografo connesso
* La componente connessa non è estendibile con un vertice esterno rimanendo connessa ( => è il sottografo connesso più grande).

L'insieme delle cc di un grafo G forma una ***partizione*** di V.
per dimostrarlo dobbiamo vedere che
1) l'intersezione delle cc è vuota => per assurdo
2) l'unione è V.

## Grafo vuoto (E_n)
un grafo G si dice vuoto se l'insieme degli archi è l'insieme vuoto. Se ha n vertici, ha n componenti connesse

## Grafo completo (K_n)
grafo G per cui esistono tutti i possibili archi $ \binom{V}{2} $

## Grafo complemento
dicesi complemento di grafo G il grafo cosruito sugli stessi vertici, che ha un insieme di archi che gode di questa proprietà: $ (u,v) \in E \iff (u,v) \notin E' $.

Un grafo G è completo se e solo se il suo complemento è vuoto.

## Grafo bipartito
un grafo è bipartito se è possibile dividerlo in due sottografi vuoti. gli archi, se ci sono, connettono i due sottografi, ma non sono nei sottografi. Un grafo si dice bipartito completo se ci sono tutti gli archi possibili che connettono i due sottografi. Un grafo bipartito completo ha n1 * n2 archi.

## Grado del vertice
Ad ogni vertice posso associare un numero, detto grado, che è il numero di vertici adiacenti, o anche il numero di archi incidenti.
Si indica con deg
in caso di grafi non orientati si parla di grado del vertice, in caso di grafi orientati si parla di grado in entrata e grado in usicta.

### Esercizio
costruire un grafo su n vertici che abbia come proprietà che tutti i vertici abbiano grado diverso. Non è possibile:
Congettura: se G è un grafo finito non orientato, allora esistono almeno due vertici che abbiano lo stesso grado
Dimostrazione: supponiamo per assurdo che esista un grafo g con tutti i gradi diversi. il grado di un vertice sarà sempre maggiore uguale a 0 e minore uguale a n-1. Significa che ci sarà un vertice con grado 0, un vertice con 1, 2, ... ,n-1. Avremmo l'assurdo che ci sia un vertice con grado 0 e uno con grado n-1 => il vertice collegato con tutti deve essere collegato anche con il vertice scollegato, che è assurdo.

### Lemma della stretta di mano
Vale solo per grafi non orientati. Indichiamo con m il numero di archi. La somma dei gradi dei vertici è sempre 2m. 

### Calcolo
Il grado di un vertice si può calcolare tramite la matrice di adiacenza:
$$ deg(i) = \sum_{j=1}^{n}a_{ij} $$.

### Grafi regolari
Un grafo si dice K-regolare se per ogni u in V, il grado è K
**proprietà:**:
- se G è 2-regolare, il numero di archi coincide col numero di vertici (conseguenza della stretta di mano) => non è un albero
- se G è 3-regolare, allora n è pari
- se G è 4-regolare, allra m è pari
- Se G è un grafo non orientato, allora il numero di vertici di grado dispari è pari


### Esercizio
sia A la matrice nxn di adiacenza di G. Essendo quadrata si può fare A*A. cosa rappresenta a_{ij} della matrice risultante?

***

lezione mancante

***

# Matrice di adiacenza proprietà
quando si moltiplica la matrice di adiacenza per sé stessa, ogni a_{ij} rappresenta il numero di cammini di lunghezza 2 tra i nodi i e j.

## Teorema
$ a^k_{ij} = $ numero di cammini di lunghezza k tra i e j.
### dim
$ A^k = A^{k-1} \times A $. da cui $ a^k_{ij} = \sum_{l=1}^n a_{lj} \cdot a^{k-1}_{il} $. Il secondo termine è il numero di cammini di lunghezza k-1 tra i e l, mentre il primo assume valori 1/0, che indica la presenza o meno dell'arco. Immagina ci siano n cammini tra i e l, dove l è il penultimo vertice prima di j. i cammini fino a j devono essere fatti da 0 se non c'è cammino o n se c'è. per ogni l questo vale, di conseguenza devo sommare per ogni nodo l tutte le n, qeusto è il significato di quella sommatoria.

**grafi orientati**: in un ciclo un grafico orientato deve avere tutti i vertici distinti, in questa rappresentazione non è detto che accada.

## Esercizio 
Mostrare che un grafo G non orientato contiene $ K_3 $ (grafo completo con tre vertici) se e soltanto se si verifica la seguente condizione: 
$$ \exist i, j \in V, i \neq j t.c. a_{ij} \cdot a^2_{ij} \neq 0 $$.

Ovvero dimostrare l'esistenza di un triangolo ciclico in un grafo utilizzando le matrici di adiacenza. La dimostrazione in realtà è abbasstanza ovvia.

## Esercizio
Se G è un grafo non orientato,
1. La traccia della matrice di adiacenza quanto vale? 0, perché la diagonale è sempre nulla in quanto non esistono cappi.
2. La traccia del quadrato di A a cosa è uguale? la somma di tutti i gradi dei nodi, che è uguale a due volte la cardinalità degli archi (2m). Per il lemma della stretta di mano
3. La traccia del cubo? $ tr(A^3) = \sum_{i=1}^{n} a^{(3)}_{ii} $ ->  numero di cammini di lunghezza 3 per ogni a_ii è 2 volte il numemro di triangoli che passano attraverso i (i due versi di percorrenza del triangolo). Sommando tutti questi a_ii, cosa otteniamo? 6 volte il numero di triangoli in G.

per k maggiori invece le cose si complicano, perché non è detto che il cammino sia un ciclo. Queste relazioni fino al grado 3 sono comunque molto interessanti.

# Graph isomorphism
problema che non è dimostrato sia intrattabile ma per il quale non esiste algoritmo efficiente. Non è per nulla banale quindi verificare che due grafi siano isomorfi, è abbstanza banale invece dimostrare che non lo siano.
### Condizioni necessarie ma NON sufficienti
1. cardinalità V1 = cardinalità V2
2. cardinalità E1 = cardinalità E2
3. vettore in cui sono scritti in ordine crescente tutti igradi del mio grafo: degree-sequence(G1) = degree-sequence(G2).
4. una clique è un sottografo completo. È detta massima se è la più grande in assoluto, è detta massimale se non è contenuta in una clique più grande. Si indica con omega(G) il clique number, ovvero la cardinalità della clique massima. -> omega(G1) = omega(G2).

# Connettività 
Perché un grafo di n vertici sia connesso è necessario che ci siano almeno n-1 vertici. Dimostro per induzione su n = |V|. 
* Base: n=1 -> numero di archi è 0, |V| = 1, effettivamente |E| = |V|-1
* acido (passo induttivo): n>=2. Sia G connesso con n vertici. Prendo G' sottografo di G senza un vertice z. NOn posso a priori garantire che G' sia connesso. Lavoro però sulle sue componenti connesse. k=|cc|. se G' è connesso, k=1. Mi aspetto che per ogni cc, |E| sia >= |V|-1. 
  Da cui $ |E| = \sum_{i=1}^k |E_i| +deg(z) $ ovvero la somma degli archi delle componenti connesse, a cui vanno aggiunti gli archi del vertice eliminato. Tutti gli E_i sono maggiori uguali di |V_i| -1 , da cui posso maggiorare $ |E| \geq \sum_{i=1}^k (|V_i| -1) +deg(z) $, che è uguale a $ \sum_{i=1}^k |V_i| -k +deg(z) $. La sommatoria è esattamente |V|-1, percHé la sommatoria della cardinalità di cc è la cardinalità iniziale, -1 per via del vertice cavato. Posso dire essere sicuramente vero che deg(z) >= k. per l'ipotesi iniziale che il grafo di partenza fosse connesso, quindi la disuguaglianza continua a valere in quanto si sta maggiorando. il grado di z non può essrere minore di k xk sennò il grafo iniziale non sarebbe connesso.

## Grafi aciclici

## Grafi Complemento

osservazioni: sono vere queste cose? 

* grafo G connesso e duale connesso: non è una implicazione valida (il complemento di un grafo completo è il grafo vuoto)
* gradfo G connesso e G' disconnesso: non è un'implicazione valida, per esempio grafi autocomplementari
* grafo G disconnesso e G' connesso: unica implicazione valida
* entrambi disconnessi: non è un implicazione valida per lo stesso discorso del punto 1

dimostrrazione informale del punto 3
prendiamo le k componenti connesse del grafo G (ovviametne k>=2). il complemento per forza collega queste componenti connesse. u e v sono vertici. ci sono due casi:
1. u appartiene a una cc e v a un'altra -> soluzione banale: nel complemento ci sarà direttamente un arco che li connette
2. u, v appartengono alla stessa cc -> sono entrambi connessi a un nodo terzo su un'altra cc.

c'è sempre un cammino tra due vertici u,v presi nel grafo complemento di G -> è connesso. 

