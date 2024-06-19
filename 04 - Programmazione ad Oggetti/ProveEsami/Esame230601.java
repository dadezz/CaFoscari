package ProveEsami;

import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;

public class Esame230601 {
    
}
/*ogliamo realizzare in Java 8+ una classe BST, parametrica su un tipo generico T, che rappresenta alberi binari
di ricerca (Binary Search Tree) i cui nodi sono decorati con valori di tipo T. Un albero binario di ricerca `e un
normale albero binario, tuttavia gli elementi al suo interno vengono mantenuti con un certo ordine dato da una
peculiare propriet`a ricorsiva.
il nodo radice ha un valore superiore a tutti i nodi del sotto-albero sinistro ed inferiore a tutti i nodi del
sotto-albero destro. E questo `e vero non solo prendendo in esame la radice dell’albero, ma prendendo qualsiasi
nodo in qualunque punto dell’albero!
Quando si inserisce un nuovo nodo nell’albero `e necessario metterlo nel punto giusto, rispettando questa propriet`a,
cos`ı che l’albero sia sempre in uno stato valido.
Segue l’implementazione da completare della classe BST. */

class BST<T> implements Iterable<T> {
    
    protected final Comparator<? super T> cmp;
    
    protected Node root;
    
    protected class Node {
        protected final T data;     //dato
        protected Node left, right; //puntatori
        protected Node(T data, Node left, Node right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
        protected Node(@NotNull T data) {
            this(data, null, null);
        }
    }
    public BST(Comparator<? super T> cmp) {
        this.cmp = cmp;
    }
    public void insert(T x) {
        root = insertRec(root, x);
    }
    /*Si implementi ricorsivamente il metodo insertRec() badando a rispettare la propriet`a degli alberi
    binari di ricerca enunciata sopra. Per determinare se discendere nel sotto-ramo sinistro oppure in quello destro
    `e necessario utilizzare il Comparator passato in costruzione per confrontare l’argomento x con il campo data
    del nodo n */
    // 1.a
    @NotNull
    protected Node insertRec(@Nullable Node n, @NotNull T x) {
        if (n == null)
            return new Node(x);
        int r = cmp.compare(x, n.data);
        if (r < 0)
            n.left = insertRec(n.left, x);
        else if (r > 0)
            n.right = insertRec(n.right, x);
        return n;
    }
    /*Gli alberi devono essere iterabili e l’iteratore deve attraversare l’albero in DFS (Depth-First Search), fornendo
    gli elementi di tipo T secondo il criterio denominato in-order, che consiste nel visitare prima il sotto-ramo
    sinistro, poi il nodo, poi il sotto-ramo destro. */
    protected void dfsInOrder(Node n, Collection<T> out) { 

    }
    @Override
    public Iterator<T> iterator() {
        
    }
    public T min() {

    }
    public T max() {

    }
}