/**
 * progettare una calcolatrice, facendo il parsing delle stringhe in ingresso (espressioni).
 * Facciamo a step. prima versione è minimal: due operandi e un'operazione. 
 * Oggi faremo un intensivo uso degli stream, oggi vedremo anche l'overloading dell'operatore >>
*/

#include <iostream>

int main0(){
    int lval = 0;
    char op = 0;
    int rval = 0;

    std::cin >> lval;
    std::cin >> lval >> op >> rval; //estrae un intero, poi un carattere e poi un altro intero

    /**
     * cin  è un operatore binario con associatività a sinistra, quindi prima si prende lval, che restituisce un risultato
     * (che è uno stream), e lo butta in input a lval, a sua volta dà stream etc.
     * 
     * è equivalente a scrivere 
     * ((std::cin>>lval) >> op) >> rval;
    */

    int res = 0;
    if (op == '+') res = lval+rval;
    else if (op == '-') res = lval-rval;
    else{
        std::cerr << "invalid operand: " << op << std::endl; //differenza con cout: il canale di uscita (standard output e errore)    
        return 1;
    }

    std::cout<<"the result is: " << res << std::endl;
    return 0;
}

/**
 * in esecuzione, 9--2 riporta 11, perché lo stream interpreta il 9 come intero, il - come operatore, il -2 come intero.
 * uno spazio è interruzione dello stream, molti spazi vengono collassati in un unico.
 * 
 * 5 + 17 sono 6 caratteri. il >> è un operatore formattato. se trova uno spazio, lo salta, e se deve prendere un intero
 * sa come comportarsi (prende i due caratteri del 17, non solo uno).
 * il cin ha testina in partenza su lval, prende il 5 e passa la testina al +, e passa lo stream a op. etc.
 * 
 * è da porre attenzione sugli operatori formatttati e gli altri. per esempio, la get() non ha formattazione. Se
 * si inserisce uno stream sbagliato, cin lo nota.
*/

/**
 * seconda versione:
 * si usano i double, lo switch, si estende l'operatività a tutti gli operandi e se ne prendono più di due. 
 * trattiamo sequenze di operazioni (e finiscono con un uguale).
 * 
 * 
 * Il cin e il cout hanno dei booleani nascosti, nel senso che possono essere usati come condizione.
 * se il cin è in errore, restituisce false, altrimenti true.
 * 
 * 
 * Il cin sa interpretare -3.14 come double, fa la gran parte del lavoro di parsing.
 * un buon esecizio è implementare il parsing (ricevo caratteri e interpreto)
*/
#include <string>

int parse_error1(std::string err){
    std::cerr << err << std::endl;
    return 1;
}

int evaluate1(){ // extracts expression, evaluates it and returns 1 (success) or 0 (error)
    std::cout<< "insert expresssion (valid operands: +-*/): "<<std::endl;
    std::cout<< "expression must end with = " << std::endl;
    std::cout<< "expample: 5+7*243-6/2= " << std::endl;

    double lval=0, rval=0;
    char op='0';
    
    std::cin >> lval >> op;     //per ora prendo lval e op
    if(!std::cin) return parse_error1("invalid expression");

    while(op != '='){
        std::cin >> rval;
        if(!std::cin) return parse_error1("invalid expression");

        switch (op) {
            case '+': lval += rval; break;
            case '-': lval -= rval; break;
            case '*': lval *= rval; break;
            case '/': lval /= rval; break;
            default: return parse_error1("invalid expression"); break;
        }

        std::cin >> op;
    }

    std::cout << "result: " << lval << std::endl;
    return 0;
}

int main1() {

    return evaluate1();
    return 0;
}

/**
 * gestione delle eccezioni: throw, try, catch.
 * 
 * una funzione può "lanciare" una struct/class. se lo fa, la funzione esiste e il chiamante piò prendere lo stato dell'oggetto.
 * 
 * di norma è usato per gestire gli errori.
 * 
 * esempio minimale:
*/

