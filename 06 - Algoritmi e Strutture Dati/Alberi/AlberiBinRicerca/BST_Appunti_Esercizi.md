# Minimo
* pre: x è in T, alberoBinRIc
* post: restituisce il nodi che contiene chiave minima

sempre a sinisrta:
```rust 
Tree_min(x) {
    while x->left != NIL
        x = x.left
    return x
}
```
# Massimo 
analogo a dx
# Predecessore e successore
L'ordine è dato dall'output di una visita simmetrica.
Dato un nodo, voglio trovare un suo predecessore e successore nell'ordine stabilito in una visita simmetrica.

* Se il nodo ha un figlio destro, il successore è il minimo del sottoablero destro
* Se non ha un figlio destro, l'antenato più prossimo di x il cui figlio sx è antenato di x. O, più semplicemente, la prima svolta a destra risalendo verso la radice

```rust
fn Tree_succ(x) {
    if x.right != NIL
        return Tree_min(x.right)
    else 
        y = x.padre
        while y != NIL AND x == y.right
            x = y
            y = y.padre
        return y
}
```

predecessore è simmetrico

# Inserimento

* pre: z è un nodo t.c. z.key = v e z.left = z.right = NIL
* post: inserisco il nodo z in T mantenendo le proprietà di albero binario di ricerca

```rust
fn Tree_insert(T, z){
    y = NIL
    x = T.root
    while x != NIL
        y = x   //diventa il padre di z
        if z.key < x.key
            x = x.left
        else 
            x = x.right
    z.p = y
    if y == NIL /* l'albero era vuoto */
        T.root = z
    else 
        if z.key < y.key
            y.left = z
        else 
            y.right = z
}
```

# Eliminazione

* se z è una foglia, modifichiamo suo padre z.p oer sostituire z con NIL
* se z ha un unico figlio, stacchiamo z creando un collegamento tra suo figlio e suo padre
* per eliminare un nodo "completo", bisogna sostituirlo col suo successore.

definiamo un'operazione ausiliaira: spostare sottoablero con radice in v nella posizione del sottoablero con radice in u

```rust
fn Transplant(T, u, v){
    if u.p == NIL
        T.root = v
    else 
        if u == u.p.left
            u.p.left = v
        else 
            u.p.right = v
    if v != NIL
        v.p = u.p
}
```
Il costo di questa operazione è costante

```rust
fn Tree_delete(T, z){
    if z.left == NIL
        Transplant(T, z, z.right)
    else if z.right == NIL
        Transplant(T, z, z.left)
    else 
        y = Tree_min(z.right) // successore
        if y.p != z
            Transplant(T, y, y.right)
            y.right = z.right
            z.right.p = y
        Transplant(T, z, y)
        y.left = z.left
        y.left.p = y
}
```

# Costruzione albro binario di ricerca
Avendo Tree_insert possiamo pensre di usare quella. 
* pre: A array che contiene le chiai che voigliamo inserire in T

```rust
fn BuildBST(A) {
    t = newTree()
    for i = 0 TO A.size
        u = CreaNodo(a[i])
        TreeInsert(t, u)
    return t
}
```

Qual è la complesità di questa funzione? treeinsert è o(h), i l for è fatto da a.size. Nel caso peggiore, tipo input ordinato in modo crescente, creo un albero complemamente sbilanciato, e diventa O(n²).

Serve una procedura migliore. Partiamo dal caso peggiore di array ordinato: 
* pre: A è ordinato

un'idea è partire dal coso centrale e ricorsivamente fare uguale nei due sottoarray dx e sx

```rust
fn BuildBSTott(A){
    t = newtree()
    t.root = buildBSTott_aux(A, 1, A.length, NIL)
    return t
}
fn BuildBSTott_aux(A, inf, sup, padre){
    if inf>sup
        return NIL
    else
        med = parte_intera((inf+sup)/2)
        r = creaNodo(A[med])
        r.p = padre
        r.left = buildBSTott_aux(A, inf, med-1, r)
        r.right = buildBSTott_aux(A, med+1, sup, r)
        return r
}
```

vantaggio? è un albero bilanciato, con altezza log(n).

T(n)= {
    c                   se n= 0
    2T(n/2) + d         se n>0
}

applico master theorem f(n) = d; n ^ (log2(n²)) = n
siamo nel caso primo -> O(n) 

