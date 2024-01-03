# Algoritmi di ordinamento

Ho come input una sequanza di n numeri. L'output  è una permutazione.
Dimostreremo il limite inferiore di complessità: nlogn. Vedimao i principali algoritmi

***
# Insertion Sort   
Tipico esempio delle carte. ne hai 10 in mano e una carta alla volta la inserisci in modo ordinato. Cè una parte ordinata e la j-esima carta, non ordinata, vado a metterla al suo posto. È una tecnica incrementale: ho k elementi già ordinati e voglio estendere al (k+1)esimo elemento la soluzione. Ho un **ordinamento in loco**: In ogni istante al più un numero costante di elementi dell'array di input sono registrati all'esterno dell'array (= non ho bisogno di memoria ausiliaria aggiuntiva, o al massimo è costante e non dipende da n).

post: ordina A[1, ..., a.lenght]


```cpp 
void insertionSort(A){
    for j = 2 to A.lenght{
        key = A[j]
        i = j-1
        while (i>0 && A[i]>key){
            A[i+1] = A[i]
            i = i-1
        }
        A[i+1] = key
    }
}
```

qual'è l'invariante di questa procedura? il sottoarray A[1.. j-1] è formato dagli elementi ORDINATI che originariamente erano in A[1 ... j-1]
Da cui:
Quando il ciclo termina, j assume il  A.length+1. L'invariante è vero anche alla fine del ciclo, quindi il sottoarray costituito dagli elementi [1 ... a.length+1] è formato dagli elementi ordinati che originariamente erano in A. quindi il vettore di partenza è ordinato e questo ordine è una permutazione dell'A di partenza
### cmplessità
**TEO**: Linsertion sort ordina in loco n elementi eseguendo, nel caso peggiore, Theta(n²) confronti.
**DIM** ordina in loco xk ho un solo elemento memeorizzato fuori dall'array di input.
Il ciclo esterno è eseguito n-1 volte ed esegue il numero di confronti espresso da 

$$ \sum_{j=2}^{n}j-1 = \sum_{k=1}^{n-1}k = \frac{(n-1)n}{2} $$ 


il caso migliore? array già ordinato in ordine crescente, divetanta Theta(n)

caso peggiore? array ordinato in senso inverso

***
# Merge sort
fonde insieme porzioni ordinate, basato su divide et impera.

* divide: divide l'array in due sottoarray, l'indice delimitatore q è la metà del vettore di partenza. 
* impera: ordina i due sottoarray in modo ricorsivo usando la funzione mergesort. se il problema è sufficientemente piccolo (0 o 1 elementi), risolve direttamente
* combina: fonde insieme i due sottoarray ordinati per generare un singolo array ordinato.

```cpp
void mergesort (A, p /*indice partenza*/, r/*indice finale*/){
    if (p<r){
        q = parte_intera_inferiore((r+p)/2)
        mergesort(A, p, q)
        mergesort(A, q+1, r)
        merge(a, p, q, r)
    }
}
```
procedura merge:
* input: A, p, q, r
* p <= q < r
* i due sottoarray sono ordinati. per le restrizioni su p, q, r, nessuno dei due è vuoto
* output: i due sottoarray sono fusi in un unico array ordinato 
```cpp
void merge(A, p, q, r){
    n1 = q-p+1  //num elementi primo sottovettore]
    n2 = r-q    //num lemeneti secondo
    // creo due sottovettori aux
    aux1 = Array[n1]
    aux2 = Array[n2]
    for i=1 to n1
        aux1[i] = A[p+i-1]
    for j=1 to n2
        aux2 = A[q+j]
    aux1[n1 + 1] = +inf
    aux2[n2 + 1] = +inf //valore sentinella pseudocode; nella realtà, un controllo che l'array non sia vuoto
    for k = p to r
        if (aux1[i] <= aux2[j]){
            A[k] = aux1[i]
            i++
        }
        else{
            A[k] = aux2[j]
            j++
        }
}
```

