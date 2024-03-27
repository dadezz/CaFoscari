#include "insieme.hpp"
#include <vector>

constexpr int hashsize = 8;
constexpr int hashaux = 5;

using namespace std;

struct Elem{
    int info;
};
typedef Elem *PElem;

struct Insieme::Impl{
    vector<PElem> content;
    int numelementi;
    PElem DEL;
};

int funHash(int val, int i){
    return (val%hashsize + i*(1+ 2 * (val%hashaux)))%hashsize;
}

/*post: costruisce un insieme vuoto */
Insieme::Insieme(){
}

/*post: costruisce un insieme contenente gli elementi di set (anche gli elementi devono essere copiati) */
Insieme::Insieme(const Insieme& set) {
}

/*post: rimuove l'insieme */
Insieme::~Insieme(){
}

/*post: inserisce il valore val nell'insieme se non è presente*/
void Insieme::inserisci(int val){
}

/*post: rimuove l’elemento val dall'insieme */
void Insieme::cancella(int val){
}

/*post: restituisce il numero di elementi nell'insieme */
int Insieme::numElementi() const {
}


/*post: restiusice true se l'elemento e' presente nell'insieme, altrimenti false */
bool Insieme::contiene(int val) const {
}

/*post: restituisce un nuovo insieme che contiene gli elementi che appartengono ad almeno uno dei due insiemi*/
Insieme Insieme::unione(const Insieme& I_2) const {
}

/*post: restituisce un nuovo insieme che contiene gli elementi in comune tra se stesso e I_2*/
Insieme Insieme::intersezione(const Insieme& I_2) const {
}

/*post: restituisce un nuovo insieme  che contiene gli elementi nell'insieme che non sono presenti in I_2*/
Insieme Insieme::differenza(const Insieme& I_2) const {
}

/*post: stampa il contenuto dell'insieme */
void Insieme::stampa() const {
}
