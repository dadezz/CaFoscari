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
#ifdef HEAP
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
#endif
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
la radice u di un albero T e un valore k verifica se T è k-compreso e ritorna true se T è
k-compreso, false altrimenti.
b. Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza
e la loro risoluzione tramite il metodo di sostituzione.
c. Specificare il linguaggio di programmazione scelto.*/

struct  Node_1 {
    int key;
    Node_1* left;
    Node_1* right;
}; 
typedef  Node_1* Pnode_1;

int somma_nodi(Pnode_1 x){
    if (!x) return 0;
    else return x->key + somma_nodi(x->left) + somma_nodi(x->right);
}
bool k_compreso(Pnode_1 x, int k){
   int somma = somma_nodi(x);
   if (somma > k || somma <k) return false;
   return true;
}

/**
 * funzione scritta in c++. La complessità è Theta(n). Infatti:
 *  - è limitata inferiormente da n poiché visita tutti i nodi dell'albero
 *  - dimostro che è limitata superiormente da n per induzione col metodo di sostituzione:
 *  T(n) = { c se n=0; T(k) + T(n-k-1) + d se n>0}, con k = numero di nodi del sottoalbero sinistro.
 * 
 *  suppongo che la complessità sia lineare, per cui T(n) = an + b. Caso base: T(0) = c per definizione, da cui a=0 e b=c.
 *  Passo induttivo: suppongo vero che, per ogni m<n la complessità sia lineare, e devo dimostrare T(n) = T(k) + T(n-k-1) + d è nella
 *  forma an + b. 
 *  Sostituisco: T(n) = a(k) + b + a(n-k-1) + b + d., da cui ak + b + an -ak -a + b + d, da cui an - a +2b + d.
 *  Eguaglio, an - a +2b + d = an + b, ricavo a = b+d, e posso scrivere T(n) = (b+d)n + c. cvd.
*/
//////////////////////////////////////////////////////////////////////////////////////
/**
 * Dato un vettore A di n numeri naturali, scrivere una procedura efficiente che ordini A in modo
tale che nel vettore risultante, dati i e j con 1 <= i <= j<=n, vale
mod(A[i], 3) <= mod(A[j], 3), dove mod(x, 3) è il resto della divisione di x per 3.
a. Dire se la soluzione proposta è in loco e se è stabile.
b. Valutare e giustificare la complessità della procedura proposta.
*/

void ordina_mod(std::vector<int>& v){
    if (v.size() == 0) return;
    std::vector<int> a0, a1, a2;
    for (int i=0; i<v.size(); i++){
        if (v[i]%3 == 0)
            a0.push_back(v[i]);
        else if (v[i]%3 == 1)
            a1.push_back(v[i]);
        else 
            a2.push_back(v[i]);
    }
    int index = 0;
    for (int i=0; i<a0.size; i++)
        v[index++] = a0[i];
    for (int i=0; i<a1.size; i++)
        v[index++] = a1[i];
    for (int i=0; i<a2.size; i++)
        v[index++] = a2[i];
}

/**
 * La soluzione proposta non è in loco, in quanto richiede una copia esterna di tutti gli n elementi contenuti nel vettore di partenza.
 * La soluzione è stabile in quanto l'ordine relativo tra elementi "uguali" (in questo caso, di modulo3 uguale) rimane invariata.
 * 
 * La soluzione ha complessità spaziale Theta(n), perché richiede l'allocazione di memoria aggiuntiva tale da memorizzare tutti gli n elementi.
 * La soluzione ha complessità temporale Theta(n), perché il primo ciclo itera n volte, i tre finali rispettivamente n1+n2+n3 volte, ma i tre vettori
 * sono partizione di quello di partenza, da cui n1+n2+n3 = n. Quindi in tutto ho 2n iterazioni più una qualche costante k per allocazione di memoria, 
 * assegnamenti e confronti. quindi in tutto Theta(n).
*/


/**
 * Si deve organizzare una gara di programmazione. Ogni programmatore ha un punteggio che esprime la sua
abilità (più alto è il punteggio migliore è il programmatore). Ogni programmatore è abbinato a un altro
programmatore e la differenza fra i loro punteggi è detta “scarto”.
a. Scrivere un algoritmo efficiente int scarto(int n, int punteggi[]) che dati n programmatori con n pari e
i loro punteggi restituisce il minimo scarto totale (somma degli scarti delle varie coppie) che si può
ottenere pianificando in modo ottimale le coppie nella gara.
b. Calcolare e giustificare la complessità dell’algoritmo proposto.
Si devono scrivere le eventuali procedure/funzioni ausiliarie utilizzate.
*/

// ordino il vettore e le coppie sono adiacenti

