/*
In questo task realizziamo un monitor Tavola che gestisce la sincronizzazione delle bacchette. 
Il monitor lo definiamo come una classe separata Tavola :
*/
public class Tavola {
    private boolean bacchette[]; // le bacchette
    private final int NFIL;      // il numero di filosofi

    // crea le NFIL bacchette e le inizializza a true (presenti)
    // NOTA: non serve sincronizzarlo e' prima della creazione dei filosofi
    Tavola(int NFIL) { 
        int i;
        this.NFIL=NFIL;                 // memorizza il numero dei filosofi
        bacchette = new boolean[NFIL];  // crea le bacchette
        for (i=0;i<NFIL;i++)    // inizializza le bacchette a true
            bacchette[i] = true;
    }

    // raccoglie la bacchetta sinistra
    synchronized void raccogli_sx(int index) throws InterruptedException {
        while(!bacchette[index]) wait();
        bacchette[index] = false;
    }
    // raccoglie la bacchetta destra
    synchronized void raccogli_dx(int index) throws InterruptedException {
        raccogli_sx((index+1)%NFIL); // la dx e' sx del filosofo successivo
    }   

    // deposita la bacchetta sinistra e notifica TUTTI i filosofi
    synchronized void deposita_sx(int index) {
        bacchette[index] = true;
        notifyAll();
    }
    // deposita la bacchetta destra e notifica TUTTI i filosofi
    synchronized void deposita_dx(int index) {
        deposita_sx((index+1)%NFIL); // la dx e' sx del filosofo successivo
    }   
}

/*
Spiegazione:
La classe Tavola prende come parametro nel costruttore il numero di filosofi NFIL in modo da poter gestire il numero corretto di NFIL bacchette;
Le bacchette sono implementate come un array di NFIL booleani e vengono create e inizializzate a true nel costruttore;
La classe Tavola implementa 4 metodi synchronized per la raccolta e deposito delle bacchette:

    raccogli_sx(index): raccoglie la bacchetta sinistra, con indice index, da implementare;
    raccogli_dx(index): raccoglie la bacchetta destra con indice (index+1)%NFIL, implementato come raccogli_sx((index+1)%NFIL);
    deposita_sx(index): deposita la bacchetta sinistra, con indice index, da implementare;
    deposita_dx(index): deposita la bacchetta destra con indice (index+1)%NFIL, implementato come deposita_sx((index+1)%NFIL).

Lo scopo di questo task è implementare i due metodi raccogli_sx(index) e deposita_sx(index) ricordandosi di usare lo schema

while (condizione di attesa)     |    // rende eventualmente falsa la condizione di attesa
    wait()                       |    notify() oppure notifyAll()

    NOTA: al momento non è necessario eseguire il codice in quanto lo faremo al prossimo task!

La condizione di attesa utilizzata in raccogli_sx(index) senza spazi e senza parentesi è la password per il Task 3!
 */