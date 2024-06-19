package ProveEsami;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.function.Function;
import java.util.function.Supplier;

/*Si implementi un metodo statico generico in Java 8+ che, dato un iteratore ed una funzione, produce un nuovo
iteratore che in maniera asincrona applica la funzione ad ogni elemento dell’iteratore originale. Ci`o significa che
un thread diverso deve processare ciascun elemento */

class Esame230905 {

/*Si implementi tutto ci`o che `e necessario dello snippet seguente 
 *  static <A, B> Iterator<Supplier<B>> asyncIterator(Iterator<A> it, Function<A, B> f) {
        return new Iterator<>() {
            @Override
            public boolean hasNext() {  }
            private class Future implements Supplier<B> {
                public Future(Supplier<B> f) {  }
            }
            @Override
            public Supplier<B> next() { }
        };
    }
Si badi che la classe innestata Future ha lo scopo di semplificare l’implementazione della next(). Essa
rappresenta una computazione in corso che non `e ancora terminata. Essendo di fatto un Supplier, sar`a
possibile conoscere il risultato invocando il metodo get(). Naturalmente questo risultato sar`a possibile
ottenerlo solamente dopo aver atteso che il relativo thread abbia finito di computare il Supplier passato in
costruzione.
*/
    static <A, B> Iterator<Supplier<B>> asyncIterator(Iterator<A> it, Function<A, B> f) {
        /*
         * la funzione deve ritornare un nuovo iteratore. l'iteratore è una classe composta da next() e hasnext().
         * siccome è una "copia" dell'iteratore di partenza, se c'è il next di it c'è anche dell'iteratore che ritorno
         * il next allo stesso modo segue il percorso di it. si salva momentaneamente it.next(), ovvero quello attuale, facendo scorrere it.
         * poi deve applicare la funzione f su a.
         * l'iteratore deve ritornare un supplier, cioè deve ritornare una funzione -> una lambda.
         * 
         * uso Future come nested class da ritornare, che implementa l'interfaccia supplier. supplier è il tipo di lambda con il "get".
         * quindi, creo una variabile per ciò che devo gettare (r) e per il thread. Quando costruisco il future (quindi quando ritorno la lambda
         * nel next()) creo anche il thread e lo faccio partire, poi nella get lo aspetto e restituisco.
         */
        
        
        return new Iterator<>() {
            @Override
            public boolean hasNext() { 
                return it.hasNext();
            }
            
            class Future implements Supplier<B> {
                private B r;
                private final Thread t;

                public Future(Supplier<B> f) {
                    t = new Thread( () -> r = f.get()); 
                    t.start();
                }
                @Override
                public B get() {
                    try {
                        t.join();
                    } catch (InterruptedException e){
                        throw new RuntimeException(e);
                    }
                    return r;
                }

            }


            @Override
            public Supplier<B> next() {
                A a = it.next(); // prendo l'elemento attuale e intanto scorre;
                return new Future(() -> f.apply(a));
            }
        };
    }

    /*Si implementi il seguente metodo statico in modo che utilizzi il metodo statico asyncIterator() di
    cui all’esercizio precedente per scorrere l’argomento iterabile e ordinare in maniera asincrona i suoi elementi1.
    static <T extends Comparable<? super T>> void sortLists(Iterable<List<T>> c */
    static <T extends Comparable<? super T>> void sortLists(Iterable<List<T>> c){
        /* se devo chiamare asyncIterator(Iterator<A> it, Function<A, B> f), 
        * diciamo che è ovvio che mi servirà storare il tipo di ritorno da qualche parte
        * 
        * poi, sto ricevendo un iteratore, dopo magari lo itero...
        */
        Iterator<Supplier<List<T>>> it = asyncIterator(c.iterator(), (x) -> {Collections.sort(x); return x;});
        while(it.hasNext()){
            Supplier<List<T>> x = it.next();
            x.get(); // unnecessary
        }
    }

}