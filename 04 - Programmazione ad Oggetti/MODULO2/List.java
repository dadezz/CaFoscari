package MODULO2;

public interface List<T> extends Collection <T> {
    T get(int i);
    
    T set(int i, T x);

    void add(int index, T x);

    T remove(int index);
}