# Caratterizzazione degli alberi

Se G è un grafo non orientato, allora sono equivalenti le seguenti affermazioni:
1. G è un albero
2. due vertici qualsiasi di G sono connessi da un unico cammino
3. G è connesso, ma se un arco qualsiasi è rimosso da G allora il grafo risultante è disconnesso
4. G è connesso e |E| = |V|-1
5. G è aciclico e |E| = |V|-1
6. G è aciclico ma se aggiungo un arco qualisiasi allora il grafo risultante ha almeno un ciclo

# Alberi di copertura minimi (MST)

non orientato, connesso. Un albero di copertura è un sottinsieme di archi che formano un albero e toccano tutti i vertici del grafo.
Più formalmente: un albero di copertura è un insieme T di archi tale che (V, T) è un albero
Ora, considerando un albero connesso pesato sugli alberi, diversi alberi di copertura hanno diversi pesi. È in sto contesto chce si inserisce il MST

Il MST gode sdi queste proprietà:
1. T sia un albero di copertura
2. W(T) sia il più piccolo tra tutti gli alberi i copertura