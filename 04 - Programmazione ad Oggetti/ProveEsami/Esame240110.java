package ProveEsami;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.function.Function;

/*
 * Si consideri un metodo statico in Java 8+ di nome parallelFactorial() che data una Collection<Integer>
produce una Collection<FactorialThread>. Per ogni intero della collection di input viene effettuato lo spawning
di un nuovo thread che ne computa il fattoriale e ne conserva il risultato in qualche modo. Tutti i thread creati
vengono ritornati nella collection di output, che naturalmente ha la stessa lunghezza della collection di input
 */
public class Esame240110 {
}

/*
 * Si implementi la classe FactorialThread in modo che estenda java.lang.Thread e fornisca un
metodo getter per l’accesso al risultato della computazione del fattoriale. Si presti attenzione all’attesa della
fine della computazione, gestendo opportunamente la cosa.
 */
class FactorialThread extends Thread {

    int n;
    int result;

    public FactorialThread(int n){
        this.n = n;
    }

    @Override
    public void run(){
        result = 1;
        for (int i=1; i<=n; i++){
            result *= i;
        }
    }
    public int get_result(){
        try {
            join();
        } catch (InterruptedException e){
            throw new RuntimeException(e);
        }
        return result;
    }


    /* Si implementi il metodo statico parallelFactorial() avente la seguente firma:
static Collection<FactorialThread> parallelFactorial(Collection<Integer> c)
Ogni thread deve lavorare concorrentemente agli altri, ciascuno calcolando il fattoriale di un intero proveniente
dalla collection di input. La funzione parallelFactorial() non deve attendere la fine delle computazioni,
ma deve ritornare subito la collection di output.
(c) 1 punti (bonus) Si raffini la firma del metodo statico parallelFactorial() di cui al punto precedente in
modo che il tipo di input ed il tipo di output siano, rispettivamente, pi`u generale e pi`u specializzato possibile,
senza tuttavia rivelare dettagli sull’implementazione. */
    static List<FactorialThread> parallelFactorial(Iterable<Integer> c){
        List<FactorialThread> result = new ArrayList<FactorialThread>();
        for(int e : c){
            FactorialThread t = new FactorialThread(e);
            t.start();
            result.add(t); 
        }
        return result;
    }

    /* Si scriva uno snippet di codice che testi il metodo statico parallelFactorial() stampando i
risultati di ciascuna computazione*/    
    public static void Main(String[] args){
        
        for(FactorialThread x : parallelFactorial(List.of(1, 2, 3, 4, 5))){
            x.get_result();
        }
    }

    /*i dia una seconda implementazione del metodo statico parallelFactorial() usando la funzione di ordine
superiore map(). In particolare si proceda nel seguente modo:
i. Si implementi un metodo statico map() avente la seguente firma:
static <A, B> List<B> map(Iterable<A> i, Function<A, B> f)
Esso deve applicare la funzione f ad ogni elemento di i e produrre in output tutti i risultati delle
applicazioni.
ii. Si reimplementi parallelFactorial() tramite una singola invocazione della map().*/

    static <A, B> List<B> map(Iterable<A> i, Function<A, B> f) {
        List<B> result = new ArrayList<>();
        for(A x : i){
            result.add(f.apply(x)); 
        }
        return result;
    }
    static List<FactorialThread> parallelFactorial_2(Iterable<Integer> c){
        return map(c, (n) -> { FactorialThread t = new FactorialThread(n); t.start(); return t; });
    }

}
