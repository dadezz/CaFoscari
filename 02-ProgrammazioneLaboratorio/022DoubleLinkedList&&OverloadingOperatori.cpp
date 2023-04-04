#include<iostream>

class doublelist {
    private:
        struct cella
        {
            int info;
            cella* next;
            cella* prev;
        };
        typedef cella* Pcella;
        Pcella head;
        Pcella tail;
        void copy(Pcella, Pcella);
    public:
        doublelist();
        doublelist(const doublelist &);
        ~doublelist();
        void prepend(int);
        void append(int);
        void print() const;
        int & at(int) const;
        int & at(int);
        bool operator==(const doublelist& l) const;
};

doublelist::doublelist(){
    this->head = nullptr;
    this->tail = nullptr;
}
doublelist::doublelist(const doublelist & s){
    copy(s.head, s.tail);
}
void doublelist::copy(Pcella h, Pcella t){
    head = nullptr;
    tail = nullptr;
    while(h != nullptr){
        this->append(h->info);
        h = h->next;
    }
}
void doublelist::append(int e){
    Pcella nuova = new cella;
    nuova->info = e;
    nuova->next = nullptr;
    nuova->prev = tail;
    if (tail!=nullptr) tail->next = nuova;
    else head = nuova; //se la lista è vuota, devo cambiare anche head
    tail = nuova;
}
void doublelist::prepend(int e){
    Pcella nuova = new cella;
    nuova->info = e;
    nuova->next = head;
    nuova->prev = nullptr;
    if (head!=nullptr) head->prev = nuova;
    else tail = nuova;
    head=nuova;   
}
void doublelist::print() const{
    Pcella pc = head;
    while (pc){
        std::cout<<pc->info;
        pc = pc->next;
    }
}
int & doublelist::at(int pos) const{
    /**
     * voglio fare come in python, permettere di usare gli at con indici negativi, per 
     * indicare l'Nesimo elemento a partire dalla fine della lista.
     * Esempio: voglio indicare con -2 il penultimo e con -1 l'ultimo.
     * Questa cosa è molto utile, perché permette di accedere agli elementi in coda
     * senza partire a scorrere tutto dall'inizio, risparmiando così operazioni
    */
    if (pos>=0){
        Pcella pc = head;
        while(pc && pos){
            pc = pc->next;
            pos--;
        }
        if(pc) return pc->info;
        else; //lancia eccezione
    }
    else {
        pos = -pos-1;
        Pcella pc = tail;
        while(pc && pos){
            pc = pc->prev;
            pos--;
        }
        if(pc) return pc->info;
        else; //lancia eccezione
    }
}
int & doublelist::at(int pos) {
    /**
     * voglio fare come in python, permettere di usare gli at con indici negativi, per 
     * indicare l'Nesimo elemento a partire dalla fine della lista.
     * Esempio: voglio indicare con -2 il penultimo e con -1 l'ultimo.
     * Questa cosa è molto utile, perché permette di accedere agli elementi in coda
     * senza partire a scorrere tutto dall'inizio, risparmiando così operazioni
    */
    if (pos>=0){
        Pcella pc = head;
        while(pc && pos){
            pc = pc->next;
            pos--;
        }
        if(pc) return pc->info;
        else; //lancia eccezione
    }
    else {
        pos = -pos-1;
        Pcella pc = tail;
        while(pc && pos){
            pc = pc->prev;
            pos--;
        }
        if(pc) return pc->info;
        else; //lancia eccezione
    }
}

/**
 * Tutto molto bello. 
 * Per conforntare due liste con un bel '==', cosa fare?
 * se avessi due liste con stessi valori concatenati (info), sarebbero uguali, ma la condizione restituirebbe false
 * perché i puntatori saran diversi.
 * 
 * Devo quindi dire a c++ come interpretare il ==.
 * 
 * chiamo il metodo == del primo dei due e gli passo il secondo operando come const reference
*/

bool doublelist::operator==(const doublelist& l) const{
    Pcella pc1 = head;
    Pcella pc2 = l.head;
    bool uguali = true;
    while (pc1 and pc2 and uguali){
        if (pc1->info != pc2->info){
            uguali = false;
        }
        pc1 = pc1->next;
        pc2 = pc2->next;
    }
    return pc1 == pc2;
}

/**
 * E fin qui...
 * L'overloading dell'assegnamento è già più rognoso.
 * 
 * per esempio, deve esserci associatività a destra.
 * altro ancora, l2=l1  -> devo deepcopiare l1 in l2, ma magari l2 già aveva uno stato suo, che va deletato prima.
 * 
 * e che cazzo succede se scrivo l2=l2 ? se faccio come prima, distruggo lo stato di l2 e poi prendo lo stato di l2 (che non esiste più) e ce lo ficco.
 * Ho tagliato il ramo su cui stavo seduto LMAO
 * la semantica di deep copy deve tenere conto due queste 3 difficolta:
 * 
 * 1. assegnamenti in catena
 * 2. distruzione stato precedente
 * 3. autoassegnamento 
*/

