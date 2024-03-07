package MODULO2;

public interface Collection<T> extends Iterable<T> {
    void add(T x);

    default void addAll(Collection<T> c){
        Iterator<T> it = c.iterator();
        while (it.hasNext()){
            add(it.next());
        }
    }

    void clear();

    default boolean contains(T x){
        /* deve dire se il parametro c'è nella sequenza */
        Iterator<T> it = iterator();
        while (it.hasNext()) {
            T e = it.next();
            // il binding non è necessario in realtà
            if(e.equals(x))
                return true;
        }
        return false;
    }

    boolean isEmpty();

    Iterator<T> iterator();

    void remove(T x);

    int size();

}