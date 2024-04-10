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