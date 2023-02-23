/**
 * vogliamo estrarre una carta in modo che non venga riestratta.
 * Va deciso come codificare le informazioni, scegliendo la struttura dati corretta.
 * ci serve il mazzo di carte.
 * ci serve la carta estratta.
 * ci serve il mazzo di carte già estratto.
 * 
 * Tipicamente viene in mente di tenere un vettore di 40 booleani estratta/no, e controllare ogni volta che si 
 * estrae randomicamente se è estratta o meno. soluzione estremamente inefficiente, percHé il numero di prove 
 * fatte aumenta moltissimo per ogni estrazione, non scala (si immagini l'ultima estrazione, ha probabilità 1/40).
 * 
 * Una soluzione molto migliore è avere un array di interi. seleziono numero casuale tra zero e size-1.
 * questo numero, lo metto in ultima posizione e l'ultimo elemento lo metto nella posizione estratta.
 * mi segno poi che l'ultima posizione è una in meno.
*/

#include<vector>
#include<iostream>
#include<cstdlib> //porting della libreria C stdlib.h per C++
#include<ctime>

void inizializza(std::vector<int> & v, int carte){
    v.resize(carte);
    for(int i=0; i<carte; i++){
        v.at(i) = i+1;
    }
}

void stampa(std::vector<int> v){ //metto reference o copia? la copia è inefficiente, ma la reference mette in dubbio il chiamante
    std::cout<<"[ ";
    for(int i=0; i<v.size(); i++){
        std::cout<<v.at(i)<<' ';
    }
    std::cout<<" ]"<<std::endl;
}

int estrai(std::vector<int> & v){
    int daestrarre = rand()%v.size();
    int result = v.at(daestrarre);
    v.at(daestrarre) = v.at(v.size()-1); // non mi serve in realtà aggiungere in coda la carta estratta.
    v.pop_back();
    return result;
}

int main(){
    std::vector<int> mazzo;
    int ncarte;
    std::cin>>ncarte;

    inizializza(mazzo, ncarte);
    stampa(mazzo);

    srand(time(NULL));

    for (int i=0; i<ncarte; i++){
        std::cout<<"estratta:\t"<<estrai(mazzo)<<std::endl;
    }
    stampa(mazzo);

    return 0;
}

/**
 * come risolvere il problema stampa? io voglio usare la reference ma garantire al chiamante che non modifichero il parametro
 * 
 * Esiste apposta la parola chiave const per questo motivo.
*/

void stampa1(const std::vector<int> & v);
/**
 * se provassi nel corpo della funzione a modificare v, avrei un errore.
 * in questo modo mi evito la copia e mi assicuro comunque che non venga modificato.
 * Non ha molto senso usarla per tipi piccoli (interi etc), ha moltissimo senso per vettori etc.
 * I const possono essere letti e non scritti.
*/