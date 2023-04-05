#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cassert>

/**
 * XML è utile per storare dati leggibili dalla macchina e dall'uomo senza problemi
 * 
 * <note>
 *      <to> Tove </to>
 *      <from> Jani </Jani>
 *      <heading> Reminder</heading>
 *      <body>Don't forget me this weekend</body>
 * </note>
 * 
 * si nota facilmente che è un albero: dalla radice note ci sono dei nodi (to, from, geading, body etc). È ovviametne possibile 
 * annidarne altri
 * 
 * <person gender="female"> ogni tag può avere un attributo. questo puo essere tra apici o tra virgolette.
 * Esistono i tag unari <iurng/>
 * 
 * 
 * GRAMMATICA:
 * assumiamo di aver eliminato i commenti e il preambolo iniziale. chiamiamo tree il non terminale iniziale. X e Y delle stringhe, S e A non terminali
 * 
 * T -> <XA>TS</X>  |   <XA>Y</X>   |   <XA/>
 * S -> µ   |   TS                                      //lista vuota oppure albero seguito da una lista di alberi
 * A -> µ   |   X="Y"A   |   X='Y'A                      //lista di attributi
*/


// XML tutorial: https://www.w3schools.com/xml/
// XML viewer online: https://countwordsfree.com/xmlviewer
// dataset:
// https://aiweb.cs.washington.edu/research/projects/xmltk/xmldata/data/mondial/mondial-3.0.xml

/*
    XML Grammar (after removing comments and XML preamble):

    note: X,Y are not nonterminals: they stand for "any string"

    A tree is either an enclosed sequence of trees (S)
    or an enclosed string (leaf) or self-closing tag.
    T -> <X A> TS </X> | <X A> Y </X> | <X A/>

    sequence of trees
    S -> epsilon | TS

    a list of attributes
    A -> epsilon | X="Y" A | X='Y' A
 */

struct keyvalue {
    std::string key;
    std::string val;
};

std::vector<keyvalue> kv;

struct parse_error {
    std::string msg;
};

// check if 'read' and 'expected' characters match
void check(char read, char expected) {
    std::string err{"Parse error. Read: '"};
    err += read;
    err.append("'. Expected: '");
    err += expected;
    err.append("'.");
    if (read != expected) throw parse_error{err};
}

// removes from std::cin:
// 1) the XML preamble <?xml string ?>
// 2) all comments, of the form   <!-- string -->
std::string remove_comments() {
    std::string res;

    while (std::cin) {
        char c1 = 0, c2 = 0;
        c1 = std::cin.get();

        if (c1 == '<') {
            c2 = std::cin.get();

            if (c2 == '!' or c2 == '?') {
                char buf[2];
                buf[0] = std::cin.get();
                buf[1] = std::cin.get();

                int i = 0;  // start position in buf

                while (not((buf[i % 2] == '-' and buf[(i + 1) % 2] == '>') or
                           (buf[i % 2] == '?' and buf[(i + 1) % 2] == '>'))) {
                    buf[i % 2] = std::cin.get();
                    i++;
                }

            } else {
                res += c1;
                res += c2;
            }

        } else {
            if (not std::cin.eof()) res += c1;
        }
    }

    return res;
}

void T(std::istream&);

void S(std::istream& is) {
    //un T inizia sempre con <nome ...
    //caso µ: inizia con </nome>
    //S -> µ | TS
    //notare che s non consuma caratteri, ma chiama solo recorsivamente

    char c1 = 0; char c2 = 0;
    is >> c1 >> c2;
    is.putback(c2);
    is.putback(c1);

    if (c1 == '<' and c2 != '/'){
        T(is);  // i non terminali prendono in input uno stream, il cin vien fatto nel main
        S(is);
    }

};

void A(std::istream& is) {};

void T(std::istream& is) {
    //T -> <X A> TS </X> | <X A > Y </X> | <X A/>

    //ci mangiamo la parentesi <
    char c = 0;
    is >> c;
    check(c, '<');
    //step successivo è estrarre tutto fino alla prima parentesi triangolare chiusa

    std::string tag;
    std::getline(is, tag, '>'); // estraggo "X A>" oppure "X A/>"
                                //ricordiamo che il carattere > non sarà estratto

    // mi creo un istringstream con tag appena creato
    std::istringstream iss{tag};
    std::string X1;
    //posso estrarre la x con la getline e spazio come separatore
    std::getline(iss, X1, ' ');
    //iss ora contiene 'A' oppure 'A/'
    //posso chiamare ora il non terminale A
    A(iss);
};

// 1) parses the XML from std::cin, checking some (not all) format errors
// 2) extract all values of attributes "population" and stores them as integers to file "population"
// 3) loads back the integers from file "population" and stores them in a vector.

int main() {
    std::string xml = remove_comments();
    std::istringstream iss{xml};
    try {
        T(iss);
    } catch (const parse_error& e) {
        std::cout << e.msg << std::endl;
        return 1;
    }
    std::cout << "XML is in correct format." << std::endl;

    std::vector<uint64_t> population;
    for (auto p : kv) {  // extract all populations
        if (p.key == "population") population.push_back(stoi(p.val));
    }
    uint64_t N = population.size();

    // store populations in a binary file called "population"
    std::ofstream ofs{"population", std::ios::binary};
    ofs.write(reinterpret_cast<const char*>(population.data()), N * sizeof(uint64_t));
    ofs.close();

    // read back populations from file and store them in a new vector
    std::ifstream ifs{"population", std::ios::binary};
    std::vector<uint64_t> population2(N, 0);
    ifs.read(reinterpret_cast<char*>(population2.data()), N * sizeof(uint64_t));
    ifs.close();

    assert(population == population2);
    return 0;
}