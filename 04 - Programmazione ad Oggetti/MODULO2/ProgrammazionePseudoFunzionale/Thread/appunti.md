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
public class ConsumerProducer {
    
}