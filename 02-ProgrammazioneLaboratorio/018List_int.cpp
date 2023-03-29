#include<iostream>

class List_int{
    public: 
        int elimina_fondo(int n); //voglio eliminare le ultime n celle
        void List_int::ribalta();
    private:
        struct cella{
            int info;
            cella* next;
        };
        cella* l;
        typedef cella* Pcella;
        int elimina_fondo_rec(Pcella & h, int n);
        void List_int::ribalta_rec(Pcella & h);
};


int List_int::elimina_fondo_rec(Pcella & h, int n){
    if (h == nullptr) return 0;
    int cancellati = elimina_fondo_rec(h->next, n);
    if (cancellati < n){
        delete h;
        h = nullptr;
        return cancellati+1;
    }
    else return n;

    /** ✨✨✨✨✨✨✨✨✨✨✨✨✨✨
     * ✨LA FATINA DELLA RICORSIONE ✨
     *  ✨✨✨✨✨✨✨✨✨✨✨✨✨✨
    */
}

int List_int::elimina_fondo(int n){
    /**
     * k = numero di celle
     * 
     * SOLUZIONIITERATIVE:
     * soluzione con complessità k*n: ciclo innestato
     * soluzione con complessità 2k: prima conti le celle e poi ripassi eliminando le ultime
     * soluzione con complessità k: due puntatori fratelli, distanti n, quando il primo arriva alla fine, il secondo inizia a eliminare
     * 
     * SOLUZIONERICORSIVA:
     * implemento.
     * so cancellare quando la lista è lunga k-1. 
     * la chiamata ricorsiva mi ritorna quanti elementi ha cancellato. se ne ha cancellati meno di n bon non faccio nulla, 
     * altrimenti se ne ha eliminati meno di n, eliminpo quello il cui sono e dico di averne cancellarti ricorsione più uno.
     * caso base: se la lista è buota, non devo cancellare nulla ottimo oro benon
     * 
     * BAM complessità k. 
    */
    return elimina_fondo_rec(l, n);
}

void List_int::ribalta_rec(Pcella & h){
    if (l != nullptr and h->next != nullptr){
        Pcella supporto = h->next;
        ribalta_rec(supporto);
        h->next->next = h;
        h->next = nullptr;
        h = supporto;
    }
    /**
     * fatti lo schemino del prof con la lista e capisci xk il supporto
    */
}

void List_int::ribalta(){
    return ribalta_rec(l);
}

/**
 * come ribaltare una lista senza duplicarla, usando la ricorsione
 * 
 * STRATEGIA:
 * So ribaltare una lista con k-1 elementi. 
 * tolgo il primo elemento della lista e lo appendo alla lista ribaltata. ovviamente, se non c'è nulla da ribaltare, non ribalto nulla
 * 
 * 1. tolgo
 * 2. ribalto k-1
 * 3. appendo in coda
*/