#include <vector>
#include <algorithm>
#include <iostream>
/////////////////////////////////
    // ESERCIZIO 1
/////////////////////////////////

/*
Un albero binario si dice t-bilanciato se per ogni suo nodo vale la proprietà: le altezze dei sottoalberi radicati nei suoi figli differiscono per al più t unità.

    Dato un albero binario, scrivere una funzione EFFICIENTE che restituisca il minimo valore t per cui l'albero risulti t-bilanciato.
    Discutere la complessità della soluzione trovata.

Il prototipo della funzione è:
int tBil(PNode u);
*/
/*
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.

Il tipo PNode è così definito:
*/
struct Node{ 
  int key;
  Node* left;
  Node* right;
};
typedef Node* PNode;

/*
 soluzione
function Decomponibile(u) {
    if u == NIL 
        risolvi_direttamente()
    else 
        risultato_sx = Decomponibile(u.left)
        risultato_dx = Decomponibile(u.right)
        return ricombina(risultato_dx, risultato_sx)
}

Mi serve tenere in qualche modo conto globalmente della soluzione finora trovata, e ricorsivamente dell'altezza di ogni sottoalbero, per poter scegliere
tra il modulo della differenza tra i rami e il miglior risultato trovato finora. Posso quindi portarmi dietro come puntatore il risultato e ritornare la 
altezza. Potrei anche portarmi un pair senza quindi usare fnzioni ausiliarie, ma non lo trovo sensato
*/
int tBil_Aux(PNode u, int& risultato){
    if (u == nullptr) {
        return 0;
    }
    int altezza_sinistra = tBil_Aux(u->left, risultato);
    int altezza_destra = tBil_Aux(u->right, risultato);
    int differenza = altezza_destra>altezza_sinistra ? altezza_destra-altezza_sinistra : altezza_sinistra-altezza_destra; // modulo della differenza
    risultato = risultato > differenza ? risultato : differenza; // max tra i due
    return 1 + (altezza_destra > altezza_sinistra ? altezza_destra : altezza_sinistra); // ritorno ilmassimo tra le due altezza
}

int tBil(PNode u){
    int risultato = 0;
    tBil_Aux(u, risultato);
    return risultato;
}

//////////////////////////////////
    // ESERCIZIO 2
/////////////////////////////////
/*
Sia T un albero generale i cui nodi hanno campi: key, left-child e right-sib. Si scriva una funzione EFFICIENTE che verifichi la seguente proprietà: 
per ogni nodo u, le chiavi dei figli del nodo u devono avere valori non decrescenti considerando i figli di u da sinistra verso destra.

Il prototipo della funzione è:
bool isNonDec(PNodeG r);
*/
/*
Restituisce true se la proprietà è verificata altrimenti false.

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.

Il tipo PNodeG è così definito:
*/
struct NodeG{  
  int key;
  NodeG* left_child;
  NodeG* right_sib;
};
typedef NodeG* PNodeG;
/*
Soluzione 
devo guardare prima in profondità, quindi le foglie del ramo più a sinistra. se quelle sono decrescenti, ritornerò true, e scorro con un while
i nodi fratelli nel livello attuale, guardando intatno se ogni rightsib è >= del nodo attuale (in tal caso ritorno falso e stoppo), e guardando la stessa
caratteristica nei figli
*/
bool isNonDec(PNodeG r){
    if (r == nullptr)
        return true;
    bool decrescente = true;
    while (r != nullptr && decrescente){
        if (r->right_sib) {
            if (r->right_sib->key < r->key) 
                decrescente = false;
        }
        decrescente = decrescente && isNonDec(r->left_child);
        r = r->right_sib;
    }
    return decrescente;
}
//////////////////////////////////
    // ESERCIZIO 3
