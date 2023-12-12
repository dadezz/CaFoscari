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
/*
ANALISI COMPLESSITÀ
L'algoritmo in questione è una visita all'albero, cioè visita tutti i nodi dell'albero, solo una volta ognuno. 
Ha complessità temporale asintotica Theta(n).
Questo perché:
Il caso base è u==nullptr, ovvero n=0, la cui complessità è costante (una operazione di return). Nel caso N>0, l'algoritmo esegue due chiamate ricorsive, una per ogni sottoalbero, più una serie di confronti e assegnamenti con complessità costante. Ciò si traduce in T(n) = T(k) + T(n-k-1) + d, dove k è il numero di nodi del sottoablero dx (0<=k<=n-1) e d è il tempo costante di ogni visita del nodo. 
Siccome se n=1, k deve essere 0, abbiamo che T(1) = T(0) + T(0) + d. T(0) per definizione è costante, quindi T(1) è costante, da cui si evince che la complessità per la visita del singolo nodo è costante.
Passando alla ricorrenza, notiamo subito che (k + (n-k-1)) equivale a n-1, da cui si può semplificare la ricorrenza in T(n) = T(n-1) + d. Sviluppando la ricorsione, si arriva alla forma T(n) = T(1) + T(1) + ... n volte, da cui T(n) = nT(1), da cui, infine, T(n) = Theta(n).
*/

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

/*
ANALISI COMPLESSITÀ
La complessità dell'algoritmo in questione si può analizzare in modo analogo a quella dell'esercizio 1. 
Il caso base ha sempre complessità costante. Per quanto concerne invece la parte ricorsiva del problema, va analizzato il caso peggiore, quello cioè in cui la guardia del ciclo while è sempre vera (la verifica di quest'utlima ha complessità costante). Il ciclo while itera su ogni "fratello" del nodo in analisi, quindi m iterazioni. Ogni iterazione, oltre a una serie di operazioni ha complessità costante, ha una chiamata ricorsiva, sull'intero sottoalbero del nodo visitato in quella iterazione del ciclo. 
Dalla definizione della struttura dati, ogni nodo di un sottoalbero non può avere come antenato un nodo di un altro sottoalbero, di conseguenza, i sottoalberi di ogni "fratello" non hanno nodi in comune. Dal momento che vengono lo stesso visitati tutti (sempre nel caso di guardia vera) si può assumere, per semplicità di calcolo, che, se ci sono k sottonodi, essi sono equamente divisi nei vari sottoalberi. La somma infatti è sempre la medesima, a prescindere dalla distribuzione dei nodi, si potrebbe proseguire il calcolo con k1 + k2 + ... + km, e imporre la somma = k, oppure con k/m e va da sé che k/m * m = k. 
Si ottiene quindi che per ogni passo ricorsivo la complessità diventa
T(n) = d + mT(k), con k = (n-1)/m, da cui si ottiene, come nell'esercizio precedente, T(n) = Theta(n). Questo nel caso peggiore. Considerando che il ciclo while contiene una guardia che non per forza è vera, non è detto che tutta la serie di visite venga portata a termine, da cui la complessità si riduce a O(n).
*/

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

Nell'analisi della complessità alcune considerazioni sulla mia scelta implementativa (unordered map)
*/


PNode ricostruisci_aux(const std::vector<int>& va, const std::vector<int>& vs, int va_start, int va_end, int vs_start, int vs_end, unordered_map<int, int>& map){
    //caso base
    if (va_start >= va_end || vs_start >= vs_end) return nullptr;

    //creo nodo radice
    PNode node = new Node;
    node->key = va[va_start];

    // trovo il nodo nel vettore simmetrico
    auto indice = map[node->key];
    int lunghezza_sinistra = indice - vs_start;

    // faccio le due chiamate ricorsive (destra e sinistra):
    // devo splittare i due array, in destro e sinistro. uso l'indice trovato sopra come segnaposto
    node->left  = ricostruisci_aux(va, vs, va_start + 1, va_start + 1 + lunghezza_sinistra, vs_start, indice, map);
    node->right = ricostruisci_aux(va, vs, va_start + 1 + lunghezza_sinistra, va_end, indice + 1, vs_end, map);

    return node;
}

