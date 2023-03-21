#include <iostream>
#include <string>
#include <limits>
#include <assert.h>
#include <vector>

struct token {

    static constexpr double inf = std::numeric_limits<double>::max(); // static significa che se ho 10 token, ce ne sarà una sola
    token() : m_value(inf), m_type(0) {}; //liste di inizializzazione.


    /**
     * ho bisogno di fare cin>>token e cout<<token, in modo che venga riconosciuto.
     * ridefinisco quindi con l'overloading
    */
    /////////overloading:
    friend std::ostream& operator<<(std::ostream& os, token const & t);
    //friend: non è funzione di classe (è esterna) ma può vedere i membri privati della classe

    friend std::istream & operator>>(std::istream & is, token & t);



    double get_value() const {
        assert(is_double());
        return m_value;
    }
    char get_type() const {
        assert(not is_double());
        return m_type;
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

std::ostream & operator<<(std::ostream & os, token const & t){ 
    //gli stream vanno sempre passati per reference
    //il token lo passiamo per reference percHé non voglio copiar tutto, e lo passo const percHé modifica stream, non token
    //il tipo restituito dalla funzione operator<< (che è parola chiave di cpp) deve essere di tipo std::ostream &, così si permette l'associativita
    os << "[m_value = "<<t.m_value << ", m_type = " << t.m_type << "]";
    return os;
}
std::istream & operator>>(std::istream & is, token & t){
    //stavolta token non è const perché modifico.
    /**
     * caso 1: 5.14+....
     * caso 2: +3....
    */

    char c;
    is >> c;
    if((c >= '0' && c <= '9') or c == '.'){ // caso 1: inizio con un numero (positivo)

    }
}


int main(){
    std::vector<token> tokens;
    do{
        token t;
        std::cin >> t;
        tokens.push_back(t);
        std::cout << t << std::endl;
    } while(not tokens.back().is_eq());
}


/**
 * context free grammars
 * 
 * le espressioni sono alberi. i nodi che hanno figli sono operatori, le foglie sono numeri.
 * la struttura dell'albero codifica la precedenza degli operatori.
 * 
 * Vediamo un esempio di CFG per generare stringhe palindorme
 * 
 * P -> µ | aPa | bPb | a | b.      (µ = stringa vuota)
 * 
 * qualsiasi cammino si scelga nell'espressione ricorsiva è un palindromo sull'alfabeto [a, b].
 * 
 * a -> aPa -> abPba -> abµba -> abba. 
 * 
 * le grammatiche possono essere usate dall'alto al basso ("generazione"). i parser fanno il contrario, partono dalla stringa
 * e seguono la derivazione al contrario. durante la risalita si collezionano informazioni utili sulla stringa.
 * 
 * Un altra grammatica per i palindromi è con più non-terminali
 * 
 * P -> µ | aA | bB | a | b
 * A -> Pa
 * B -> Pb
 * 
 * questa è equivalente alla precedente, ma usa più non-terminali (come servirà a noi)
 * 
 * P -> aA -> aPa -> abBa -> abPba -> abµba -> abba.
 * 
 * g++ cosa fa in pratica? prende in input la stringa e ci calcola una grammatica sopra (nelle slide, una grammatica semplificata del linguaggio C.
 * 
 * 
 * un esempio di CFG: balanced parentheses sequence
 * 
 * visit (u):
 *      if u == TERMINATORE : return;
 *      print (
 *      visit(u.left)
 *      visit(u.right)
 *      print )
 * 
 * main:
 *      visit(root)
 * 
 * guardo la radice: ci stampo la ( iniziale e la ) finale.
 * chiamo ricorsivamente i figli e ci stampo le rispettive parentesi
 * (()())
 * 122331
 *          (1)
 *         /   \ 
 *       (2)   (3)
 *       / \   / \ 
 *      T   T T   T
 * 
 * e cosi via. ( in questo caso termina qui, coi terminatori T finali).
 * 
 * Proviamo intanto a calcolarne l'altezza. 
 * Primo step: scrivere un programma che costruisca parentesi bilanciate
 * 
 * 
 * T -> (S)
 * S -> µ | TS
 * 
 * (intuitivamente, T é un albero, S è una sequenza di alberi. T alla fin fine genera un albero con le parentesi e basta, è S che fa il resto della sequenza)
 * 
 * ( ( ) ( ( ) ) ( ) )  proviamo a derivare questo albero con la regola sopra
 * 
 * T -> (S) -> (TS) -> ((S)S) -> ((µ)TS) -> (()(S)(S)) -> (()(TS)(µ)) -> (()((S))()) -> (()((µ))()) -> ( ( ) ( ( ) ) ( ) )
 * 
 * Come tradurlo in C++?
 * 
 * beh, uso le due funzioni T e S, che restituiscono la altezza dell'albero. In S, se sono in µ, l'albero è alto 0 (caso base), nell'altro ci 
 * sarà l'altezza massima del ramo più alto tra la chiamata ricorsiva di T e di S. In T, restituisco 1 + chiamata ricorsiva di S.
 * 
 * il caso di ricorsione è un po' più complicato del solito, percHé è un ciclo di ricorsione, si rischia il loop infinito. in questo caso comunque c'è il
 * terminatore µ.
 * 
 * Piccola nota: noi stiamo calcolando il numero di nodi, ma siccome l'altezza è definita come numero di archi, basta fare T() -1 nel main.
 * 
 * SOLO la funzione T consuma parentesi dallo standard input, S non consuma simboli in input. Ha però bisogno di leggere l'input senza consumarlo 
 * (per capire quali sono i due casi).
*/