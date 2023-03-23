/**
 * Lezione prezza 23 marzo 2023
 * 
 * CONTEXT FREE GRAMMARS, ALBERI, CALCOLCATRICE
*/

/**
 * I CTF sono grammatiche utili per scrivere parsers.
 * L'altezza di un albero è il numero di archi tra root e la foglia più lontana (il percorso più lungo).
 * 
 * Per scriverlo, assumiamo che l'albero sia fatto bene (senza errori di parentesi non chiuse etc).
 * la grammatica chiede di generare ricorsivamente i rami (o di esplorarli nel caso di parser). Il
 * codice C++ segue fedelmente questo concetto, per ogni non terminatore ci sarà una chiamata ricorsiva in funzione.
 * 
 * uso µ per indicare la stringa vuota
*/

#include <iostream>
#include <string>
#include <cassert>

int S();

//non prendo parametri perché leggo dallo std input. ritorno il numero di nodi (nel main -1 per il n di archi)
int T(){ 
    // T si asoetta che ci sia una parentesi aperta, in caso contrario lancio un asseert
    char c = 0;
    std::cin >> c; // leggi (
    //gli spazi se ci sono vengono saltati in automatico. la get() non formatta, se si vuole
    assert(c=='(');
    
    int h = S(); //legge l'albero interno
    std::cin >> c; // leggi )
    assert(c==')');

    return h+1;
}

int S(){
    char c = 0;
    std::cin >> c; //vede qual'è la prossima parentesi
    std::cin.putback(c);//la rimette al suo posto. così facendo, può controllare nell'if successivo
                        // quale sia la parentesi mangiata (e lasciarla da dare in pasto a T)

    if (c == '('){
        int h1 = T(); // height of the first tree in the sequence
        int h2 = S(); // height of the tallest tree in the rest of the sequence
        return std::max<int> (h1, h2);
    } 
    else return 0; 
}

int main1(){
    std::cout << "height of the tree = " << (T()-1) << std::endl;
}

/**
 * proviamo ora ad aggiungere numeri o operazioni nei nodi. nelle foglie ci sono i numeri, nei nodi le operazioni
 * 
 * dentro alle foglie scrivo i numeri (terminali, sopra a due foglie metto l'operatore)
 * 
 * ad esempio: (+(+(1)(8))(3)) equivale a (1+8)+3
 * 
 * partiamo assumendo ci siano solo alberi binari. una possibile CFG è la seguente:
 * 
 * E-> (double) | (+EE) | (*EE)
 * 
 * proviamo a scrivere il codice
*/

//consumes an arithmetic tree form std::cin and returns its value
double E(){
    // E-> (double) | (+EE) | (*EE)         E è una chiamata ricorsiva alla funzione, le altre sono input

    char c=0;
    std::cin >> c; //eat (
    assert(c=='(' and "non si può iniziare un albero senza parentesi aperta");

    // esempio 1: +(3.14)(2))
    // esempio 2: *(3.14)(2))
    // esempio 2: 2)

    //mi trovo in uno dei tre casi: la stringa inizia o con cifra o con * o con +
    std::cin >> c;
    assert((c=='+' or c=='*' or (c>='0' and c<='9')) and "mi aspetto o una cifra o un'operazione");

    double res=0;

    if (c>='0' and c<='9'){
        std::cin.putback(c); //lo rimetto nello stream
        std::cin>>res; //leggo un double già formattato
    }
    else if (c=='+'){
        res = E() + E();
    }
    else {
        res = E() * E();
    }
    std::cin>>c; //mangio parentesi chiusa
    return res;
}

int main(){
    std::cout << "insert exp and press ENTER" << std::endl;
    double result  = E();
    std::cout << "result = " << result << std::endl;
}

/**
 * errori tipici sono per esempio dimenticarsi di mangiare la ) e tutti i terminali, o di contare uno dei casi 
 * non terminali, o di ributtare il carattere nello stream
*/

///////////////////////////////////////////////////////////////////////
// LEGGERA ESTENSIONE È AMMETTERE CHE UN NODO ABBIA PIÙ DI UN FIGLIO //
///////////////////////////////////////////////////////////////////////

/**
 * E-> (DOUBLE)  |  (+ES)  |  (*ES)
 * S-> E  |  ES
 * 
 * E è un'espressiione, S è una sequenza di espressioni
 * 
 * next lesson.
*/