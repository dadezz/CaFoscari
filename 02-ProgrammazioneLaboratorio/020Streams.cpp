#include <fstream>
#include <iostream>
#include <string>
#include <vector>
/**
 * RECAP DEGLI STREAMS
 * 
 * i programmi processano I/O. ci sono pero troppi tipi di input e output (file, rete, tastiera etc).
 * tutti consumano o producono dati, gli stream servono ad astrarre  il concetto di I/O
 * 
 * lo stream è un flusso di dati, una sequenza di byte, che a seconda del parser che abbiamo viene letta in modo diverso
 * 
 * sono una sequenza di byte con segno. se estratti come uint_32_t, venfono estratti blocchi da 4 byte etc.
 * 
 * gli stream hanno dei buffer, che sono una roba che non vediamo, è un'arraty temporaneo in cui vengono salvati i successivi elementi
 * dello stream. La lettura è lenta, per velocizzarla, si usa un buffer. l'idea è la stessa ddella cache
 * 
 * 
 * un po' di strem in c++ sono:
 * istream          tipo genereal edi input (esempio: cin)
 * ostream          "       "      "  output
 * ifstream         input di file
 * ofstream         putput di file
 * istringstream    pesca i dati da una stringa   
 * ostringstream    idem, output
 * 
 * sia if/of che istring/ostring sono sottoclassi di istream/ostream
 * 
 * gli stream non possono essere passati per valore, ma per reference.
 * è un oggetto legsto in modo indissolubile alla periferica fisica, andrebbe copiato anche quello xD.
 * ci troveremmo con due oggetti cout che puntano sullo stesso monitor, quindi anche li si passasse per copia, in realta si influenzano
 * uguale
 * 
 * 
 * gli stream hanno uno stato
 * good()       operation succeed
 * eof()        end of input (end of file)
 * fail()       smthng unexpected happened, per esempio un parser che trova qualcosa di inaspettato
 * bad()        errore come fail ma molto grave (anche periferica rotta)
 * 
 * il casting dello stream a bool, tipo if(std::cin), è convertito a not fail(). non è convertito in good().
 * good() è il not di tutti in and
 * 
 * se facciamo clear(), lo stato dello stream torna good().
 * 
 * std::getline estrae una stringa fino al raggiungimento  di un carattere delimitatore 
 * istream& getline(istream& is, string& str, char delim);
 * 
 * se ho un formato gg/mm/aa, e facessi per esempio getline (, , '/'), il carattere /
 * viene comunque consumata, anche se non viene inserita nel giorno/mese/anno
 * 
*/

int main1(){
    std::ifstream ifs("question.txt");
    std::string line;
    while( std::getline(ifs, line, '\n')){
        std::cout<<"read line is: "<<line<< " -"<<std::endl;
    }
    return 0;
}

/**
 * per scrivere dati non formattati, std::ostream::write()
 * salva dati tali e quali. prende in input un array di char e una lunghezza dello stream.
 * 
*/

int main2(){
    std::vector<int> v{23,145,12,89};
    size_t size = v.size();
    //std::ostream f//("myfile", std::ios::binary);     //importante il flag binary: byte spuri (non devono essere umanamente leggibili)
    //f.write(reinterpret_cast<char const*>(&size), sizeof(size));
        /**
         * sto prendendo l'intero e lo converto in un puntatore a interi.
         * poi lo reinterpreto, da int* a char const*
         * 
         * quindi sul fiile f devo salvare questo array di 8 byte(un intero) e la lunghezza dell'array è 8
        */
   // f.write(reinterpret_cast<char const*>(v.data()), size * sizeof(v.front()));
        /**
         * v.data() restituisce un puntatore ai dati sottostanti del vettore (in sto caso int*).
         * quanto è lungo? size * la lunghezza del primo elemento del vettore
        */
}

////////////////////////////////////////////////////////////////////////////////////////

/**
 * uno stream può essere chiuso con .close(), utile se devo usarli successivamente come se non li avessi usati
 * alla fine di uno scope, viene comunque chiamato il distruttore, quindi il close non è strettamente necessaria
 * 
 * per leggere uno stream non formattato, c'è read (char* s, streamsize n); mi raccomando preallocare s, segmentation fault altrimenti
 * 
 * 
 * EREDITARIETÀ
 * c++ usa una gerarchia di classi
 * tutti gli stream vengono derivati da istream e ostream. cin, istringstream e ifstream, per esempio, possono essere passati alla classe superiore.
 * Non c'è un mismatch di tipi, perché sono tutti sottotipi della stessa classe
*/