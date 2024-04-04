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