PNode ricostruisci(const std::vector<int>& va, const std::vector<int>& vs){
    std::unordered_map<int, int> map;
    for (int i = 0; i < vs.size(); ++i) {
        map[vs[i]] = i;
    }

    return ricostruisci_aux(va, vs, 0, va.size(), 0, vs.size(), map);
}

/*
Per le stesse considerazioni fatte nell'esercizio 2, per calcolare la complessità si può supporre l'albero come bilanciato (o più correttamente che abbia lo stesso numero di nodi nei due sottoalberi), in quanto a ogni chiamata ricorsiva vengono analizzate 2 partizioni (quindi distinte e la cui somma è il numero totale) dei nodi dei sottoalberi.

considerazione sull'implementazione: inizialmente avevo pensato a una ricerca sul vettore vs per l'indice di split, poi però ho notato che quell'informazione sarebbe stata ricalcolata ad ogni chiamata di funzione, e ha complessità O(n). non solo, anche la chiamata ricorsiva in sé richiedeva (o almeno io avevo risolto in questo modo) di copiare la metà del vettore (usando gli iteratori per allocare la memoria correttamente). 
in questo primo caso avremmo avuto quindi:

caso base: costante
funzione ricorsiva: "find" ha complessità lineare O(n), distance è O(1) in quanto i vector sono ad accesso diretto, la chiamata ricorsiva, per i motivi di cui sopra, si può ridurre a 
ricostruisci (vector(n/2), vector(n/2)), per entrambe le chiamate.
Abbiamo quindi una struttura del tipo
T(n) {
    costante            if n==0
    O(n) + d + 2T(n/2)  altrimenti
}
Si può risolvere con il master theorem. O(n) + d si può semplificare direttamente in O(n).
f(n) = O(n), a=2, b=2. d = log2(2) = 1. Le condzioni di applicabilità sono rispettate.
f(n) = Theta(n^1), siamo nel secondo caso, la complessità è Theta(nlogn)

Con l'implementazione attuale della funzione, invece, c'è un Theta(n) nella funzione principale, che è il popolamento dell'unordered map, poi però nella ausiliaria ogni espressione ha complessità costante, rimane la chiamata ricorsiva, 
che è Theta(n).
Con l'aggiunta quindi di un fattore n nella complessità spaziale, si riesce a ridurre il problema a complessità Theta(n), che per essere precisi è formato da quello iniziale in "ricostruisci" e dalla chiamata ricorsiva che ha forma 2T(n/2).
*/


//////////////////////////////////
    // ESERCIZIO 4
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
                  
*/// (debug) int i =1;

void aux1 (int root, int key1, const PNode nodo_destro_variabile, std::vector<std::vector<int>>& mat){
    if (nodo_destro_variabile == nullptr) return;
    // (debug) std::cout<<"aux1 su root: "<<root<<"key: "<<key1<<" e u: "<<nodo_destro_variabile->key<<"; iterazione: "<<i++<<std::endl;
    mat[key1][nodo_destro_variabile->key] = mat[nodo_destro_variabile->key][key1] = root;
    aux1(root, key1, nodo_destro_variabile->left, mat);
    aux1(root, key1, nodo_destro_variabile->right, mat);
}
void minAntleftu (int root, const PNode sx, const PNode dx, std::vector<std::vector<int>>& mat){
    if (sx == nullptr) return;
    aux1(root,  sx->key, dx, mat);
    minAntleftu(root, sx->left, dx, mat);
    minAntleftu(root, sx->right, dx, mat);
}

void minAntru(PNode root ,PNode u, std::vector<std::vector<int>>& mat){
    if (u==nullptr) return;
    // (debug) std::cout<<"minAntru su root: "<<root->key<<" e u: "<<u->key<<"; iterazione: "<<i++<<std::endl;
    mat[root->key][u->key] = mat[u->key][root->key] = root->key;
    minAntru(root, u->left, mat);
    minAntru(root, u->right, mat);
}
void minAntCom(PNode r, std::vector<std::vector<int>>& mat){
    if (r==nullptr) return;
    minAntru(r, r, mat);
    minAntleftu(r->key, r->left, r->right, mat);
    minAntCom(r->left, mat);
    minAntCom(r->right, mat);
}

