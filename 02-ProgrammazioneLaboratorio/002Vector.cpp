/**
 * 20 febbraio 2023
*/

/**
 * passaggio dei parametri per copia: prevede che quando si chiama la funzione 
 * venga allocato lo spazio dei parametri formali, inizializzati valutando l'espressione dei parametri effettivi.
 * 
 * void esempio (int a, double b){
 *      ...
 * }
 * 
 * int main(){
 *      int k; 
 *      ...
 *      esempio(k+3, 25);   // right value
 * }
 * 
 * a e b vengono creati e allocati, inizializzati a k+3 e 25. "copio" appunto il valore delle espressioni.
 * passaggio per copia e per valore sono sinonimi. a e b vengono eliminati dalla memoria alla fine dello scope.
 * 
 * passaggio dei parametri per riferimento:  i parametri formali sono nomi alternativi per i parametri effettivi.
 * c'è un collegamento tra il nome visibile dal sottoprogramma e quello non visibile (fuori dallo scope).
 * 
 * void esempio_ref (int & a, double & p){
 *      ...
 * }
 * 
 * int main(){
 *      int x;
 *      double p;
 *      ...
 *      esempio_ref(x, p);      //left value
 * }
 * 
 * modificando a e b dentro la funzione, modifico anche x e p del chiamante. a e b non viene allocato in memoria. se avessi un
 * parametro effettivo di un megabyte, dovrei copiarlo tutto, ma nel passaggio per referenza ciò non avviene.
 * c'è un'attenzione maggiore sui tipi a questo punto. mi interessa infatti in questo caso il left value.
 * ugualmente, non posso mettere un int dove c'è un double. il casting vale solo nel caso di right value.
 * 
*/

// some examples 

typedef struct s{
    int a;
    double b;
} ts;

void f0(ts x){
    x.a = 12;
    x.b = 12.3;
}

int main0(){ //codice C
    ts y;
    f0(y);
}
/**
 * in questa chiamata, i campi di y non vengono modificati, perché c'è passaggio per copia
*/

void f1(ts & x){
    x.a = 12;
    x.b = 12.3;
}

int main1(){ //codice C++
    ts y;
    f1(y);
}
/**
 * in questa chiamata, i campi di y vengono modificati, perché c'è passaggio per indirizzo.
*/

ts f2(ts x){
    x.a = x.a+2;
    x.b = x.b*2;
    return x;
}

int main2(){
    ts y, w;
    y.a=4, y.b = 3.0;
    w=f2(y);
}
/**
 * si copia bit per bit l'oggetto.
*/
typedef struct s1{
    int a;
    double b[40];
} ts1;
/**
 * se struct s fosse così definita, quando passo su x, copio tutti e 40 i double?
 * quando passo un array in C in realtà passo l'indirizzo di memoria del primo elemento dell'arrray.
 * 
 * Se il vettore fosse passato da solo, in C, copio l'indirizzo di memoria, quindi un for in f() modificherebbe il vettore,
 * se passo la struct, copio tutti e 40 i valori del vettore perché la struct prevale sull'array. 
 * 
 * In c++, si migliora sta cosa, non usando gli array alla C, e si fa in modo che se si vuole fare
 *  un passaggio per copia, avvenga sempre la copia, se si fa un passaggio per indirizzo si copi l'indirizzo, non quella cosa ibrida 
 * che si usa in C.
 * 
 * La semantica del C per questo non la useremo (nonostante sia compatibile col C++)
*/

/**
 * come rimpiazzo gli array?
 * uso la standard library.
*/
#include<vector>

int main(){
    std::vector <double> v; //v è un vettore di double.
    /**
     * la caratteristica di dichiarare l'oggetto vector con la possibilità di inserire il tipo, si chiama template.
     * per esempio se si volesse fare un algoritmo sull'intersezione tra insiemi, esso funzionerebbe in ogni caso sia con
     * double, con int, con stringhe etc etc.
     * è possibile quindi scrivere un algoritmo che valga per tutto, a cui di volta in volta si passa il tipo che serve.
    */

    //non ho specificato la grandezza dell'array, ma posso.
    //tuttavia, specificare la lunghezza in c++ non è importante.
    std::vector <double> v2(20);
    
    // per aggiungere un elemento in fondo all'array, non dobbiamo preoccuparci dello spazio
    //chiaro che v sta in memoria dinamica, non nello stack.
    v.push_back(13.14);
 
    /**
     * da notare l'utilizzo del punto: dentro le struct in C++ ci possono essere sia variabili che funzioni (metodi).
    */

    //è ancora possibile chiamare un elemento dell'array tramite
    v[0] = 15.1;

    //tenderemo però a non usarlo, preferendo
    v.at(0) = 15.1;
    //perché v[] non controlla se l'indice esista nel vettore, mentre at controlla e in caso manda un eccezione.
    //ovviamente, at è più lento di []. Se si è 100% certi della posizione e ci sono problemi di performance, conviene [].

    //quando ho un vettore c-like, se lo passo come parametro mi serve la lunghezza, in questo caso è invece compresa nella struttura
    v.size();

    //per rimuovere l'ultimo elemento dal vettore
    v.pop_back();

    /**
     * un vettore passato per copia viene copiato completamente.
    */  
}




