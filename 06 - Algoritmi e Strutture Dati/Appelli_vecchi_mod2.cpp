/*
Scrivere un algoritmo che date due sequenze X e Y, rispettivamente di m e n caratteri, restituisca la lunghezza di
una sottosequenza di lunghezza massima comune a X e Y (LCS). Più precisamente:
a) dare una caratterizzazione ricorsiva della lunghezza di una LCS, definendo lung[i, j] come la lunghezza
di una LCS delle sequenze Xi e Yj con 0<=i <= m e 0 <= j <= n. Si ricordi che Xi è il prefisso di X di
lunghezza i e Yj è il prefisso di Y di lunghezza j;
b) tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo top-down che
determina la lunghezza di una LCS;
c) valutare e giustificare la complessità dell’algoritmo;
d) ci sono input per il quale il metodo top-down risulta preferibile rispetto al metodo bottom-up?
Motivare adeguatamente la risposta
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int lcs_aux (string x, string y, vector<int>& matrix, int i, int j){
    
    //caso base: no lettere disponibili
    if (i<0 || j<0) return 0;
    
    // effettiva programmazione dinamica
    if (matrix[i*y.length() + j] != -1) return matrix[i*y.length() + j];

    if (x[i] == y[j]) 
        return (matrix[i*y.length() + j] = lcs_aux(x, y, matrix, i-1, j-1) + 1); // assegnamento è espressione -> ritorna il valore, oltre a metterlo giusto
    else 
        return (matrix[i*y.length() + j] = max(lcs_aux(x, y, matrix, i-1, j), lcs_aux(x, y, matrix, i, j-1)));
}
int lcs (string x, string y){
    
    // caso base: stringhe vuote
    if (x.length() == 0 || y.length() == 0) return 0;

    // inizializzazione
    vector<int> matrix(x.length() * y.length());
    for(int i=0; i<x.length(); i++){
        for (int j=0; j<=y.length(); j++){
            matrix[i*y.length() + j] = -1;
        }
    }

    // algoritmo
    return lcs_aux(x, y, matrix, x.length()-1, y.length()-1);
}

int main(){
    string a("abbac");
    string b("abbbc");

    cout<<lcs(a, b)<<endl;
    return 0;
}

/*
la complessità dell'algoritmo è Theta(m*n), in quanto nella funzione principale ci sono due cicli annidati rispettivamente fino a n e fino a m;
La funzione ausiliaria potrebbe sembrare esponenziale, ma la ricorsione viene effettuata solo nel caso la corrispondente cella della matrice non sia
stata già visistata in precedenza (infatti, se viene visitata il valore originale viene cambiato, e non c'è più possibilità che venga rivisitata
e il valore cambiato). di conseguenza, l'algoritmo esegue al più m*n visite (ogni cella della matrice), di conseguenza la complessità totale è Theta(m*n)

rispetto a un algoritmo bottom-up, ci sono casi in cui questo è più efficiente. Infatti, il bottom-up controlla tutte le celle della matrice, sempre;
invece questo è limitato dagli if. Per esempio, risulta più efficiente se le due stringhe sono uguali
*/

/*
Il diametro di un grafo pesato è definito come la massima distanza tra due vertici del grafo, dove, come è noto,
per “distanza tra due vertici” u e v si intende la lunghezza del cammino minimo tra u e v. Si sviluppi un algoritmo
efficiente (ovvero polinomiale) che accetti in ingresso un grafo G e ne calcoli il suo diametro (si assuma che G
non contenga cicli negativi). Si dimostri la correttezza dell’algoritmo proposto e si determini la sua complessità
computazionale.
Nota. Nel caso in cui si faccia uso di algoritmi noti si dimostri anche la loro correttezza
*/

vector<vector<int>> floyd_warshall(vector<vector<int>>& matrix, int n /*rows == cols*/){
    vector<vector<vector<int>>> D(n, vector<vector<int>>(n, vector<int>(n)));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            D[0][i][j] = matrix[i][j];
        }
    }

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D[k][i][j] = min(D[k-1][i][j], D[k-1][i][k] + D[k-1][k][j]);
            }
        }
    }

    return D[n-1]; // Return the last slice of D
}

int diametro(vector<vector<int>>& matrix, int n /*rows == cols*/){
    int infinity = numeric_limits<int>::max();
    vector<vector<int>> result = floyd_warshall(matrix, n);
    int max = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            if (result[i][j] != infinity && result[i][j] > max) max = result[i][j];
    return max;
}

