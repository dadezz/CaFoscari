/**
 * estendiamo il calculator con le variabili.
 * Prendi codice ulima lezione e aggiungi sta roba.
 * 
 * Scriviamo in pratica una specie di interprete di un linguaggio molto semplice, in cui si puo fare assegnamento di 
 * variavibili.
 * 
 * per esermpio voglio che il mio programma faccia x = (35*5); y =12; p(x) [p sarebbe print]; 
 * si termina il programma con un punto, dopo ogni statement invece un punto e virgola, in stile C
 * 
 * 
 * GRAMMATICA:
 * L -> S. | S;L                    linguaggio (lista di statement)     ----> S;S;S;S;S.
 * E -> P|E + P|E - P               espressione
 * P -> T|P * T|P/T                 produttoria
 * T -> double | (E) | var          termine
 * S -> var = E | p(E)              statement
 * 
 * si noti in p(e) che una var è un'espressione (da E generi P, da P generi T e T finisce in var).
*/


/**
 * devo modificare la classe token. per semplificare, le variabili sono tutte le lettere minuscole tranne la p.
 * aggiungo 
 * 
 * bool is_var() const {return m_type>='a' and m_type <='z' and m_type != 'p'}
 * bool is_print() const {m_type == 'p'}
 * bool is_dot() const {m_type == '.'}
 * char get_var_name() const {return m_type};
 * 
 * 
 * gurdiamo ora T:
 * ho un caso in più: aggiungo 
 * else if (v[i].is_var()){
 *      res = vars[v[i].get_var_name()]; //extracts value of variable with name v[i] mi serve però variabile globale come double vars[256]: uso le variabili come indice nell'array}
 *      i++; //consumes token 'var'
 * }
 * 
 * S:
 * devo aggiungere il non terminale S.
 * 
 * void S (const std::vector<token>& v, int & i){   //void perché gli statements non restituiscono alcun risultato (ricordiamo, in C/++ si)
 *      in quali due casi mi trovo?
 *      if(v[i].is_var()){
 *          //s -> var = E;
 *          char c = v[i].get_var_name();
 *          i += 2; //consume tokens "var" && "="
 *          double res = E(v, i);
 *          vars[c] = res;  // metto il valore nell'array globale con tutti i valori delle espressioni
 *      }
 *      else {
 *          assert(v[i].is_print());
 *          i  += 2; //consumo "p("
 *          double res = E(v, i); //calcolo ricorsivamente l'espressione
 *          i++; //consumo anche la parentesi di chiusura ')'
 *          std::cout<<res<<std::endl;
 *      }
 * }
 * 
 * 
 * manca ora la lista di statements
 * L: ( non mi serve foreard declaration)
 * void L(std::vector<token>& v, int & i){
 *      // L -> S. | S;L
 * 
 *      S(v, i); // consime first statements
 *      if (v[i].is_dot()){
 *          //deo consumare il punto che è un terminale
 *          i++;
 *          return;
 *      }
 *      else {
 *          i++; //consum ';'
 *          L(v, i);
 *      }
 * }
 * 
 * NEL VETTORE IN INPUT VA SEMPRE CONST
 * 
*/


/**      IL MAIN DIVENTA QUINDI
 * MAIN: 
 * int main(){
 *     std::vector<token> tokens;
 *     do {
 * 
 *         token t;
 *         std::cin>>t;            //estraggo il vettore di token
 *         tokens.push_back(t);
 * 
 *     } while(not tokens.back().is_dot()); //ripeto finche l'ultimo token aggiunto non è il punto
 * 
 *     int i = 0;
 *     L(tokens, i);
 *     
 *     return 0;
 * }
*/


/**
 * È carina l'estensione per gli if, nella grammatica cambia solo S
 * 
 * S ->  (COME PRIMA) | IF(E < E){L}
 * (obv posso estendere e non mettere solo il minore).
 * 
 * 
*/