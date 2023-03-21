#include<iostream>
/**
 *  OVERLOADING DEI METODI , IN PARTICOLARE DEL METODO AT
*/

/**
 * CHIAMATA AL COSTRUTTORE
 * 
 *    - DICHIARAZIONE DI UNA VARIABILE GLOBALE O LOCALE
 *    - DICHIARAZIONE DI UN OGGETTO DINAMICO
 *    - DICHIARAZIONE DI OGGETTO DI UNA CLASSE
*/

/**
 *    funzioni che tornano una reference:
 * 
 *    int& foo( int b ){
 *          int k = b;
 *          return K;              
 *    }
 * 
 *    ritorno una reference, quindi un nome alternativo per una variabile
 *    il nome alternativo è associlato ad un oggetto locale : la variabile k
 * 
 *    quando si va a fare foo(7) = 15;
 *    si deve andare a cercare la reference alla variabile che dentro la funzione però viene distrutta.
 *    
 *    int k; => la variabile k non viene distrutta all'interno della funzione 
 *    int& foo( int b ){
 *       k = b;
 *       return k; //qui torno un lvalue, ritorno l'oggetto che dentro la funzione si chiama k
 *                   qui non posso fare return k + 8; perchè questo si trasforma in un rvalue
 *    }
 *    
 *    int foo(int b){
 *         int k = b;
 *         return k; //qui ritorno un rvalue, ritorno un valore che non ha senso che venga usato a sinistra di un assegnamento
 *          qui posso fare : return k + 8;
 *    }
 *    
 *    se faccio foo(7) = 15;
 *    viene modificata la variabile k globale.
 *    Non è importante che k sia una reference o no.
 *    
 *    quando restituisco un lvalue restituisco un oggetto che può essere scritto o che può essere letto
 * 
 *    CLASSICONTAINER:
 *      classe che serve a memorizzare dei valori, che tengono dei valori
 * 
 *      lista di interi
*/

class list_int
{

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

    private:
        //mettendo la cella dentro la parte privata,il chiamante non può nemmeno accedere alla definizione della lista
        struct cell
        {
            int info;
            cell* next;
        };

        cell* h;      
};

list_int::list_int()
{
     h = nullptr;
}

list_int::list_int(const list_int& s){
    cell* pc = s.h;

    while ( pc != nullptr)
    {
        append(pc->info);
        pc = pc->next;
    }
       
   
}

list_int::~list_int()
{
    cell* pc = h;
    while ( pc != nullptr)
    {
        h = h ->next;
        delete pc; 
        pc = h;
    }
}

void list_int::prepend(int e){ // mettere l'oggetto in testa
       
     cell* x = new cell; // la prepend funziona anche con la lista vuota
     
      x->info = e;
      x->next = h;
      h = x; // h punta dove punta nuova

}

void list_int::print(){
 
   cell* pc = h;
   while ( pc != nullptr)
   {
     std::cout<<h->info<<" , ";
   }
   std::cout<<std::endl;

}

int main(){

}