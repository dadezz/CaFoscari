thread è una classe definita nel jdk. Gli viene passato un runnable -> una delle 4 forme di lambda, che non prende nulla e non ritorna nulla.
`() -> {... ; ...}`. Ha un metodo run() che non prende nulla e non torna nulla. Da dove viene? da runnable (thread implementa runnable). 

È così percHé prima esistevano in un modo, poi sono stati cambiati. 

prima:
```java
public class Threads {
    public static class Mythread extends Thread {
        @Override
        public void run() {
            while(true){
                System.out.println("ciao");
            }
        }
    }
    public static void main(String[] args){
        Thread t = new MyThread();
        t.start(); 
        while(true){
            System.out.println("pippo");
        }
    }
}
```
il metodo start è ereditato dalla classe Thread del jdk: `void start() : schedules this thread to begin execution`. -> lo mette in coda al round robin. 
se chiamassi run, invocherei un metodo dal thread principale. start invece avvisa il sistema operativo che crea il thread e usa il codice scritto dentro run. start quindi non è bloccante, non esegue nulla, spawna un thread e fa partire il codice, in parallelo, quindi la riga subito dopo viene eseguita subito. pippo viene printato mescolatamente a ciao. 

Il secondo costruttore di Thread è `Thread(Runnable task)`. Ricordiamo che runnable è una delle 4 tipologie di funzioni (lambda), che contiene la funzione run che prende nulla e ritorna nulla. esattamente come la funzione run dei thread. Thread è quindi un runnable. Ma in che senso Thread è un runnable ma anche prende un runnable in costruttore? significa che io posso usare un thread senza dovermi ereditare la classe. Un runnable posso crearllo con un anonymous class o con una lambda. Il runnable che gli passo è il codice che voglio che il thread mi esegua. 

```java
public static void loop(String msg){
    System.out.println(msg);
}

// ...

new Thread(() -> loop("ciccio")).start();
// il garbage collector butterà via l'oggetto perché non l'hai bindato, ma 
// il thread esiste nel OS. Spesso in realtà è utile tenersi la variabile, tipo per una join
```

ora quindi ci sono tre metodi per spawnare un thread: ereditare la classe, usare un anonymous class, usare una lambda.
Il primo stile è più verboso, ma in caso di thread molto complessi è meglio usarlo, se invece il thread è rapido, senza dati, che fa scciocchezze, meglio usare la lambda


```java
class ConsumerProducer {

    public static List<Integer> buff = new ArrayList<>();

    /**
    * vecchia maniera
    */
    static class Producer extends Thread implements Runnable{

        @Override
        public void run() {
            Random rnd = new Random();

            while(true) {
                int n = rnd.nextInt();
                buff.add(n);
                try {
                    Producer.sleep(3);
                    System.out.println("ho stampato : " + n);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }

    }

    static class Consumer extends Thread implements Runnable{

        @Override
        public void run() {
            while(true) {
                if(buff.size() != 0) {
                    int n = buff.remove(0);
                    System.out.println("ho letto : " + n);
                }
            }
        }
    }
}

public class Mythread extends Thread implements Runnable{
    
    public static String suffix = "ciao";  

    public static void loop(String msg) {
        while(true)
            System.out.println(suffix + " " + msg);
    }

    @Override
    public void run() {
        loop("Pippo");
    }

    public static void main(String[] args) throws InterruptedException {

        /*
        Thread t = new Mythread();
        Thread t2 = new Thread(new Runnable() {
            @Override
            public void run() {
                loop("ciccio");
            }
        }); // qui ci voglio passare un Runnable.
        new Thread(() -> loop("Franco")).start();
        t.start(); //metto effettivamente in coda il thread da schedulare.
        t2.start();
        
        loop("Mamma"); // questo viene messo in coda -> da schedulare anche lui    
        */
        Thread p = new ConsumerProducer.Producer();
        Thread c = new ConsumerProducer.Consumer();
        
        p.start();
        c.start();
        try{
            p.join(); // aspettare senza fare un busy loop
            c.join(); //lmao non uscirà mai xk sono while(true)
        } catch (InterruptedException e) {}
    }
}
```

Ora se io lancio sta cosa ottengo eccezione index out of bound, in particolare il consumer in buff.remove(0).
Questo perché il consumer non aspetta se il buffer è vuoto

è lo stesso problema dei semafori di sistemi operativi
```java
while(true){
    if (!buff.isEmpty()){
        int n = buff.remove(0);
        System.out.println(n);
    }
}
```
come aspetto senza fare una busy loop? 
Un monitor: assomiglia a un semaforo. Fa una cosa leggermente diversa: si mette in attesa sull'entità e poi un'altra entità li sveglia.
"se il buffer è vuoto, mi metto a dormire e uso un monitor. Il producer ognii volta che produce qualcosa pinga il monitor che sveglia il consumer".
Questa cosa in JAVA è un fia bizzarra: tutti i reference type in java sono anche monitor. Questo xk dentro object ci sono due metodi: uno è `wait()`, l'altro è `notify()`.
Quando si chiama la wait il thread va in pausa, e rimane li finché qualcun altro non chiama notify e lo sveglia. ma chi? chiunque, percHé l'oggettto deve essere object e tutti lo sono
```java
public void run(){
    while (true){
        if (buff.isEmpty()){
            buff.wait();
        }
    }
}

// nel producer
public void run(){
    Random rnd = new Random();
    while(1){
        int n = rnd.nextInt();
        buff.add();
        buff.notify();
    }
}
```
la notifyall sveglia tutti, la notify ne sveglia una sola. C'è un'eccezione da catturare nella wait, la stessa che è necessario catturare nella join.

E tutto ok. vado in exec e ho errore a runtime: `IllegalMonitorStateException` il monitor è illegale percHé il thread corrente non è l'owner. cosa può esserci che va storto? 
Stiamo accedendo in due alla stessa struttura dati. Se le strutture dati non sono pensate per l'accesso concorrente si chiamano "thread unsafe". e l'array list non lo è.
Si risolve usando un semaforo. per l'esattenzza un mutex. Ci aspetteremmo che pure java, come C, abbia due primitive lock/unlock. In realtà java fornisce un costrutto sintattico apposito:

```java
// nel producer
public void run(){
    Random rnd = new Random();
    while(1){
        int n = rnd.nextInt();
        synchronized (buff){ //lock
            buff.add();
            buff.notify();
        }   //unlock
    }
}
```
notare che qualsiasi oggetto funge da semaforo, in sto caso buff. Quello all'interno è una critial section. Con la wait, il semaforo viene messo a verde, in sto modo si evita il deadlock