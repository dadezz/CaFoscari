# JDK
per un po di lezioni esploreremo la jdk (libreria).

#### piccola parentesi
```java
public interface I{
    void a();
    void b();
}

public abstract class J{
    abstract void a();
    abstract void b();
}
```

ste due robe sono semanticamente identiche, e un'eventuale implementazione/estensione definisce un nuovo sottotipo in entrambi i casi.

```java
public interface I{
    void a();
    void b();
    default void c(){
        a();
        b();
    }
}

public abstract class J{
    abstract void a();
    abstract void b();
    void c(){
        a();
        b();
    }
}
```

Anche ste due qua sopra sono assolutamente identiche.

Tornando a noi,

## Iterable
iterabile, può essere scorsa (iterator è l'iteratore che ci permette di scorrere). È un'interfaccia. Ha due metodi di default, più un metodo che va implementato, `Iterator iterator()`. Iterator è un'altra classe, che non ha alcun collegamento con Iterable. Iterable è una struttura dati che può essere iterata, Iterator è l'oggettino, il puntatore, che ti serve per iterare, non è una struttra dati, non deve estendere iterable.

### Collection
estende iterable. Vuol dire che deve implementare il metodo iterator

### List 
Estende Collection. JDK non usa la semantica dell'algoritmica. (secondo gli algortirmi, array è una struttura dati ad accesso in O(1), lista è un accesso in O(n)). Per JDK, una lista è qualsiasi cosa a cui si possa accedere tramite indice (per esempio, al conrario di `Set`, altra estensione di Collection). Le linked list sono liste, perché si può definire un getter a indice, solo che non è in tempo O(1), ma O(n). 

### come iterare

```java
// al posto di fare a basso livello,
for (int i=0; i<v.size(); i++){
    //do
}
// uso l'iteratore
//notare che è meglio per la subsumption, perché l'accesso per index è definito 
//da list, mentre l'iterator da Iterable
Iterator<Integer> it = v.iterator();
while(it.hasNext()){
    int n = it.next();
    System.out.println(n);
}
```
NB: È interessante vedere che il metodo next ritorna il valore attuale, e poi si sposta. È l'analogo per gli iteratori del `++` postfisso. Prima ritorna i, poi incrementa. 