void ricombina(int n, int punteggi[]){
    int* v1 = malloc(sizeof(int)*n/2);
    int* v2 = malloc(sizeof(int)*n/2);

    for (int i=0; i<n/2; i++){
        v1[i] = punteggi[i];
    }
    for (int i=n/2; i<n; i++){
        v2[i-n/2] = punteggi[i];
    }
    int i=0; int j=0; int z=0;
    while(i<n/2 && j<n/2){
        if (v1[i] <= v2[j]){
            punteggi[z++] = v1[i++];
        }
        else {
            punteggi[z++] = v2[j++];
        }
    }
    while(i<n/2){
        punteggi[z++] = v1[i++];
    }
    while(j<n/2){
        punteggi[z++] = v2[j++];
    }

    free(v1);
    free(v2);
}

void ordina(int n, int punteggi[]){
    if (n > 1){
        ordina(n/2, punteggi+n/2);
        ordina(n/2, punteggi);
        ricombina(n, punteggi);
    }
}

int scarto(int n, int punteggi[]){
    ordina(n, punteggi);
    int ris = 0;
    for(int i=0; i<n; i+=2){
        ris += punteggi[i+1] - punteggi[i];
    }
    return ris;
}

/*
a) Dare la definizione di antenato di un nodo in un albero T.
b) Sia T un albero binario di ricerca contenente n chiavi distinte. Siano inoltre k1, k2 due
chiavi contenute in T. Scrivere una funzione efficiente in C antenato(Tree t, int k1, int k2)
che restituisce 1 se k1 è un antenato di k2 in T, 0 altrimenti. Si devono scrivere le eventuali
funzioni/procedure ausiliarie utilizzate.
c) Determinare e giustificare la complessità della soluzione proposta.
d) Scrivere i tipi in C Tree e Node.
*/

// un antenato di x è un qualsiasi nodo y che si trova in un cammino dalla radice a x.

struct Node{
    int key;
    Node* parent;
    Node* left;
    Node* right;
}

struct Tree {
    Node* root;
}

typedef enum {false, true} bool;

int antenato(Tree t, int k1, int k2){
    if (k1 == k2) return 1; // un nodo è antenato di sé stesso.
    
    bool trovato_k1, trovato_k2;
    trovato_k1 = trovato_k2 = false;
    Node* aux = t.root;

    while (aux != nullptr && !trovato_k1) {
        // condizioni che escono dal while sicuramente
        if (aux->key == k1) trovato_k1 = true;
        if (k1 < aux->key && k2 > aux->key) aux = nullptr; // sfrutto definizione di albero binario
        
        // ora di fatto sto cercando k1, che se è antenato di k2 in ogni caso viene prima
        if (k1 < aux->key) aux = aux->left;
        else aux = aux->right;
    }

    if (!trovato_k1) return 0;

    while(aux != nullptr && !trovato_k2){
        if (aux->key == k2) trovato_k2 = true;
        else if (k2 < aux->key) aux = aux->left;
        else aux = aux->right;
    }

    return trovato_k2 == true ? 1 : 0;    
}

/**
 * La complessità della soluzione proposta è O(h), con h altezza dell'albero. Ponendo n=numero di nodi dell'albero, Diventa un O(logn)
 * in caso di albero bilanciato, o O(n) nel caso peggiore di albero fortemente sbilanciato o degenere in lista. È O grande e non Theta in quanto
 * è solo limitato superiormente dal numero dei nodi di un cammino dalla radice alla foglia, ma nel caso immediato la risoluzione è costante.
 * 
 * Questa complessità è dovuta al fatto che, trascurati confronti e assegnamenti a complessità costante, il primo while esegue nel peggiore dei casi
 * (non viene mai trovato k1) esattamente h passi; in tutti gli altri casi si ferma alla profondità del nodo avente k1 come chiave, per poi
 * lasciare spazio al secondo while (qualora ci entrasse), che ricomincia a iterare da quella profondità fino al massimo al livello più basso
*/

/*
Realizzare una funzione efficiente triplo che, dato un array A di n interi, verifica se esiste
una coppia di indici i, j tali che A[j] = 3 ∗ A[i]. Restituisce 1 e i corrispondenti indici se la
coppia esiste, 0 altrimenti.
Analizzare la complessità e scrivere le eventuali funzioni/procedure ausiliarie utilizzate
*/

/*
fn Triplo(A, n){
    m = nuova unordered_map(int->int)
    for i=0 to n
        m[3*A[i]] = i
    trovato = false
    j = 0, index = 0
    while !trovato and j<n
        index = find(m[A[j]]) // -1 if not exists
        if index != -1
            trovato = true
        j += 1
    return index
}

La complessità asintotica temporale è Theta(n) in quanto il primo ciclo viene eseguito esattamente n voltee il secondo al più n volte,
la ricerca in una mappa ha complessità media costante.
da cui n<=T(n)<=2n. La funzione richiede uno spazio ausiliario proporzionale a n, da cui la complessità spaziale è Theta(n).
*/

