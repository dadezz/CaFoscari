package MODULO2;

public class StructuralSet<T> implements Set<T> {

    private List<T> l = new ArrayList<>();

    @Override
    public void add(T x) {
        if(!l.contains(x)){
            l.add(x);
        }
    }

    @Override
    public void clear() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'clear'");
    }

    @Override
    public boolean isEmpty() {
        return l.isEmpty();
    }

    @Override
    public Iterator iterator() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'iterator'");
    }

    @Override
    public void remove(T x) {
        l.remove(x);
    }

    @Override
    public int size() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'size'");
    }
    
}
