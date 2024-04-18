# Wildcard e Overloading

## Overloading

Metodo con lo stesso nome di un altro ma con parametri/tipi differenti. È una caratteristica del lniguagggio, non tutti permettonon di avere metodi con lo stesso nome ma firme diverse

```java
public class Dog extends Animal {
    public void eat (Animal a) {...}
    public void eat (Dog a) {...}
}
```

immaginiamo che chiamo eat con un Dog, viene chiamato il secondo -> il sistema di risoluzione dell'overloading chiama quello "più vicino". Da Dog a Animal c'è "un colpo" si subsumption

Il tipo di ritorno NON appartiene alla firma di un metodo -> cambiare tipo di ritorno è override.

### covaraianza del tipo dei parametri

```java
public class Overloading {
    public static class A {
        public A m() {;}
    }
    public static class B extends A {
        public B m() {;}
    }
}
```
questo non è un overload, ma è un override. cambia il tipo di ritorno. il tipo di ritorno cambia insieme al tipo di this (prima ritornava un A e poi ritorna un B; esattamente com this che prima era A poi era B)
```java
public class Overloading {
    public static class A {
        public Number m() {;}
    }
    public static class B extends A {
        public Integer m() {;}
    }
}
```

In A ritorno Number, in B ritorno Integer. Number è il supertipo di Integer come A è il supertipo di B.

## Wildcards 

```java
public class Misc {
    public static <A, B> List <B> map(Iterable <A> c, Function<A, B> f){
        ---
    }
    public static void main(String[] args){
        List<String> l1 = List.of("pippo", "plusto", "paperino");
        List<Integer> l2 = map(l1, (String s) -> s.lenght());
    } 
}
```

posso riscrivere la funzone con:
```java
public class Misc {
    public static <A, B> List <B> map(Iterable <A> c, Function<A, ? extends B> f){
        ---
    }
    public static void main(String[] args){
        List<String> l1 = List.of("pippo", "plusto", "paperino");
        List<Integer> l2 = map(l1, (String s) -> s.lenght());
    } 
}
```
`Function<A, ? extends B>`: esprime la covarianza. non è un tipo xk non posso dichiaraci una funzione. questa lambda `(String s) -> s.lenght()` ha tipo Function(string->integer). riscrivo l'ultimo statement con ` List<Number> l2 = map(l1, (String s) -> s.lenght());`

Non c'è dubbio su chi sia A in questo tipo; il tipo di ritorno della lambda è integer, ma viene messo su una lista di Number. Java capisce che B è number, e la lambda ritorna un qualcosa che estende Number