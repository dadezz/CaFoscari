# Progetto 

## kaggle
* raccolta di contest in cui viene chiesto a chiunque di risolvere un task di machine learning
* è stata scelta una di queste come contest.
* C'è una scadenza, ma ai dati si ha accesso anche dopo quindi non c'è da preoccuparsi
* i partecipanti posssono condividere il codice, quindi possiamo trarre ispirazione da altri, purché sappiamo esattamente cosa fa ogni riga di codice
* c'è un form di discussione
* c'è una leaderboard (tanto perderei)
* posso anche creare jupiter notebook che girano sui loro server, che magari ha risorse migliori della macchina locale, e non c'è bisogno di scaricarsi i dati.

## task
predirre il livello di problematicità dell'utilizzo di internet nei minori.
Abbiamo accesso a divers tipi di informazione:
* demographics (età, sesso, ma anche roba tipo salute fisica: massa corporea, bmi, pressione saguigna etc)
* iis: la variabile che dobbiamo predire
* serie temporale di accelerometro (facoltativo usarlo percHé non vedremo a lezione)

una roba difficile è che tante misure sono mancanti. in particolare, l'iis è mancante per una buona fetta dei partecipanti al training test.
(dove l'etichetta non ce l'ho posso clusterizzare e intuire quale sarebbe quella giusta, altrimenti posso buttare via)

## cosa consegnare:
uno o più notebook con tutto quello che bisogna fare coi dati, e un report di non più di 5 pagine (font >10) di report. dopo ci sarà un orale in cui si può raccontare tutto, se non ci sta scritto nel codice.
Non c'è scadenza per la consegna, basta che sia entro l'anno. si può fare più volte, ma come lo scritto se lo si rifà, si rifiuta automaticamente il voto precedete, e se va peggio ti attacchi.

## si prevede che:
il progetto elabori i dati e confronti almeno due modelli di predizione. uno da sklearn e uno più avanzato, oer esempio lightgbm o xgboost o catboost.
bisogna dire quanto sono importanti le features. 
Se il modello sbaglia di molto, provare a investigare se c'è qualche particolarità in comune per quel gruppo

## valutazione
si valuta:
* il report (scrittura pulita e formale, discorsiva, plot fatti bene etc.)
* qualità del codice
* depth of analysis
* il voto fa media 30% con lo scritto, ma se insufficiente va ripresentato