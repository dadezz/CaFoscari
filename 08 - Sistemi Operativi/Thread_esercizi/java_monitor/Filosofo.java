


/*
Lo scopo di questo primo task è di creare ed eseguire i 5 thread Filosofo, ognuno dei quali con un indice distinto da 0 a 4.
Partiamo da questo codice:
*/
public class Filosofo extends Thread {
    static final int NTHREAD=5;             // numero di filosofi
    final int index;                        // indice locale del filosofo

    // il filosofo memorizza il proprio indice e il monitor condiviso
    Filosofo(int index) {
        this.index = index;
    }
    
    // il thread esegue il codiceFilosofo a meno di interruzioni
    public void run()  {
        try { 
            codiceFilosofo(index);
        } catch (InterruptedException e) {
            System.out.println("Il filosofo "+index+" e' stato interrotto");
        }
    }

    // il filosofo pensa e mangia come al solito
    void codiceFilosofo(int index) throws InterruptedException {
        while(true) {
            // PENSA 
            System.out.println("Filosofo " + index +" pensa");
            Thread.sleep(1000);
            
            // raccoglie la bacchetta sinistra
            // raccoglie la bacchetta destra

            //MANGIA
            System.out.println("Filosofo " + index +" mangia");
            Thread.sleep(1000);

            // deposita la bacchetta sinistra
            // deposita la bacchetta destra
        }
    }

    public static void main(String args[]) throws InterruptedException {
        int index;
        
        // crea NTHREAD filosofi e li esegue
        for(index=0;index<NTHREAD;index++) {
            // Crea il filosofo con indice 'index' e lo esegue
            // ..... inserire qui il codice mancante .....
            new Filosofo(index).start();
        }
        // esce lasciando i filosofi al loro destino
    }
}
/*
Spiegazione:

La costante NTHREAD=5 indica il numero di thread che verranno creati ed eseguiti;
La classe Filosofo estende Thread e quindi può essere usata per creare thread ed eseguirli;
Ogni oggetto Filosofo ha un index da 0 a 4 che lo identifica, questo index viene passato al costruttre;
Il metodo run(), che viene invocato automaticamente quando viene creato ed eseguito il thread, non fa altro che invocare codiceFilosofo() e gestire InterruptedException;
Il metodo codiceFilosofo() implementa il classico schema del filosofo a cena che pensa, raccoglie le bacchette, mangia, e deposita le bacchette ma le bacchette al momento non vengono né raccolte né depositate (lo faremo in un task successivo!);
Il metodo main fa in ciclo for per creare ed eseguire i thread Filosofo ma il codice dovete inserirlo voi … !

Il codice deve, in una sola istruzione, creare l’oggetto Filosofo con index opportuno ed eseguire il thread corrispondente.

Una volta inserita l’istruzione provate a compilare ed eseguire il programma. Dovreste vedere i filosofi che pensano e 
mangiano tutti assieme (visto che le bacchette ancora non sono implementate). Ad esempio:
*/



/// codice aggiutno: new Filosofo(index).start();