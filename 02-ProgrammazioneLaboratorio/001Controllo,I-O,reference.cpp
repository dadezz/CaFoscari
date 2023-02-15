#include<iostream>
using namespace std;
/**
 * definizione delle costanti in C:
*/
const int z = 7;

//oppure 

#define z 7

/**
 * in c++ c'è una modalità più elegante
*/

constexpr int k = 7; 

/**
 * Oggi si parla in realtà di strutture di controllo.
 * Esistono usi preferenziali dei cicli. Per esempio, qualsiasi ciclo for può essere riscritto come while (e viceversa).
 * ma allora perché ci son 2 cicli? c'è un uso preferenziale.
 * La regola è che le variabili che vengono consultate dentro la condizione del for possono essere modificate soltanto nella 
 * epressione di iterazione 
 * (=> dall'intestazione del for posso già capire quanti sono i passi del ciclo).
 * La differenza fondamentale nell'analisi dei due cicli è la terminazione. Nel caso del ciclo, la terminazione deve essere ovvia.
 * Nel blocco non vanno mai alterate le variabili di condizione.
 * Inoltre, bisogna tendere a evitare l'utilizzo di "break" e "continue".
 * Questo perché nel corso si impara la programmazione strutturata, quindi senza salti incondizionati (no goto etc).
 * 
 * Qualsiasi codice che contiene qualsiasi utilizzo di salti incondizionati, può essere scritto usando i paradigmi della programmazione condizionata
 * TEOREMA DI BOHM-JACOPINI
 * 
 * Naturalmente ci sono casi in cui potrei usare sia il while che il for, è buona regola che dove si può fare il for ci sia il for.
 * 
 * LINGUAGGIO TURING-COMPLETO
 * massima espressività per un linguaggio. Il while garantisce la turing-completezza, il for (utilizzato bene) non ha la medesima espressibìvità.
 * 
 * invariante di un ciclo: vera immediatamente prima dell'esecuzione del ciclo e vera lungo tutta l'esecuzione del ciclo.
 * per esempio: 
*/

int main(){
    int v[20];
    bool resp = false;
    int i = 0;
    while (i<20 && !resp){
        if (v[i] == 5){
            resp = true;
        }
        i++;
    }
    if (resp)
        cout<<"presente";
    else 
        cout<<"non presente";


/**
 * si noti che sia i che resp sono invarianti del ciclo. Infatti, nella condizione del cout avrei potuto tranquillamente inserire i invece di resp
 * 
*/

    int a;
    int b;

    //MCD
    while(a!=b){
        if (a>b)
            a = a-b;
        else
            b = b-a;
    }

    cout<<a;

/**
 * l'invariante del ciclo è ciò che fa sì che il ciclo funzioni. in questo caso mcd è l'invariante di ciclo.
 * Se voglio vedere che il ciclo calcoli proprio mcd, metto mcd come condizione del ciclo. Se mcd cambia, allora non è l'invariante...
 * se il ciclo continuasse oltre alla condizione, l'invariante varierebbe.
 * 
 * nel trovare il numero più grande di un array, qual è l'invariante del ciclo?
 * bisogna ragionare pensando di essere nel bel mezzo del ciclo. sto scorrendo il vettore. all'inizio ho scorso il primo elemento. e il primo
 * elemento è il più grande. vado un po'avanti e controllo l'altezza e così via. é vero che x è sempre il più grande della porzione che ho guardato?
 * si. max è l'invariante del ciclo, perché è sempre il massimo della porzione che ho visitato.
 * 
 * l'invariante del ciclo è una proprietà, non un valore. il contenuto di max è sempre l'elemento più grande, anche se cambia durante le iterazioni.
 * 
*/

/**
 * INPUTOUTPUT:
 * si usa la libreria iostream.
 * tutti i nomi della standard library si usano nello spazio dei nomi chiamato std.
 * 
 * da cui:
*/

    std :: cin >> a;
    std :: cout << a;

    // "usando lo standard namespace, prendimi la funzione che si chiama cin".

    /**
     * si noti che non c'è necessità di specificare il tipo, l'operatore di flusso >> sa farlo in automatico.
    */

    std :: cout << "hello" << a << " " << b << std :: endl;

    // c'è  differenza tra \n e endl, perché endl fa il flush dell'output.

    /**
     * si può evitare di usare std :: ogni volta, usando all'inizio "using namespace std". non è però consigliabile, 
     * in quanto, essendo tantissimi nomi nel namespace, c'è alta probabilità di conflitto.
    */

/**
 * REFERENCE:
 * caratteristica tipica del c++, per evitare l'utilizzo dei puntatori.
 * INtroduco un nuovo nome, non allocato in memoria, che è un nuovo nome per qualcosa che esiste già
*/

    double s;
    double & d = s; // d è un modo diverso di chiamare s. 
        //una reference va inizializzata al momento della dichiarazione.
    double f = 3.14;
    d = f; // modifica sia a che b, perché sono la stessa cosa. 
}
/**
 * viste così nn sono molto utili le reference. 
 * quando uso la reference, nessuno mi dice che debba avere lo stesso scope della variabile a cui fa riferimento. Ecco che posso 
 * usarle nelle funzioni in modo super fico
*/
void swap (int & a , int & b){
    //vengono stanziate le reference a e b: nomi alternativi per a e y. Significa che quando modifico a e b
    //sto modificando rispettivametne x e y, perché sono la stessa cosa.
    //quando termina la funzione, i nomi vengono buttati ma non devo liberare nulla in memoria, perché
    //sono solo dei segnaposti. 
    //il tutto quindi senza usare i puntatori.
    int c;
    c = a;
    a = b;
    b = c;
}

int main2(){
    int x = 3, y = 4;
    swap (x, y);
    std :: cout << x << " " << y << std :: endl;
    /**
     * questo meccanismo di passaggio dei parametri prende il nome di "passaggio per referenza" o "passaggio per indirizzo".
     * 
     * la reference viene inizializzata con un left value, i parametri devono essere variabili vere e proprie, non posso mettere
     * swap(x+5, y) o simili.
     * 
     * Nel passaggio per copia, il parametro sarebbe right value. 
    */

}