# thread in java

## creazione
attenzione alla differenza tra run e start

```java
public class CreaThread extends Thread {
    public void run(){
        System.out.println("Saluti da " + this.getName());
    }

    public static void main(String[] args){
        CreaThread t = new CreaThread();
        t.start;
    }
}
```

```java
public class CreaThread2 implements Runnable {
    public void run() {
        System.out.println("Saluti da " + Thread.currentThread().getName());
    }
    public static void main(String[] args) {
        CreaThread2 r = new CreaThread2();
        Thread t = new Thread(r);
        t.start();
    }
}
```

## Addormentare un thread
ogni evento asincrono è un'eccezione che va gestita

```java
public void run() {
    try {
        sleep(1000);
    }
    catch (InterruptException e){
        System.out.println("["+getName()+"] mi hanno interrotto");
        return;
    }
}
```

## Esercizio

Esercizio 1: creazione, interruzione e attesa di thread
Creare n thread, rallentarli tramite sleep(), provare ad interromperne l’attesa utilizzando t.interrupt() e attendere la terminazione con t.join() (analogamente a quanto si fa con i thread POSIX), dove t è l’oggetto thread. Aggiungere opportune print per osservare l’esecuzione.


```java
public class CreaThread extends Thread {
   
    public void run(){
        
        try {
            sleep(1000);
        }
        catch (InterruptException e){
            System.out.println("["+getName()+"] mi hanno interrotto");
            return;
        }
        
        System.out.println("Saluti da " + this.getName());
    }

    public static void main(String[] args){
        CreaThread t1 = new CreaThread();
        CreaThread t2 = new CreaThread();
        CreaThread t3 = new CreaThread();
        CreaThread t4 = new CreaThread();
        CreaThread t5 = new CreaThread();
        t1.start;
        t2.start;
        t3.start;
        t4.start;
        t5.start;

        t1.interrupt();

        t1.start.join();
        t2.start.join();
        t3.start.join();
        t4.start.join();
        t5.start.join();
    }
}
```

oppure 

```java
public class CreaTantiThread extends Thread {
    static final int NTHREAD=5;     // numero di thread da creare
    final int index;                // indice del thread appena creato

    // costruttore: memorizza l'indice del thread 
    CreaTantiThread(int i) {
        index = i;
    }
    
    // codice da eseguire allo startup del thread 
    public void run()  {
        try {
            // NOTA: se l'interruzione arriva prima della sleep viene
            // bufferizzata!
            sleep(2000);  // dorme per 2 secondi
        } catch(InterruptedException e) {
            System.out.println("["+getName()+"]"+" Ah mi hanno interrotto!!");
            return; 
        }
        // saluta ed esce
        System.out.println("Saluti dal thread " + getName());
    }

    /* main: crea i NTHREAD thread ne interrompe alcuni e attende la
       terminazione. NOTA: con join devo gestire InterruptedException,
       ma nessuno interrompera' mai le join di questo main quindi la 
       ignoriamo */
    public static void main(String args[]) throws InterruptedException {
        int i;
        Thread t[] = new Thread[NTHREAD];
        
        // crea 5 thread e li esegue
        for(i=0;i<NTHREAD;i++) {
            t[i] = new CreaTantiThread(i);
            t[i].start();
        }
        
        // interrompe il terzo thread
        t[3].interrupt();
        
        // attende la terminazione dei thread
        for(i=0;i<NTHREAD;i++) {
            t[i].join();
           }
        
        // saluta ed esce
        System.out.println("Saluti dal thread " + Thread.currentThread().getName());
    }
}
```

## Monitor
ogni oggetto in java ha un mute implixito utilizzanto per garantire mutua esclusione dui metodi.
I metodi sono eseguiti in mututa esclusione soo se dichiarati synchronizzed
ogni oggettto ha un unica condition implicita sulla quale si possono edettaure le operazionei standard wait, notify(), notifyAll().
se il metodo è statico allora il mutex è a livello di classe nivece che di oggetto

si può anche sincronizzare parti di codice di un metodo non sync nel seguente modo:
```java
synchronized(this){
    contatore = contatore+1;
}
```
this indica a quale oggetto fae riferimento per ottenere il lock impliicio. in questo caso è l'oggetto stesso, ma è possibile indicare oggetti differenti e quindi sincronizzarsi utilizzando il mutex di tali oggetti

**sincronizzazione rientrante**: è possiblie chiamare un metodo sunchronized da un altro synchronized senza problemi. una volta entrati lì, finché non esco ho sempre il mutex, è rilasciato solo dal primo che viene invocato.

### Esercizio

Implementare due thread che lavorano su un contatore condiviso, osservare le usuali interferenze e rimediare ponendo il codice all’interno di metodi synchronized. Suggerimento: mettere il contatore in una classe apposita (che fungerà da monitor) e implementare i metodi per l’incremento e la lettura/stampa del valore.

```java
public class Monitor {
    public int contatore = 0;
    public void incrementa(){
        synchronized(this){
            contatore++;
        }
    }
    public int leggi(){
        return contatore
    }

    /*
    nel main sopra, creo un oggetto di tipo monitor e lo passo ai costruttori dei thread
    */
}
```

solution:

```java
public class Interferenze extends Thread {
    static final int MAX=1000000;           // iterazioni massime
    Contatore c;                            // Monitor passato dal main

    // costruttore, memorizza il monitor nel campo c
    Interferenze(Contatore cont) {
        c=cont;
    }
    //   i thread incrementano MAX volte il contatore
    //   NOTA: non possono fare c.count++ perche' e' privato! 
    public void run() {
        int i;
        for (i=0;i<MAX;i++)
            c.incrementa();     // questo metodo e' in MUTEX perche' synchronized
    }

    //   il main crea i thread, attende la terminazione e stampa il contatore 
    public static void main(String args[]) throws InterruptedException {
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

/*  questa classe implementa un Monitor in cui e' possibile incrementare il valore 
 *  di un contatore da diversi thread in mutua esclusione.
 *  provare a togliere il 'synchronized' dal metodo incrementa per osservare 
 *  le interferenze */
class Contatore {
    private int count=0;    // privato: no accessi diretti!

    // il metodo synchronized garantisce mutua esclusione sullo stesso oggetto
    synchronized void incrementa() {
        //oppure: synchronized(this) {count++;}
        count++;
    }

    // non serve sincronizzarlo visto che lo usiamo alla fine dal main: gli altri
    // thread sono gia' terminati (la join garantisce che il main e' l'unico 
    // thread in esecuzione) inoltre la lettura non crea mai interferenze
    int valore() {
        return(count);
    }
}
```