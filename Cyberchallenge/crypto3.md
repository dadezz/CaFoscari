# hash
l'output si chiama digest. 
Cosa può essere una funzione hash? 
banalmente, l, o s[0], o s^e mod n sono tutte funzioni hash valide
al contrario per esempio la funzione identità non è una funzione hash valida, in quanto non è di lunghezza fissa

## hash crittografico
- one way
- resistente a collisioni -> per definizione, ci sono infinite collisioni. si intende che non si possono trovare facilmente e che è ragionevolmente improbabile trovare 2 hash ugugali (sufficienti bit di entropia per esempio)

negli hash crittografici, un piccolo cambiamento dell'input cambia in maniera drastica l'output -> definito effetto valanga. Questo non evita ovviamente le collisioni, ma le evita tra messaggi simili.
non esiste algoritmo efficiente esplicito per trovare collisioni. 

3 livelli di resistenza (in ordine di forza): 
1. impossibilità di risalire dal digest al messaggio originale
2. è difficile, dato il primo messaggio, trovare un secondo messaggio che è collissione col primo
3. è difficile, in generale, trovare una coppia di messaggi che collidono.

come trovare collisioni?
paradosso dei compleanni -> quante persone devono esserci in una stanza affinché con probabilità >= 50% 2 persone abbiano lo stesso compleanno? solo 23! è controintuitivo. basta poco per garantire una buona probabilità che si verifichi sto evento.

Questo concetto può esserci utile per le collisioni hash. consideriamo un digest di n bit
- prendi $ 2 ^{n/2} $ diversi messaggi.
- guarda se ci sono messaggi con lo stesso digest. 
- se non ne troviamo, ripeti di nuovo.

per trovare di per certo delle collisioni servirebbero $ 2^n +1 $ messaggi. ma per avere una buona probabilità? $ 2 ^{n/2} $

github.com/corkami/collisions

# merkle damgard paradigm
compression function: fixed_lenght x fixed_lenght = fixed_lenght

supponiamo di avere una compression function:

1. prendi il messaggio
2. aggiungi il padding per avere la lunghezza necessaria 
3. dividi in k blocchi di lunghezza c
4. inivia con un inizialization vector fissato
5. applica in catena la compressione, a patire dal vettore x il primo blocco, poi il risultato x il secondo blocco etc

se scegliamo bene questa compression function, il risultato sarà resistente alle collisioni. 
quale può essere quindi?

1. block cypher
2. il blocco corrente è usato come chiave
3. il precedente risultato intermedio è usato come plain text
4. l'output è xorato coll'output del blocco precednte

quindi: applicazione di cifrario simmetrico + xor

è sicuro dal pov crittografico. MD5, sha1 e sha2 usano tutte sta roba

# md5
produce 128 bit di digest. 