/////////////////////////////////
/*
Dati due vettori contenenti rispettivamente i valori dei nodi tutti DISTINTI ottenuti da 
una visita in ordine anticipato e da una visita in ordine simmetrico di un albero binario, si ricostruisca l’albero binario.

Il prototipo della funzione è:
*/
PNode ricostruisci(const std::vector<int>& va, const std::vector<int>& vs);
/*
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
/*
Soluzione
Ci sono tre modi di visitare un albero:
    1. Visita anticipata: prima visito il nodo in cui mi trovo, poi vado sui due sottoalberi
        Visita(r){
            if r != NULL 
                visita_il_nodo;
                visita(r->left);
                visita(r->right);
        }
    2. Visita simmetrica: guardo il ramo sx, poi visito il nodo in cui sono, poi il ramo dx
        Visita(r){
            if r != NULL 
                visita(r->left);
                visita_il_nodo;
                visita(r->right);
        }
    3. Visista posticipata: guardo prima il ramo sx, poi il ramo dx, poi visito il nodo in cui sono
        Visita(r){
            if r != NULL 
                visita(r->left);
                visita(r->right);
                visita_il_nodo;
        }

        A
      /   \
    L       B
  /  \       \
E     R       O


Output nei vari casi: 
    1.  A L E R B O
    2.  E L R A B O
    3.  E R L O B A

nell'esercizio, ci sono le stringhe 1 e 2. 

il primo elemento del vettore preorder è la radice dell'albero e ci alloco la memoria
Nel vettore simmetrico, esso divide in due rami dx e sx. 
alla prima iterazione trovo quindi:
    A
  /  \
(ELR)   (BO)

passo quindi al secondo elemento del primo vector. So che si trova nel ramo sx di A ed è a sua volta radice del sottinsieme trovato.
     A
   /  \
  L    (BO)
 / \
(E) R

passo quindi al terzo elemento. so che è a sx e lo alloco. è l'ultimo elemento rimasto nel sottinsieme sinistro delle visite simmetriche
-> il prox nodo sta a destra
     A
   /  \
  L    (BO)
 / \
E   (R)

infatti, il quarto elemento è R, lo alloco come figlio dx. Il sottinsieme (ELR) ora è concluso 

     A
   /  \
  L    (BO)
 / \
E   R

con lo stesso procedimento risolvo il ramo destro
*/


PNode ricostruisci(const std::vector<int>& va, const std::vector<int>& vs){
    //caso base
    if (va.size() == 0 || vs.size() == 0) return nullptr;

    //creo nodo radice
    PNode node = new Node;
    node->key = va[0];

    // trovo il nodo nel vettore simmetrico
    auto indice = find(vs.begin(), vs.end(), node->key);
    int lunghezza_sinistra = std::distance(vs.begin(), indice);

    // faccio le due chiamate ricorsive (destra e sinistra):
    // devo splittare i due array, in destro e sinistro. uso l'indice trovato sopra come segnaposto
    node->left = ricostruisci(std::vector<int>(va.begin()+1, va.begin()+1+lunghezza_sinistra), std::vector<int>(vs.begin(), indice));
    node->right = ricostruisci(std::vector<int>(va.begin()+1+lunghezza_sinistra, va.end()), std::vector<int>(indice+1, vs.end()));

    return node;
}
//////////////////////////////////
    // ESERCIZIO 3
