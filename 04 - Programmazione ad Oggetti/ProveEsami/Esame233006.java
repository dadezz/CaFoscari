package ProveEsami;

import java.util.Iterator;
import java.util.function.Function;


/*Si prenda in considerazione la seguente classe Java 8+, parametrica su due generics X e Y, le cui istanze rappre-
sentano sequenze iterabili di coppie di coordinate cartesiane X × Y che rappresentano i punti individuati da una
funzione X → Y in un determinato intervallo del dominio X.
public class FunSeq<X extends Number & Comparable<? super X>, Y extends Number> implements Iterable<Pair<X, Y>> {
    private final X a, b;
    private final Function<? super X, ? extends Y> f;
    private final Function<X, X> inc;
    public FunSeq(X a, X b, Function<? super X, ? extends Y> f, Function<X, X> inc) {
        this.a = a;
        this.b = b;
        this.f = f;
        this.inc = inc;
    }
    // da finire di implementare
}
Al costruttore vengono passati l’intervallo di dominio [a, b), la funzione f e la funzione inc per incrementare l’ascissa.
La funzione f `e la funzione principale: per ogni ascissa x di tipo X compresa nell’intervallo [a, b), l’applicazione
f (x) ha tipo Y. La sequenza iterabile consiste in coppie (x, f (x)) di tipo Pair<X, Y> che rappresentano l’ascissa
e l’ordinata di ogni punto. Essendo impossibile rappresentare funzioni continue, le ascisse procedono in maniera
discreta secondo un valore di incremento: la funzione inc `e necessaria proprio per calcolare la prossima ascissa
nella sequenza.
(a) Si definisca una classe Pair parametrica su 2 generics A e B che rappresenta coppie immutabili.
(b) Si finisca di implementare la classe FunSeq opportunamente. Per realizzare il confronto delle as-
cisse, si noti che il type parameter X `e vincolato non solo ad essere un Number ma anche a implementare
Comparable<X>.
(c) Si implementi uno snippet di codice che utilizzi la classe FunSeq per rappresentare la parabola
x2 + 2x − 1 nel piano R × R nell’intervallo di dominio [−2, 2) con incremento di ascissa 0.1. Ci`o significa che
le ascisse partono da -2 e procedono a step di 0.1 fino a 2 (escluso), producendo ((2 − 0.1) − (−2))/0.1 = 39
punti. Si definisca la parabola con una opportuna lambda.
(d) (bonus) Si implementi uno snippet simile a quello del punto precedente ma che rappresenti la
parabola data nel piano R × Z, ovvero con ordinate di tipo int. */

class Pair<T1, T2> {
    public final T1 first;
    public final T2 second;
    
    Pair(T1 first_, T2 second_){
        first = first_;
        second = second_;
    }
}

class FunSeq<X extends Number & Comparable<? super X>, Y extends Number> implements Iterable<Pair<X, Y>> {
    private final X a, b;
    private final Function<? super X, ? extends Y> f;
    private final Function<X, X> inc;
    public FunSeq(X a, X b, Function<? super X, ? extends Y> f, Function<X, X> inc) {
        this.a = a;
        this.b = b;
        this.f = f;
        this.inc = inc;
    }
    // da finire di implementare
    @Override
    public Iterator<Pair<X, Y>> iterator() {
        return new Iterator<Pair<X,Y>>() {
            private X x = a;
            @Override
            public boolean hasNext() {
                return x.compareTo(b) < 0;
            }

            @Override
            public Pair<X, Y> next() {
                Pair<X, Y> res = new Pair<> (x, f.apply(x));
                x = inc.apply(x);
                return res; 
            }
            
        };
    }
}

public class Esame233006 {
    public static void Test1(){
        /*Si implementi uno snippet di codice che utilizzi la classe FunSeq per rappresentare la parabola
        x2 + 2x − 1 nel piano R × R nell’intervallo di dominio [−2, 2) con incremento di ascissa 0.1. Ci`o significa che
        le ascisse partono da -2 e procedono a step di 0.1 fino a 2 (escluso), producendo ((2 − 0.1) − (−2))/0.1 = 39
        punti. Si definisca la parabola con una opportuna lambda. */
        FunSeq<Double, Double> result = new FunSeq<>(
            -2.0, 
            2.0, 
            (x) -> x*x + 2*x -1, 
            (x) -> x+1.0
        );
        for(Pair<Double, Double> el : result){
            System.out.println("(" + el.second + " -> " + el.second + ")\n");
        }
    }
    public static void Test2(){
        /*Si implementi uno snippet simile a quello del punto precedente ma che rappresenti la
        parabola data nel piano R × Z, ovvero con ordinate di tipo int. */
        FunSeq<Double, Integer> result = new FunSeq<>(
            -2., 
            2., 
            (x) -> (int) (x*x + 2*x -1), 
            (x) -> x+1.0
        );
        for(Pair<Double, Integer> el : result){
            System.out.println("(" + el.second + " -> " + el.second + ")\n");
        }
    }
}