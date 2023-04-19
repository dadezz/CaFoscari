/**
 * LISTA DOPPIAMENTE CONCATENATA CON VETTORI
 * 
 * la cella precedente contiene il puntatore a prev, la cella contiene info e quella successiva contiene puntatre a next (indice)
 * 
 * 
*/
#include "030ListDL.hpp"
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;
#define MAXE 10

struct ListDL::impl{
    vector<int> v;
    int head;
    int tail;
    int free;
};

ListDL::ListDL(){
    pimpl = new impl;
    pimpl->v.resize(MAXE*3);
    pimpl->head = -1;
    pimpl->tail = -1;
    pimpl->free = 0;

    for (int i=0; i<MAXE; i++){
        pimpl->v.at((1*3)+2) = (i+1)*3;
    }
    pimpl->v.at((MAXE-1)*3+2) = -1;
}

ListDL::ListDL(const ListDL& s){
    pimpl = new impl;
    pimpl->v = s.pimpl->v;
    pimpl->head = s.pimpl->head;
    pimpl->tail = s.pimpl->tail;
    pimpl->free = s.pimpl->free;

    /**
     * è sbaliato scrivere pimpl = s.pimpl;
     * perché viene copiato il puntatore, non la lista. modificando una modifichi l'altra.
     * (idem oggetto morto)
    */
}

//; ; ;  ;;; ;;; ;;;  ; ; ;   ;;; ;;; ;  ; ; ; ;  ;   ; ; ;  ;;; ; ; ;  ; ;;; ;  ;;; ;;; ;;;      // un SOS GHE SBORO che compila :)

ListDL::~ListDL(){
    delete pimpl;
}

void ListDL::prepend(int e){
    if(pimpl->free != -1) {
        int nuovo = pimpl->free;
        pimpl->free = pimpl->v.at(pimpl->free +2);
        pimpl->v.at(nuovo) = -1;
        pimpl->v.at(nuovo+1) = e;
        pimpl->v.at(nuovo+2) = pimpl->head;
        pimpl->head = nuovo;
        if(pimpl->tail == -1) pimpl->tail = nuovo;
        if(pimpl->head != -1) pimpl->head = nuovo;
    }
}

void ListDL::print() const {
    for (int i=0; i<MAXE; i++){
        std::cout<<i*3<<": ";
        cout << "[" << pimpl->v.at(i*3) << ", " << pimpl->v.at(i*3+1) << ", " << pimpl->v.at(i*3+2) << "]" <<endl;
    }
}

int& ListDL::at(int pos){
    int pc = pimpl->head;
    while(pc != -1 && pos>0){
        pc = pimpl->v.at(pc+2);
        pos--;
    }
    if (pc!=-1) return pimpl->v.at(pc+1);
    else return pimpl->v.at(MAXE*3); //uso un'eccezione dei vector per semplicità, dovrei gestirmela io
}

const ListDL& ListDL::operator=(const ListDL l){
    if (this != &l){
        pimpl->v = l.pimpl->v;
        pimpl->head = l.pimpl->head;
        pimpl->tail = l.pimpl->tail;
        pimpl->free = l.pimpl->free;
    }
    return *this;
}

bool ListDL::operator==(const ListDL& l) const{
    bool res =true;
    int pc1 = pimpl->head;
    int pc2 = l.pimpl->head;
    while(pc1 != -1 and pc2 != -1 && res){
        if (pimpl->v.at(pc1+1) != pimpl->v.at(pc2+1)) res = false;
        else{
            pc1 = pimpl->v.at(pc1+2);
            pc2 = l.pimpl->v.at(pc2+2);
        }
    }
    return (pc1==-1 && pc2==-1);
}

ListDL ListDL::operator+(const ListDL& l) {
    ListDL res = *this;
    int pc2 = l.pimpl->head;

    while(pc2!=-1) {
        append(l.pimpl->v.at(pc2+1));
        pc2 = l.pimpl->v.at(pc2+2);
    }
    return res;
}

int main(){
    ListDL l;
    l.print();
    l.prepend(15);
    l.prepend(20);
    l.prepend(30);

    l.at(1) = 200;

    l.print();

    return 0;
}