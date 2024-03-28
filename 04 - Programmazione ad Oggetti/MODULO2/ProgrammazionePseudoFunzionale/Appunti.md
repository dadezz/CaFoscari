# Progr Funzionale

2 paradigmi: imperativo e funzionle. cosa cambia? l'assegnamtno.
In Java, che è un linguaggio imperativo, che adotta uno stile ad oggetti, esiste un aspetto dei linguaggi funzionali: le lambda.
Il paradigma funzionale ha dei vantaggi in termini di robustezza del codice. 

# Lambda
in java non c'è stata fino alla versione 8 (2010). Le lambda sono funzioni anonime. 

## Foreach

Volgio fare una cosa come un foreach. una funzione che prende due parametri: il primo è un iterabile, il secondo è una funzione e la funzione applica la funzione passata come parametro ad ogni elemento della collection. Una funzione così definita è detta **funzione di ordine superiore**.

```c
void for_each(int* a, size_t len, void(*f)(int)){
    // funztion di ordine superiore
    for(int i=0; i<len; i++){
        f(a[i]);
    }
}

void print_int(int n){
    printf("%d\n");
}

void main(){
    int A[10] = ...;
    for_each(A, 10, print_int);
}
```

Questo modo di programmare si chiama funzionale: hai una funzione di ordine superiore che fa tante cose potenti in modo generale a cui passi delle funzioni che vanno applicate. 
Tutto ciò sarebbe carino se non dovessi ogni volta scrivermi la funzione e passarla. Sarebbe bello poter scrivere lì direttamete quando la chiamo

```c
void main(){
    int A[10] = ...;
    for_each(A, 10, printf("%d\n"));
}
```

ricorda qualcosa sta roba del non dare un nome alle funzioni? le lambda! 
Faccio la stessa roba in java, senza function pointer, ad oggetti, senza lambda:

```java
public class FunctionPointerExample {
    interface MyFunction<T> {
        void apply(T x);
    }

    public static <T> void forEach (Collection<T> c, MyFunction<T> f){
        for (T x : c){
            f.apply(x);
        }
    }   

    public static void main(String[] args){
        List<Integer> l = List.of(1, 2, 3, 4);
        // uso un anonymous class per costruire al volo un istanza di myfunction
        foreach(l, new MyFunction<int>{
            public void apply(Integer x){
                System.out.println(x);
            }
        })
    }
}
```

È un poì' una merda dover fare un anonymous class per passare una funzione al foreach. 

```java
public static void main(String[] args){
    List<Integer> l = List.of(1, 2, 3, 4);
    // uso un anonymous class per costruire al volo un istanza di myfunction
    foreach(l, x -> System.out.println(x));
}
```

La lambda è il passaggio di un pezzo di codice. In Java si può tranquillamente simulare una lambda con un anoonymous class, quindi non è che ci fosse proprio bisogno delle lambda. Ma tra scrivere quella merda in ventordici righe e una lambda c'è molta differenza.

Sintassi della lambda in Java: la labda è un'entità di primo ordine, computa qualcosa e ha un tipo.
Inizia con un nome di variabile, ha una freccia e poi ciò che deve fare. All'interno della funzione c'è il riferimento al parametro della funzione.
Ha la sintassi della funzione eccetto il nome (perché anonima). 
La sintasssi di una fn normale è
Tipo nome (Tipo parametri) {corpo}

la sintassi di una lambda è:

(Tipo nome_parametro) -> corpo(Tipo parametro);

anzi, è sintetizzabile senza tipi

nome_parametro -> corpo(parametro);

facciamo un altro esempio (sempre con entrambe le forme). Per ogni elemento voglio sommare 1

```java
public static void main(String[] argv){
    List<Integer> l = List.of {1, 2, 3, 4};
    forEach(l, new MyFunction<Integer>() {
        public void apply(Integer x){
            x = x+1;
        }
    })
}
```

mettendo sta roba su intellij, x = x+1 avrebbe la scritta "x non usato". ma io x lo sto passando by reference, perché x è un Integer. Sta roba sideffecta l'input.

Con sintassi della labda:

```java
public static void main(String[] argv){
    List<Integer> l = List.of {1, 2, 3, 4};
    forEach(l, x -> x=x+1);
}
```

Se faccio due cose invece che una?

```java
public static void main(String[] argv){
    List<Integer> l = List.of {1, 2, 3, 4};
    forEach(l, new MyFunction<Integer>() {
        public void apply(Integer x){
            if (x>5){
                x = x-1;
            }
        }
    })
}
```
bastano le graffe. sono omittibili solo se il corpo è in forma di espressione e non di statement
```java
public static void main(String[] argv){
    List<Integer> l = List.of {1, 2, 3, 4};
    forEach(l, x -> {if (x>5) x=x+1});
}
```

Se volessi ritornare qualcosa dalla lambda?

```java
// interfaccia che rappresenta l'insieme delle funzioni unarie che prendono un tipo e ritornano un tipo.
// mi tocca averne 2 perché void non è un tipo, non posso passarlo, è solo una keyword.
interface Function<A, B>{
    B apply(A x);
}


// funzione che trasforma una collection di qualcosa in una collection di qualcos'altra
public static <A, B> Collection<B> map (Collection<A> c, Function<A, B> f){
    Collection<B> r = new ArrayList<>();
    for (A x : c){
        B b = f.apply(x);
        r.add(b);
    }
    return r;
}

public static void main(String[] args){
    List<Integer> l = bew ArrayList<>();
    Collection<Integer> r = map(l, new Function<Integer, Integer>){
        public Integer apply(Integer x){
            return x+1;
        }
    }
}

// se volessi usarla come lambda
public static void main(String[] args){
    List<Integer> l = bew ArrayList<>();
    Collection<Integer> r = map(l, x -> x+1);
    // oppure r = map(l, x -> {return x+1;}); siccome è un solo statement, posso evitare di scrivere il return, lo scrivo come espressione
}
```

per esempio posso anche ritornare una collection di boolean

```java
public static void main(String[] args){
    List<Integer> l = new ArrayList<>();
    Collection<Boolean> r = map(l, x -> x>1);
}
```

ovviamente l'interfaccia Function già esiste nel jdk, esattamente come questa, stesso nome e stesso apply.
L'interfaccia delle funzioni che hanno input ma non hanno output al posto di Function si chiamano Consumer.
* Function : prende e ritorna
* Consumer : prende e non ritorna
* Supply : non prende e ritorna
* Runnable : non prende e non ritorna