per dimostrarne il funzionamento: invariante:
il sottoarray A[p ... k-1] contiene ordinati i k-p elementi più piccolo di aux1[1 ... n1 +1] e aux2[1 ... n2+1]. inoltre, gli elementi rispettivamente nelle posizioni i e j di aux1 e aux2 sono i più piccoli elementi dei loro array che non sono stati copiati in a.
*conclusione*: alla fine del ciclo for, k = r+1. sostituendo k nella definizione dell'invariante, otteniamo che il sottoarray (array intero) contiene ordinati i r+1-p elementi più piccoli di auxq e aux2. inoltre, i e j sono i più piccli elementi dei loro array che non sono stati cpiati  in a. il numero di elementi in aux1 e aux2: n1+1+n2+1 = r-p+3 = r-p+1 -> non ho copiato in a i due valori sentinella (+inf). ho inseirot quindi solo e tutti gli elementi corretti.

### complessità?
* merge: i due  primi cicli costano rispettivamente Theta(n1) e Thta(n2). Il ciclo cicciotto ultimo è Theta(r-p+1). r-p+1 è n. T_merge(n) = Theta(n1+n2) + Theta(n) = q-p+1+r-q  = r-p+1 = n -> Theta(n).
* mergesort: T(n) = 2T(n/2) + Theta(n) (merge). Applico master theorem: siamo nel secondo caso -> T(n) = nlogn.

