package MODULO2;

public class StructuralSortedSet<T extends Comparable<T>> extends StructuralSet<T> implements SortedSet<T> {

    @Override
    public T first() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'first'");
    }

    @Override
    public T last() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'last'");
    }

    public void add(T x){
        super.add(x);
        sort();
    }
    private void sort(){
    }

    
}
