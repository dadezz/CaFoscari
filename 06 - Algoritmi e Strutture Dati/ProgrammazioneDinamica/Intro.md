# Programmazione Dinamica

Si applica quando:
* un problema si riduce a un inseieme di sottoproblemi più piccoli
* diversamente dal divide-et-impera, i sottoproblemi sono sovrapposti (si ripetono).

Se i sottoproblemi si ripetono, un approccio DEI risulta inefficiente in quanto risolve tante volte lo stesso problema, spesso esponenzialmente inefficiente.
***IDEA***: risolvo il sottoproblema una sola volta, memorizzando la soluzione e ripescandola se il  sottoproblema si ripresenta.

In genere si utilizza in caso di problemi di ottimizzazione:
* molte soluzioni
* ogni soluzione ha un costo
* voglio costo massimo o minimo (UNA soluzione ottima)

Per sviluppare u algoritmo di programmazione dinamica, è utile eseguire questi 4 passi:

1. fornire una caratterizzazione della struttura di un asoluzione ottima (voglio capire come è fatta una soluzione ottima)
2. dare una definizione ricorsiva del valore di una soluzione ottima
3. Calcolare effettivamente le soluzioni (top-down o bottom-up indiffeerentemente)
4. individuare una soluzione ottima sulla base delle info calcolate al passo 3

***

## Taglio delle aste

Azienda produce aste d'acciaio e le vende a pezzi, e il prezzo dipende dalla lunghezza.
Data un'asta di lunghezza n e prezzi diversi per ogni lunghezza < n, calcolare come tagliare l'asta per ottimizzare il guadagno
Assumo che il costo del taglio sia costante (irrilevante).

* **input**: Lunghezza N e tabella di prezzi per lunghezza, $ P_i = \{1..n\} $.
* **output**: ricavo massimo

**esempio**: $ P_i  = \{(1:1), (2:5), (3:8), (4:9), (5:10), (6:17), (7:17)\}; N = 7. $
- tutti pezzi da 1: 7*1 = 7
- solo un pezzo da 7: 1 * 17 = 17
- un pezzo da 4 e uno da 3: 1 * 9 + 1 * 8 = 17
- due pezzi da 2 e uno da 3: 2 * 5 + 1 * 8 = 18

quest'ultima è UNA soluzione ottima, ma non l'unica. per esempio 6+1 è ugualmente ottima, e anche il commutativo 1+6, 2+3+2, 3+2+2...

In quanti modi possibili posso tagliare la mia asta?
A ogni posizione intera, posso decidere se tagliare o meno. Le possibili scelte sono $ 2^{n-1} $ . Posso ovviamente forcebrutare, ma l'analisi esplicita di tutti i problemi avrebbe costo esponenziale. -> $ \Theta(2^n) $
Con la programmazione dinamica riesco a passare a una complessità polinomiale.
Seguiamo quindi i passi indicati:
1. Caratterizzo il problema: Ricavo massimo $ r_n $ per un'asta di lunghezza n
2. definisco struttura ricorsiva:
   * $ r_0 = 0 $
   * $ r_n = MAX(p_n, r_1 + r_{n-1}, r_2 + r_{n-2},...) $

Vado a fare un taglio in qualche posizione i=1 .. n-1 e massimizzo il ricavo per i pezzi ottenuti. Quando, come in questo caso, la soluzione è ottenuta sfruttando le soluzioni ottime di sottoproblemi, si dice che vale la proprietà della sottostruttura ottima (molto importante, va ricercata sempre quando si fa programmazione dinamica).
Posso caratterizzare in modo più semplice tagliando un pezzo in modo definitivo e suddividere uteriorimente in modo ottimo la parte rimanente. Avrò di conseguenza un solo sottoproblema. La formulazione ricorsiva che posso utilizzare diventa:
   * $ r_0 = 0 $
   * $ r_n = MAX_{1 \leq i \leq n}(p_i, r_{n-i}) $

```cpp
   //input: p = vettore dei prezzi; n lunghezza asta da tagliare
   //output: ricavo massimo
   int cut_rod(int p, int n){
      if (n==0) {
         return 0;
      }
      else {
         q--;
         for (int i=0; i<n; i++){
            q = std::max(q, p[i]+cut_rod(p, n-i));
         }
         return q;
      }
   }
```
T(n) è  il numero di chiamate ricorsive che vien fatto da `cut` quando la chiamata viene fatta con il secondo parametro uguale a n.
* $ T(n)=1 \iff n=0 $
* $ T(n)=\sum_{i=1}^{n}T(n-i) = 1+ \sum_{j=0}^{n-1}T(j) $

