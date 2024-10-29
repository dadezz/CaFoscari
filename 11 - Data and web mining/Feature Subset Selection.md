# Feature Subset Selection
dato un dataset di feature indicare solo quelle davvero interessanti.

Anche se devo trovarmi io le feature, inizialmente posso pensare che più info dò meglio è, ma abbiamo visto che ci possono essere correlazioni spurie che vanno a sporcare le previsioni. 
In linea generale non è facile capire il sottinsieme migliore. l'ottimo oltretutto sarebbe provare tutti i subset -> 2^n. infattibile.

i metodi dsvluppati sono sostanzialmente in 3 categorie
* embedded: alcuni algortmi per costruzione hanno una forma di selezione di feature. per eesmpio l'albero di decisione a ogni nodo sceglie alcune feature. se non vengono selezionate possiamo pensare di toglierle perché inutili
* filter: feature selezionate **prima**: matrice di correlazione tra tutte le coppie di feature. possono essere ridondanti (correlazione altissima) o scorrelate con la label.
* wrapper: guardo l'acccuracy se cambia o meno aggiungendo una feature

## wrapper
va bene su qualunque modello, non faccio assunzioni che sia albero o altro.
* sequential forward selection: greedy. sequenzialmente, viene aggiunta una feature alla volta al sottinsieme selezionato. mi fermo quando l'incremento è marginale o quando raggiungo il numero di feature massima desiderata
* sequential backward selection: al contrario di prima, parto da tutte e ne tolgo una alla volta

## embedded approach based on feature importance
prendiamo come esempio di riferimento una random forest. ad ogni nodo un albero sceglie la miglior feature. Se una feature non è mai stata utilizzata la butto via. o se è usata su una root è più importante che su una foglia .
oppure, sfruttiamo il gain calcolato sull'utilizzo della feature: se la feature da un bel guadagno, la butto meno via di una che dà un guadagno infimo.
OBV stiamo scartando feature che vanno bene su quel modello.
posso usare un modello buono ma poco costodo per selezionare le feature e poi mettere il subset selezionato su un modello costoso che è quello reale che voglio usare, così da diminuire il costo.
Allenando il modello ottengo uno scoring delle features.
Che succede se ho due features uguali nel dataset, che importance avranno? dipende dall'implementazione dell'algoritmo. diciamo che prenderò alternativamente una o l'altra, quindi l'importance sarà dimezzata.
se selezionassi le feat con maggior importance, potrebbe vapoitare che andrei a elimanre una feature molto importante ma smezzata. Cio invece non accadrebbe nel caso io procedessi con eliminazione progressiva dalla meno importante: 
elimino una, ricalcolo, elimino una, ricalcolo e così via. in sto modo, quando elimino una delle due correlate, l'altra assume di nuovo la importance giusta, e il tutto è più safe.
**recursive elimination**: simile alla backward, ma guardo l'importance (è quello appena spiegato). in sklearn è sklearn.feature_selection.RFE
di nuovo, come faccio a trovare il numero giusto dei parametri? uso cross validation, come per trovare il miglior numero di alberi nella foresta. di nuovo fa tutto sklearn.
 