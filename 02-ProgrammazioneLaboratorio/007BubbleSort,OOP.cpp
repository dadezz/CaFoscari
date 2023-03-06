/**
 * 6 marzo 2023
 * 
 * lezione divisa in due: 
 * 1. ordinamento vettore
 * 2. OOP
*/

#include <iostream>
#include <vector>

/**
 * BUBBLE SORT
 * Algoritmo di ordinamento.
 * vogliamo modificare l'array senza crearne una copia, in modo tale che sia ordinato.
 * viene definito ordinamento sul posto percHé non duplica nulla.
 * Prendiamo l'array e immaginiamo di averlo diviso in due parti.
 * la prima delle due è ordinata e la seconda no, e contiene solo elementi più grandi della prima parte
 * 
 * questo è l'invariante del ciclo che andrà a costituire l'algoritmo. Il divisore delle due parti si chiama soglia.
 * 
 * L'idea è: prendi il numero più piccolo della parte disordinata, lo metti nella posizione subito dopo la soglia
 * e sposti la soglia avanti di uno.
*/

int indice_minimo(const std::vector<int> & vettore, int partenza){
    int i_minimo = partenza;
    for (int i = partenza+1; i<vettore.size(); i++){
        if (vettore.at(i) < vettore.at(i_minimo))
            i_minimo = i;
    }
    return i_minimo;
}

void bubble_sort_minimo (std::vector<int> & vettore){
    //trovo indice minimo e swappo con soglia
}

/**
 * questo qui sopra è il metodo più intuitivo per farlo.
 * quando però il bubble sort è stato creato, le cose erano salvate su nastri magnetici, 
 * quindi c'era la necessità di mantenere il principio di località spaziale (idem per la cache attuale), 
 * così da non dover riavvolgere il nastro.
 * Il bubble sort scambia sempre celle vicine tra loro, e quindi produce meno cache miss rispetto al metodo qui sopra.
*/

//vediamo quindi come portare giù in soglia.

/**
 * parte dalla fine dell'array e confronta gli ultimi 2 elementi. Se sono ordinati non fa nulla, altrimenti li scambia.
 * a sto punto controlla la coppia successiva, e così via. in questo modo, l'elemento più piccolo lo porto
 * via via piu vicino alla soglia. alla fine oltre la soglia non vado a vedere, lavoro sempre nella parte più alta.
 * 
 * nota: si chiama bubble sort perché ogni numero è una bolla, hanno un peso che dipende dal numero e mano a mano si fanno
 * salire le bolle dalla più leggera alla più pesante.
 * 
 * quanti accessi faccio alla memoria?
 * più o meno, la somma dei primi n numeri naturali, quindi grosso modo un numero di accessi che dipende dal quadrato della lunghezza
 * dell'array. N**2.
 * Ordinare l'array sul posto col bubble sort è estremamente dispendioso. ANche il quick sort, nel caso peggiore è n**2. per scendere di
 * complessità, devo investire in memoria e non ordinare sul posto.
 * 
 * (così per curiosità, un ordinamento fattoriale, ben peggiore, sarebbe provare tutte le permutazioni controllando se sono
 * ordinate)
*/

void scambia();

void bubble_sort(std::vector<int> & v){
    int soglia = 0; //il vettore è ordinato nell'intervallo [0, soglia[.

    //un ciclo spinge soglia dall'inizio alla fine dell'array
    for(; soglia < v.size(); soglia++){     //dovrebbe essere minore uguale, ma posso mettere minore:
                                            //se ho tutti gli elementi meno uno ordinati e l'ultimo è il più grande, è anch'esso ordinato.
        for (int i = v.size()-1; i>soglia; i--){
            if(v.at(i) < v.at(i-1)) 
                scambia();
        }
    }
}

/**
 * TODO: nel caso in cui il ciclo interno non faccia nemmeno uno swap, voglio che l'algoritmo capisca che la parte
 * disordinata in realtà è anch'essa ordinata, quindi non è più necessario portare avanti la soglia e si può uscire dal ciclo.
 * (obv è da usare un while, per l'uso preferenziale del ciclo for).
 * 
 * provare anche a invertire l'algoritmo, ordinando prima i grandi e poi i piccoli.
*/

/**
 *  OOP. eravamo rimasti alla struct. 
*/

struct Punto {
    double x;
    double y;
    void trasla(double dx, double dy){
        this->x+=dx; //il this-> non è obbligatorio, è come il self di py.
        y+=dy;
    }
};


int main1(){
    Punto a, b; //non è necessario "struct" in cpp
    a.x = 10;
    a.y = 20;
    b.x = 4;
    b.y = 6;
    a.trasla(-2, 10.5); // a.x = 8; a.y = 30.5
    return 0;
}

/**
 * molto simile alla keyword struct c'è la keyword class.
 * C'è la differenza che nel codice del main1 non funziona più nulla.
 * i campi x e y sono infatti protetti. non possono essere letti o scritti all'infuori della classe.
 * se volessi rendere tutto pubblico dovrei mettere public:
*/

class punto {
    public: 
        double x;
        double y;
        void trasla(double dx, double dy){
            this->x+=dx; //il this-> non è obbligatorio, è come il self di py.
            y+=dy;
        }
};

/**
 * per quale ragione vogliamo rendere privato qualcosa? 
*/

class adv {
    public:
        void setxy(double nx, double ny){
            x = nx;
            y = ny;
        }
        double getx(){
            return x;
        }
        double gety(){
            return y;
        }
        void trasla(double dx, double dy){
            this->x+=dx; //il this-> non è obbligatorio, è come il self di py.
            y+=dy;
        }
    private: 
        double x;
        double y;
};

/**
 * chi utilizzerà un oggetto adv non potrà direttamente scrivere dentro x o y, in modo da preservarmi da possibili errori
*/

int main2(){
    adv a;
    a.setxy(10, 20);
    a.trasla(2, 10.5);
    std::cout<<a.getx()<<" "<<a.gety()<<std::endl;
   // a.x = 15;  ERRORE
}

/**
 * un vantaggio reale è creare una funzione con firma uguale pubblica che però in privato gestisca sia coordinate polari che cartesiane.
 * vedremo prox lez
*/