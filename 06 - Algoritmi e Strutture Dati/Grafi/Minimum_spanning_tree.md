# Caratterizzazione degli alberi

Se G è un grafo non orientato, allora sono equivalenti le seguenti affermazioni:
1. G è un albero
2. due vertici qualsiasi di G sono connessi da un unico cammino
3. G è connesso, ma se un arco qualsiasi è rimosso da G allora il grafo risultante è disconnesso
4. G è connesso e |E| = |V|-1
5. G è aciclico e |E| = |V|-1
6. G è aciclico ma se aggiungo un arco qualisiasi allora il grafo risultante ha almeno un ciclo

# Alberi di copertura minimi (MST)

non orientato, connesso. Un albero di copertura è un sottinsieme di archi che formano un albero e toccano tutti i vertici del grafo.
Più formalmente: un albero di copertura è un insieme T di archi tale che (V, T) è un albero
Ora, consideriamo un albero connesso pesato sugli archi G=(V, E, w). diversi alberi di copertura hanno diversi pesi. È in sto contesto chce si inserisce il MST. $W(T)=\sum_{(u,v)\in T} w(u, v)$

Il MST gode sdi queste proprietà:
1. T sia un albero di copertura
2. W(T) sia il più piccolo tra tutti gli alberi i copertura.

*def*: dato un grafo, un taglio è un sottinsieme di vertici di V. taglia appunto in 2 il grafo.
**Fatto cruciale dei MST**: dato un taglio sul grafo G, comunque io prenda il taglio so che ci sarà sempre almeno un arco che attraversa il taglio (perché connesso). Tra tutti gli archi che attraversano il taglio, prende il nome di *arco leggero* l'arco con meno peso.
Se (u, v) è un arco leggero, allora questo arco appartiene a un MST. Questa proprietà suggerisce anche un algoritmo di ricerca del MST (prendo i vari tagli).
***dim***: sia T un MST di G. Ci sono due possibilità.
1. (u, v) appartiene a T -> cvd.
2. (u, v) non appartiene a T. Useremo la tecnica del "cuci e taglia", che mi permette di costruire un altro mst, che conterrà l'arco (u, v).
   * passo "cuci": aggiungo (u,v) a T, e ottengo T'. se (u,v) non apparteneva  a T, ci sarà sicuramente un altro arco (x,y) che attraversa il taglio. w(u, v) <= w(x,y).
   * passo "taglia": tolgo il vecchio arco (x,y) da T'. T'' = T'\ {(x,y)}. affermo ora che T'' sia MST. sicuramente è un ST per come l'ho costruito. ma è davvero minimo? W(T'') dovrebbe essere uguale a W(T), perché per ipotesi T era un MST. $W(T'') = W(T) + w(u,v) - w(x, y)$. ma $ w(u,v) - w(x, y) \leq 0$, da cui $W(T'') \leq W(T)$. d'altra parte, siccome T era un albero di copertura minimo, segue che T'' non può avere peso minore di T, per cui i due pesi sono per forza uguali e quindi T'' è un MST.

abbiamo appena dimostrato che se (u,v) è arco leggero che attraversa un taglio, allora questo implica che esiste T che è un MST di G, tale che (u,v) appartiene a T. Ora dimostriamo una proprietà simile.

Se (u,v) è l'**unico** arco leggero che attraversa il taglio, allora il quantificatore esistenziale diventa universale -> $\forall T \in MST(G) : (u, v) \in T$. Verificando ciò, potremmo dimostrare che se esiste un solo arco leggero ricadremmo nel caso 1, completando cosi la dimostrazione. Vediamo, procediamo per assurdo. 
Per assurdo supponiamo che la tesi sia falsa: $\exists T \in MST(G) : (u, v) \notin T$. applichiamo il cuci e taglia. Costruisco T' = T + (u, v). si forma un ciclo. In sto ciclo ci sarà sicuramente un arco (x, y) che attraversa il taglio. lo tolgo. costruisco T'' = T'-(x,y). T'' è quindi un albero di copertura, il cui peso è $W(T'') = W(T) + w(u,v) - w(x, y)$. w(u, v) è strettamente minore di w(x,y). Questo implica che W(T'') < W(T). Ma quindi ho trovato un albero di copertura di peso strettamente minore di W(T), che però era un albero minimo, assurdo.

***

prendiamo ora un grafo G e un arco (u,v) che ha il peso minimo tra tutti gli archi del grafo Allora questo arco appartiene a un qualche mst. dimostriamo anche questo con la tecnica del cuci e taglia. Prendiamo un qualsiasi MST, chiamiamolo T.
caso 1: l'arco appartiene a T -> cvd
caso 2: non appartiene. aggiungo l'arco a T, diventa T', T' ha un ciclo, cavo via un altro arco del ciclo, ottengo T''. Banalmente, T'' è un ST(G); il peso di T'' deve essere il peso di T piu arco aggiunto meno arco eliminato. ma siccome il peso di (u, v) è il minore di tutto il grafo, la quantità è minore o uguale di 0, ma anche maggiore di T, quindi uguale, quindi esiste mst e bla bla formalmente. 

## Teorema fondamentale degli MST
Sia G = (V, E, w) non orientato, conness, con w: E -> R. siano
1. A sottinsieme di archi contenuto in qualche MST
2. (S, T\\S) è un taglio di G che rispetta A, ovvero non c'è nessun arco di A che attraversa il taglio
3. un arco (u, v) è un arco leggero che attraversa iltaglio.  lo chiamo ù. 

Tesi:
se ste tre robe son vere, allora esiste un mst di G che contiene A unito ù. Se vale sta proprieà, si dice anche che ù è *sicuro* per A. 
(notare che sta roba suggerisce un metodo incrementale che inizisa da A insieme vuoto, a cui aggiunge sempre ù fino a n-1 archi). 

Dimostrazione:
è abbastanza banale, con la stessa tecnica.
sia T un mst che contenga A.
1. ù appartiene a T -> cvd
2. no.

cuci e taglia. aggiungo ù a T, creando t' con un ciclo. tolgo (x,y) e creo t'' che è un MST. cosa mi garantixce l'unione è vera? l'ipotesi 2: siccome il taglio rispetta A, l'arco x,y non può appertenere a A