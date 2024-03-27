/**
Esercizio 1
Scrivere una funzione EFFICIENTE order che ordini in modo non crescente n numeri interi compresi nell'intervallo da 0 a n4 - 1 nel tempo O(n).
Il prototipo della procedura è:
void order(vector<int>& arr)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
#include <vector>
#include <cmath>
#include <iostream>

void counting_sort(std::vector<int>& arr, std::vector<int>& b, int cifra);
void order (std::vector<int>& arr){
    /**
     * devo usare algoritmo di ordinamento lineare. sfruttando la conoscenza del fatto che gli interi del vettore sono compresi
     * tra 0 e n^4-1. L'idea è usare il radix sort, con i numeri scritti in base n, su 4 cifre.
     * Il radix sort scorre su ogni cifra ogni elemento, applicando a quella cifra il counting sort.
     * Il counting sort è un algoritmo di ordinamento lineare, in quanto itera singolarmente 4 volte 
     * (4 è una costante moltiplicativa e in quanto tale non influisce sulla complessità asintotica) sugli N elementi del vettore, 
     * e su un vettore che, per come è costruito, ha anch'esso n elementi (infatti, il range in cui possono variare gli elementi,
     * è fatto in modo da essere esattamente N). 
     * Il vettore iniziale è quindi lungo N, il vettore delle occorrenze è lungo Theta(N), in particolare esattamente N. In tutto ci sono
     * 4 cicli for, quindi il counting sort ha complessità Theta(4N) -> Theta(N).
     * 
     * Il radix sort ha complessità anch'esso lineare, in quanto è stata scelta la base in modo da avere un numero di cifre costanti,
     * conosciute a priori. Nel caso specifico, di n^4-1, se si prende come base n si ottiene un nuemro di cifre massimo pari a 4.
     * Il radix sort non fa altro che chiamare il counting sort 4 volte. dal momento che 4 è una costante, otteniamo una complessità asintotica
     * lineare.
    */
    int n = arr.size();
    std::vector<int> b (n);
    for (int i = 0; i<4; i++){
        counting_sort(arr, b, i);
        arr = b;
    }
    // il vettore è ordinato in ordine crescente. per farlo al contrario, lo giro, usando b come appoggio.
    // il costo è O(n) in quanto va a scorrere due volte il vettore per tutta la lunghezza, senza quindi intaccare la comlpessità asintotica
    for(int i=0; i<n; i++){
        b[i] = arr[n-i-1];
    }
    for(int i=0; i<n; i++){
        arr[i] = b[i];
    }
}

void counting_sort(std::vector<int>& arr, std::vector<int>& b, int cifra){
    // n è arr.size(), k è n, in quanto ogni numero è espresso in base n
    int n = arr.size();
    int powern = std::pow(n, cifra);
    std::vector<int> c(n);
    for (int i=0; i<n; i++){
        c[i] = 0;
    }
    for (int j = 0; j<n; j++){
        int digit = (arr[j] / powern) % n;
        c[digit]++;
    }
    for (int i=1; i<n; i++){
        c[i] = c[i] + c[i-1];
    }
    for (int j = n-1; j>=0; j--){
        int digit = (arr[j] / powern) % n;
        b[c[digit]-1] = arr[j];
        c[digit]--;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Il tipo ValCol e' cosi' definito:

typedef struct{
    int value;
    char colour;
} ValCol; 
/*Esercizio 2

Sia A un vettore in cui ogni elemento contiene due campi: A[i].value contiene un numero intero ed A[i].color 
contiene un colore ('b' o 'n'). Gli elementi di A sono ordinati in ordine crescente rispetto al campo value.

a) Si consideri il problema di ordinare gli elementi di A rispetto al campo color secondo l’ordinamento b < n, 
facendo in modo che gli elementi dello stesso colore siano ordinati rispetto al campo value. 
Si scriva una procedura EFFICIENTE per risolvere il problema proposto. Si valuti e giustifichi la complessità.

Il prototipo della procedura è:*/

void ordinaPerColore(std::vector<ValCol>& arr);

/*b) Si consideri il problema di ordinare gli elementi di A rispetto al campo value, 
facendo in modo che gli elementi che hanno stesso value siano ordinati rispetto al campo colore (sempre con la convenzione b < n). 
Si scriva una procedura EFFICIENTE per risolvere il problema proposto. Si valuti e giustifichi la complessità.

Il prototipo della procedura è:*/

void ordinaPerValore(std::vector<ValCol>& arr);

void ordinaPerColore(std::vector<ValCol>& arr){
    /**
     * Per ipotesi, l'array è già ordinato rispetto al campo value, mi è sufficiente quindi raggruppare secondo i due campi colore,
    */
    std::vector<ValCol> b;
    std::vector<ValCol> n;

    for(int i=0; i<arr.size(); i++){
        auto x = arr.at(i);
        if (x.colour == 'n') n.push_back(x);
        else b.push_back(x);
    }

    int i=0;
    for(; i<b.size(); i++){
        arr[i] = b[i];
    }
    i = 0;
    for(; i<arr.size(); i++){
        arr[i+b.size()] = n[i];
    }
}
void ordinaPerValore(std::vector<ValCol>& arr){
    /**
     * per la stessa ipotesi di cui sopra, posso agire allo stesso modo:
     * il vettore arr di partenza è già ordinato rispetto al campo value, ciò significa che mi basta
     * splittare i due colori e dopo eseguire un merge. 
     * I vettori dei due colori sono già ordinati, in quanto parto da un vettore già ordinato. facendo il merge dopo
     * riesco a rimettere sempre in ordine per value, pescando però sia da un lato che dall'altro
    */
    std::vector<ValCol> b;
    std::vector<ValCol> n;

    // separo i due colori
    for(int i=0; i<arr.size(); i++){
        auto x = arr.at(i);
        if (x.colour == 'n') n.push_back(x);
        else b.push_back(x);
    }

    // eseguo il merge
    int i, j, w;
    i = j = w = 0;
    while(i<b.size() && j<n.size()){
        auto xb = b.at(i).value;
        auto xn = n.at(j).value;

        if (xb <= xn) 
            arr[w++] = b.at(i++);
        else
            arr[w++] = n.at(j++);
    }

    // finisco gli eventuali valori mancanti
    while(i<b.size())
        arr[w++] = b.at(i++);
    while (j<n.size())
        arr[w++] = n.at(j++);
}

/**
 * è immediato vedere che in entrambi i casi la complessità è lineare. Prima viene copiato una volta tutto l'array,
 * separandolo in due array separati (ma il cui numero complessivo di elementi è comunque n).
 * 
 * poi in un caso vengono semplicemente ricopiati nuovamente i due array nell'array originale, uno di seguito all'altro per un totale 
 * quindi di 2 cicli for da n iterazioni -> Theta(N);
 * nel secondo caso succede la stessa cosa, solo che al posto di copiarli di seguito, vengono copiati in altro ordine, per un totale 
 * in ogni caso di n iterazioni
 * 
 * la complessità è in entrambi i casi theta(n)
*/