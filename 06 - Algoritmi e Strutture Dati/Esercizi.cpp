#include <vector>
#include <algorithm>
/**
 * Scrivere una funzione efficiente in C o in C++ blackHeight(u)che dato in input la radice u di un albero binario, 
 * i cui nodi x hanno, oltre ai campi key, left e right, un campo colche può essere B(per “black”) oppure R(per “red”),
 * verifica se per ogni nodo, il cammino da quel nodo a qualsiasi foglia contiene lo stesso numero di nodi neri 
 * (altezza nera del nodo x). In caso negativo, restituisce -1, altrimenti restituisce l’altezza nera della radice. 
 * 
 * a.Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza.
 * b.Scrivere il tipo del nodo dell’albero in C o in C++ a seconda del linguaggio scelto.
*/

struct Node {
    int key;
    Node* left;
    Node* right;
    char col;
};
typedef Node* Pnode;


int blackHeight(Pnode u){
    if (u == nullptr) return -1; // succede solo in radice, la f non viene mai più chiamata su nullptr
    if (u->right == nullptr && u->left == nullptr) 
        return u->col == 'B' ? 1 : 0;
    int res_sx, res_dx;

    // risultato destro
    if (u->right != nullptr){
        if (u->col == 'B'){
            int aux = blackHeight(u->right);
            res_dx = (aux == -1 ? -1 : 1+aux);
        }
        else {
            int aux = blackHeight(u->right);
            res_dx = (aux == -1 ? -1 : aux);
        }
    }

    if (res_dx == -1) return -1; // se già non è valida la proprietà è inutile che io continui la visita

    // risultato sinistro
    if (u->left != nullptr){
        if (u->col == 'B'){
            int aux = blackHeight(u->left);
            res_sx = (aux == -1 ? -1 : 1+aux);
        }
        else {
            int aux = blackHeight(u->left);
            res_sx = (aux == -1 ? -1 : aux);
        }
    }

    if (res_dx == -1 || res_dx != res_sx) 
        return -1;
    else 
        return res_dx;
}
/*complessità lineare in quanto visita di un albero binario*/

/**
 * Si consideri la struttura dati Max-Heap implementata tramite un vettore (secondo lo schema
visto a lezione).
a) Si scriva la definizione di Max-Heap.
b) Si realizzi in modo efficiente in pseudocodice la funzione Differenza(H1,H2) che dati
due Max-Heap H1 e H2 contenenti rispettivamente n1 e n2 interi (anche ripetuti),
ritorna in output un nuovo Max-Heap contenente gli elementi che appartengono a H1
ma non appartengono a H2. In presenza di duplicati se x compare k1 volte in H1 e k2
volte in H2, nel Max-Heap differenza x dovrà comparire max{0, k1-k2}.
c) Si determini e giustifichi la complessità in funzione di n1 e n2.
Si devono scrivere le eventuali funzioni/procedure ausiliarie utilizzate.
*/

/**
 * max_Heap è una struttura dati basata su un albero binario quasi completo, le cui foglie (unico livello eventualmente non riempito) sono tutte
 * addossate nel lato sinistro. È caratterizzato dal fatto che ogni nodo è maggiore/uguale dei nodi figli, e di conseguenza la radice contiene il massimo
 * È comoda l'implementazione su vettore in quanto la posizione dei nodi come indici è immediata e
 * determinata da semplici calcoli: parent(i) è la parte inferiore intera di i/2, il figlio sinistro è i*2 e il destro i*2+1
*/
typedef std::vector<int> Heap;

void Heap::max_heapify(int i){
    int l = left(i);
    int r = right(i);
    int massimo;
    if (l<heap_size && this[i]<this[l]){
        massimo = l;
    }
    if (r<heap_size && this[massimo]<this[r]){
        massimo = r
    }
    if (i!=massimo) scambia(massimo, i);
    max_heapify(massimo);
}

int Heap::extract_max(){
    if (this.heap_size <1) return error;
    int ris = this[0];
    this[0] = this.heap_size--;
    this.max_heapify(1);
    return ris;
}

Heap differenza(Heap h1, Heap h2){
    Heap ris;
    while(!h1.empty() && !h2.empty()){
        if (h1.max() == h2.max()) { // controlli costanti
            h1.extract_max();   //log n
            h2.extract_max();
        }
        else if (h2.max() > h1.max){
            h2.extract_max();   // log n
        }
        else {
            int aux = h1.extract_max(); // log n
            /** posso fare un push back senza heapify perché estraendo i massimi uno alla volta, 
             * ho un'estrazione ordinata in ordine decrescente. un array ordinato col max in radice
             * è per definizione un max_heap
            */
            ris.push_back(aux); //const
        }
    }
    while (!h1.empty()){
        int aux = h1.extract_max();
        ris.push_back(aux);
    }
    return ris;
}

/**
 * l'unione dei due cicli viene eseguita al più n1+n2 volte. "al più" perché sicuramente h1 viene scorso del tutto, non è detto sia così invece per
 * h2. della serie di if/else ne viene selezionato a ogni iterazione uno solo. In ognuno è presente un extract_max(), che ha complessità O(logn), con n
 * numero dei nodi dell'heap su cui viene chiamata. Nel primo caso l'operazione è presente due volte, da cui O(log(n1+n2)). Dal momento che le costanti 
 * moltiplicative sono trascurabili nello studio della complessità asintotica, La funzione ha complessità O((n1+n2)log(n1+n2)).
*/

/**Sia T un albero binario i cui nodi x hanno i campi left, right e key, dove key è un numero
intero. L’albero si dice k-compreso, per un certo numero naturale k, se per ogni nodo x la
somma delle chiavi dei nodi dell’albero radicato in x è compresa tra -k e k.
a. Scrivere una funzione efficiente in C o C++ k_compreso(u,k) che dato in input
la radice u di un albero T e un valore k verifica se T è k-compreso e ritorna 1 se T è
k-compreso, 0 altrimenti.
b. Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza
e la loro risoluzione tramite il metodo di sostituzione.
c. Specificare il linguaggio di programmazione scelto.*/

struct  Node_1 {
    int key;
    Node_1* left;
    Node_1* right;
}; 
typedef  Node_1* Pnode_1;

bool k_compreso(Pnode_1 x, int k){
    
}