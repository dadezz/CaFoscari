#include <fstream>
#include <iostream>
#include <string>
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
*/