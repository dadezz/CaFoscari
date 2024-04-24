# Cammino

Parliamo sta volta di grafi orientati. si dice che v è raggiungibile da u se esiste un cammino tra u e v. L'insieme dei cammini tra u e v è definito come C={p | p è un cammino tra u e v}. se v non è raggiungibile da u, l'insieme C è vuoto. 

## Cammini minimi
Se gli archi sono pesati, il problema risulta evidente: trovare il cammino minimo. Si definisce peso di un cammino la grandezza $w(p) = \sum_{i=1}^{q} w(x_{i-1}, x_i)$.
distanza tra due vertici: peso del cammino minore. Nel caso di mancanza di cammino tra i due vertici, la distanza è per convenzione infinito. C'è una terza possiblità, che si presenta nel caso ci fossero dei pesi negativi all'interno di un grafo. Questo perché se ho un ciclo per esempio con +1 e -3, più ciclo più trovo cammini con peso inferiore, il minimo non esiste (e sono infiniti i cammini). Per convenzione, quando succede una cosa di sto tipo la distanza sarà -infinito. Quando incontro un ciclo il problema c'è se la somma dei pesi degli archi è positiva (ok) o negativa (male). Nell'ultimo caso, si dice ciclo negativo. 

Ci sono 4 classi di algoritmi, nel caso sorgenti e destinazioni siano singole o multiple.
L'algoritmo di Dijkstra e di Bellman-Ford appartengono alla categoria singola-multipla, mentre Floyd-Marshall è multipla-multipla. Non giarderemo multipla-singola perché non è altro che un singola-multipla con gli archi invertiti. Il singola-singola è un caso particolare di singola-multipla, perché tanto dal punto di vista di complessità computazionale non si può fare meglio

### Sottocammini
Sottocammini di cammini minimi sono minimi. Si dimostra per assurdo. 

# Algoritmo di Dijkstra 
Come per l'algoritmo di prim, ci saranno due campi associati a ogni vertice del grafo, sorgente inclusa. il primo campo è d[u], ed è una stima della distanza tra s e il vertice; il secondo è pi[u], che è un puntatore al predecessore

1. Inizializzazione: per ogni vertice v del grafo, assegna +infinito a d[v] e NIL a pi[v]. Il vertice sorgente viene inizializzato con d[v] = 0.
2. Rilassamento: se d[v] > (d[u] + w(u,v)), aggiorno d[v] con () e pi[v] con u

L'algoritmo estrae un vertice alla volta, e ogni volta che lo fa rilassa tutti gli archi uscenti
Q = coda con priorità, contiene i vertici da estrarre, con chiave d.

```c
dijkstra(G, w, a){
    inizializza(G);
    Q <- V[G];
    S <- insieme_vuoto;
    while (Q != insieme_vuoto){
        u <- extract_min(Q);
        for each V in adj[u]{
            relax(u, v, w(u,v));
        }
        S <- S unito {u};
    }
}
```

## Teorema
Alla fine dell'algoritmo di Dijkstra si avrà:
1. $ d[u] = \delta (s, u) \forall u \in V $
2. $ g_{\pi} $ è un albero di camm. min.

### Dimostrazione
dimostriamo solo il punto 1.
$ \forall u \in V $ all'atto dell'estrazione di u dalla Q si ha che $ d[u] = \delta (s, u) $. Se dimostro questo, per la proprietà del limite inferiore riesco a dimostrare il teorema. Procediamo per assurdo. Facciamo finta che esista un vertice per cui non valga questa proprietà, quindi che $ d[u] \neq \delta(s, u) $. Suppongo anche che questo sia il primo vertice per cui accade. 

1. Osservazione: il vertice u sicuramente non è la sorgente: immediatamente dopo la init, ho d[s] = 0, che è la distanza tra s e sé stesso; questo perché non ci sono pesi negativi.
2. Osservazione: al momento dell'estrazione di u, S sarà non vuoto. 
3. Osservazione: u sarà sicuramente raggiungibile da s: se u non fosse raggiungibile, la distanza sarebbe infinito, ma guarda caso d[u] dopo la init è +inf, e coincide con delta. per ipotesi però delta è diverso da d.

Sia p un cammino minimo tra s e u. ci sarà un certo momento in cui il cammino attraversa il taglio S/Q, pirtendo da un vertice x in S a un vertice y in Q

1. $ d[x] = \delta[x] e d[y] = \delta [y] $: nel caso di x possiamo dirlo xk la proprietà di "diverso" deve valere per u per la prima volta, e x è già stato estratto. y per la proprietà della convergenza: se mi trovo su un cammino minimo e il predecessore ha d = delta, allora la prima relax su y sistema d=delta anche su y.
2. d[u]<=d[y] e delta(s, y) <= delta (s, u).
3. delta(s, u) = delta(s, y)+somme dei pesi tra y e u.
4. delta(s,u) <= d[u]

Mettendo isieme i pezzi finora, riusciamo a dimostrare d[u] = delta[s,u]?

delta(s.u) <= d[u] <= d[y] <= delta(s,y) <= delta(s, u). da cui si deriva l'uguaglianza. 

## Pesi negativi?
si potrebbe pensare di sommare una costante a tutti i pesi sugli archi, non è corretto però. il problema sorge per il fatto che il peso di un cammino dipende da quanti archi ci sono. la costante viene sommata tante volte quanti sono gli archi. uno può tenerne conto ogni passo che fa, ma a livello computazionale non è una buonissima idea.

