package MODULO2;

public class SingleLinkedList<T> implements List<T>{
    
    protected class Node {
        public T data;
        public Node next;

        public Node(T data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    /*
     * veri due campi della linked list. 
     * pointer e quanti ne ho
     */
    protected Node head;
    protected int size;

    
    public SingleLinkedList(){
        this.head = null; //non necessario xk se ne occupa java
    }


    @Override
    public void add(T x) {
        if (head == null){
            head = new Node(x, null);
        }
        else {
            Node n = head;
            while(n.next != null){
                n = n.next;
            }
            n.next = new Node(x, null);
        }
    }


    @Override
    public void clear() {
        head = null;    // multi shot, diciamo che per ora va ben cosi    
    }

    @Override
    public boolean isEmpty() {
        return head == null;
    }


    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {

            private Node n = head;

            @Override
            public boolean hasNext() {
                return n != null;
                /* ragionare sul perché n e non n.next */
            }

            @Override
            public T next() {
                T r = n.data;
                n = n.next;
                return r;
            }

        };
    }


    @Override
    public void remove(T x) {
        /* intanto scorriamo.
         * con l'iteratore o senza? 
         * l'iteratore ci dà l'elemento T dentro il nodo, a noi serve il nodo
         * ergo lo dobbiamo scrivere.
         * 
         * Mi evito la variabile di appoggio "head" usando un caso specifico per la head e un caso generale 
         * per il resto della lista
         */
        Node n = head;
        if (head != null){
            if (n.data.equals(x)){
                head = head.next;
                size--;
            }
            else {
                while (n.next != null) {
                    if (n.next.data.equals(x)) {
                        n.next = n.next.next;
                        size--;
                        return;
                    }
                }
            }
        }
    }


    @Override
    public int size() {
        return size;
    }


    protected Node getNode(int i){
        if (i <0 || i>= size())
            throw new RuntimeException(String.format("SingleLinkedList.get(): index %d out of bound %d", i, size())); 
        Node n = head;
        for(; i<0; i--){
            n = n.next;
        }
        return n;
    }

    @Override
    public T get(int i) {
        return getNode(i).data;
    }

    @Override
    public T set(int i, T x) {
        if (i <0 || i>= size())
            throw new RuntimeException(String.format("SingleLinkedList.get(): index %d out of bound %d", i, size())); 
        Node n = getNode(i);
        T old = n.data;
        n.data = x;
        return old;
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