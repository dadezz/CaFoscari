/**
 * 08 marzo 2023
 * IMPLEMENTAZIONE STRINGHE PASCAL
 * pascal aveva linguaggio stringa nativo, lungo al max 255 caratteri, e il primo carattere era interpretato come numero 
 * dei caratteri all'interno della stringa (quindi non finiva con \0 e si contavano le lettere a partire dalla posizione 1).
*/
#include<string>
#include<iostream>
class string_pascal1 {
    public:
        void print(){

        }
        void set(const std::string & s);
        void setchar(int pos, char c){

        }
        char getchar(int pos){
            return ;
        }
        void setsize(int dim){

        }
    private:
        char buff[256];
};

/**
 * voglio implementare la funzione FUORI dalla classe, e nella classe dichiararla e basta.
 * in questo modo posso mettere la classe nell'header, per dire all'utente come usare l'oggetto,
 * nascondendo l'implementazione del metodo
*/
void string_pascal1::set(const std::string & s){
    if (s.length()<= 255) buff[0] = s.length();
    else buff[0] = 255; //tronco la stringa
    for (int i = 1; i<=buff[0]; i++){
        buff[i] = s.at(i-1);
    }
}
void string_pascal1::print(){
    for (int i=1; i<=buff[0]; i++){
        std::cout<<buff[i];
    }
}

int main(){
    string_pascal1 p;
    string_pascal1 z;
    p.set("Hello");
    p.setchar(1, 'b');
    p.print();

    p = z; // è lecito, copia carattere per carattere i due buffer, perché la semantica dell'assegnamento tra
            // struct o classi è copiare bit per bit lo stato di destra dentro quello di sinistra.
            // obv in caso di puntatore copio il puntatore, non l'oggetto puntato. Si chiama shallow copy, 
            // il contrario è deep copy, non supportata su cpp, ma impareremo come ridefinire l'assegnamento
            // e istruire cpp a fare deep copy (glielo dico io come).
} 

/**
 * quando dichiariamo un vector, è di dimensione 0, idem per la stringa. come faccio a inizializzare in qualche modo l'oggetto quando 
 * lo dichiaro e basta?
 * 
 * il metodo in questione si chiama costruttore. Costruttore = metodo chiamato ogniqualvolta si istanzia l'oggetto di una classe.
 * deve chiamarsi con lo stesso nome della classe e non ritornare nulla. Se non ha alcun parametro formale, viene chiamato costruttore di
 * default (default constructor). se non si definisce alcun costruttore, cpp aggiunge il costruttore di default.
 * se invece di definisce almeno un costruttore, anche con parametri, vanno definiti tutti i costruttori, default compreso, perchè cpp
 * non lo mette più al posto nostro.
 * 
 * Il costruttore viene chiamato in modo automatico quando si istanzia un oggetto di una classe. (dichiarazione o new).
 * Senza il costruttore sono comunque autorizzato a dichiarare l'oggetto ma non inizializzato.
*/


class string_pascal{
    public:
        string_pascal();//costruttore. anche questo può andare fuori
        string_pascal(const std::string & s);
        string_pascal(const string_pascal & s); // costruttore per copia, importantissimo, essenziale per il passaggio per copia
                    // esempio: se passassi per copia come definito da C, copiereitutti i 256 caratteri.
                    // mi serve o posso semplicemente copiare solo la stringa che ho?
                    // il copy constructor mi ridefinisce il passaggio per copia
        void print();
        void set(const std::string & s);
        void setchar(int pos, char c){

        }
        char getchar(int pos){
            return ;
        }
        void setsize(int dim){

        }
    private:
        char buff[256];
};

string_pascal::string_pascal(){
    buff[0] = 0; // il costruttore mette lunghezza = 0
}
/**
 * Naturalmente, i costruttori possono ricevere anche parametri,
 * richiamando anche funzioni dell'oggetto stesso.
 * 
 * Notare che i due costruttori hanno lo stesso nome, ma si differenziano per i parametri formali.
 * Tecnica chiamata overloading dei metodi. 
*/
string_pascal::string_pascal(const std::string & s){
    set(s);
}
string_pascal::string_pascal(const string_pascal & s){
    /**
     * quando parlo di buff, parlo del mio o di s? 
     * se non dico nulla è dell'oggetto che sto creando, altrimenti chiamo l'oggetto.
     * ma buff non è privato? oggetti appartenti alla stessa classe possono modificare attributi privati
     * di altri oggetti della stessa classe
    */
    buff[0] = s.buff[0];
    for (int i = 1; i <= buff[0]; i++){
        buff[i] = s.buff[i];
    }
}
void string_pascal::set(const std::string & s){
    if (s.length()<= 255) buff[0] = s.length();
    else buff[0] = 255; //tronco la stringa
    for (int i = 1; i<=buff[0]; i++){
        buff[i] = s.at(i-1);
    }
}
void string_pascal::print(){
    for (int i=1; i<=buff[0]; i++){
        std::cout<<buff[i];
    }
}

int main(){
    string_pascal a;
    string_pascal * p = new string_pascal;  // la new è intelligente, chiama in automatico il costruttore
                                              // ricordiamo la definizione di oggetto: sia p che il new sono 2 oggetti
    std::string jy = "erga" ;
    string_pascal u = jy; //mi richiama il costruttore con parametro
 
}