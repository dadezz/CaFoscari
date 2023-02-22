#include <vector>
#include <iostream>
/**
 * 22 febbraio 2023
*/

/////////////////////////////////
//          PATTERN ACCUMULO
///////////////////////////////// 
void leggi(std::vector<int> & v);


void somma_elementi_vettori(std::vector<int> & v){
    leggi(v);
    int sum = 0;
    for (int i=0; i<v.size(); i++){
        /**
         * qual è l'invariante?
         * somma. Infatti, in ogni istante del codice, contiene la somma degli elementi tra 0 e i-1.
        */
        sum += v.at(i);
    }
    std::cout << sum << std::endl;
}

/**
 * il codice sopra è riscrivibile in altro modo. con un nuovo ciclo: for-each.
 * Ad ogni iterazione, viene copiato il valore contenuto nella posizione considerata.
 * Di conseguenza, non posso usarlo per scrivere ma solo per leggere.
 * Di conseguenza, sempre, non posso modificare la dimensione dell'array (pop o push back)
 * vedremo piu avanti il motivo, c'entrano gli iteratori. Funzionano sotto il tappeto con i puntatori,
 * di conseguenza cambiando l'oggetto c'è il rischio di segmentation fault, ma vedremo più avanti.
 * 
 * Mi serve se so che devo scorrerli tutti e non mi serve l'indice ma l'elemento contenuto.
 * 
 * Può essere usabile solo su container / oggetti iterabili
*/

void somma_elementi_vettori_foreach(std::vector<int> & v){
    leggi(v);
    int sum = 0;
    for (auto e:v){  // al posto di int posso usare auto: c++ controlla staticamente il tipo a destra e inizializza di conseguenza.
        /**
         * scorro il ciclo per elemento e non per indice.
         * il vantaggio del for each lo vediamo con la funzione leggi. 
         * Sicuramente comunque il codice è più leggibile
        */
        sum += e;
    }
    std::cout << sum << std::endl;
}

void leggi(std::vector<int> & v){ //DOVREI SCRIVERLA SOPRA
    int ne;
    std::cin>>ne;   //lunghezza
    v.resize(ne);
    for(int i = 0; i<ne; i++){
        std::cin >> v.at(i);
    }
}

void leggi_foreach(std::vector<int> & v){ //DOVREI SCRIVERLA SOPRA
    int ne;
    std::cin>>ne;   //lunghezza
    v.resize(ne);
    for(auto e:v){
        std::cin >> e; // così è inutile perché scrivo nella copia. uso una reference piuttosto
    }
    for(auto & e:v){
        std::cin >> e; // e non è più una copia dell'elemento, ma è l'elemento giusto.
    }
    /**
     * ecco la risposta alla domanda sopra. for-each è comodo se non si crea la copia
    */
}

std::vector<int> copia_vettore(std::vector<int> v){
    /**
     * a differenza del C, il C++ è molto più easy.
     * non serve fare copia elemento per elemnto, basta un
    */
    std::vector<int> nuovo = v;
    //anche auto nuovo = v;
    return nuovo;
}
///////////////////////////////////////
//          PATTERN CONTATORE
///////////////////////////////////////
void quantità_pari(std::vector<int> & v){
    leggi(v);
    int pari = 0;
    for (auto e:v){
        if (e%2 == 0){
            pari++;
        }
    }
    std::cout<<pari<<std::endl;
}
///////////////////////////////////////
//              MATRICE
///////////////////////////////////////
void crea_matrice(){
    std::vector<std::vector<int>> matrice;
    int nr, nc;
    std::cin >> nr >> nc;   //in esecuzione, scrivere numeri separati da spazio
    matrice.resize(nr);
    for (auto & e:matrice){
        e.resize(nc);
    }
}