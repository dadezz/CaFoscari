package ProveEsami;

import java.util.concurrent.LinkedBlockingQueue;

/*Si prenda in considerazione la seguente interfaccia Java:
public interface Pool<R> {
    R acquire() throws InterruptedException; // acquisisce una risorsa
    void release(R x); // rilascia una risorsa e la rimette nella pool
}

Una pool `e un container di oggetti che si comporta come una coda bloccante: `e possibile ottenere una risorsa con
acquire() per poi restituirla alla pool tramite il metodo release().
Il generic R astrae il tipo della risorsa fornita dalla acquire() e restituita alla pool tramite la release().
Quando la coda `e vuota e nessun oggetto `e disponibile, il metodo acquire() deve essere bloccante. Al fine di
semplificare l’implementazione, si utilizzi un oggetto di tipo LinkedBlockingQueue come struttura dati d’appoggio
per la coda bloccante all’interno della pool. La classe LinkedBlockingQueue `e fornita dal JDK ed i suoi metodi
pi`u importanti sono:
class LinkedBlockingQueue<E> implements BlockingQueue<E> {
    LinkedBlockingQueue(); // costruisce una coda bloccante vuota
    void add(E x); // aggiunge un elemento alla coda
    E take() throws InterruptedException;   // (bloccante) estrae la testa, se la coda `e vuota
                                            // aspetta che ci sia un elemento
    E peek();   // (non bloccante) ritorna la testa senza rimuoverla,
                // oppure ritorna null se non c'`e nulla
    int size(); // numero di elementi nella coda
}
 */
public class Esame220113 {
    
}

interface Pool<R> {
    R acquire() throws InterruptedException; // acquisisce una risorsa
    void release(R x); // rilascia una risorsa e la rimette nella pool
}
/*Si implementi una classe generica SimplePool che implementa l’interfaccia Pool e realizza una sem-
plice pool usando LinkedBlockingQueue internamente come coda bloccante. Naturalmente deve esserci un
modo per pre-popolare la pool: si progetti un qualche meccanismo ragionevole per farlo senza fare assunzioni
troppo strette sul type parameter. */
class SimplePool<R> implements Pool<R> {
    LinkedBlockingQueue<R> coda = new LinkedBlockingQueue<>();

    SimplePool(){
        super();
    }

    @Override
    public R acquire() throws InterruptedException {
        return coda.take();
    }

    @Override
    public void release(R x) {
        coda.add(x);
    }

};
interface Resource<T> {
    T get(); // getter dell'oggetto di tipo T
    void autorelease(); // rilascia questo oggetto e lo rimette nella pool da cui proviene
};

class AutoPool<T> implements Pool<Resource<T>>{
    LinkedBlockingQueue<T> coda = new LinkedBlockingQueue<>();

    @Override
    public Resource<T> acquire() throws InterruptedException {
        T r = coda.take();
        return new Resource<>() {
            public T get(){
                return r;
            }
            public void autorelease(){
                coda.add(r);
            }
            @Override
            protected void finalize(){
                autorelease();
            }
        };
        
    }

    @Override
    public void release(Resource<T> x) {
        x.autorelease();
    }
    

};