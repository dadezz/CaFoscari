#include <iostream>
#include <cassert>
#include <string>
#include <limits>
#include <vector>

struct token {

    static constexpr double inf = std::numeric_limits<double>::max(); // static significa che se ho 10 token, ce ne sarà una sola
    token() : m_value(inf), m_type(0) {}; //liste di inizializzazione.
    friend std::ostream& operator<<(std::ostream& os, token const & t){ 
        os << "[m_value = "<<t.m_value << ", m_type = " << t.m_type << "]";
        return os;
    }
    friend std::istream & operator>>(std::istream & is, token const & t);
    double get_value() const {
        assert(is_double());
        return m_value;
    }
    char get_type() const {
        assert(not is_double());
        return m_type;
    }
    bool is_double() const { return m_type == 0 && m_value != inf; }
    bool is_open() const { return m_type == '('; }
    bool is_close() const { return m_type == ')'; }
    bool is_add() const { return m_type == '+'; }
    bool is_sub() const { return m_type == '-'; }
    bool is_mult() const { return m_type == '*'; }
    bool is_div() const { return m_type == '/'; }
    bool is_eq() const { return m_type == '='; }
    private: 
        double m_value; // value of the double
        char m_type;    // ()*-/+=
};

/***
 * 
 * abbiamo visto la gramatica così definita:
 * E-> (DOUBLE)  |  (+ES)  |  (*ES)
 * S-> E  |  ES
 * 
 * E è un'espressiione, S è una sequenza di espressioni
 * 
 * Estendiamo l'arithmetic tree in modo da accettare più di due elementi
 * 
 * esempio: (+(2.3)(1.78)(*(1.2)(3.5)))
 * 
 * grammatica: 
 * E -> (double) | (+ES) | (*ES)   // ESPRESSIONI (UN ALBERO)    
 * S -> ES | E    //SEQUENZA DI ALBERI CON ALMENO UN ALBERO
 * 
 * assumiamo che i double con segno prefisso non sonon ammessi per semplicita
*/

double S(char);

double E(){

    // E -> (double) | (+ES) | (*ES)

    char c = 0;
    std::cin >> c; //letto '('
    assert(c=='(');

    double result = 0;

    std::cin >> c; //lettto una cifra o un poertatore +/*

    if(c>= '0' and c <= '9'){   // caso 'double'
        std::cin.putback(c);
        std::cin >> result;
    }
    else if (c == '+') result = E() + S('+');
        /**
         * spiego il motivo dell'argomento di S.
         * ci sono più di due nodi perogni nodo, E è facile da combinare con S, col
         * + in mezzo, ma S come deve trattare i due sottonodi?
         * 
         * Esempio: E = (1.2), S = (2.3) (4). cosa succede tra i due double di S? devo dirgielo in qualche modo, entre tra S ed E è pacifico
         * 
         * 
        */
    else result = E() * S('*');
}

double S(char op){
    // S -> E | ES
    double result = E(); //dopo la chiamata della E mi trovo sempre con una parentesi chiusa o aperta, a seconda dei due casi della grammatica
    char c = 0;
    std::cin >> c;
    std::cin.putback(c);

    if (c == '('){
        double rhs = S(op);
        if (op=='+') result += rhs;
        if (op=='*') result *= rhs;
    }
    else {
        assert(c==')');
        //abbiamo solo E, devo solo restituire il valore di E
    }
    return result;
}

/**
 * se aggiungessi il - e il /, non funzionerebbe. perché ?
 * l'associatività è applicata al contrario.
 * Per esempio: 5-2-2 = (-(5)(2)(2)), che dovrebbe essere (5-2)-2, ma il codice restituisce
 * 5- (2-2).
 * il problema sta in result = E() - s('-').
 * 
 * 
 * voglio migliorare la grammatica in modo da avere 
 * E-> (D)  |  (+ES)  |  (*ES)
 * 
 * ovvero non dover utilizzare l'operatore formattato cin>>, ma da definirmi direttametne D
 * grammatica per i double:
 * 
 * come è fatto un double? ammettiamo il segno meno prefisso (i positivi sono senza segno)
 * 
 * D -> -U | U              // D sta per double e U sta per unsigned duble
 * U -> I | I.F             // I sta per intero e F per frazionaria. dal pov della grammatica sono stessa roba (sequenza di cifre), mi serve distinguerle per codice
 * I -> [0-9] | I[0-9]      //voglio restituire I*10 +cifra (esemoio: 123 =  12*10 +3)
 * F -> [0-9] | [0-9]F      //  "       "        (cifra+F)/10 esempio: 123 -> 0.123. ricorsivamente, ho 1 23 -> (1+0.23)/10 -> 0.123
 * 
 * 
*/

unsigned int I(){
    //I non consuma caratteri, quindi dovrei chiamare ricorsivamente sempre I per primo, finendo in un loop infinito,
    //risolvo quindi con la ricorsione

    unsigned int result = 0u;
    while (std::cin.peek()>='0' and std::cin.peek()<='9'){
        char c=0;
        std::cin>>c;
        result = result * 10 + (c - '0');
    }
    return result;
}

double F(){
    //per la f è diverso: prima consuma un carattere e poi chiama la ricorsione
    char c = 0;
    std::cin>>c;
    if (std::cin.peek()>='0' and std::cin.peek()<='9') return (F() + (c-'0'))/10.0;
    return double(c-'0')/10.0;
}