/*
ANALISI COMPLESSITÀ.
sia n il numero dei nodi dell'albero.

minAntCom:
caso base costante; la funzione poi ha una chiamata a minAntru su n e una chiamata a minAntleftu su n-1. Chiama poi sé stessa distintamente sui sottoalberi, effettuando di fatto una visita. La complessità della visita si dimostra, in modo analogo alla dimostrazione dell'esercizio 1, essere Theta(n). 
La complessità della funzione sarà quindi data da:
Theta(n) * (T(minantru) + T(minantleftu)).

MinAntru:
caso base costante; la funzione effetta un assegnamento costante e poi due chiamate ricorsive a sé stessa e, con la medesima dimostrazione, si calcola la complessità Theta(n).

Aux1:
Anch'esso è una visita, solo di un sottoalbero però. Sempre per le stesse considerazioni su albero partizionato degli esercizi precedenti, si può considerare Theta(n/2).

MinAntleftu:
caso base costante. la funzione effettua un assegnamento costante, chiama aux e visita il suo sottoalbero. Notare sempre che sia aux1 che minantleftu "lavorano" sui sottoalberi indipendenti del nodo visitato dalla funzione madre, non sullo stesso.

Possiamo arrivare a un'equazione del tipo:
T(n) = [minantru] + [Minantleftu] + T(k) + T(n-k-1) + d
da cui:
T(n) = n + k*(n-k-1) + T(k) + T(n-k-1) + d

Sempre per le stesse considerazioni su albero partizionato degli esercizi precedenti, si può considerare la complessità come visita su metà albero (meno il nodo iniziale)
Si può assumere k = n/2, così da semplificare, a meno di costanti, in

T(n) = n + (n/2)*(n-n/2) + 2T(n/2) + d
T(n) = n + n^2/2 - n^2/4 +2T(n/2) + d
T(n) = n^2 + 2T(n/2).

Applicando il master theorem, a=2, b=2, f(n) = Omega(n^(1+0.5)) e 2(n^2/2) <= 0.5*n^2. Siamo nel terzo caso, ecco che 
T(n) = Theta(n^2)

Si può fare una visione generale di tutte le ricorrenze:
poniamo di avere l'albero qui rappresentato:

        n1
      /    \
    n2       n3
  /  \    /    \
n4    n5  n6    n7

Si inizia dalla visita di n1. le coppie di nodi sono gli assegnamenti che vengono fatti (speculari sottintesi).

n1  -> (minantru)   (n1, n2)
                    (n1, n4)
                    (n1, n5)
                    (n1, n3)
                    (n1, n7)
    -> (minantleftu) n2     (n2, n3)
                            (n2, n6)
                            (n2, n7)
                        -> n4   (n4, n3)
                                (n4, n6)
                                (n4, n7)
                        -> n5     (n5, n3)
                                (n5, n6)
                                (n5, n7)
    -> n2   -> (minantru)   (n2, n4)
                            (n2, n5)
            -> (minantleftu) n4     (n4, n5)
        -> n4   nulla
        -> n5   nulla
    -> n3   -> (minantru)   (n3, n6)
                            (n3, n7)
            -> (minantleftu) n6     (n6, n7)
        -> n6 nulla
        -> n7 nulla

È facile quindi notare che ogni coppia di nodi viene visitata una sola volta, senza neppure passare per la coppia speculare, determinando così una complessità totale di O(n^2). non theta proprio perché si evita di ripassare su una coppia già visitata
*/
//////////////////////////////////
    // ESERCIZIO 5