struct myerror{
    std::string msg;
};

int react_area2(int a, int b){
    if (a<0 or b<0) throw myerror {"arguments must be >= 0"};
    return a*b;
}

int main2(){
    std::cout << react_area2(-2, 5) << std::endl; //così non sto gestendo l'errore:
    // "terminate called after throwing an istance of myerror. aborted"
}

int main3(){
    try{
        std::cout << react_area2(-2, 5) << std::endl;
    } catch (myerror const & e){
        std:: cerr << e.msg << std::endl;
    }

    //ho gestito l'eccezione, quindi non devo mandare il messaggio di errore, il programma è a posto
    return 0;
}

/**
 * tornando all'esempio della calcolatrice 2, ecco come posso cambiare il codice con la gestione degli errori
*/

struct parse_error4{
    std::string msg;
};

int evaluate4(){ // extracts expression, evaluates it and returns 1 (success) or 0 (error)
    std::cout<< "insert expresssion (valid operands: +-*/): "<<std::endl;
    std::cout<< "expression must end with = " << std::endl;
    std::cout<< "expample: 5+7*243-6/2= " << std::endl;

    double lval=0, rval=0;
    char op='0';
    
    std::cin >> lval >> op;     //per ora prendo lval e op
    if(!std::cin) throw parse_error4{"invalid expression"};

    while(op != '='){
        std::cin >> rval;
        if(!std::cin) throw parse_error4{"invalid expression"};

        switch (op) {
            case '+': lval += rval; break;
            case '-': lval -= rval; break;
            case '*': lval *= rval; break;
            case '/': lval /= rval; break;
            default: throw parse_error4{"invalid expression"}; break;
        }

        std::cin >> op;
    }

    std::cout << "result: " << lval << std::endl;
    return 0;
}

int main4() {

    try {
        return evaluate4();
    } catch (parse_error4 const & e){
        std::cerr << e.msg << std::endl;
        return 1;
    }
    return 0;
}

/**
 * problema con questa seconda versione: non c'è la precedenza tra gli operatori. in qualche modo devo "guardare in avanti".
 * se ho 1+2, non devo fare subito la somma, devo guardare cosa c'è dopo il 2.
 * Per questa cosa usiamo le grammatiche e la tokenizzazione.
 * il prossimo step sarà separare l'input in token.
 * 
 * definiamo la struct token e facciamo un vettre di token.
 * il token può essere un operatore o un numero. salvo il tipo di token e il relativo valore
*/
#include<limits>

struct token {

    static constexpr double inf = std::numeric_limits<double>::max(); // static significa che se ho 10 token, ce ne sarà una sola
    token() : m_value(inf), m_type(0) {}; //liste di inizializzazione.
    /**
     * qual è la differenza col costruttore classico 
     * token(){
     *      m_value = inf;
     *      m_type = 0;
     * }
     * 
     * in questo caso, istanzio gli oggetti col valore di default e poi li sovrascrivo, 
     * nel caso precedente li inizializzo direttamente all'inizio.
     * quindi faccio un assegnamento in meno.
    */


    /////////overloading:
    friend std::ostream& operator<<(std::ostream& os, token const & t);
    //friend: non è funzione di classe (è esterna) ma può vedere i membri privati della classe



    double get_value() const {
        // ...
    }
    char get_type() const {
        // ...
    }
    bool is_double() const {
        return m_type == 0 && m_value != inf;
    }
    bool is_open() const {
        return m_type == '(';
    }
    bool is_close() const {
        return m_type == ')';
    }
    bool is_add() const {
        return m_type == '+';
    }
    bool is_sub() const {
        return m_type == '-';
    }
    bool is_mult() const {
        return m_type == '*';
    }
    bool is_div() const {
        return m_type == '/';
    }
    bool is_eq() const {
        return m_type == '=';
    }

    private: 
        double m_value; // value of the double
        char m_type;    // ()*-/+=
};