### Vantaggi e svantaggi
vantaggio principale è la complessità, il costo ben più contenuto di insertionsort.
è un metodo stabile ( pure l'insertion).

**metodo stabile** = i numeri con lo stesso valore si presentano nell'array di output con lo stesso ordine in cui si trovavano nell'array di input


Svantaggio principale è che non è in loco: memoria aggiuntiva proprorzionale linearmente al numero di elementi da ordinare.
Altro svantaggio: il tempo di calcolo dipende esclusivamente dal numero di lementi da ordinare ed è indifferente dal loro ordine (quindi non cambia la complessità se gli elmenti son già ordinati)

*** 
# Quick sort (Tony Hoare, 1960)
algo basato sulla tecnica del divide et impera.
* divide: partiziona in due sottoarray, ma stavolta q di suddivisione è escluso: A[p .. q-1], A[q+1 .. r] (eventualmente vuoti). La partizione è t.c. ogni elementi di A[q .. q-1] sia minore o uguale ad A[q ]. che, a sua volta, è minore o uguale a ogni elemento di A[q+1, .. r]. L'indice q è arte di questa èrpciedura di partizionamento. A[q ] è chiamto pivot
* impera: ordina i due sottoarray chiamando ricorsivamente quicksort. Risolve diretttamente se il problema è sufficientemente piccolo.
* combina: triviale: poicHé i sottoarray sono ordinati sul posto, non occorre alcun lavoro per combinarli. L'inttero array risulta quindi ordinato.

```cpp
void quicksort(A, p, r) {
    if (p<r) 
        q = partition(A, p, r)
        quicksort(A, p, q-1)
        quicksort(A, q+1, r)
}
int partition(A, p, r){
    x = a[r] //elemtno finale. 
    i = p-1
    /*in ogni momento vorrò che il array sia suddiviso in 3 porzioni: prima della i son minori di x, da i a j sono maggiori di x e poi ci sono gli elemnti che ancor ano ho controllato*/
    for j=p to r-1
        if (a[j] <= x){
            i = i+1
            scambio a[i] e a[j]
        }
    // ho scorso tutti gli elementi: è rimasta fuori solo x
    scambia A[i+1] e a[r]
    return i+1
}
```
invariante: in posizione x c'è sempre a[r] e per ogni k in [p.. i], a[k] è minore uguale a x e tutti i k tra i+1 e j-1, a[k]>x e p minug j minugr e p-1 minug i minug j-1

### Complessità
* partition:eseguo il ciclo THeta n volte, con n = r-p+1
* quicksort: T = T(k) + T(n-k-1) + Theta(n). secondo caso mastertheorem = nlogn. 

Il tempo di partizionamento del quicksort dipende dal partizionamento dei sottoarray: se i due sono bilanciati, allora il quinksort ha una compllesità come il mergesort. Se sono fortemente sbilanciati, allora ha prestazioni pessime come l'insertion sort nel caso peggiore. Il caso peggiore di partizionamento è quando il pivot è il massimo / minimo del vettore. per come è implementato l'algoritmo, è il caso del vettore già ordinato (si prede sempre il massimo a ogni chiamata ricorsiva). LA ricorrenza diventa quindi T(n-1) + Theta(n) = T(n-1) + cn. 

Svilupo l'albero di ricorsione:
cn -- T(n-1)
cn -- c(n-1) -- T(n-2)
cn -- c(n-1) -- c(n-2) -- ..... -- T(0)


 $$ T(n) =  \sum_{i=1}^{n}ci + T(0) = c*\frac{n(n+1)}{2} + T(0) = \Theta(n^2) $$ 

caso migliore: partizionamenti bilanciati, diciamo n/2, la ricorrenza è la stessa del mergesort per cui, col master theorem, $\Theta(n\log(n))$ 

Ma quindi il caso medio? non guardiamo dimostrazione formale, ma è più vicino al caso migliore. poniamo che ci sia una partizione proporzionale, tipo 1:9. la ricorrenza è T(n) = T(n/10) + T(9n/10) + cn. sviluppiamo al ricorrenza:

cn -- cn/10 + c9/10 + cn -- cn/100 + 9cn/100 + 9cn/100 + 81cn/100 -- 

ogni costo è cn. qual'è l'altezza del cammino? $\log_{10}n$ , da cui O(nlogn).

E cosa succede invece se ho una partizione fortunata e una no? Quindi, alternanza di partizioni buone e pessime.
Posso fare un sistema di ricorrenze
 $L(n) = 2U(n/2) + \Theta(n)$      //lucky

 $U(n) = L(n-1) + \Theta(n)$        //unlucky

 $L(n) = 2(L(n/2-1) + \Theta(n/2))  + \Theta(n/2)$ 

 $L(n) = 2(L(n/2-1) + \Theta(n/2))$ dimostrabilmente $\Theta(n\log(n))$ 

## Ottimizzazioni

Come eliminare il problema del caso peggiore? 
### Versione randomizzata del quicksort
Siccome il problema è l'input ordinato, ci metto un fattore randomico: il pivot lo scelgo a caso.
Invece di scegliere sempre a[r] come pivot, scambio a[r] con un elemento scelto a caso. 

```cpp 
randomized_partition(A, p, r){
    i = random(p, r);
    scambia(a[i], a[r])
    return partition (A, p, r)
}
randomized_quicksort(a, p, r){
    if (p<r){
        q = randomized_partition(A,p,r)
        randomizer_quicksort(A, p, q-1)
        randomized_quicksort(a, q+1, r)
    }
}
```
tutte le chiavi sono distinte.
* tempo di esecuzione indipendente dall'ordinamento nell'input
* nessuna assunzione sulla distribuzione dell'input
* nessun specifico input mi determina il comportamento nel caso peggiore
* il caso peggiore è determinato solo da gnereatore di numeri casuali

### quick+insertion sort
utilizzare l'insertion sort su vettori di piccola dimensione

```cpp
if (r-p <= M /*da quanto ho capito, M spesso compreso tra 5 e 25*/)
    insertionsort(A, p, r)
```

Un'alternatiav è non rodinare il vettore quando è sufficientemente piccolo (caso base -> return nulla), quindi il quicksort restituisce un array quasi ordinato. Poi, si chiama insertionsort che è efficiente in vettori quasi ordinati
```cpp
void sort (A, p, r){
    quicksort(A, p, r)
    insertionsort(A, p, r)
}
```

### pivot mediano
 si puòscegliere il pivot come la mediana di tre elementi del vettore
* si preleva un elmento a sinistra, uno al centro e uno a destra
* si prende la mediana e si scambia con l'elemento in posizione a[r]

### chiavi duplicate
in presenza di chiavi duplicate, il randomized quicksort funziona correttamente? no

Invece di dividere il vettore in 2 parti, lo suddivido in 3: minore, uguale, maggiore.
ridefiniamo partition: permuta gli elementi della porzione che va da p a r e restituisce sta volta due indici q e t, con p minug q minug t minug r, tali che 
* tutti gli elementi di q..t sono uguali
* ogni elemento di a[p..q-1] è minore di a[q]
* ognin elementi di a[t+1..r] è maggiore di a[q]

L'array viene quind così partizionato
| min | ugu | ? | mag | x |

```cpp
partition(a, p, r){
    x = a[r]
    min = eq = p
    max = r
    while(eq<mag){
        if (a[eq] < x){
            scambia(a[min], a[eq])
            eq++
            min++
        }
        else if (a[eq] == x)
            eq++
        else {
            mag--
            scambia (a[mag], a[eq])
        }
    }
    return <min, mag>
}
```

**complessità e invariante**: 

* invariante: x = a[r] e per ogni k appartenente a (p, ...,  min) a[k]< x e, per ogni x compreso tra min e q, a[k] =x e, per ogni k tra mag e r, a[k]> x e p minug min minug eq minug mag minug r. Tra eq e mag c'è un buco, contentente gli elemnti non visitati.
* complessità il ciclo viene eseguito r-p volte. Assumendo n = numero di ele del vet di partenza, n = r-p+1 => complessità totale Theta(n).

## Vantaggi:
 * algo di ordinamento in loco
 * in media t exe O(nlogn)

## Svantaggi:
* nel caso peggiore è Theta(n²)
* non è stabile

***
# HeapSort
usa una struttura dati particolare che è l'heap: albero binario quasi completo. Tutti i livelli sono completamente riempiti tranne eventualmente l'ultimo, in cui tutte le foglie sono addossate a sinistra

Un heap può essere memorizzato in un array A con due attributi: length, heap_size (indica il numero di elementi dell'heap che sono memorizzati nell'array A)

A[1 .. A.heap_size]
La radice dell'albero è A[1]. Se i è l'indice di un nodo, allora parent(i) è la parte inferiore intera di i/2. left(i) è i*2, right(i) è i *2+1.
Notare che sono tutte e tre operazioni molo facili da implementare in binario in quandto shift.
Due tipi di heap:
1. max_heap, la cui proprità è: per ogni nodo diverso dalla radice, A[parent(i)] >= A[i]. ovvero la radice contiene il massimo. Non da confondere con le proprietà dell'albero binario di ricerca. Il sottoalbero di un nodo, si consegueenza, contiene valori non maggiori di quelli contenuti nel nodo stesso (dimostrare per induzione)
2. min_heap, che ha la proprietà simmetrica a questa appena vista

## Heap:
* L'altezza di un heap di n elementi è parte intera inferiore di logn. DIM: poiché un heap è un albero quasi cokmpleto, se ha un'altezza h allora haun numero di nodi compreso tra $\sum_{i=0}^{h-1}2^i+1 = 2^h$ e $\sum_{i=0}^{h}2^i = 2^{h+1}-1$ 
  siccome $h <= \log(n) <h+1$ , allora $\lfloor\log(n)\rfloor$ .
* Nell'array che rappresenta un heap di n elementi, le foglie sono i nodi con indici da $\lfloor (n/2) \rfloor +1$ a n.
* Ci sono al massimo $\lceil \frac{n}{2^{h+1}} \rceil$ nodi di altezza h in un qualsiasi heap di n elementi. 

### max_heapify
procedura che serve per mantenere la proprietà max_heap
* pre: gli alberi con radice in left(i) e right(i) sono max:heap
* post: l'albero radicato in i è un max_heap

```cpp
void max_heapify(A, i){
    l = left(i)
    r = right(i)
    if(l<=A.heap_size && a[l]>a[i])
        massimo = l
    else
        massimo = i
    if (r<= A.heap_size && a[r]>A[massimo])
        massimo = r
    if (i!=massimo)
        scambia(a[i], a[massimo])
        max_heapify(A, massimo)
}
```

Tempo di esecuzione è O(h), dove h è l'altezza del nodo i percHé ad ogni chiamata ricorsiva scendo di un livello dell'albero. Per le carateristiche dell'heap, allora texe = O(logn)

### costruzione heap
dato un vettore disordinato trasformarlo in un heap
```cpp
build_max_heap(A){
    A.heapsize = A.length
    for i = parte_intera_inferiore(A.length/2) down to 1
        max_heapify (A, i)
}
```

Invariante: ogni nodo i+1, i+2, ... , n è radice di un max_heap, con n=a.length
ANALISI: Limite superiore: Ogni chimata di max_heapify costa O(logn) e ci sono O(n) chiamate, quindi il tempo di exec è limitato sicuramente da O(nlogn). In realtà questo limite non è stretto. L'odsservazione fondamentale è che il tempo di eseczione è o(h) e varia cioè con l'altezza del nodo.

Assumo di applicare la max_heapify a tutti i nodi dell'albero (maggiorazione). 
per il lemma 3, io ho 
 $$  \sum_{h=0}^{\lfloor \log n \rfloor}\lceil \frac{n}{2^{h+1}} \mathcal{O}(h) \rceil  $$ 
vado a fare un'ulteriore maggiorazione
 $$ \mathcal{O}(\sum_{h=0}^{\lfloor \log n \rfloor}\lceil \frac{h}{2^{h}}  \rceil) $$ 
è una sommatoria nota (+inf)

 $$  \sum_{h=0}^{\infin}hx^h = \frac{x}{(1-x)^2} per |x|<1 $$ 
affinché io possa usare sta sommatoria, pongo x = 1/2

maggioro infine ulteriormente:
 $$  \mathcal{O}(\sum_{h=0}^{\infin} \frac{h}{2^{h}})= \mathcal{O}(2n) = \mathcal{O}(n) $$ 
Il tempo di esecuzione di build_max_heap è O(n).

Definita la struttura, posso finalmente implemenare un algoritmo di ordinamento:
```cpp
Heapsort(A){
    build_max_heap(A)
    for i = a.length down to 2
        scambia(a[1], a[i])
        a.heapsize--
        max_heapify(a, 1)
}
```
INVARIANTE: il sottoarray 1..i è un maxheap che contiene li elemnti più piccoli di a[1..n] e il sottoarray a[i+1..n] contiene gli (n-i) elementi più grandi di a[1..n], ORDINATI.

vediamo come funziona il ciclo:
16 14 10 8 7 9 3 2 4 1

prendo l'1 e lo scambio col 16

1 14 10 8 7 9 3 2 4 16

applico maxheapify:

14 8 10 4 7 9 3 2 1 16

ora prendo il 14 e lo metto nella posizione finale. 

1 8 10 4 7 9 3 2 14 16

applico maxheapify, 

10 8 9 4 7 1 3 2 14 16

poi prendo il 10, e via di seguito maxheapify etc.
andando a iterare così, estraggo sempre gli elementi massimi.
Quando il ciclo termina, i = 1, sostituendo nell'invariante il valore 1, risulta che il sottoarray a[1] è un maxheap che contiene l'elemento più piccol di A di partenza, e il sottoarray a[2..n] contienegli n-1 elementi più grandi di a[1..n], odinati -> ecco che il vettore risulta ordinato.

### complessità
build:max_heap costa n. il ciclo viene eseguito n-1 volte, e contene max_heapify applicata sempre alla radice dell'albero. da cui $$ T(n) = \mathcal{O}(n)+\mathcal{O}(n\log n) =\mathcal{O}(n\log n) $$ 

L'algoritmo trasforma il vettore di partenza in uno heap, quindi è de facto in loco.
L'algoriemo heapsort ordina in loco n elementi eseguendo nel caso peggiore nlogn confronti. Prende la caratteristica migliore di insertionsort (loco) e di mergesort (complessità)e le unisce. Però una implementazione efficiente del quicksort come quella che abbiamo visto risulta comunque essere mediamente migliore (non nel caso peggiore come abbiamo visto).
