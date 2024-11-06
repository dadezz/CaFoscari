serie di messaggi; predire se spam o meno.
problema: non abbiamo le feature

serve in qualche modo crearsele
# procedimento

## divisione
ovviamente, divido train e set 

## baseline
classificatore più stupido possibile

## feature processing

### testo come insieme di parole
le mie feature saranno le parole. 

**opzione 1** la versione base è "contiene" e "non contiene" quella parola. poi potrei trasformare tutto in lowercase, togliere la punteggiatura. unisco tutte le parole dei vari set

da qui vado di albero di decisione. vedo subito un grandissimo aumento di accuracy (per esempio nell'esempio del prof si passsa da 82 in baseline a 97).
sto metodo è particolarmente stupido.

**opzione 2** uso le frequenze al posto del semplice "compare o no"

**opzione 3** non tutte le parole sono uguali (le parole "in" "a" etc non sono indicative di un argomento). come faccio a distinguerle? o con un dizionario esterno opure, idea basica, guardo se compare in tanti documenti se c'è in tutti non sarà assolutamente indicativa, se c'è solo in uno è olto specifica.
questo approccio si chiama TF-ID.
inverse docueìment frequency = log(#NumeroDocumenti / #numeroDocumentiInCuiCompare)

Il peso di ogni parola è dato quindi dal peso che dicevamo prima (frequenza nello specifico documenti) moltiplicato per idf. quindi se una parola è molto presente in un documento a lo è anche in tutti, viene smorzata l'importanza.

tendenzialmente dà un grande boost

#### more text processing
posso continaure a normalizzare, per esempio mettendo tutti i verbi all'infinito e, in generale, tornando all'"origine" di una parola. cosa che si chiama **lemming**.
o, un po' meno aggressivo, lo **stemming** toglie prefissi e suffissi. meno costoso ma a volte anche migliore, perché il lemming potrebbe rischiare di ridurre troppo l'espressività.

## naive bayes
è un classificatore che non abbiamo ancora visto.
Usa la probabilità condizionata
$$ P(X|Y) = \frac{P(X|Y)P(Y)}{P(X)} $$

in generale, qual'è la probabilità di una certa classe dato un set di conoscenze a priori? poi una volta che le ho tutte, classifico con la classe che massimizza la priorità. 
le feature in sto caso sono sempre la presenza della parola

leghiamo la probabilità di una classe a quante volte abbiamo visto una certa feature con quella classe lì nel nostro train. 

cosa succede se non ho mai visto una feature in una classe? tipicamente si fa la "Laplace Correction": faccio finta che ce ne sia una in più nel mio dataset che non ho visto -> N_ij+1 e N_i + v (v è la cardinalità delle eatures).