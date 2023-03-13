/**
 * riassuntazzo:
 * ho delle struct/classi. se uso la semantica di C, lo stato non viene inizializzato alla dichiarazione, e
 * la copia è bit a bit di tutto lo stato.
 * Mi va sempre bene? no, voglio che se dichiaro qualcosa, sia vuoto o comunque abbia qualcosa di definito, e non siano valori random.
 * posso usare il concetto di costruttore. definisco uno o più metodi, chiamati automaticamente ogni volta che istanzio un oggetto della
 * classe: dichiarazione, passaggio dei parametri formali per copia, new.
 * Il costruttore garantisce uno stato dell'oggetto leggibile, coerente e significativo.
 * Il costruttore di default non richiede parametri, viene chiamato alla dichiarazione in modo automatico.
 * Posso farne di più sofisticati. per esempio, il copy constructor, o altri costruttori che prendono in input qualcosa, in modo
 * da fare un assegnamento al momento della dichiarazione, col classico metodo dell'uguale.
*/

#include <iostream>
#include <cstring>

using std::cout; using std::endl;

class StrPascal{
    public:
        StrPascal();    //Default constructor
        StrPascal(char*);
        StrPascal(const StrPascal &);   //Copy constructor
        void print();
    private:
        unsigned char buff[256];
};

StrPascal::StrPascal(){
    buff[0] = 0; //creo la stringa vuota
    cout<<"chiamato costruttore di default"<<endl;
    
}

StrPascal::StrPascal(char* str){
    int n = strlen(str);
    if (n<256){
        buff[0] = n;
    }
    else buff[0] = 255; //tronco la stringa se troppo lunga

    for (int i = 0; i<buff[0]; i++){
        buff[i+1] = str[i];
    }
    cout<<"chiamato costruttore con stringa "<<str<<endl;

}

StrPascal::StrPascal(const StrPascal & copy){
    for (int i=0; i<=copy.buff[0]; i++){
        buff[i] = copy.buff[i];
    }
    cout<<"chiamato costruttore di copia"<<endl;

}

void StrPascal::print(){
    for (int i = 1; i<=buff[0]; i++){
        std::cout<<buff[i];
    }
    std::cout<<std::endl;
}

void stampax2 (StrPascal input){
    input.print();
    input.print();
}

int main(){
    char cstring[100] = "Hello";
    StrPascal s(cstring);
    
    stampax2(s);
    /**
     * cosa viene printato? questa riga chiama il copy constructor, perché c'è un passaggio di parametro 
     * per copia, alla chiamata della funzione stampax2.
     * viene creato l'oggetto input, copiandolo da s. da cui, l'output sarà anche "chiamato costruttore per copia".
     * 
     * Il passaggio per copia prevede: 
     * 1. creazione di un oggetto di tipo passato
     * 2. copia del parametro effettivo nel parametro formale (e qui c'è la chiamata del copy constructor)
     * 
     * 
     * le chiamate al copy constructor non esistono se la firma della funzione fosse stata per reference:
     *   void stampax2 (StrPascal & input){
     * 
     * In questo caso infatti non avviene alcuna copia, c'è solo la referenza all'oggetto passato come parametro effettivo.
     *
    */
    return 0;
}

void stampax2_reference (StrPascal & input){
    input.print();
    input.print();
}

/**
 * se la firma fosse 
 *       void stampax2_reference (const StrPascal & input);
 * 
 * non compilerebbe. Perché ? 
 * la classe strpascal non è nativa, e il compilatore non sa cosa faccia il metodo print, quindi non può sapere che la stampa
 * non va a modificare il risultato. 
 * Quando chiamo la funzione input.print, dico che dev'essere const, ma il compilatore non può controllare.
 * 
 * Il c++ allora ci dà un metodo molto intelligente: dopo la dichiarazione del metodo, ci aggiungo la parola chiave const, 
 * in modo da poter dire al compilatore che quel metodo non modifica l'oggetto chiamante.
 * 
 * La classe risulterebbe quindi essere:
*/

class StrPascal_const{
    public:
        StrPascal_const();    //Default constructor
        StrPascal_const(char*);
        StrPascal_const(const StrPascal &);   //Copy constructor
        void print() const;

        // nella firma del metodo dichiaro che non modifico lo stato della classe.
        // un po' di controlli il compilatore li fa, quindi non è facilissimo "dichiarare il falso",
        // ma con l'uso di puntatori si può aggirare il problema, quindi diciamo che c'è da fidarsi della buona fede
        // del programmatore che ha scritto la classe.

        // è buona norma comunqeu metterlo in tutit i metodi che non servono a modificare la classe.
    private:
        unsigned char buff[256];
};

/**
 * esiste un altro metodo che viene chiamato automaticamente, contrapposto al costruttore: il distruttore di classe. 
*/


class StrPascal_distruttore{
    public:
        StrPascal_distruttore();    //Default constructor
        StrPascal_distruttore(char*);
        StrPascal_distruttore(const StrPascal &);   //Copy constructor
        ~StrPascal_distruttore(){
            std::cout<<"chiamato Thanos"<<endl;
        }
        void print();
    private:
        unsigned char buff[256];
};

/**
 * il distruttore viene chiamato sempre, anche quando viene stanziato l'oggetto in copia in una funzione, alla fine dello scope.
 * 
 * 1. variabile locale alla fine dello scope
 * 2. variabile globale al termine del programma
 * 3. variabile dinamica al delete.
 * 
 * se ci sono più oggetti da distruggere, prima distruggo la più recente e poi man mano quelli più vecchi
*/