/*
(a) Dato un albero binario T, definire l’altezza di un nodo v.
(b) Sia T un albero binario i cui nodi x hanno campi left, right e key. Scrivere una funzione
in C efficiente altezzaNodi(u, k) che riceve in input la radice u di un albero binario T e un
numero naturale k e restituisce il numero di nodi che hanno altezza k.
(c) Analizzare la complessità della funzione, indicando eventuali relazioni di ricorrenza.
Non si possono utilizzare strutture dati ausiliarie
*/

// si dice altezza di un nodo in un albero binario il più lungo cammino che lo separa da una foglia
int altezzaNodi_rec(Node* u, int k, int livello){
    if (u == nullptr) return 0;
    if (k == livello) return 1;
    if (k>livello) return altezzaNodi_rec(u->left, k, livello+1) + altezzaNodi_rec(u->right, k, livello+1);
}
int altezzaNodi(Node* u, int k){
    return altezzaNodi_rec(u, k, 0);
}

/*
Analisi complessità: La complessità della funzione è interamente a carico della funzione ausiliaria altezzanodi_rec. La quale, esclusi
confronti, return e somme di complessità costante, ha complessità temporale esprimibile nella forma 
T(n) = c per i casi base (n=0 o livello==k); T(n) = T(k) + T(n-k-1) + d altrimenti, con n numero dei nodi, k numero dei nodi del ramo sinistro
e d tempo costante aggiuntivo per le varie operazioni. La funzione è limitata superiormente da n, ovvero è O(n), non ha invece limite inferiore, in
quanto la ricorrenza può essere interrotta prima del caso base n=0.*/

/**
 * Sia dato un albero binario di ricerca T con n nodi e chiavi naturali. Si scriva tramite
pseudocodice una funzione efficiente che restituisca un albero binario di ricerca T′
contenente tutte e sole le chiavi pari di T.
Qual è la complessità in termini di tempo della funzione proposta? La soluzione proposta è
in loco?
Giustificare le risposte.
*/

//prima soluzione:
// visista inorder. come dimostrato a lezione fornisce l'albero in ordine crescente.
// si crea secondo albero separato totalmente sbilanciato. Complessità temporale Theta(n), spaziale O(n), risultato valido ma svantaggioso (lista).


// seconda soluzione:
// visita dell'albero.
// si procede con l'eliminazione dei nodi dell'albero. In loco-> complessità spaziale costante. L'eliminazione richiede di trovare il minimo.
// con in input un albero sbilanciato e tanti nodi dispari si finisce per avere complessità quadratica.

/*
Scrivere una funzione C efficiente, di nome simmetrico, che, dato un albero binario,
ritorna 1 se l'albero è speculare, sia dal punto di vista strutturale che nel contenuto dei nodi,
altrimenti ritorna 0.
Specificare la chiamata della funzione nel main.
Analizzare la complessità della funzione.
*/
bool simmetrico_aux(Node* x, Node* y){
    if (!x->left && !x->right) return true;
    if (!x->left || !x->right) return false;
    return (x->left->key == y->right->key) && simmetrico_aux (x->left, y->right) && simmetrico_aux(x->right, y->left);
}
bool simmetrico(Node* x){
    if (x == nullptr) return true;
    if (!x->left && !x->right) return true;
    if ((x->right && !x->left) || (x->left && !x->right)) return false;
    return simmetrico_aux(x->left, x->right);

}

/*
Sia BST+ la struttura dati che si ottiene aggiungendo ad ogni nodo x di un albero binario di
ricerca un nuovo attributo diff che contiene la differenza fra il numero di nodi nel
sottoalbero sinistro e quelli nel sottoalbero destro di x.

Modificando la procedura Tree-insert si definisca una procedura BST+-insert per
l’inserimento di una nuova chiave in un BST+.

Il prototipo della procedura è:
BST+-insert(TreeConDiff t, NodeConDiff z)
Si assuma che il nodo z sia così inizializzato:
z.p = z.left = z.right = NULL
z.key = k (nuova chiave)
z.diff = 0
Analizzare la complessità della procedura.
*/
struct diffnode{
    int key;
    int diff;
    diffnode* left;
    diffnode* right;
};
struct diffnode_tree{
    diffnode* root;
};
void bst_insert(diffnode_tree t, diffnode z){
    if (t == nullptr) 
        t = z
        return;
    x = t.root;
    while (x != nullptr){
        y = x;
        if (z.key < x.left){
            x.diff++;
            x = x.left;
        }
        else {
            x.diff--;
            x = x.right;
        }
    }
    if (y == nullptr) t.root = z;
    else {
        if (z.key < y.key) y.left = z;
        else y.right = z;
    }
}

// complessità = Theta(h), h = altezza albero, logn<=h<=n, a seconda di quanto è bilanciato l'albero, perché la funzione, 
// a meno di confronti e operazioni costanti, esegue un ciclo che itera su tutti i nodi di un cammino dalla radice a una foglia.