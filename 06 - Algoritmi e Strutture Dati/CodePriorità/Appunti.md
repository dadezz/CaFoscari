# Code di Priorità
Struttura dati che serve a mantenere un insieme dinamico di elementi s, iascuno dei quali ha un valore associato detto "chiave" o "peso". Ci sono due tipi di code:
* code di massima priorità
* code di minima priorità

## Code di Massima priorità
* insert: inserisce l'elemento x nell'insieme S
* maximum: restituisce l'elemento di S con la chiave più grande senza rimuoverlo
* extract_max: elimina e restituisce l'elelmtno di D con la chiave più grande
* increase_key: aumenta il valore della chiave di x al nuovo valore k, che si suppone sia almeno pari al valore corrente della chiave di x.

Un esempio di applicazioni di queste strutture dati è lo csheduler dei processi di un sistema operativo

## Code di Minima priorità
* insert: inserisce l'elemnto x nell'insieme S
* minimum: restituisce l'elemento di S con la chiave più piccola senza rimuoverlo
* extract_min: elimina e restituisce l'elemento di D con la chiave più piccola
* increase_key: diminuisce il valore della chiave di x al nuovo valore k, che si suppone sia 
almassimo pari al valore corrente della chiave di x.

Queste code le vedremo applicate nel modulo 2 sugli algoritmi che operano sui grafi

## Implementazione con Heap

```cpp
int heap_maximum (Heap A){
    if (A.heap_size < 1)
        error_HeapUnderflow
    else 
        return A[1]
}
int heap_extract_max(Heap A){
    if (A.heap_size <1 )
        error_HeapUnderflow
    else {
        max = A[1]
        a[1] = A[a.heap_size]
        A.heap_size = A.heapsize-1
        max_heapify(A, 1) // Log(n)
        return max
    }
}
void heap_increase_key(Heap A, T i, T key){
    if (key<A[i])
        error_key
    A[i] = key
    while (i>1 && A[parent(i)]<A[i]){
        scambia(A[i], A[parent(i)])
        i = parent(i)
    }
}
```
Il tempo di exec di heap_increae_key è O(logn) xk seguiamo un cammino dal nodo i alla radice.

```cpp
void max_heap_insert(Heap A, int key){
    a.heap_size++
    A[a.heap_size] = -inf
    heap_increase_key(a, a.heap_size, key) 
}
```
Anche queesta è O(logn) xk chiama la f precedente
**Conclusione** un heap può svolgere ciascuna delle operazioni con le code di priorità nel tempo O(logn) su un insieme dinamico di n elementi