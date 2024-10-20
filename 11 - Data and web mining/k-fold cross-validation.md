hai presente la roba del dividere i dati in test / train / validation?

può essere che vado a prendermi un validation set sfortunato. in generale, sto andando a decidere quali sono i parametri miglori basandomi su un validation set che è una piccola percentuale dei dati e può essere che mi becco la sfiga di prendermi quella poco significativa o sballata. Posso prendere la decisione basandomi su tutti i miei dati e non solo su questi? 
# cross validation
sostanzialmente consiste nel ripetere pià volte il test di valutazione. sostanzialmente partiziono in 5 il dataset. ripeto l'esperimento ogni volta usando come validation una di queste partizioni e lasciando le altre 4 a fare training. La media degli iperparametri è la misura finale delle perormaces. In sto modo sono riuscito a prendermi tutto il dataset come validatore. 
Sta rova è già implementata a livello di libreria da sklearn, perché è procedura standard. 

## stratified sampling
un campionamento casuale rischia di avere degli sbilanciamenti. se per esempio prendo un validation con un 70/30 tra le due classi, quel set tenderà a favorire i modelli che sono più accurati solo sulla prima.
**stratified sample:** al posto di scegliere campione casuale e basta, scelgo campione casuale nella classeA e poi un campione casuale nella classeB, così mantengo il bilanciamento originale. 
È usato automaticamente da sk-learn durante la cross validation

