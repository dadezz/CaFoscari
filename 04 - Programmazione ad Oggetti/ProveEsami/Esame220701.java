package ProveEsami;

import java.util.Iterator;
import java.util.Random;
import java.util.function.Function;
import java.util.stream.IntStream;

import MODULO2.ArrayList;

/*Realizziamo in Java 8+ una sottoclasse di java.util.ArrayList di nome SkippableArrayList parametrica su
un tipo T che estende la superclasse con un iteratore in grado di discriminare gli elementi secondo un predicato e
di processarli tramite due funzioni distinte a seconda dell’esito dell’applicazione del predicato all’elemento.*/

/*Si definisca una interfaccia funzionale di nome Predicate specializzando l’interfaccia generica
java.util.Function del JDK in modo che il dominio sia un generic T ed il codominio sia Boolean */
interface Predicate<T> extends Function<T, Boolean> {};
/*Si definisca una interfaccia Either parametrica su un tipo generico T e che definisce due metodi.
Il primo metodo, di nome onSuccess, prende un T e ritorna un T e viene chiamato dall’iteratore quando il
predicato ha successo. Il secondo metodo, di nome onFailure, viene invocato invece quando il predicato
fallisce, prende un argomento di tipo T e non produce alcun risultato, tuttavia pu`o lanciare una eccezione di
tipo Exception */
interface Either<T> {
    public void onFailure(T x) throws Exception;
    public T onSuccess(T x);
}
/*7
 * Si definisca la sottoclasse SkippableArrayList parametrica su un tipo E e si implementi un metodo
pubblico avente firma Iterator<E> iterator(Predicate<E> p, Either<E> f) che crea un iteratore con le
caratteristiche accennate sopra. Pi`u precisamente:
• l’iteratore parte sempre dall’inizio della collezione ed arriva alla fine, andando avanti di un elemento alla
volta normalmente;
• ad ogni passo l’iteratore applica il predicato p all’elemento di tipo T corrente, che chiameremo x: se p(x)
computa true allora viene invocato il metodo onSuccess di f e passato l’elemento x come argomento;
altrimenti viene invocato il metodo onFailure e passato x come argomento a quest’ultimo;
• l’invocazione di onFailure deve essere racchiusa dentro un blocco che assicura il trapping delle eccezioni:
in altre parole, una eccezione proveniente dall’invocazione di onFailure non deve interrompere l’iteratore;
• quando viene invocato onSuccess, il suo risultato viene restituito come elemento corrente dall’iteratore;
• quando viene invocato onFailure, l’iteratore ritorna l’elemento originale che ha fatto fallire il predicato
 */
class SkippableArrayList<E> extends ArrayList<E> {

    Iterator<E> iterator(Predicate<E> p, Either<E> f) {
        MODULO2.Iterator<E> it = super.iterator();
        return new Iterator<E>() {

            @Override
            public boolean hasNext() {
                return it.hasNext();
            }

            @Override
            public E next() {
                E x = it.next();
                boolean res = p.apply(x);
                if (res) {
                    return f.onSuccess(x);
                }
                else{
                    try {
                        f.onFailure(x);
                    } catch (Exception e) {
                    }
                    return x;
                }

            }
    
        };
        
    }
}
/*Si scriva un esempio di codice main che:
• costruisce una ArrayList di interi vuota di nome dst;
• costruisce una SkippableArrayList di interi di nome src e la popola con numeri casuali compresi tra 0
e 10, inclusi gli estremi1;
• invocando solamente una volta il metodo iterator(Predicate<E>, Either<E>) di src con gli argo-
menti opportuni, somma 1 a tutti gli elementi di src maggiori di 5 e appende in coda a dst quelli minori
o uguali a 5 */
public class Esame220701 {
    public static void main(String args[]){
        ArrayList<Integer> dst = new ArrayList<>();
        SkippableArrayList<Integer> src = new SkippableArrayList<>();
        Random rnd = new Random();
        for (int i = 0; i<30; i++){
            int x = rnd.nextInt(11);
            src.add(x);
        }
        Either<Integer> f = new Either<>() {

            @Override
            public void onFailure(Integer x) throws Exception {
                dst.add(x);
            }

            @Override
            public Integer onSuccess(Integer x) {
                return x+1;
            }
            
        };
        Iterator<Integer> it = src.iterator((x) -> (x>5), f);
        while(it.hasNext()) it.next();
    }
}