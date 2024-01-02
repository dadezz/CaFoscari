# Heap Delete
* pre i nodo della maxheap (compreso tra i e heapsize)
* post: rimuovere nodo i e A rimane max heap

devo mantenere che il mio albero risulti quasi completo.

Potrei sostituire l'elemento con l'ultimo e poi chiamare heapify. In realtà non è sempre la selta migliore, percHé la heapify controlla verso ilbasso, ma l'anomalia può essere presente verso l'alto. Devo controllare il valore del nodo che voglio cancellare. se è maggiore è ok questa operazione, altrimenti tocca guardare verso in alto
```cpp
void HeapDelete(Heap A, int i){
    if (A.heap_size == 1){
        A.heapsize--;
    }
    else {
        int val = A[1];
        A[i] = A[a.heapsize];
        A.heap_size--;
        if (val > A[i])
            max_heapify(A, i);
        else{
            while(i>1 && A[i]>A[Parent(i)]){
                scambia(A[i], A[Parent[i]]);
                i = Parent[i];
            }
        }
    }
}
```
sia il ramo if che il ramo else è logn -> Texe = O(logn).

# Es ordinamento
dato un intero k e un array v di n interi, scrivere un algo per troavareuna coppia di posizioni distinte i e j, tali che 1 minug i minug j minug n, e v[i] + v[j] = k. La funzione deve restituire true se tali posizioni esistono e fornire i valori, altrimnti false. Al massimo spazio aggiuntivo costante.

```cpp
struct s {
    int v1, v2;
    bool b
}
s sommak(Array k, int k){
    ordina(A); //da implementare
    /*prima soluzione:
    per ogni elemento i=1 cerco in [i+1, n] il valore k-v[i] con ricerca binaria. 
    ha complessità nlogn, come l'ordinamento, per cui ok*/

    /*posso andare sotto a nlogn sfruttando meglio l'ordinamento?
    prendo il minimo e il massimo
    uso un bool che mi dice se non ho trovato.
    poi ciclo, finché non ho scorso gli elementi e non ho trovato la soluzione, sommo elemento minimo con max, e vedo se è minore o magg di k. Se è maggiore, posso smettere di ciclare sul max perché  ogni somma con lui sarà più grande di k. idem vale viceversa per il minore*/
    int p = 1;
    int f = A.length;
    bool t = false;
    typename::s st;
    while (p<f && !t){
        if (A[p] + A[f] == k){
            t = true;
        }
        else if (A[p]+A[f] < k)
            p++;
        else 
            f--;
    }
    st.b = trovato;
    st.v1 = A[p];
    st.v2 = A[f];
    return st;
}
```

il criterio è essere sempre certi che la implementazione non elimini altre soluzioni.

# Es MAxHeap
scrivere una funzione che, dato un albero binario di ricerca T memorizza le chiavi di T in un array v strutturato come max_heap e restituisce heap_size.

La ipotesi di avere un albero binario di ricerca è molto forte. Infatti, esso è ordinato in senso crescente. Per cui basta visitarlo al contrario popolando il Max_Heap.

```cpp
int CostruisciMaxHeap (Tree t, Heap A){
    if (t.root == NULL) return 0;
    u = treemax(t.root);
    i = 1;
    while (u != NULL){
        A[i++] = u.key;
        u = treepred(u);
    }
    return i-1;
}
```
è la visita di un albero, di conseguenza complessità Theta(n).

# Es Complessità
Progettare un algoritmo che ricevuto un intero 1 minug k minug n e un array v non ordinato di n elementi distinti, restituisca il k-esimo elemento piò piccolo di v

* **soluzione Theta(nlogn)**

ordino l'array con un algoritmo Theta(nlogn) e restituisco il v[k]
```cpp
int cercaKesimo(Array v, int k){
    mergesort(v, 1, v.length);
    reurn v[k];
}
```

* **soluzione O(n+klogn)**

In tempo n trasformo il vettore in un minheap, se estraggo k volte l'elemetno minimo, ottengo il risultato richiesto
```cpp
int cercakesimo(Array v, int k){
    build_min_heao(v);
    for (int i=0; i<k; i++){
        x = heap_extract_min(v);
    }
    return x;
}
```

* **soluzione con O(nlogk)**