si può dimostrare per induzione su n che $ T(n) = 2^n $. Infatti:
* caso base, $ n= 0: T(0) = 2^0 = 1 $, verificato
* passo induttivo , $ n>0 : T(n+1) = 1 + \sum_{j=0}^{n+1-1}T(j) = 1+ \sum_{j=0}^{n-1}T(j)+ T(n) = T(n) + T(n) = 2T(n). $ Per ipotesi induttiva: $ 2\cdot 2^n $. 

3. costruzione algoritmo: 
Guardando l'albero di ricorsione, si nota che lo stesso sottoproblema è risolto più volte e i problemi distinti sono pochi (n). se memorizziamo la soluzione dei sottoproblemi una volta calcolata, la possiamo riutilizzare se incontriamo nuovamente lo stesso sottoproblema.
SE: 
* i sottoproblemi distinti sono un numero polinomiale 
* ciascuno si risolve in tempo polinomiale

ALLORA:
memorizzando le soluzioni e evitando di ricalcolarle, si ottiene un algoritmo polinomiale.
Abbiamo quindi 2 possibilità:
1. top-down: salva in una tabella le soluzioni dei problemi già risolti
2. bottom-up: ordina i sottoproblemi a partire dal più piccolo e memorizza le soluzioni ottenute
### Top down (memoization) 
Il metodo ricalca lo stesso algoritmo di cui sopra, fa solo un controllo in più: verifica se è già stata calcolata la soluzione che cerchiamo.

```cpp

int memoized_cut_rod_aux(int p, int n, std::vector r){
   if (r[j] <0) {
      if (j==0)
         r[j] = 0;
      else {
         q--;
         for(int i=0; i<j; i++){
            q = std::MAX(q, p[i]+memoized_cut_rod_aux(p, j-i, r));
         }
         r[j] = q;
      }
   }  
   return r[j];
}

int memoized_cut_rod(int p, int n){
   std::vector r(n);
   for(int i=0; i<n; i++){
      r[i] = -1; //inizializzo il vettore
   }
   return memoized_cut_rod_aux(p,n,r);
}

```
Costo: Una chiamata ricorsiva di `memoized_cut_rod_aux` per risolvere un problema precedentemente risolto termina immediatamente. Si giunge al rampo `else`  una sola volta per ogni sottoproblema j=1..n
Per risolvere un sottoproblema di dimensione j, quante sono le chiamate ricorsive che facciamo? il ciclo for effettua j iterazioni. Quindi il numero totale di iterazioni del ciclo for per tutte le chiamate ricorsive è: $ \sum_{j=1}^n j = n(n+1)/2 = \Theta(n^2) $.

Il tempo di exec di `memoized_cut_rod` è $ \Theta(n) + \Theta(n^2) = \Theta(n^2) $. Siamo passati da una funzione esponenziale a una funzione quadratica, al costo di avere un array in più in memoria.

### Bottom-up

```cpp
int bottom_up_cut_rod (int p, int n){
   std::vector r(n);
   r[0] = 0;
   for (int j=0; j<n; j++){
      q=-1;
      for(int i=0; i<j; i++){
         q = std::MAX(q, p[i]+r[j-i]);
      }
      r[j] = q;
   }
   return r[n];
}
```

Costo: risulta essere semplice da calcolare: $ \sum_{j=1}^n \Theta(1) \cdot j = \Theta(1) \cdot n(n+1)/2 = \Theta(n^2) $
Dal punto di vista asintotico, i due algoritmi hanno lo stesso costo. In questo caso specifico, il bottom-up risulta più efficiente perché evita chiamate ricorsiv (-> costanti moltiplicative minori). Non è però sempre vero, perché il top-down non sempre calcola tutti i sottoproblemi, mentre il bottom-up lo fa sempre

4. Trovare la soluzione

Il valore trovato adesso dà il ricavo massimo, ma non dà la soluzione su come effettuare i tagli. Per farlo mi serve un vettore in più oltre a quello del ricavo: Memorizza la posizione del primo taglio che mi porta alla soluzione ottima. In sto caso modifichiamo l'algoritmo bottom-up, perché più breve da scrvere, ma vale per entrambi.

```cpp
std::pair<vector<int>, vector<int>> ext_bottom_up_cut_rod(int p, int n){
   std::vector<int> r(n);
   std::vector<int> s(n);
   r[0] = 0;
   for (int j=0; j<n; j++){
      q=-1;
      for(int i=0; i<j; i++){
         if (q<p[i] + r[j-i]){
            q=p[i]+r[j-i];
            s[j] = i;
         }
      }
      r[j] = q;
   }
   return pair(r,s);
}

void print_cut_rod_solution(int p, int n){
   std::pair<vector<int>, vector<int>> rs = ext_bottom_up_cut_rod(p, n);
   while(n>0){
      print(s[n]);
      n=n-s[n];
   }
}
```
costo = n^2 + ciclo(n). -> theta(n^2).






























