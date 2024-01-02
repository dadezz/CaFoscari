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
}
```
è la visita di un albero, di conseguenza complessità Theta(n).