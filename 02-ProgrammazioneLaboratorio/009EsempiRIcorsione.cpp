#include <iostream>
#include <string>
#include <vector>

using std::vector; using std::string; using std::cout; using std::cin; using std::endl;

/**
 * binary search:
 * returns the position of x onto the vector if x is found, -1 otherwise
*/
int binary_search_aux(const vector<int> & a, int x, int lo, int hi){
    if (lo > hi) return -1;

    int mid = (hi+lo)/2;
    if (x == a.at(mid)) return mid;
    else {
        if (a.at(mid) < x) return binary_search_aux(a, x, mid, hi);
        else return binary_search_aux(a, x, lo, mid);
    }
}
int binary_search(const vector<int> & a, int x){
    return binary_search_aux(a, x, 0, a.size()-1);
}

/**
 * bubble sort ricorsivo
*/
void swap(int* a, int n){
    //moves a[0] in the correct position inside a
    if (n<=1) return;
    //a has at least 2 elements
    if (a[1] < a[0]) {
        int aux = a[0];
        a[0] = a[1];
        a[1] = aux;
        swap(a+1, n-1);
    }

}
void sort(int* a, int n){
    if (n<=1) return;
    sort (a+1, n-1);
    swap(a, n);
}

/**
 * integer to base 2
*/
string bin(uint64_t n){
    if (n==0) return "0";
    if (n==1) return "1";
    return bin(n/2) + (n%2 ? string{"1"} : string{"0"});
}

int main0(){
    int a[] = {8, -1, 0, 17, 19, 2};
    int dim = sizeof(a)/sizeof(int);

    sort(a, dim);
    cout<<"lmao"<<endl;

    for(auto each:a) {
        cout<<" "<<each<<" ";
    }
    cout<<endl;
    long int n = 23574733562;
    string s;
    s = bin(n);
    cout << s << endl;
    return 0;
}

/**
 * next time we'll see some example where recursive functs calls others recursive functs and viceversa.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Exercises

/**
 * Il massimo comune divisore MCD(a,b) tra due interi a <= b si calcola ricorsivamente 
 * con l'algoritmo di Euclide come segue: se a == 0, restituisci b. Altrimenti, 
 * restituisci MCD(b-a,a). Scrivere una funzione ricorsiva per calcolare MCD.
*/

void scambia (int & a, int & b){
    int aux = a;
    a = b;
    b = aux;
}

int mcd(int a, int b){
    if (a>b) scambia(a, b);
    if (a == 0) return b;
    else return mcd(b-a, a);
}

/**
 * La edit distance ED(x,y) tra due stringhe x,y è il numero minimo di sostituzioni, 
 * inserimenti, cancellazioni (di un carattere singolo) che dobbiamo effettuare su x 
 * per trasformarla in y. Per esempio, ED("sunday" , "saturday") = 3 perchè possiamo 
 * trasformare "sunday" in "saturday" con tre modifiche: prima, inserisco due 
 * caratteri "at", ottenendo "satunday"; infine, rimpiazzo la 'n' in 'r', ottenendo 
 * "saturday". In tutto 3 modifiche: due caratteri inseriti e un carattere sostituito 
 * (ci possono essere diversi modi di effettuare il numero minimo di modifiche; a noi 
 * interessa solo calcolare il numero minimo di modifiche). Altro esempio: ED("abc" , 
 * "ac") = 1, perchè basta eliminare 'b' da "abc" per ottenere "ac". Scrivere un 
 * programma ricorsivo per calcolare ED(x,y). Nota: il corpo della funzione si scrive
 * in 6 linee di codice! evitate soluzioni troppo complicate.
*/

#include <cstring>

int min(int a, int b, int c){
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int distance(char* x, char* y){
    if (strlen(x) == 1 && strlen(y) == 1 && x[0] == y[0]) return 0; //caso base str uguali
    if (strlen(x) == 1 && strlen(y) == 1 && x[0] != y[0]) return 1; //caso base distanza 1 (rimpiazzi)
    if (strlen(x) == 0 && strlen(y) > 0) return strlen(y);  //caso base inserimento lettere
    if (strlen(y) == 0 && strlen(x) > 0) return strlen(x);
    if (x[0] == y[0]) return distance(x+1, y+1);    //se i primi due caratteri sono uguali, posso ridurre il prooblema al resto della stringa
    /**
     * tip: non bisogna guardare COSA cambiare, ma QUANTO. non serve capire quali lettere aggiungere, ma solo quante
     * come nel labirinto snake, posso ritornare il minimo tra le tre vie possibili: aggiunta, sostituzione e rimozione
    */
    return 1 + min(
        distance(x+1, y),   //sto rimovendo un carattere da x (lo shifto in avanti).
        distance(x+1, y+1), //chissenefrega di cosa e come cambio, se cambio qualcosa posso spostarmi ad analizzare la rimanente parte.
        distance(x, y+1)    //sto aggiungendo un carattere a x (perché shifto di uno y)
    );   
}

int main(){
    cout<<mcd(8, 64)<<endl;
    char a[] = "saturday";
    char b[] = "sunday";
    cout<<"quanti cambi: "<<distance(a, b)<<endl;
    return 0;
}