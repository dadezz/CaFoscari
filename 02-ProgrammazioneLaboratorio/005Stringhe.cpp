#include <iostream>

/**
 * 27 febbraio 2023
 * stringhe
*/


// l'operatore & legge left value (variabile) e restituisce right value (espressione)
// l'operatore * funziona all'opposto: prende l'indirizzo di memeoria (espressione, right value), e restituisce un left (variabile)
int main1(){

    //IN C:

    char s[200] = "hello";
    char t[50] = "hello";
    s == t; //false
    //s in realtà è la scrittura zuccherata di &s[0]. da cui ->
    //s = t; errore perché s è rightvalue, s e t sono due espressioni, si potrebbe piuttosto fare
    char *u = s;
    u == s; //true
}

/**
 * in C, per allocare memoria si usava malloc/free, operatore non tipato, ora esiste new/delete, operatori tipati
 * non serve quindi passare la dimensione
 * 
*/
#include <string>

int main(){
    std::string s1, s2;
    std::cin>>s1;
    std::cin>>s2;
    if(s1 == s2); //fa esattamente quello che ci aspettiamo
    s1 = s2; //assegamento valido
    s1 > s2; //valido: test ordine lessicografico
    std::string s3 = s1+s2; //concatena le stringhe
    s1 = s1 + "ciao"; //funziona

    /**
     * lo spazio da cin viene considerato separatore, perché solo \n venga considerato tale, usare getline
    */

    s1.length(); //restituisce lunghezza
}

void f(std::string s); //viene passata una copia della stringa
void f2(std::string & s1); //passaggio per reference
void f1(const std::string & s2);
    //non faccio la copia del parametro effettivo solo per efficienza, passaggio per reference ma senza modificazioni.