Se l'input non è ordinato? Prima si ordina e poi si applica sto algoritmo. Anticipo che l'ordinamento sta in nlogn, quindi la complessità massima totale è nlogn

# Esercizi
## 1
dati due numeri x e y definiamo la distanza tra xe y come d(x, y) = |x-y|. Sia T un albero binario di ricerca le cui chiavi sono numeri interi e avente almeno due nodi. Scrivere una funzione efficiente che restituisca la sditanza minima fra le chiavi di due nodi di T

ipotesi forti a disposizione: 
* albero binario di ricerca
* almeo due nodi presenti

Visito l'albero in modo smmetrico, così ordino l'insieme delle chiavi -> la distanza minima tra due chiavi va cercata nelle coppie successive e non in tutte le coppie disponibili. È una banale visita + un for su array -> 2N -> Theta di N


```rust
fn DistanzaMinima(T){
    x = Tree_min(T.root)
    y = Tree_successor(x)
    mind = y.key-x.key
    x = Tree_successor(y)
    while x != NIL
        diff = x.key - y.key
        if diff < mind:
            mind = diff
        y = x
        x= TreeSUccesor(y)
    return mind
}
```

L'attraversamento simmetrico di un albero binario di ricerca di N nodi può essere implementato trovando l'elemento minimo nell'albero con la procedura tree_min e poi effettuando n-1 chiamate di tree_successor. Viene eseguito in tempo THETA(n).
DIMOSTRAZIONE BLANDA:
la chiamata  atree min seguita da n-1 chiamate a tree.succ esegue esattamente una visita simmetrica come fa la procedura in order. Infatti, INORDER stampa prima il minimo (il valore di tree_min) e poi per definizione il tree_succ è il prox nodo di una visita simmetrica. 
l'algortmo richiede come minimo Omega(n) perché fa n chiamate di funzione. Inoltre attraversa al più 2 volte gli n-1 archi dell'albero, da cui O(n). PercHé al più due volte? una volta scendendo e una volta risalendo. INfatti:
sia (u, v) un generico arco. Partendo dalla radice dobbiamo attraversare (u, v) da u a v prima di attraversarlo nel senso opposto. L'unico modo di attraversarlo da u a v (downword) è nella funzione tree_min, mentre upword nella tree_succ quando il nodo non ha un figlio destro.

# Esercizi
## 1
Scrivere una funzinoe effic che, dato una alb bin ric verifica se è sddisfatta la seguente condizione: per ogni intero k se le chiavi k e k+2 sono nellì'albero, allora anche al chiave k+1 è nell'albero

come faccio a verificarla? basta verificare quando non è veriicata: se ho una chiave k e il successore è k+2, non è verificata

```rust
fn check(T) {
    u = t.root
    if u == NIL
        return true
    u = Tree_min(u)
    ok = true
    while(u != NIL && ok)
        succ = Tree_succ(u)
        if (succ != NIL && succ.key == u.key+2)
            ok = false
        else
            u = succ
    return false
}
```

T exec è O(n).

## 2
Dato un alb bin, scrivere una f che controlli se l'albero è un alb bin ric

usiamo la definizione di albbinric 

```rust
fn checkBST(u){
    if u == NIL
        return true
    else 
        < ris, min, max > = check_aux(u)
    return ris
}
fn check_aux(u){
    if (u.left == NIL)
        rissx = true
        minsx = u.key
        maxsx = u.key
    else 
        <rissx, minsx, maxsx> = check_aux(u.left)
    if u.right == NIL
        risdx = true
        mindx= u.ey
        maxdx = u.key
    else 
        <risdx, mindx, maxdx> = check_aux(u.right)
    if !rissx || !risdx || maxsx>u.key || mindx<u.key
        return <false, -, ->
    else 
        return <true, minsx, maxdx>    
}
```

La complessità è theta(n) in quanto visita.

in alternativa, usiamo il teo appena dimostrato che una visita simmetrica non decrescente implica un BST
```rust
fn check(u){
    if u == NIL
        return true
    ok = true 
    u = Tree_min(u)
    while (u!= NIL && ok)
        succ = Tree_succ(u)
        if (succ!=NIL and succ.key < u.key)
            ok = false
        else 
            u=succ
    return ok
}
```