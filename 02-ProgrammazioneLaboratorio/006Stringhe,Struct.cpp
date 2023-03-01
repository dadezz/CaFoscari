/**
 * 01 marzo 2023
 * 
 * Stringhe, alcuni esempi
*/
#include <iostream>
#include <string>
#include <vector>
//stringa palindroma
//tutte le funzioni che restituiscono un booleano vengono chiamate funzioni di decisioni

bool pal(const std::string &s){
    bool risp = true;
    
    /*
    for(int i = 0; i<s.length()/2; i++){
        if (s.at(i) != s.at(s.length()-1-i)) 
            risp = false;
    }
    Giusta, ma non riflette l'uso preferenziale dei cicli
    */
    
    int i = 0;
    while(i<s.length()/2 && risp){
        if (s.at(i) != s.at(s.length()-1-i)) 
            risp = false;
        i++;
    }
    return risp;
}

//dato un vettore di stringhe, ritornare la concatenazione 
std::string concatenazione(const std::vector<std::string> & vs){
    std::string res;    //la std library non necessita di inizializzazione esplicita, perché
                        //quando si dichiara viene automaticamente inzializzata a vuoto.
    for(const auto & each:vs){
        res = res+each;
    }
    return res; //all'uscita dallo scope, prima di essere eliminato, viene copiato sul chiamante.

    /**
     * come evitare la copia finale? non serve porsi questi problemi, si vedrà più avanti, esiste comunque
     * la semantica move che al posto di copiare, muove l'oggetto verso il destinatario, quindi si arrangia
     * ad efficientare C++ stesso.
     * Facendo un confronto con C, l'efficienza è la stessa, non c'è un reale beneficio nell'usare le str
     * alla C rispetto di quelle alla C++.
    */
}

/**
 * STRUCT IN CPP :
 * posso avere anche delle funzioni come campi
*/

struct coppia{
    int x;
    int y;
    int sum(){
        return x+y;
    };
};

// esempio utilizzo:

int main(){
    struct coppia c;
    c.x = 4;
    c.y = 6;
    coppia c1;
    c1.x = 23;
    c1.y = 27;
    std::cout<<c.sum()<<std::endl;      //10
    std::cout<<c1.sum()<<std::endl;     //50
}

/**
 * si noti la mancanza di parametri formali nella firma della funzione.
 * Dal punto di vista di sum, x e y sono variabili che va a prendere da uno scope esterno, la struct,
 * come se fossero variabili globali: in una funzione non serve metterle nella firma.
 * 
 * l'oggetto copia contiene già tutto, la sum sa che può accedere allo stato della struct su cui è definita.
 * ovviamente nulla vieta che possa ricevere ulteriori parametri esterni.
 * 
 * è l'idea base della programmazione ad oggetti: definisco metodi che lavorano sul proprio stato, non
 * su parametri esterni.
 * 
 * PROGRAMMAZIONE AD OGGETTI
 * lol esempio stupido.
 * ho uno studente e la necessità di lavare i capelli.
 * nella programmazione procedurale, ho la mia funzione barbiere, che chiamo sul mio studente.
 * nella programmazione ad oggetti, ho lo studente e gli dico di lavarsi i capelli.
 * non so come venga fatto, delego il metodo all'oggetto stesso, so solo che lo chiamo e mi dà il risultato.
 * 
 * nella programmazione procedurale, devo sapere com'è strutturata una stringa a basso livello (\0 finale ad esempio)
 * per sapere come calcolarne la lunghezza, mentre c++ mi permette di avere un oggetto di tipo stringa, fatto da chiuque,
 * che  mi dà la possibilità di usarle e chiamare i metodi su loro stesse, senza passare lo stato della struct su cui
 * devono lavorare né dover sapere le caratteristiche specifiche della struttura dell'oggetto che si manipola.
 * 
 * Questo sistema di programmazione ad oggetti si chiama incapsulamento, la programmazione ad oggetti permette di 
 * astrarre un problema, senza dover maneggiare puntatori, memoria etc, tutto perché questi saranno incapsulati nei
 * metodi delle struct. 
 * I vector (abbiamo fatto la libreria in C per esempio), fanno larghissimo uso dei puntatori, ma tutto sotto il tappeto,
 * se li gestiscono i metodi. a me interessa soltanto l'effetto del metodo, ad alto livello. quando faccio la struct coi metodi,
 * una volta fatta ho la possibilità di scrivermi codice pulito e ad alto livello senza curarmi dei particolarsmi del linguaggio/sistema
 * 
 * l'incapsulamento:
 * una porzione della struct è visibile dall'esterno, un'altra no. in "coppia", ad esempio, posso definire x e y come né leggibili
 * né scrivibili, sono private nelle struct, in quel caso l'unico modo che ho di interagire con l'oggetto è tramite i metodi
 * 
 * 
 * Prox lezione vedremo le classi e l'incapsulamento. Sostanzialmente, classi e struct sono la stesssa cosa, cambia che se non c'è
 * nulla di specificato, nelle struct è tutto public, nelle classi è tutto private
*/