# Algoritmo di Bellman-ford
algortitmo di forza bruta che fa relax a tappeto.
```c
Bellman-ford(G, w, s) {
    inizializza(G);
    for i=1 to |V[G]|-1{
        for each (u, v) in E[G]{
            relax(u, v, w(u,v));
        }
    }
    // in presenza di un grafo con pesi negativi possono esserci cicli negativi
    // questa seconda parte serve a segnalare la presenza di cicli negativi
    for each (u, v) in E[G]{
        if (d[v] > d[u] + w[u, v]) {
            return false; // nel grafo ci sono cicli negativi: non fidarti del risutato ottenuto
        }
    }
    return true;
}
```

complessità: inizializza = N. i due for = (n-1)m; ultimo ciclo = m. Da cui n*m complessità totale

## Teorema
Se G non contiene cicli negativi raggiungibili dalla sorgente, allora alla fine dell'algoritmo:
1. $ d[v] = \delta(s,v) \forall v \in V $
2. $ G_{\pi} $ è un albero di camminio minimo
3. l'algoritmo restituisce true.

Se invece G contiene un ciclo negativo raggiungibile dalla sorgente, allora alla fine dell'algortimo:
1. l'algoritmo restituisce false.

### dimostrazione
come prima non dimostreremo (2).
Poniamoci nel primo caso, quindi non esistono cicli negativi raggiungibili dallla sorgente.
prendo un vertice v. sicuramnente quindi delta(s,v) non è -inf. o è inf o appartiene a R. se è infinito, è ovvia la dimostrazione, percHé già dopo la init d=delta; Se appartiene a R? chiamo p un cammino minimo semplice tra s e v (può esistere cammino non semplice se il ciclo ha peso 0). Non essendoci cicli, nel caso peggiore p ha n-1 archi.

Immediatamente dopo la init, d[x_0] = delta(x_0, x_0). poi per la proprietà della convergenza ad ogni passo (al passo k), ho d[x_k] = delta (s, x_k). e la dimostrazione in realtà è finita. fai il passo per ogni arco e top.

DImostriamo la parte finale con restituzione del booleano.
La parte finale è:
```c
for each arco
    if d[v] > d[u]+w(u,v)
        return false; 
return true;
```
Alla domanda "in che condizione l'algo restituisce true?" si risponde "quando non entra mai nell'if", ovvero per nessun arco la condiione viene verificata.

Dimostriamo "Se invece G contiene un ciclo negativo raggiungibile dalla sorgente, allora alla fine dell'algortimo: l'algoritmo restituisce false.". pocedo per assurdo.

...

### Complessità (confronto Dijkstra e BF)

...

# Esercizi da tentare

1. dato un grafo G orientato con pesi strettamente positivi per ogni arco. Vogliamo scrivere un algoritmo che risponde a "esiste un ciclo in G in cui il prodotto dei pesi sugli archi sia minore di 1?" hint: ricondurre a un problema che so già risolvere, non costruire nuovi algoritmi. Si provi a immaginare di creare un nuovo grafo a partire da quello dato che abbia pesi diversi ma struttura uguale. i pesi nuovi sono dati da log(peso vecchio)
2. problema simile, richiede la trasformazione di elementi del grafo. Sia dato un grafo orientato G. ad ogni arco v è associato valore reale r compreso tra 0 e 1 (1 comrpeso e 0 escluso). il numero rappresenta l'affidabilità di un canale di comunicazione, più precisamete la probabilità che il messaggio che viaggia sull'arco venga ricevuto correttamente. Si assuma inoltre che le probabilità siano indipendenti. Si scrivaa un algo efficiente per trovare il cammino più affidabile tra i vertici dati

# Distanze tra tutte le coppie

algo che prenda in input grafo con sua funz peso e restituisca tutte le distanze. Una prima soluzione è riutilizzare algoritmi che già conosciamo: prendo Dijkstra o BF che unziona con sorgente singola e lo lancio su tutti i nodi 
```py
def iterated_BF(G, w):
    for v in v(G):
        BF(G, w, v)
```

Complessità:
1. caso sparso
   1. DJ: n^2logn
   2. BF: n^3
2. caso denso
   1. DJ: n^3
   2. BF: n^4

Con programmazione dinaica, possiamo scrivere un algoritmo con complessità Theta(n^3), sempre, anche con pesi negativi. L'unico difetto è che viene battuto da DJ, solo sotto due condiioni particolari: grafo sparso e senza pesi negativi.

## Algoritmo di Floyd Warshall
faremo una prima semplificazione: assumeremo i vertici come numerati; esistono pesi negativi ma non cicli negativi.
Il grafo è rappresentato da W = (w_{ij}). Trovo 0 se i=j. trovo w(i, j), ovvero il peso dell'arco se i è diverso da j e esiste un arco tra i e j. trovo +inf se non esiste arco.
L'algoritmo ritorna una matrice nxn con in posizione d_ij = distanza(i,j).

```py
def Floyd_Warshall(W):
    n = rows(W)
    D[0] = W # n matrici D
    for k in range (1, n):
        for i in range (1, n):
            for j in range (1, n):
                D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k]+ D[k-1][k][j])
    return D[k]
```
parto da W, poi produco D1, poi D2, etc fino a Dn. 
La formuletta dice quanto segue: nella matrice k-esima, il valore in d_ij è formato dal minimo tra il numero nella stessa posizione della matrice precedente e la somma dei valori nella posizione ik e kj. vediamo di capire la correttezza di sta cosa che non ha un cazzo di senso.

### Correttezza

siano i vertici V={1, 2, ..., N}. Sia poi l'insieme di cammini DD = {p  tale che p è un cammino semplice tra i e j con vertici intermedi <= k}