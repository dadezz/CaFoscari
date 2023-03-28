/**
 * cambiare l'implementazione di una classe nella sezione privata senza dover cambiare header
 * e quindi senza dover ricompilare i vari sorgenti
*/

#include <iostream>
#include <vector>

//questa è la classe come costruita la volta scorsa.

class list_int_vecchio{
    public:
        list_int_vecchio();
        list_int_vecchio(const list_int_vecchio& s);
        ~list_int_vecchio();
        void append(int e);
        void prepend(int e);
        bool is_empty() const;
        int& head(); // qui posso scrivere e leggere l'elemento di testa
        const int& head() const; // qui posso solo leggere l'elemento di testa
        void print();
        int list_int_vecchio::size() const;
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

/**
 * mi serve un modo di poter modificare l'implmentazione della classe senza dover modificare l'header: PIMPL
*/

class list_int{
    public:
        list_int();
        list_int(const list_int & l);
        ~list_int();
        void prepend(int el);
        void append(int el);
        void stampa() const;
    private:
        struct Impl;    //stands for implementation
        Impl * pimpl;
};

/**
 * a c++ non interessa sapere quali oggetti un puntatore punta per sapere la dimensione del puntatore (che è ciò che va nello stack)
 * nel momento in cui vado nel list.cpp (che scrivo qua sotto di seguito), definisco:
*/ 

//#include "list.hpp"

struct list_int::Impl{
    std::vector<int> v;
};

list_int::list_int(){
    pimpl = new Impl;
}

list_int::list_int(const list_int& l){
    pimpl = new Impl;
    pimpl->v = l.pimpl->v;
}

list_int::~list_int(){
    delete pimpl;
}


void list_int::prepend(int el){
    pimpl->v.resize(pimpl->v.size()+1);
    for(int i=pimpl->v.size()-1; i>0; i--){
        pimpl->v.at(i) = pimpl->v.at(i+1);
    }
    pimpl->v.at(0);
}

void list_int::append(int el){
    pimpl->v.push_back(el);
}

void list_int::stampa() const{
    for(auto & e:pimpl->v){
        std::cout<<" "<<e;
    }
}


