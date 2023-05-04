#include<iostream>
#include<string>

class Number{
  public:
    Number();                   //costruttore
    Number(unsigned int m);     //converte un unsigned int nella lista richiesta
    Number(const Number& l);    //copy constructor
    Number(std::string s);      //dato un numero codificato con una stringa
                                //scritto in modo che la cifra piu' significativa e' nella prima posizione
                                //generare un Number
    ~Number();                  //distruttore

    void print() const;         //stampa la lista: siccome le cifre meno significative sono in testa, devo stampare al contrario

    Number operator+(const Number& x) const;
    Number operator*(const Number& x) const;
    bool operator==(const Number& x) const; 
    bool operator!=(const Number& x) const;
    Number& operator=(const Number& x);
    void prepend(char x){   //appende all'inizio della lista
        List aux = new Cell;
        aux->next = n;
        aux->info = x;
        n = aux;
    }
    void append(char x){    //appende in coda alla lista
        if (n == nullptr) {
            prepend(x);
            return;
        }
        List scorre = n;
        while(scorre->next){
            scorre = scorre->next;
        }
        scorre->next = new Cell;
        scorre->next->info = x;
        scorre->next->next = nullptr;
    }

  private:
    //Non modificare
    struct Cell{
      char info;
      Cell* next;
    };
    typedef Cell* List;

    List n; //head
    List sum(List l1, List l2, char carry) const;   //somma tra due numeri 
    void print_rec(List l) const;   //parte ricorsiva della print

    
    //Parte modificabile (ma attenzione: ora è progettata per guidarvi)
   
    void destroy(List h);   //elimino la lista (delete delle celle).
    List copy(const List pc);   //copia la lista
    bool equal(List l1, List l2) const; // operator == 
    List convert(unsigned int); //converte un unsigned int nella lista richiesta
    

};

//Costruttore di default, 0 e' codificato con la lista vuota
Number::Number() {
    n=nullptr;
}

//converte un unsigned int nella lista richiesta
Number::Number(unsigned int m) {
    n = convert(m);
}

//studia questa funzione per comprendere completamente la rappresentazione nel numero
//e' un bell'esempio di ricorsione
Number::List Number::convert(unsigned int m) {
  if (m==0)
    return nullptr;
  else {
    List pc = new Cell;
    pc->info = static_cast<char>(m%10);
    pc->next = convert(m/10);
    return pc;
  }
}

//stampa la lista: siccome le cifre meno significative sono in testa, devo stampare al contrario
void Number::print() const {
  if (n==nullptr) 
    std::cout<<"0";
  else
    print_rec(n);
}

//parte ricorsiva della stampa
void Number::print_rec(List l) const {
  if (l) {
    print_rec(l->next);
    std::cout<<static_cast<char>(l->info+'0'); //Ecco il type casting explicito in C++
  }
}

//distruttore
Number::~Number() {
  destroy(n);
}

//funzione di disruzione ricorsiva
void Number::destroy(List h) {
  if (h) {
    destroy(h->next);
    delete(h);
  }
}

//primo metodo da implementare: dato un numero codificato con una stringa
//scritto in modo che la cifra piu' significativa e' nella prima posizione
//generare un Number. Attenzione non fare la conversione string->int->list
//perche' potresti avere errori di overflow
Number::Number(std::string s) {
    n = nullptr;
    for(int i = 0; i<s.length(); i++){
        prepend(s[i]-'0');
    }
}

//secondo metodo da implementare: copy constructor
//consigliato far uso della funzione privata ricorsiva copy
//potrebbe esserti utile anche per l'assegnamento!
Number::Number(const Number&x) {
    n=nullptr;
    n = copy(x.n);
}


Number::List Number::copy(const List pc) {
    if (pc == nullptr) return pc;
    copy(pc->next);
    prepend(pc->info);
    return n;
}



//l'operatore + non va modificato. Deve utilizzare il metodo sum come indicato
Number Number::operator+(const Number& x) const {
    Number res;
    res.n = sum(x.n, n, 0);
    return res;
}

