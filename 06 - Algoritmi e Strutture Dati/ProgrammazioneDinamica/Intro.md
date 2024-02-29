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

3. 











































