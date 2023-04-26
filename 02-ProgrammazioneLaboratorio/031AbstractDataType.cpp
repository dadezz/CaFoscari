/**
 * lo stack è nu esemoio di ADT
 * 
 * ha definite 2 operazioni: 
 *  push = inserisco un elmento
 *  pop = estrae dallo stack l'elemtno che è dentro da meno tempo    (LIFO)
 * 
 * A sto punto, ho finito di spiegare lo stack. Il problema di come lo realizzo è un'altra questione
 * 
 * Lo stack è abbastanza semplice da implementare con le liste:
 * 
 * push -> prepend;
 * pop -> pop_front;
 * 
 * Se lavorassi col vector:
 * 
 * push -> inserisco in coda (push back)
 * pop -> elimino dalla coda (pop back)
 * 
 * Quando è utile una struttura a stack? 
 * abbiamo sempre detto che un algoritmo iterativo può essere trasformato in ricorsivo.
 * Come faccio però a fare il passaggio inverso? è sempre possibile a patto di utilizzare una struttura dati a stack.
 * Non ne vediamo la dimostrazione, ma è abbastanza intuitivo: mimo nella struttura a stack la parte di memoria,
 * con le relative chiamate a funzione nello stack.
 * 
 * Un esempio classico è la notazione polacca post-fissa, usata per molto tempo dalle calcolatrici scientifiche
 * programmabili HP.
 * 
 * Significa che l'operatore va combinato dagli ultimi due operatori.
 * 2+3 diventa 2 3 +
 * (2+3)*5 devo fare 2 3 + 5 *
 * 2+3*5 diventa 2 3 5 * +
 * 
 * Si noti la mancanza di parentesi
 * 
 * Con lo stack, rimuovo gli ultimi 2 operatori, li combino, faccio la push del risultato.
 * Non si sfrutta la commutatività, i numeri compaiono nella stesso ordine (tipo divisione e sottrazione sono ok).
 * Non ho bisogno nemmeno di parentesi né di regole di priorità
 * 
 * (2+3)*(5+7)  ->   2 3 + 5 7 + *
 * 
 * per implementare: faccio cin di un token alla volta. se è un numero faccio la push, se è un operatore faccio la pop
 * degli ultimi due e il push del risultato. 
 * 
 * 
 * ADT QUEUE
 * 
 * la queue ha due operazioni primitive:
 * 
 *  enqueue -> aggiunge un elemento
 *  dequeue -> estrae l'elemento  che è da più tempo    (FIFO)
 * 
 * Come implento la queue con le liste? ho due possibilità: append e rimozione da testa oppure prepend e rimozione da coda
 * La sol corretta è append + rimoziione da testa xk + vleoce e - spazio
 * 
 * come implemento invece coi vector?
 * Supponiamo che la queue possa contenere max 100 elementi, la porzione di array che contine gli elemtni può stare anche in mezzo,
 * dalla cella di indice from alla prima cella libera " to ". sia from che to, man mano che pusho dentro il vector, diventano più
 * grandi e viaggiano verso destra. prima o poi to arriva a 99. se agiungo un elemento, il prox lo metto a 0 (operatore modilo).
 * può  quindi capittare che to sia minore di from. posso inserire e togliere tutto sempre con difficolta costatnte
 * 
 * se faccio la enquee scrivo dentro a to e to++
 * se faccio enqeue toglo da from e from++
 * 
 * mi basta quindi controllare che il numero di elementi sia minore di size.
 * 
 * Unica roba: se from == queue, può essere che size sia 0 ma anche che size sia full.
*/