/////////////////////////////////
/*
Nel centro di Preparazione Olimpica Acqua Acetosa "Giulio Onesti" si allenano la nazionale maschile e femminile di sollevamento pesi. Purtroppo, anche qui può accadere che i pesi vengano rimessi nei posti sbagliati.
Date n coppie di manubri con pesi distinti, i manubri sono posizionati senza un ordine particolare su due rastrelliere. Inizialmente ogni fila ha un numero uguale di manubri. Trattandosi di una palestra professionale ben finanziata, c'è spazio infinito alle due estremità di ciascuna rastrelliera per sostenere eventuali pesi aggiuntivi.
Per spostare un manubrio, si può farlo rotolare in uno spazio vicino libero sulla stessa rastrelliera quasi senza sforzo, oppure si può prenderlo, sollevarlo e posizionarlo in un altro posto libero; questo richiede forza proporzionale al suo peso.
Qual è il peso più pesante che si deve sollevare per poter mettere pesi identici uno accanto all'altro? Si tenga presente che su ciascuna rastrelliera dopo la riorganizzazione potrebbe esserci sistemato un numero diverso di pesi; questo è consentito.

Il prototipo della funzione è:
*/
int PesoMinimo(std::vector<int> pesi_1, std::vector<int> pesi_2);
/*
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.

Esempio:
input:                       output:
5
2 1 8 2 8                   2
9 9 4 1 4

input:                       output:

8
7 7 15 15 2 2 4 4      0
5 5 3 3 9 9 1 1
*/
/*
SOLUZIONE
orcoddemonio che cazzo è non ho manco capito la richiesta
*/
#include <unordered_map>

using namespace std;

int PesoMinimo(std::vector<int> pesi_1, std::vector<int> pesi_2){
    unordered_map<int, int> index_map_1;
    if (pesi_1.size() == 0) return 0;
    // prima iterazione: Theta(N)
    // popolamento dell'unordered map
    for(int i=0; i<pesi_1.size(); i++){
        index_map_1[pesi_1[i]]++;
    }
    
    int result = 0;  //valore di ritorno finale

    // max elemento disaccoppiato (per forza di cose devo spostarlo)
    for (int i = 0; i<pesi_1.size(); i++)
        if(index_map_1[pesi_1[i]] %2 == 1)
            result = result > pesi_1[i] ? result : pesi_1[i];


    int guardia;
    // ora scorro tutto il vettore, mi sposto di uno in uno in cerca di coppie.
    /**
     * 28218
     * 
     * popolo la map e scopro che 1 è disaccoppiato. result = 1
     * 
     * guardia 2. devo scorrere finché non trovo un altro 2.
     * se trovo un numero maggiore di result (in sto caso 8), sposto la guardia all'elemento trovato, 
     * e aggiorno result con max(result, 2). 
     * poi scorro con guardia 8, e vedo se dentro c'è qualche numero maggiore di result. in sto caso non trovo nulla fino al 
     * prossimo 8. assegno guardia al numero successivo. non lo trovo, in sto caso allora result è 2 e finisce ciclo
    */
    guardia = pesi_1[0];
    for (int i = 1; i<pesi_1.size(); i++){
        if (pesi_1[i] == guardia) guardia = pesi_1[++i];
        else if (pesi_1[i] > result){
            result = result > guardia ? result : guardia;
            guardia = pesi_1[i];
        }
    }
    guardia = pesi_2[0];
    for (int i = 1; i<pesi_2.size(); i++){
        if (pesi_2[i] == guardia) guardia = pesi_2[++i];
        else if (pesi_2[i] > result){
            result = result > guardia ? result : guardia;
            guardia = pesi_2[i];
        }
    }
    return result;
}

/*
ANALISI COMPLESSITÀ
La creazione della unordered map richide Theta(n), lo stesso richiede la ricerca del max elemento disaccoppiato, poi 2 cicli iterano fino ad n, risultando complessivamente in 4*Theta(n), da cui Theta(n). La complessità spaziale è dominata dall'unordered map, che ha n come ordine di grandezza, è quindi anch'essa lineare
*/

int main(){
    int n;
    cin>>n;
    vector<int> v1 (n);
    vector<int> v2 (n);
    for (int i=0; i<n; i++){
        cin>>v1[i];
    }
    for (int i=0; i<n; i++){
        cin>>v2[i];
    }
    cout<<endl<<PesoMinimo(v1, v2);
}