/*Per dimostrare formalmente la correttezza dell'algoritmo di Floyd-Warshall, possiamo procedere con una dimostrazione per induzione. 
Dimostreremo che dopo ogni iterazione dell'algoritmo, la matrice delle distanze più brevi aggiornata è corretta.
**Base dell'induzione:** All'inizio, la matrice delle distanze più brevi conterrà le distanze dirette tra i vertici, 
ovvero la matrice dei pesi del grafo. Questo è corretto poiché non ci sono distanze più brevi di quelle dirette.
**Passo induttivo:** Supponiamo che dopo l'iterazione k, la matrice delle distanze più brevi, chiamiamola D_k, sia corretta. 
Dimostriamo che dopo l'iterazione k+1, la matrice D_{k+1} è corretta.
Durante l'iterazione k+1, ogni elemento D_{k+1}[i][j] viene aggiornato con il minimo tra il valore precedente D_k[i][j] e 
la somma delle distanze più brevi tra i vertici i e k+1, e tra k+1 e j, ovvero D_k[i][k+1] + D_k[k+1][j]. Quindi:
D_{k+1}[i][j] = min(D_k[i][j], D_k[i][k+1] + D_k[k+1][j])
Poiché abbiamo già supposto che D_k è corretta, possiamo affermare che D_k[i][j] contiene la distanza più breve tra i e j 
utilizzando solo i vertici da 1 a k. Inoltre, se un percorso più breve passasse attraverso il vertice k+1, allora 
D_k[i][k+1] + D_k[k+1][j] sarebbe la lunghezza di quel percorso, poiché D_k[i][k+1] sarebbe la distanza più breve 
da i a k+1 e D_k[k+1][j] sarebbe la distanza più breve da k+1 a j. Pertanto, prendendo il minimo tra D_k[i][j] e D_k[i][k+1] + D_k[k+1][j], 
otteniamo la lunghezza del percorso più breve tra i e j che può includere il vertice k+1.
Quindi, dopo l'iterazione k+1, la matrice D_{k+1} contiene le distanze più brevi tra i vertici usando solo i vertici da 1 a k+1. 
Poiché k è stato scelto arbitrariamente, possiamo estendere questa dimostrazione a tutte le iterazioni fino a raggiungere la fine dell'algoritmo.
Pertanto, la matrice delle distanze più brevi prodotta dall'algoritmo di Floyd-Warshall è corretta per ogni coppia di vertici nel grafo, 
dimostrando così la correttezza dell'algoritmo.
*/

/*Si scriva l’algoritmo di Dijkstra, si dimostri la sua correttezza, si fornisca la sua complessità computazionale*/

/*
si inizializza il grafo associando a ogni vertice due campi: puntatore al predecessore e stima della distanza.
si inseriscono i vertici di G in una coda di priorità con chiave d. si crea il taglio s.
finché Q non si svuota, si estrae un vertice e si fa la relax sui vertici a esso adiacenti

PSEUDOCODICE:
dijkstra(G, w, s){
    init(G)
    S <- insieme vuoto;
    Q <- V[G]
    while Q non vuoto {
        u <- extract_min(Q)
        S <- S U u
        for each v in adj[u]{
            relax (u,v, w(u,v))
        }
    }
}

Le prime fasi dell'algoritmo hanno tutte complessità lineare sul numero di vertici. 
la sua complessità computazioneale totale è dominata dal while, che itera su ogni vertice. all'interno del while c'è la sistemazione della
coda di priorità, che ha complessità logaritmica. il ciclo for innestato itera su ogni vertice adiacente al veritice ispezionato. 
ripetuto per ogni vertice del grafo (ciclo while esterno) questo porta a fare tante relax quanti gli archi del grafo, quindi |E|.
di conseguenza, la complessità è m + n*logn, dove indico con m il numero di archi e n il numero dei vertici

per dimostrare la correttezza, si può procedere per assurdo. dobbiamo dimostrare che d[u] = delta [s,u]. Supponiamo che u sia il primo vertice
per cui questa proprieà non venga rispettata
u non può essere la sorgente perché già in inizializzazione d=delta=0. per lo stesso motivo u deve essere raggiungibile da s. 
Prendiamo allora un taglio del grafo: S e Q; s in S e u in Q. siano ora x e y due vertici appartenenti al cammino minimo p tra s e u. 
in particolare, x subito prima del taglio e y subito dopo. x, essendo nel taglio della sorgente e dei vertici già visitati ha d=delta, in quanto per
ipotesi u è il primo vertice per cui questo non accade, e x è stato estratto prima di u. y è collegato ad x da un arco leggero che attraversa il taglio,
quindi per il teorema della convergenza anche per y vale che d=delta. d[u]<=d[y] per costruzione della coda di priorità, e allo stesso tempo 
delta(s, y)<=delta(s,u), in quanto y viene prima di u nel cammino p.
mettendo insieme le informazioni otteniamo:
d[y] = delta(s,y) <= delta(s,u) <= d[u] <=d[y]. da cui ne deriva che delta(s,u) = d[u], che va a contraddire l'ipotesi iniziale e a dimostrare quindi 
la correttezza dell'algoritmo
*/