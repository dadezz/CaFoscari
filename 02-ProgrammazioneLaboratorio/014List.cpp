//continuazione 013
#include <iostream>
#include <vector>

class list_int{
    public:
        list_int();
        list_int(const list_int& s);
        ~list_int();
        void append(int e);
        void prepend(int e);
        bool is_empty() const;
        int& head(); // qui posso scrivere e leggere l'elemento di testa
        const int& head() const; // qui posso solo leggere l'elemento di testa
        void print();
        int list_int::size() const;
    private:
        //mettendo la cella dentro la parte privata,il chiamante non può nemmeno accedere alla definizione della lista
        struct cell{
            int info;
            cell* next;
        };
        typedef cell* pcella;
        pcella h;
        void append_ric(pcella & testa, int e);   
        void print_ric(pcella testa);   
};
list_int::list_int(){
    h = nullptr;
}
list_int::list_int(const list_int& s){
    cell* pc = s.h;
    while ( pc != nullptr){
        append(pc->info);
        pc = pc->next;
    }
}
list_int::~list_int(){
    cell* pc = h;
    while ( pc != nullptr){
        h = h ->next;
        delete pc; 
        pc = h;
    }
}

void list_int::prepend(int e){ // mettere l'oggetto in testa
     cell* x = new cell; // la prepend funziona anche con la lista vuota
      x->info = e;
      x->next = h;
      h = x; // h punta dove punta nuov
}

void list_int::print_ric(pcella testa){
    if (testa){
        std::cout<<testa->info<<" ";
        print_ric(testa->next);
    }
}
void list_int::print(){
    list_int::print_ric(h);
}

void list_int::append(int e){
    //fare append e prepend sulla lista vuota,
    //potrei fare ricorsione fino a lista vuota e poi chiamare prepend.
    //non ha senso però modificare h, perché perdo l'informazione della testa della lista. 
    //posso risolvere con un metodo privato, vedi riga 23
    append_ric(h, e);
}

void list_int::append_ric(pcella & testa, int e){
    if (testa == nullptr){
        testa = new cell;
        testa -> info = e;
        testa -> next = nullptr;
    }
    else append_ric(testa -> next, e);
}

bool list_int::is_empty() const {
    return h==nullptr;
}

int& list_int::head(){
    return h->info;
}

const int& list_int::head() const {
    return h->info;
}

int list_int::size() const{
    int res=0;
    pcella p = h;
    while(p){
        res++;
        p = p->next;
    }
    return res;
}


//////////////////////////////////////////////////////////////////////
// prendo la stessa parte pubblica ma cambio la privata.
// come in python, quello che faccio con le liste è implementato con i vector
/////////////////////////////////////////////////////////////////////

/**
 * la scelta è discutibile... serve di più l'accesso diretto o la modificabilità delle liste?
 * c++ la risolve meglio. esiste sia vector che list. se fai tanti prepend/eliminazione elementi conviene usare le 
 * liste, altrimenti i vector, sta al programmatore decidere cosa conviene 
*/

class list_int_diversa{
    public:
        list_int_diversa();
        list_int_diversa(const list_int_diversa& s);
        ~list_int_diversa();
        void append(int e);
        void prepend(int e);
        bool is_empty() const;
        int& head(); // qui posso scrivere e leggere l'elemento di testa
        const int& head() const; // qui posso solo leggere l'elemento di testa
        void print();
        int list_int_diversa::size() const;
    private: 
        std::vector<int> v;
};

list_int_diversa::list_int_diversa(){}
list_int_diversa::list_int_diversa(const list_int_diversa& e){
    v = e.v;
}
void list_int_diversa::prepend(int e){
    v.resize(v.size()+1);
    for(int i=v.size()-1; i>0; i--){
        v.at(i) = v.at(i-1);
    }
}
list_int_diversa::~list_int_diversa(){
} // non ho fatto new, quelle del vector si arrangia il vector

/**la cosa scomodissima del modificare le parti private è che cambia anche
 * l'header.
 * 
 * è vero che non bisogna cambiare il sorgente del main, ma bisogna ricompilare.
 * 
 * Ecco che esiste l'idioma pimpl. 
 * Nella parte privata, si mette solo un puntatore a dove la si definisce, e in questo modo 
 * l'header non cambia.
 * così facendo, non devo né riscrivere il codice né ricompilare, main e librerie
 * sono del tuttp indipendenti
*/ 

