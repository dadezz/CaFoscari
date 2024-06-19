/*
 * Implementare due thread che lavorano su un contatore condiviso, osservare le usuali interferenze e 
 * rimediare ponendo il codice all’interno di metodi synchronized. 
 * Suggerimento: mettere il contatore in una classe apposita (che fungerà da monitor) e 
 * implementare i metodi per l’incremento e la lettura/stampa del valore.
 */

public class Template_Synchronized {
}

/* e' possibile incrementare il valore di un contatore da diversi thread in mutua esclusione.*/
class Contatore {
    private int count=0;

    // il metodo synchronized garantisce mutua esclusione sullo stesso oggetto
    synchronized void incrementa() {
        count++;
    }

    int valore() {
        return(count);
    }
}

class Interferenze extends Thread {
    static final int MAX=1000000;
    Contatore c;
    Interferenze(Contatore cont) {
        c=cont;
    }

    //   i thread incrementano MAX volte il contatore
    public void run() {
        int i;
        for (i=0;i<MAX;i++)
            c.incrementa();     // questo metodo e' in MUTEX perche' synchronized
    }




    
    static void main(String args[]) throws InterruptedException {
        int j=0;
        Thread t[] = new Thread[2];
        Contatore cont = new Contatore(); // crea un singolo monitor
        
        // crea i 2 thread e li esegue
        for(j=0;j<2;j++) {
            t[j] = new Interferenze(cont); // passa il monitor ai thread
            t[j].start();
        }

        // attende la terminazione
        for(j=0;j<2;j++) t[j].join();

        // stampa il contatore, il valore atteso ed esce
        System.out.println("FINITO " + cont.valore() + " mi aspettavo " + MAX*2);
    }
}

