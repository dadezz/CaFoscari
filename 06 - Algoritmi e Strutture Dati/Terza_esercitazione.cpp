/**
Esercizio 1
Scrivere una funzione EFFICIENTE order che ordini in modo non crescente n numeri interi compresi nell'intervallo da 0 a n4 - 1 nel tempo O(n).
Il prototipo della procedura è:
void order(vector<int>& arr)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
#include <vector>

void order (std::vector<int>& arr){
    /**
     * devo usare algoritmo di ordinamento lineare. sfruttando la conoscenza del fatto che gli interi del vettore sono compresi
     * tra 0 e n^4-1
     * l'idea è usare il counting sort
     *      Input: A[1..n] dove a[i] è un intero compreso nell'intervallo.   
     *      Output: vect ordinato.

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
    */

}