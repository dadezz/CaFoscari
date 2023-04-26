/**
 * quando si restituisce un oggetto per value, da una funzione, prima del CPP11 veniva effettuata
 * una deep copy. 
 * Per poter essere spostato di scope doveva essere copiato. Ma che senso ha copiarlo se muore subito dopo?
 * ugualmente, in un assegnamento, va copiato tutto, ma che senso ha?
 * 
 * Col RVO viene evitata la prima cosa: il compilatore si rende conto che il chiamante e l'oggetto ritornato
 * sono la stessa cosa, quindi non copia, ma passa assegna la memoria dell'oggetto direttamente al chiamante.
 * 
 * In sta lezione quindi cerchiamo di capire come rubare le risorse anche nel secondo caso, cosa definita come
 * MOVE Semantics.
 * 
 * funziona assegnando la memoria di un oggetto temporaneo dentro all'oggetto finale. 
 * Si fa uno swap dei puntatori e poi si dealloca l'oggetto temporaneo.
 * 
 * La semantica deve aver senso solo per oggetti temporanei, non devono continuare a esistere nello scope principale
 * 
 * In particolare, è importante la differenziazione tra l-value e r-value.
 * 
 * Il compilatore quindi deve usare la move semantics solo sugli rvalue (tipo i valori di ritorno di una funzione)
*/

#include <iostream>
#include <vector>
using std::vector;
using std::endl;
using std::cout;
using std::cin;

//il doppio & mi permette di prendere la reference a un rvalue

float get_some(){return 3.14;}  // è un r-value: (float) 3.14

float && good_ref = get_some(); // obv, non è safe utilizzare good ref, perché get_some() non esiste più
                                //però questo almeno è il modo corretto di prendermi l'indirizzo di un rvalue.
                                //good ref è ora un l-value

/**
 * un r-value reference può esistere anche come argomento di una funzione
*/
vector<float> get_some_float_vec();

vector<float> v = get_some_float_vec();
void print_vec(vector<float> const & vec);
void print_vec(vector<float> const && vec);

int main1(){
    print_vec(v);                    // QUESTO CHIAMA LA PRIMA FUNZIONE (&)
    print_vec(get_some_float_vec()); // QUESTO CHIAMA LA SECONDA FUNZIONE (&&)
}

/**
 * ecco quindi che ho un modo di distinguere la chiamata tra r-val e l-val.
 * A seconda del tipo r/l che metto come parametro, posso costruire funzioni diverse
*/

/**
 * MOVE SEMANTICS / MOVE ASSIGNMENT : costruttore nuovo che prende in input un r.val reference.
 * rubiamo il puntatore all'oggetto temporaneo.
 * funziona in casi del genere:
 * 
 * my_class x;
 * x = get_object();
 * 
 * lo vediamo nel container listVal
*/