double U(){
    double result = I();
    char c = 0;
    std::cin>>c;
    if (c == '.'){
        return result + F();
    }
    else {
        std::cin.putback(c);
        return result;
    }
}

double D(){
    char c =0 ;
    std::cin>>c;
    if(c=='-') return -U();
    std::cin.putback(c);
    return U();
}


/**
 * ecco che a riga 83 posso  mettere result = D() invece di usare un cin.
 * e nell'if appena sopra posso aggiungere or c=='-'
*/
int main(){
    std::cout<<"inserire espressione: "<<std::endl;
    double result = E(); //la funzione si mangia un intera espressione;
    std::cout << "il risultato è: "<< result << std::endl;
}


/**
 * VEDIAMO ORA DI COMPLETARE IL PROGETTO. UNIAMO TUTTI I CONCETTI
 * 
 * lasciamo perdere le parentesi bilanciate e consideraimao una grmmatica che si cooupu
 * di risolvere:
 * - associatività da sinistra
 * - espressioni ricorsive
 * 
 * possiamo considerare ongni espressione come null'altro che una sommatoria di prodotti
 * (anche perche il prodotto ha precedenza sulla somma)
 * 
 * e così risolviamo il problema di ricorsione e precedenza del prodotto.
 * come sistemare l'associatività a sinistra?
 * 
 * E -> P | E+P | P+E
 * P -> T | T*P | P*T
 * T -> (double) | (E)
 * 
 * E -> P + P + P....+ P  diventa E -> P | E + P | E - P (si espande ricorsivamente )
 * 
 * si nota che  (3 - 2) => espressione
 * 3 viene visto come prodotto :
 *     il quale viene espanso come termine
 * quindi la espressione a questo punto diventa 3 
 * si fa quindi E - P , il prodotto è 2 
 * successivamente si fa 3 - 2
 * altro esempio : ( 3 - 2 ) + 5
 * ( 3 - 2 ) => singolo termine
 * che può essere espansa in (E)
 * ogni E prima o poi deve essere calcolata come espressione
 * 
 * 
 * UNENDO IL TUTTO, QUINDI :
*/

struct token { 
    public:
        static constexpr double inf = (double)std::numeric_limits<int>::max();
        token(): m_type(0),m_value(inf) {}  //initializer list
        friend std::istream& operator>> ( std::istream& is ,token& t){
            char c = 0;
            is >> c;
            if( c >= '0' and c <= '9'){
                //putback annulla l'effetto di quella lettura senza perdere il carattere appena letto
                is.putback(c);
                is >> t.m_value;
            }else{
                t.m_type = c;
            }
            return is;
        }
        double getValue() const{ return m_value; };
        char   getType() const { return m_type ;} ;
        bool is_double()const{return m_type == 0 and m_value != inf; };
        bool is_open()const { return m_type == '('; };
        bool is_close()const{ return m_type == ')'; };
        bool is_add()const{ return m_type == '+'; };
        bool is_sub()const{ return m_type == '-'; };
        bool is_mul()const{ return m_type == '*'; };
        bool is_div()const{ return m_type == '/'; };
        bool is_eq()const { return m_type == '=';};
    private:
       char m_type;
       double m_value;
};


double E(const std::vector<token>& tokens, int& i); // forward declareation

double T( const std::vector<token>& tokens, int& i){
    double res = 0;
    if(tokens.at(i).is_double()){
        res = tokens.at(i).getValue();
        ++i;
    }else{
        assert(tokens.at(i).is_open());
        ++i;

        res = E(tokens,i);
        
        assert(tokens.at(i).is_close());
        ++i;
    }
    return res;
}

double P( const std::vector<token>& tokens, int& i){
    double res = T(tokens,i);
    token t = tokens.at(i);
    while ( t.is_mul() or t.is_div()){
        ++i;
        if( t.is_mul()) res *= P(tokens,i);
        if( t.is_div()) res /= P(tokens,i);
        t = tokens.at(i);
    }
    return res;
}

double E(const std::vector<token>& tokens, int& i){ //E -> P |E + P | E - P, basta vedere che E viene comunque viene espanso in un prodotto,è sempre corretto leggere sempre un P
    double res = P(tokens,i);
    token t = tokens.at(i);
    while ( t.is_add() or t.is_sub()){
        ++i;
        if( t.is_add()) res += P(tokens,i);
        if( t.is_sub()) res -= P(tokens,i);
        t = tokens.at(i);
    }
    return res;
}

int main(){
    std::vector<token> tokens; // ( 1.5 + 4) * 11 
    do{
        try {
            token t;//chiama il costruttore
            std::cin>>t; //leggo da input con l'operatore >> appena ridefinito
            if(t.is_double()){
                std::cout<<t.getValue()<<std::endl; 
            }else{
                std::cout<<t.getType()<<std::endl;  
            }
            tokens.push_back(t);
        }
        catch(const std::runtime_error& e){
            std::cerr<<e.what()<<std::endl;
        }
    } while(!tokens.back().is_eq()); // si ferma quando token quando arriva ad "="
   
    int i = 0;
    std::cout<<"result is: "<<E(tokens,i)<<std::endl;
    
   return 0;
}
