/**
Esercizio 1
Scrivere una funzione EFFICIENTE order che ordini in modo non crescente n numeri interi compresi nell'intervallo da 0 a n4 - 1 nel tempo O(n).
Il prototipo della procedura è:
void order(vector<int>& arr)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
#include <vector>
void counting_sort(std::vector<int>& arr, std::vector<int>& b, int cifra);
void order (std::vector<int>& arr){
    /**
     * devo usare algoritmo di ordinamento lineare. sfruttando la conoscenza del fatto che gli interi del vettore sono compresi
     * tra 0 e n^4-1. L'idea è usare il radix sort, con i numeri scritti in base n, su 4 cifre.
     *      Input: A[1..n] dove a[i] è un intero compreso nell'intervallo.   
     *      Output: vect ordinato.
     * Il radix sort scorre ogni elemento su ogni cifra ogni elemento, applicando a quella cifra il counting sort.
     * 
     * questo il counting sort in pseudocode:
     * Array countingsort(Array a, Array b, int n, int k){
            Array c(k);
            for (int i=0; i<k; i++){
                c[i] = 0;
            }
            for (int j = 0; i<n; i++){
                c[a[j]]++;
            }
            sto contando quante volte il numero compare in a.
            ora banalmente li butto tutti nel vector e fine
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
     *
    */
    int n = arr.size();
    std::vector<int> b (n);
    for (int i = 0; i<4; i++){
        counting_sort(arr, b, i);
        arr = b;
    }
    // il vettore è ordinato in ordine crescente. per farlo al contrario, lo giro, usando b come appoggio.
    // il costo è O(n) in quanto va a scorrere due volte il vettore per tutta la lunghezza, senza quindi intaccare la comlpessità asintotica
    /*for(int i=0; i<n; i++){
        b[i] = arr[n-i-1];
    }
    for(int i=0; i<n; i++){
        arr[i] = b[i];
    }*/
}

void counting_sort(std::vector<int>& arr, std::vector<int>& b, int cifra){
    // n è arr.size(), k è n, in quanto ogni numero è espresso in base n
    int n = arr.size();
    int powern = 1;
    for (int i = 0; i<cifra; i++){
        powern *= n;
    }
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
    for (int j = n-1; j>0; j--){
        int digit = (arr[j] / powern) % n;
        b[c[digit]] = arr[j];
        c[digit]--;
    }
}


#include <iostream>



// Testing main function
int main() {
    // Test input data
    std::vector<int> test_input = {13, 25, 7, 1, 3, 19, 11, 9};

    // Display original vector
    std::cout << "Original vector: ";
    for (int num : test_input) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Sort the vector
    order(test_input);

    // Display sorted vector
    std::cout << "Sorted vector: ";
    for (int num : test_input) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