/////////////////////////////////
/*
Dato un albero binario, scrivere una funzione che costruisce un array bidimensionale mat tale che, per ogni coppia di nodi u e v, 
l’elemento mat[u][v] sia il minimo antenato comune di u e v. La funzione deve richiedere tempo O(n^2) e il suo prototipo è:
*/
void minAntCom(PNode r, std::vector<std::vector<int>>& mat);
/*
Per semplicità si assuma che i nodi abbiano chiavi numerate da 0 a n-1 e che queste chiavi identifichino il nodo. 
Di conseguenza gli indici della matrice rappresentano i nodi e in posizione mat[u][v] c'è la chiave del nodo che è il minimo antenato comune di u e v.

[Il minimo antenato comune di due nodi u e v è  l’antenato comune  di u e v che si trova più lontano dalla radice dell’albero.]

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
//soluzione
/*
Non devo prendere una coppia di nodi e trovare l'antenato comune, perché avrebbe complessita n^3 (nodi*nodi*trova_antenato, che nel peggiore dei casi è n).
Meglio sicuramente fare un ragionamento al contrario. la radice è sicuramente MAC di tutti i nodi successivi tra quelli sempre a destra e quelli sempre a sinistra.
ugualmente, radice->left è il MAC di tutti i nodi tra quelli sempre a sx e sempre a dx del suo ramo.

                 10
               /    \
             5       15
           /  \    /    \
          2    8  12    17
         / \  / \   \   /  \
        1   4 7  9   13 16  19
       /     /         /
      0     6         14
           / \      /
          18  3    11

prima chiamata: 10 è radice di 
    1) sé stessa con gli altri nodi:
        m[10][5], m[10][15], m[10][2], m[5][tutti i nodi sotto di essa]
    2) i nodi alla sua sinistra con i nodi alla sua destra:
        m[5][15], m[5][12], m[5][17], m[5][tutti i numeri a destra]
        m[2][15], m[2][12], m[2][17], m[2][tutti i numeri a destra]
        .
        .  per ogni nodo a sinistra della radice
        .
        m[3][15], m[3][12], m[3][17], m[3][tutti i numeri a destra].

seconda chiamata: 5 è radice di
    1) sé stessa con gli altri nodi:
        m[5][2], m[5][8], m[5][1], m[5][tutti i nodi sotto di essa]
    2) i nodi alla sua sinistra con i nodi alla sua destra:
        m[2][8], m[2][7], m[2][9], m[2][tutti i numeri a destra]
        m[1][8], m[1][7], m[1][9], m[1][tutti i numeri a destra]
        .
        .  per ogni nodo a sinistra della radice
        .
        m[0][8], m[0][7], m[0][9], m[0][tutti i numeri a destra]


e così via, per ogni nodo a sotto la radice. Bisogna fare sempre sia destra che sinistra, perché facendo solo quelli a sinistra e calcolando i simmetrici, non avrei mai 
il MAC di [12][17]. 
Bisogna invece scrvere il simmetrico quando il nodo trova il MAC tra sé stesso e tutti gli altri nodi. Così facendo, 
per ogni nodo visitato, c'è una relazione tra lui come indice primario e tutti i nodi dell'albero come indice secondario, definendo così complessità asintotica di O(n^2).

Si noti che non è che ogni nodo viene visitato una volta e si relaziona con tutti in una volta sola, ma a ogni visita si relaziona con nodi diversi dell'albero
                  
*/
void minAntleftu(const PNode root, const PNode v, const PNode u, std::vector<std::vector<int>>& mat, int & i){
    if (u == nullptr || v == nullptr) return;
    // (debug)) std::cout<<"minAntleftu su root: "<<root->key<<", v: "<<v->key<<" e u: "<<u->key<<"; iterazione: "<<i++<<std::endl;
    mat[u->key][v->key] = mat[v->key][u->key] = root->key;
    minAntleftu(root, v, u->left, mat, i);
    minAntleftu(root, v, u->right, mat, i);
    minAntleftu(root, v->left, u, mat, i);
    minAntleftu(root, v->right, u, mat, i);
}
void minAntru(PNode root ,PNode u, std::vector<std::vector<int>>& mat, int& i){
    if (u==nullptr) return;
    // (debug)) std::cout<<"minAntru su root: "<<root->key<<" e u: "<<u->key<<"; iterazione: "<<i++<<std::endl;
    mat[root->key][u->key] = mat[u->key][root->key] = root->key;
    minAntru(root, u->left, mat, i);
    minAntru(root, u->right, mat, i);
}
void minAntCom(PNode r, std::vector<std::vector<int>>& mat, int& i){
    if (r==nullptr) return;
    minAntru(r, r, mat, i);
    minAntleftu(r, r->left, r->right, mat, i);
    minAntCom(r->left, mat, i);
    minAntCom(r->right, mat, i);
}

int main() {
    // Crea un semplice albero binario per il test:
    /*
              3
            /   \
          1       4
        /  \       \
      2     0       5
    
    */
    PNode root = new Node {
        0, 
        new Node{
            1,
            new Node{
                3, 
                nullptr, 
                nullptr
            },
            new Node{
                4, 
                nullptr, 
                nullptr
            }
        },
        new Node {
            2,
            new Node{
                6, 
                nullptr,
                nullptr
            },
            new Node{
                5, 
                nullptr,
                nullptr
            }
        }
    };
    
    // Dimensione dell'albero
    const int treeSize = 7;

    // Inizializza la matrice con dimensione treeSize x treeSize
    std::vector<std::vector<int>> matrix {
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0},
        std::vector<int> {0, 0, 0, 0, 0, 0, 0}
    };
    int i = 1;

    // Chiama la tua funzione
    minAntCom(root, matrix, i);
    std::cout<<"iterazioni totali: "<<i<<std::endl;
    // Stampa la matrice risultante
    std::cout << "Matrice dei minimi antenati comuni:" << std::endl;
    for (int i = 0; i < treeSize; ++i) {
        for (int j = 0; j < treeSize; ++j) {
            std::cout << "Radice tra" << i << " e " << j << ": " << matrix[i][j] << " ";
            std::cout << std::endl;
        }
    }

    // Deallocazione della memoria dell'albero
    // TODO: Aggiungi una funzione per la deallocazione della memoria degli elementi dell'albero

    return 0;
}