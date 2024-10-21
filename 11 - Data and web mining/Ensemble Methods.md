# Ensemble Methods
L'idea alla base è mettere insieme più classificatori per avere risultati migliori che non un classificatore singolo. 

**esempio**
ho 3 classificatori, col 33% di error rate.
1. la probabilità che tutti sbaglino è $ \frac{1}{3}^3 = \frac{1}{27} $
2. la probabilità che la maggioranza di essi sia sbagliata è - penso a tutte le configurazioni possibili, tipo i primi 2 che sbagliano, i secondi tue o tutti e tre - . faccio i conti e scendo al 26%
   
-> l'error rate è sceso dal 33 al 26 e l'accuracy è salita dal 67 al 74.

**quindi**
più unisco classificatori migliori sono i miei risultati. anche se i classificatori di partenza non sono poi sto granché.

**problema**
il punto 1. vale solamente per classificatori indipendenti. se ho un solo dataset, gli input sono gli stessi, quindi il calcolo non è davvero fattibile in questo modo. il miglioramento è quindi sovrastimato in generale (comunque significativo e ne vale la pena), e adesso andremo a vedere come si fa ad allenare più classificatori per poter eseguire il boost.
Voglio quindi trovare il modo di rendere gli esperimenti il più possibile indipendenti tra loro.

mi serve quindi
1. tanti diversi dataset qunti sono i classificatori
   1. banalmente si può pensare di fare uno split, ma si rischia di avere troppi pochi dati per ogni classificatore
   2. una migliore soluzione è il **sampling**
2. un modo di unire i risultati ottenuti:
   1. **moda** per i problemi di classificazione
   2. **media** per i problemi di regressione

# bagging algorithm
tipo particolare di sampling (con replacement)

creo un nuovo dataset campionando da quello originale. Ha la stessa dimensione del dataset originale. cosa significa con replacement? estraggo un'istanza a caso, la copio nel mio campionamento e poi la rimetto ne dataset orignale da cui rifaccio l'estrazione (quell'istanza piò potenzilmnte essere pescata un'altra volta).
Con il replacement posso avere campioni grandi ma diversi (hanno intersezioni obv). 

for i = 1, ... ,k
    1. create a bootstrap sample D_i of D
    2. Build a model M_i on D_i
prediction for instance x is the combination of all predictions M_i(x).

-----------------------------
come fa un sottocampione ad avere la stessa misura del dataset originale? sarà più piccolo, no?
ChatGPT said:

In realtà, nel bagging, ogni sotto-campione ha la stessa dimensione del dataset originale, ma viene creato attraverso il campionamento con sostituzione. Questo significa che, per ogni riga nel sotto-campione, viene scelta una riga dal dataset originale in modo casuale, e la stessa riga può essere selezionata più volte.

Quindi, se il dataset originale ha, ad esempio, 1000 righe, ogni sotto-campione creato avrà anch'esso 1000 righe. Alcune righe saranno ripetute, mentre altre potrebbero non essere incluse. Questa caratteristica consente di mantenere la dimensione costante, creando però una varietà di dati su cui addestrare diversi modelli.

------------------------------

# boosting
parte da un'idea ben diversa. Il bagging non garantisce di avere modelli sufficientemente diversi tra loro e quindi tendono a sbagliare uguale. 
ci piacerebbe focalizzarci su istanze su cui le nostre previsioni nn erano corrette.
Nel bagging pesco a caso, il boosting è diverso. Il modello è sequenziale. alleno uno, poi passo al secondo focalizzandomi sugli errori del primo e così via.
il sampling ha il replacement come il bagging, ci aggiungo però un peso, che è la probabilità di essere incluso in un sampling. per le istanze per cui non ho una classificazione corretta metto un peso maggiore, così il mio modello avrà più istanze in cui si comporta male, così facendo cerco di compensare gli errori precedenti.
Dopo aver allenato un modello, posso misurare l'errore così:
$$
error(M_1) = \frac{1}{N} \sum_{(x_j, y_j)\in D} {w_j \cdot 1[M_j(x_j) \neq y_j]}
$$

l'errore lo uso per dare un peso anche al modello, non solo alle istanze.

Così anche le predizioni sono pesate, quando metto insieme i modelli. 
Poi calcolo alfa.
se l'istanza x è classificata correttamente, allora il suo peso viene aggiornato così: $ w_i = w_ie^{-\alpha} $
altrimenti alpha va mantenuto positivo. 
poi normalizzo così trasformo in [0, 1]
in questo modo, istanze corrette hanno numeri molto piccoli (bassa probbilità).


L'accuracy aumenta MOLTO meglio che non col bagging. Funziona davvero molto bene, anche su modelli scarsi

# intuizioni finali
Cosa fanno realmente i due algoritmi? è sempre preferibile il boosting al bagging?
torniamo a bias/variance
avere un basso bias vuol dire che il modello è molto espressivo, se è alto, non riesco a catturare i dati.
avere alta varianza vuol dire che a cambiare il campione cambia la predizione.
il bagging è un modo per abbassare la varianza, il boosting abbassa il bias.

da cui, se ho un modello con basso bias, fare il boosting è inutile. e stessa roba vale per varianza e bagging.
l'errrore può essere matematicamente diviso così:
$$
Error(M) = Bias^2+Variance+Noise
$$

noise = errore irriducibile, tipo etichette sbagliate o features sblagliate.