#include <vector>
/////////////////////////////////
    // ESERCIZIO 1
/////////////////////////////////

/*
Un albero binario si dice t-bilanciato se per ogni suo nodo vale la proprietà: le altezze dei sottoalberi radicati nei suoi figli differiscono per al più t unità.

    Dato un albero binario, scrivere una funzione EFFICIENTE che restituisca il minimo valore t per cui l'albero risulti t-bilanciato.
    Discutere la complessità della soluzione trovata.

Il prototipo della funzione è:
*/
int tBil(PNode u);
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
*/
bool isNonDec(PNodeG r);
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