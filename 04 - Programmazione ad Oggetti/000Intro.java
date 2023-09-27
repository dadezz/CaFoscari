/**
 * il bytecode ha un array con le variabili locali e uno stack con gli operandi
 * 
 */

int sum (int a, int b){
    int result = a+b;
    return result;
}

/**
 * bytecode:
 * 
 * iload_0
 * iload_1
 * iadd
 * istore_2
 * iload_2
 * ireturn
 * 
 * 
 * 
 * è il piu vicino possibile ad assembly ssenza voler 
 * dipendere dal singolo elaboratore
*/

/**
 * originally develped by gosling at sun
 * se bytecode è abbastanza invariato, java cambia molto. 
 * ogni tot ci sono delle versioni lts, l'ultima è java 21, rilasciata 19 settembre 2023
 * 
 * Perché java e non C? 
 * sono entrabmi imperativi. La sintassi è pressoché identica (se prendo codice c senza puntatori, 
 * posso copincollarlo in java)
 * 
 * c è procedurale, java ad oggetti. 
 * 
 * Non ci sono puntatori arbitrari in java. Non ci sono allocazioni e free; c'è il garbage collector, 
 * prestazione meno prevedibile
 * 
 * In realtà in java c'è un trick, si puo dire che un pezzo di codice è nativo.
 * tutte le volte che mi servono i puntatori a memoria, scrivo pezzo di codice in c e lo dichiaro come
 * codice nativo.
 * C'è quindi un'area confinata di codice che viene runnata come codice C
 * un po' come il codice "unsafe" di c#
 * 
 * Java è molto verboso, ma grazie a questo il codice può essere ben strutturato in modo da renderlo
 * di lungo termine (di facile supporto e controllo, facile da mantenedre)
 * 
 *  --- guarda la slide, interessante eempio su come il C spesso sia di difficile manutenzione e 
 *      espansione
 * 
 * Java, col paradigma orientato agli oggetti si pone l'obiettivo, tra gli altri, di avere codice 
 * di qualità, estendibile, adattivo, documentato, facile da riutilizzare.
 * 
 * Per esempio invece fa cagare per la GUI, non è il massimo per simulazioni e programmazione distribuita
 * 
 * come miglioriamo il riutilizzo del codice? con l'encapsulation
 * come migliora l'estensibilità? ereditarietà, tipi generici etc
 * 
 * debolezze: efficienza e verbosità
 * 
 *  CLASSI, CAMPI, METODI
 * 
 * 
 * OGGETTO: L'istanza di una classe. al suo interno ha valori e metodi.
 * Qual è l'idea i un oggetto?
 * Vogliamo modellare entita reali o astratte.
 * meccanismo di scrittura edl codice che ci permette di rappresentare il maniera compatta e completa la singola
 * entità, sia in termini di attrivuti che di funzionalita relative
 * 
 * se ho un oggetto albero, ho l'attributo "colore delle foglie" e il metodo "autunno" che me le rende marroni.
 * non ho metodi che arrivano di prepotenza dall'esterno per modificare li colore delle oglie.
 * 
 * Le funzioni modificano quello che si chiama "stato dell' oggetto".
 * 
*/

double CONSUMPTION = 0.01;

public class Car {
    double speed;
    double fuel;
    void accelerate(double amount) {
        speed += amount;
        fuel -= amount*CONSUMPTION;
    }
    void fullbreak(){
        speed = 0;
    }
    void refuel(double amount){
        fuel += amount;
    }
}

public class Runner{
    public static void main(String [] args){
        Car car = new Car();
        car.refuel(10);
        car.accelerate(100);
        car.accelerate(100);
        car.fullbreak();
    }
}