usiamo uno spazio aggiuntivo di k elementi, che sono gli elementi più grandi del vettore.
Scorro tutto il vettore. se la heapsize è minore di k, inserisco il mio elemento (carico l'heap con i primi k elementi del vettore).
Poi vedo se il mio (k+1)esimo elemento del vettore devo andarlo a rimpiazzare o no. Quando devo sostiruirlo? devo verificare se è minore del massimo, ho trovato un elemento più piccolo. In pratica, il maxheap deve contenere i k elementi più piccoli (e la radice sarà ciò che cerco). 
Creo l'heap grande k, poi finché trovo elementi più piccoli nel rimanente n-k, vado a rimpiazzare la radice del max_heap con questi. In sto modo alla fine mi trovo col max_heap delgi elementi più piccoli.

```cpp
int cercakesimo(Array v, int k){
    typename Heap h = new MaxHeap(k);   // costante
    for (int i=0; i<v.length;i++){      // n volte
        if (h.heap_size < k)
            max_heap_insert(h, v[i]);   // O(logk)
        else if (heap_maximum(h) > v[i]){
            heap_extract_max(h);        // O(logk)
            max_heap_insert(h, v[1]);   // O(logk)
        }
    }
    return heap_maximum(h);
}
```

# AlbBinCerca
Sia T un albero bin ric contente n nodi, sia k una chiave che occorre in T e sia x un nodo di T. SI indichi quali tra le seguenti affermazioni sono corrette, motivando brevemente le risposte.

* la ricerca di k in t ha costo O(n): vero. La ricerca in un BST ha infatti costo O(h), con h altezza di T. Nel caso peggiore in cui T sia un algbero comletamente sbilanciato h=n-1, si conseguenza O(n)
* il predecesseore di x si trova nel sottoalbero radicato in x.left. Falso. Controesempio 7->(right)9->left8. il predecessore si trova nel genitore
* la chiave massima si trova in una foglia Falso, stesso albero di prima
* eseguendo una visita posticipata di T, le chiavi vengono stampate in ordine decrescente. Falso, deve essere simetrica visitando al contrario i figli. Albero di prima come controesempio.

# Es ordinamento non serve
Sia v un array di n interi distinti; n dispari; v è detto alternante se vale la seguente condizione:v[1]>v[2]<v[3]>v[4] etc. Scrivere una procedura che renda v alternante.
 
Soluzione nlogn: ordino e poi swappo a 2 a 2. Si può fare meglio. La soluzione ottimale è n.

SI sfrutta il fatto che la proprietà richiesta è locale e non assoluta. Confronto il primo col secondo. Poi si sfreutta che sono dispari. Vado di 3 i 3, mi metto nell'elemento centrale (posizioni 2, 4, 6), poi controllo l'eleemnto 1 col successivo

1 2 -1 3 0 5 4
2 -1 1 3 0 5 4 
2 -1 3 1 0 5 4
2 -1 3 0 1 5 4 
2 -1 3 0 5 1 4

```cpp
void alterna (Array v){
    for (i=2; i<v.length-1; i+=2){  // n/2 volte
        if (v[1]>v[i-1])
            scambia();
        if (v[i] > v[i+1])
            scambia;
    }
}
```
complessit Theta(n).

# Es intersect min_Heap
Scrivere un algor che dati due min_heap contententi risettivamente n1 e n2 interi positivi, ritorna in output un nuovo min_heap contente tutti e soli gli elementi che appartengono sia a H1 che a H2

Estraggo il min da entrambi, se uguale (e lo butto in minheap), altrimenti estraggo solo dal più piccolo dei due. Il minheap risulttne può essere popolato in tempo costante se si buttano in ordine in un array.

```cpp
Heap intersect(Heap1 h1, Heap h2){
    Heap hris = new Heap(min(h1.heap_size, h2.heap_size));
    while(!h1.isempty() && !h2.isempty()){ //n1+n2 volte
        min1 = heap_minimum(h1);
        min2 = heap_minimum(h2);
        if (min1 == min2){
            hris.insert(min1);      //log ( min(n1, n2))
            heap_extract_min(h1);   //log(n1)
            heap_extract_min(h2);   //log(n2)
        }
        else if (min1<min2)
            heap_extract_min(h1);   //log(n2)
        else    
            heap_extract_min(h2);   //log(n2) 
    }
}
```

la complessità è O((n1+n2)(logn1+logn2))

# Inversioni (es difficile)
Dati un vettore v di numeri interi distinti, se i< j e v[i]>v[j], allora la coppia (i,j) è detta inversione di v. Utilizzando la tecnica divide et impera, scrivere una funzione ricorsiva efficiente che restituisca il numero di inversioni

2 3 8 6 1
(1, 5) (2, 5) (3, 5) (4,5) (3,4)     -> 5 inversioni
si può modificare il mergesort. 
Dividoo il problema in sottoproblemi. 

L'idea è  fare un alg in cui il numero di ineversioni è dato dal num di inversioni a sx + inversioni a dx +  inversioni a cavallo.

Cambiare procedura merge per contare in modo efficiente le inversioni a cavallo durante il ricombina.
