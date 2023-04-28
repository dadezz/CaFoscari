#include <iostream>
#include <cassert>
#include <string>
#include <limits>
#include <vector>

/**
 * GRAMMATICA:
 * L -> S. | S;L                    linguaggio (lista di statement)     ----> S;S;S;S;S.
 * S -> var = E | p(E)              statement
 * E -> P | E+P | E-P               espressione
 * P -> T | P*T | P/T               produttoria
 * T -> (double) | (E) | var        termine
 * 
 * si potrebbe anche aggiungere la parte : 
 * D -> -U | U              // D sta per double e U sta per unsigned duble
 * U -> I | I.F             // I sta per intero e F per frazionaria. dal pov della grammatica sono stessa roba (sequenza di cifre), mi serve distinguerle per codice
 * I -> [0-9] | I[0-9]      //voglio restituire I*10 +cifra (esemoio: 123 =  12*10 +3)
 * F -> [0-9] | [0-9]F 
*/

double vars[255];

struct token{
    public:
        static constexpr double inf = std::numeric_limits<double>::max();   // pongo infinito come il più grande double esprimibile
        token() : m_value(inf), m_type(0) {};       //lista di inizializzazione = costruttore
        friend std::ostream & operator<<(std::ostream & os, token const & t){
            os << "[m_value = "<<t.m_value << ", m_type = " << t.m_type << "]";
            return os;
        }
        friend std::istream & operator>>(std::istream & is, token & t){
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
        double get_value() const { return m_value; }
        char get_type() const { return m_type;}
        bool is_double() const { return m_type == 0 && m_value != inf; }
        bool is_open() const { return m_type == '('; }
        bool is_close() const { return m_type == ')'; }
        bool is_add() const { return m_type == '+'; }
        bool is_sub() const { return m_type == '-'; }
        bool is_mult() const { return m_type == '*'; }
        bool is_div() const { return m_type == '/'; }
        bool is_var() const {return m_type>='a' and m_type <='z' and m_type != 'p';}
        bool is_print() const {return m_type == 'p';}
        bool is_dot() const {return m_type == '.';}
        char get_var_name() const {return m_type;}
    private:
        double m_value;     // value of the double
        char m_type;        // token != numero
};

double E(const std::vector<token>&, int&);

double T( const std::vector<token>& tokens, int& i){
    // T -> double | (E) | var
    double res = 0;
    if(tokens.at(i).is_double()){
        // T -> double
        res = tokens.at(i).get_value();
        ++i;
    }
    else if(tokens[i].is_var()){
        // T -> var
        res = vars[tokens[i].get_var_name()]; //extracts value of variable with name tokens[i]
        i++;
    }
    else{
        ++i;

        res = E(tokens,i);
        ++i;
    }
    return res;
}

void S (const std::vector<token>& v, int& i){
    // S -> var = E | p(E)
    if(v[i].is_var()){
        char c = v[i].get_var_name();
        i += 2; //consume token "var" and "="
        double res = E(v, i);
        vars[c] = res; //metto il valore nell'array globale 
    }
    else {
        i += 2; //consume "p("
        std::cout<<E(v, i)<<std::endl;
        i+=1; //consumo la parentesi di chiusura ')'
    }
}

double P( const std::vector<token>& tokens, int& i){
    // P -> T | P*T | P/T               T */ T */ T .... */ T
    double res = T(tokens,i);
    token t = tokens.at(i);
    while ( t.is_mult() or t.is_div()){
        ++i;
        if( t.is_mult()) res *= P(tokens,i);
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

// lista di statements, che in pratica racchiude il programma
void L(const std::vector<token>&v, int& i){
    // L -> S. | S;L 
    S(v, i);    //consume first statements;
    if (v[i].is_dot()){
        // devo consumare il punto (fine programma)
        i++;
        return;
    }
    else {
        i+=1; //consumo il punto e virgola alla fine di ogni statements
        L(v, i);
    }
}

int main(){
    std::vector<token> tokens;  //questo vettore conterrà la mia lista di token (l'intera espressione)
    do{
        token t;    //chiama il costruttore
        std::cin>>t;    //estraggo il vettore di token
        tokens.push_back(t);
    } while( not tokens.back().is_dot()); // si ferma quando token quando arriva ad "."
    int i = 0;
    L(tokens, i);
    return 0;
}
