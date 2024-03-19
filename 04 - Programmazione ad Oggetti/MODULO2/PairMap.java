package MODULO2;

public class PairMap<K, V> implements Map<K, V> throws Map.KeyNotFoundException {

    private List<Pair<K, V>> l = new ArrayList<>();

    @Override
    public void put(K k, V v) {
        l.add(new Pair<>(k, v));
    }

    @Override
    public V get(K k) {
        Iterator<Pair<K, V>> it = l.iterator();
        while(it.hasNext()){
            Pair<K, V> p = it.next();
            if (p.first.equals(k))
                return p.second;
        }
        throw new KeyNotFoundException(k);
    }

    @Override
    public Iterator<Pair<K, V>> iterator() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'iterator'");
    }
    
}