//Questa funzione deve essere ricorsiva. Implementala con cura. Ricorda
//che l'ultimo carry potrebbe essere diverso da 0
Number::List Number::sum(List l1, List l2, char carry) const {
    if (!l1 and !l2 and !carry) return nullptr;
    int somma = 0;
    somma += l1!=nullptr ? (l1->info + carry) : carry; // se esiste l1, lo sommo con carry all'accumulatore, sennò solo il carry
    somma += l2!=nullptr ? l2->info : 0; //idem : se esiste l2, la sommo all'accumulatore.
    List nuova = new Cell;
    nuova->info = somma%10;
    if (l1!=nullptr){
        if (l2 != nullptr) nuova->next = sum(l1->next, l2->next, somma/10);
        else nuova->next = sum(l1->next, l2, somma/10);
    } 
    else {
        if (l2 == nullptr) nuova->next = sum(l1, l2, somma/10);
        else nuova->next = sum(l1, l2->next, somma/10);
    }
    return nuova;
}


//operatore di assegnamento. Segui la traccia
Number& Number::operator=(const Number& x) {
    if (this !=& x) {
        destroy(n);
        n = nullptr;
        copy(x.n);
    }
    return *this;
}


//La seguente funzione puo' essere modificata, ma e'
//consigliato usare la equal sviluppata ricorsivamente
bool Number::operator==(const Number& x) const{
  return equal(x.n, n);
}

//Da sviluppare
bool Number::equal(List l1, List l2) const {
    if (l1 and !l2) return false;
    if (!l1 and !l2) return true;
    return l1->info == l2->info and equal(l1->next, l2->next);
}

//Metodo veloce per implementare il != 
bool Number::operator!=(const Number& x) const{
    return !(*this==x);
}

//Fare il prodotto x*y significa sommare x+x+x+..+x (y volte...)
//non il modo piu' efficiente, ma il piu' facile
//Ricorda che tutte le operazioni vanno fatte coi numbers!
Number Number::operator*(const Number& x) const{
    /**
     * idea: come si fanno le moltiplicazioni in colonna?
     * 
     *   12 x
     *   34 =
     *   ____
     *   4x12 +
     *  3x12/
     *  _____
     * 
     * 4x2 = 8  con resto 0
     * 4 * 1 =  4 + 0 = 4  
     * ho quindi un number fatto come 8 -> 4
     * 
     * dopodiché, 3*2 fa 6 con resto 0
     * 3*1 fa 3 + 0 = 3
     * sono alla seconda iterazione: ci aggiungo uno 0 per shift
     * ho quindi 0->3->6
     * 
     * faccio poi somma tra i due numbers 8->4 e 0->6->3 =  360+48 = 408; 12x34 = 408 V.
     * 
     * Si crea un vettore di Numbers (così dinamicamente si possono aggiungere celle, senza sapere a priori quante ne servano)
     * L'idea e di fare un while che scorre le celle di l2 (in questo caso sarebbe il 34, quindi due iterazioni).
     * a ogni iterazione si fa la moltiplicazione della cella in questione per tutte le celle di l1 ricorsivamente, così da poter fare 
     * l'append senza sprecare troppo in prestazioni, e così da avere una facila gestione del resto. 
     * alla fine della ricorsione, si fa un for che prepende tanti 0 quanti i cicli di iterazione (alla iterazione 0 non si prepende nulla, 
     * alla seconda si ) -> questo diventa un number che va nel vettore
     * 
     * alla fine di tutto, avremo un vettore con tanti number quanti le righe del risultato della moltiplicazione in colonna (nel nostro caso 2)
     * e basterà chiamare somma = v[0] + v[1], poi somma = somma + v[2] e così via
    */
    Number res(0);
    if (this->n->info == 0 or x.n->info == 0) return res; // se è 0 ritorno zero.
    Number aux = 1;
    for (Number cont = 0; cont != x; cont = cont + aux) 
        res = (*this) + res;
    return res;
}

Number opera(Number x, Number y) {
  return x+y;
}

int main() {
  std::string s1, s2;
  std::cin>>s1;
  std::cin>>s2;
  Number n1(s1), n2(s2); 
  Number n3=24593;
  n3.print();
  std::cout<<std::endl;
  n3 = opera(n1, n2);

  n1.print(); 
  std::cout<<std::endl;
  n2.print();
  std::cout<<std::endl;
  n3.print();
  std::cout<<std::endl;
  Number n4 = Number(12)*Number(3);
  n4.print();
  if (n1==n2) 
    std::cout<<"Numeri uguali inseriti"<<std::endl;
 

  return 0;
}

