/**
 * overloading assegnamento
*/

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
        const doublelist& operator=(const doublelist& l){
            if (this != &l){
                Pcella pc = head;
                while(pc){
                    pc = pc->next;
                    delete head;
                    head = pc;
                }
                head = nullptr;
                tail = nullptr;
                pc = l.head;
                while(pc){
                    append (pc->info);
                    pc = pc->next;
                }
            }
            return *this;
        }
        doublelist operator+(const doublelist& l1) const {
            /**
             * l'oggetto ris, al momento del ritorno della funzione, muore, quidni se passo una const
             * reference non ho più l'oggetto da restituire, devo farne una copia. nel caso sopra, this
             * è una variabile semore viva, mentre ris è locale
             * 
             * [in realtà, vedremo, non viene copiato, ma viene "spostato", lo stato di ris passa all'oggetto risultato -> move semantics]
            */
            Pcella pc = head;
            doublelist ris;
            while (pc){
                ris.append(pc->info);
                pc = pc->next;    
            }
            while(pc){
                ris.append(pc->info);
                pc = pc->next;
            }
            return ris;
        }
        doublelist operator*(unsigned int n) const {
            doublelist ris;
            for(int i=0; i<n; i++){
                Pcella pc=head;
                while(pc){
                    ris.append(pc->info);
                    pc = pc->next;
                }
            }
            return ris;
        }
};

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

