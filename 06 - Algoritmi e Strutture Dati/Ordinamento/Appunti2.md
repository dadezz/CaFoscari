#  Complessità ordinamento
Quanto veloce si può ordinare? 
La complessità migliore finora trovata è $ \Theta(nlogn) $, usando solo confronti.
Vedremo che infatti è il limite inferiore.
## Dimostrazione $ \Omega(nlogn) $
Assumiamo che gli elementi siano tutti differenti. Utilizziamo per la dimostrazione un
### albero di decisione
è una struttura dati astrazione di un algor di confronto. È utile a livello teorico, non pratico. 
Esempio: albero di dec che ordina 3 elementi a1, a2, a3 usando insertion sort. Gli elementi sono costituiti da copppie di indici
```
<1, 2> :
    <= <2, 3> :
        <= <1, 2, 3>
        > <1:3> :
            <= <1, 3, 2>
            > <3, 1, 2>
    > <1, 3> : 
        <= <2, 1, 3>
        > <2, 3> :
            > <3, 2, 1>
            <= <2, 3, 1>
```
mi sposto nei vari rami a seconda di cosa sto facendo.
Per un input di dimensione n <a1 ... an>, ogni nodo interno rappresenta un confronto. è etichettato con gli indici i,j (variano da 1 a n, in quanto elementi del vettore di partenza). Vogliamo confrontare l'elemento ai con aj. vado sul sottoalbero sinistro se il confronto è ai<=aj, nel destro altrimenti. 
Ogni foglia dà una permutazione tale che il risultato è ordinato.

### ..

Dato un qualsiasi algoritmo di ordinamento basato sul confronto, posso costruire un albero di decisione che mi rappresenta il modo in cui opera l'algo di ordinamento. 
Posso costruire un albero di decisione per ogni n. L'alebro modella tutte le possibili tracce di esecuzione; il t exec (#confronti) è la lunghezza di un cammino nell'albero. Il Texec nel caso peggiore è il cammino più lungo, ovvero l'altezza dell'albero.
Limite inferiore? >= n! (posso avere percorsi che mi riportano alla stessa permutazione)
#### lemma
un  albero binario di altezza h ha al più $ 2^h $ foglie. si dimostra per induzione su h: se h=0, la radice è foglia, $ 2^0 = 1 $. Passo induttivo: Assumiamo vera la proprietà per alberi di altezza k < h, cioè #foglie <= 2^k. Sia r la radice dell'albero T di altezza h. Se r ha un solo figlio. f sono le foglie di t, che sono le foglie di t1. t1 ha altezza h-1. Per ipotesi induttiva, $ f = f_1 \leq  2^{h-1} \leq 2^h $. Se l'albero ha 2 figli, $ f = f_1 + f_2 \leq  2 \times 2^{h-1} = 2^h $

Da cui, le foglie possono essere al più 2^h, in caso di albero completo.

### Teorema
Qualsiasi algoritmo di ordinamento per confronti richiede $ \Omega(nlogn) $ confronti nel caso peggiore. Bisogna determinare l'altezza di un albero di decisione dove ogni permutazione appare come foglia. Si consideri un albero di decisione di altezza h con l foglie, che corrisponde a un ordinamento per confronti di n elementi. $ n! \leq f  \leq  2^h $ Ho trovato una maggiorazione di h: $ h >= \log_2{n!}$. Utilizzo l'approssimazione di Stirling:
$$ n! = \sqrt{2 \pi n}  (\frac{n}{2})^h(1+ \Theta(\frac{1}{n})) $$.
 Per n suff grande, considero il termine più grand, e risulta
$$ h \geq \log_2{n!} \geq n(logn -log2) \geq nlogn $$.

#### Corollario 
Heapsort e mergesort sono alg di ord ottimali, in quanto i limiti superiori sui tempi di exec corrispondono al limite inferiore $ \Omega(nlogn)$

#### Corollario
Un albero binario di ricera non può esssere costruito in tempo minore di nlogn, in quanto se trovassi un modo di farlo, avrei un mo2/3*-
++989
+-63*/52ì?_.oi,uu´→·0-'àSe poniamo ipotesi strette sull'input, e usando algoritmi alternativi, si può scendere sotto $ nlogn $. 
### Counting sort
Assunzione (molto forte): i numeri da ordinare sono interi in un intervallo limitato (0..k) per qualche k intero fissato.
Input: A[1..n] dove a[i] è un intero compreso nell'intervallo. n e  k sono parametri.
Output: vect orinato.
Serve memoria ausiliaria: C[0..k], vettore delle occorrenze.
```cpp
Array countingsort(Array a, Array c, int n, int k){
    Array c(k);
    for (int i=0; i<k; i++){
        c[i] = 0;
    }
    for (int j = 0; i<n; i++){
        c[a[j]]++;
    }
    /*sto contando quante volte il numero compare in a.
    ora banalmente li butto tutti nel vector e fine */
    for (int i=0; i<k; i++){
        c[i] = c[i] + c[i-1]; 
        // per ciascun valore i, quanti sono i valori minori uguali di i?
    }
    // posiziono l'elemento nell'ordine corretto. Se so che ci sono 5 elementi
    // minori o uguali di i, dove lo butto? in posizione 5.
    // decremento il numero di occorrenze così se ci sono ue elementi uguali, 
    // al posto di sovrapporre lo metto nella posizione immediatamente prima.
    for (int j = n; j>0; j--){
        b[c[a[j]]] = a[j];
        c[aj]--;
    }
}
```

L'algoritmo è stabile. $ T_{exec} = \Theta(k) + \Theta(n) + \Theta(k) + \Theta(n) = \Theta(k+n) $ Risulta quindi molto utile con k limitato superiormente da n