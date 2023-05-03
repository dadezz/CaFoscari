#include <iostream>

class ListCirc {
    private:
        struct Cell {
            int info;
            Cell* next;
        };
        typedef Cell* Pcell;


    public:
        Pcell start;
        int decidi (Pcell l) const;
        void insert(Pcell& l, int k);
        void print(){
            // per risolvere il problema di while(l), siccome non esiste nullptr, basta che mi segni da dove son partito
            Pcell pc = start;
            if (start) {
                do {
                    std::cout<<start->info;
                    start = start->next;
                } while (start != pc);
            }
        }
};

/**
 * problema: data una lista, decidi se è circolare o semplice
*/

int ListCirc::decidi (Pcell l) const {
    /**
     * 0 se vuota
     * 1 se circolare
     * 2 se lineare
    */
    if (l == nullptr) return 0;
    Pcell pc = l;
    do {
        l = l->next;
    } while( l!= nullptr && l!=pc);
    if (l == nullptr) return 2;
    else return 1;
}

void ListCirc::insert(Pcell& l, int k){
    if (l!=nullptr){
        Pcell n = new Cell;
        n->info = k;
        n->next = l->next;
        l->next = n;
    }
    else {
        Pcell n = new Cell;
        n->info = k;
        n->next = n;
        l = n;
    }
}

int main(){
    ListCirc r;
    r.insert(r.start, 3);
    std::cout<<"s"<<std::endl;
    r.print();
}

/**
 * LISTE CON CAPPIO
 * struttura di circolarità, ma la chiusura del cerchio non avviene su "start", ma su una cella qualsiasi.
 * Vogliamo capire se la lista è lineare o ha un cappio.
*/

struct Cella {
        int info;
        Cella* next;
    };
typedef Cella* Pcella;

bool cappio(Pcella l){
    //difficoltà n quadro
    Pcella a, t, g;
    if (l != nullptr){
        t = l;
        a = l->next;
        bool found = false;
        while(a != nullptr and not found){
            g = l;
            while(g!=a && g!=t){
                g = g->next;
            }
            if (g==a) found = true;
            t=t->next;
            a = a->next;
        }
        return found;
    }
    return false;

    /**
     * come diminuire la difficoltà? mando avanti a di due in due, finché o arriva alla fine o raggiunge/scavalca la tartaruga (da controllare entrambi i casi)
    */
}
