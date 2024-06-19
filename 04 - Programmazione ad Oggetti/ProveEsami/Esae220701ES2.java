package ProveEsami;

import java.util.Iterator;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;

import MODULO2.ArrayList;

/*Si implementi in Java 8+ una classe FiboSequence le cui istanze rappresentano sequenze contigue di
numeri di Fibonacci di lunghezza data in costruzione. Tali istanze devono essere iterabili tramite il costrutto
for-each di Java, devono pertanto implementare l’interfaccia parametrica del JDK java.util.Iterable<T>.
Ad esempio, il seguente codice deve compilare e stampare i primi 100 numeri di Fibonacci:
1Si utilizzi la classe Random del JDK per generare numeri casuali.
1
for (int n : new FiboSequence(100)) {
System.out.println(n);
}
L’implementazione richiesta deve utilizzare una funzione ricorsiva che calcola l’n-esimo numero di Fibonacci */
public class Esae220701ES2 {
    
}
class FiboSequence implements Iterable<Integer>{
    int bound;
    int actual;
    FiboSequence(int bound_){
        bound = bound_;
        actual = 0;
    }

    protected int fibo(int x){
        if (x<2) return 1;
        else return fibo(x-1) + fibo(x-2);
    }
    @Override
    public Iterator<Integer> iterator() {
        return new Iterator<Integer>(){
            public boolean hasNext(){
                return actual<bound;
            }

            public Integer next(){
                Integer x = actual++;
                return fibo(x);
            }
        };
    }

}

/*Si modifichi la classe FiboSequence in modo che i numeri di Fibonacci generati sottostiano ad
un meccanismo di caching che ne allevia il costo computazionale memorizzando il risultato di ogni passo di
ricorsione, in modo che ogni computazione successiva con il medesimo input costi solamente un accesso in
lettura alla cache. Ogni istanza della classe di FiboSequence deve possedere la propria cache. Si utilizzino
liberamente le mappe del JDK. */
class FiboSequence_cache extends FiboSequence {
    protected Map<Integer, Integer> cache;
    FiboSequence_cache(int bound, Map<Integer, Integer> map){
        super(bound);
        cache = map;
    }
    @Override
    protected int fibo(int x){
        if (x<2) 
            return 1;
        else {
            Integer r = cache.get(x);
            if (r != null) return x;
            else {
                Integer result = fibo(x-1) + fibo(x-2);
                cache.put(x, result);
                return result;
            }
        }
    }
    /*Si modifichi la classe FiboSequence in modo che la cache sia condivisa tra molteplici istanze */
    protected static Map<Integer, Integer> cache2;
}