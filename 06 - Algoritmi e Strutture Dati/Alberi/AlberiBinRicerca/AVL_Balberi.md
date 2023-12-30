Posso avere alberi binari di ricerca che possono essere sempre bilanciati?
* **ALberi AVL**: oltre alla chiave per ogni nodo è memorizzato il fattore di bilanciamento, cioè la differenza tra le altezze di sottoalbero sx e sottoalbero dx. Il valore assoluto deve essere sempre <= 1 su ogni nodo. Per delete e insert, ci sono tutta una serie di giri per mantenere bilanciato
* **B_Alberi**: hanno le seguenti proprietà:
  * tutte le foglie sono alla stesasa profondità
  * ogni nodo diverso dalla radice mantiene K(v) chiavi ordinate chiave1(v) <= chiabe2(v) <= ... <= chiaveK(v) t.c. t-1 <= k(v) <= 2t-1  con t >= 2
  * la radice mantiene almeno 1 e al più 2t-1 chiavi ordinate
  * ogni nodo interno v ha k(v)+1 figli
  * le chiavi separano gli intervalli di chiavi memorizzate nei sottoalberi: se C è una qualcunoque chiave di un sottoalbero di un nodo v, allora c1<= chiave1 <= c2 <= .... ck
* Alberi rosso-neri sono BST che hanno info aggiuntiva rispetto alla chiave che è il colore del nodo: rosso/nero. Stabliscono la distribuzione dei colori secondo certe regole, con questo invariante: il cammino più lungo sull'albero è lungo al max il doppio del cammino più breve --> l'albero risulta bilanciato