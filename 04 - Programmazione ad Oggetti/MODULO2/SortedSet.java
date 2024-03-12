package MODULO2;

public interface SortedSet<T extends Comparable<T>> extends Set<T> {
    public T first();
    public T last();
}