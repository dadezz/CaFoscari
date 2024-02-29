package MODULO2;

public class ArrayList<T> implements List<T> {
    private Object[] a;
    private int size;

    public ArrayList() {
        this.a = new Object[10];
        this.size = 0;
    }

    public void add(T x) {
        if (size >= a.length){
            Object[] old = a;
            a = new Object[a.length*2];
            for (int i=0; i<old.length; i++)
                a[i] = old[i];
        }
        a[size++] = x;
    }

    public void clear() {
        size = 0;
    }

    /*
        lancio un'eccezione checked o unchecked?
        se dichiaro di lanciarla, chi la usa è obbligato a catcharla o propagarla.
        Se non lo faccio non compila, non puoi evitare di catchare.
        Quando si fan le librerie, bisogna pensare se ha senso che quel metodo obblighi l'utente 
        a fare qualcosa o se può fregarsene
    */
    public T get(int i){
        if (i<size) return (T) a[i];
        else 
            throw new RuntimeException(String.format("ArrayList.get(): index %d out of bounds %d", i, size));
    }

    public T set(int i, T t){
        if (i<size){
            T z = (T) a[i];
            a[i] = t;
            return z;
        }
        else 
            throw new RuntimeException(String.format("ArrayList.get(): index %d out of bounds %d", i, size));
    }

    // Iterator è un'interfaccia, non posso lanciarla, quidni mi tocca 
    // fare una nested class per implementarla.
    // questa nested class non è statica. se fosse static, non avrei il this della enclosing.
    // se la class è static, non compila size, get e anche T. 
    // cosa fa static? 
        // metodo: manca this
        // class: ugualmente manca this (quello dello stronzo che sta fuori, non il suo).
    // lo stesso film si applica ai generics
    private class MyIterator implements Iterator<T> {
        int pos = 0;
        @Override
        public boolean hasNext () {
            return this.pos < ArrayList.this.size();//posso specificare un this di una classe enclosing 
                                                    //(quindi che racchiude la mia), size è di ArrayList, non di Myiterator
                                                    //non serve scriverlo, se non è necessario disambiguare
        }

        @Override
        public T next() {
            return get(pos++); //la get è dell'enclosing
        }
    }
    public Iterator<T> iterator() {
        return new MyIterator();
    }

    public boolean contains(T x){
        Iterator<T> it = iterator();
        while(it.hasNext()){
            T o = it.next();
            if (x.equals(o))
                return true;
        }
        return false;
    }

    public void remove (T x){
        for (int i=0; i<size(); i++){
            T o = get(i);
            if (o.equals(x)){
                for (int j=i; j<size()-1; j++){
                    set(j, get(j+1));
                }
                --size;
            }
        }
    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'isEmpty'");
    }

    @Override
    public int size() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'size'");
    }

    @Override
    public void add(int index, T x) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'add'");
    }

    @Override
    public T remove(int index) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'remove'");
    }
}