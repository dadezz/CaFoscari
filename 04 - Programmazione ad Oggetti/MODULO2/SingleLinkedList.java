package MODULO2;

public class SingleLinkedList<T> implements List<T>{
    
    private class Node {
        public T data;
        public Node next;

        public Node(T data, Node next){
            this.data = data;
            this.next = next;
        }
    }

    private Node head;
    private int size;

    
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
    public boolean contains(T x) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'contains'");
    }


    @Override
    public boolean isEmpty() {
        return head == null;
    }


    @Override
    public Iterator<T> iterator() {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'iterator'");
    }


    @Override
    public void remove(T x) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'remove'");
    }


    @Override
    public int size() {
        return size;
    }


    @Override
    public T get(int i) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'get'");
    }


    @Override
    public T set(int i, T x) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'set'");
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