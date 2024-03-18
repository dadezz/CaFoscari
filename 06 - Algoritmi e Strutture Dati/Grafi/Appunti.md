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

# Tipi di Grafo (non orientato)
* aciclico: se non esistono cicli. Chiamato anche foresta
* connesso: se non esistono vertici irraggiungibili. Un grafo è connesso se, comunque io prenda due vertici distinti, esiste sempre un cammino tra i due vertici. 
* Albero libero: Grafo connesso e aciclico. Ha proprietà interessanti. Per esempio, il numero di arhi coincide con il numero di vertici -1. O anche, il cammino è sempre unico. Studieremo approfonditamente