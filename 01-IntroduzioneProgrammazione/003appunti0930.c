/*
30 settembre
*/
#include<stdio.h>

int main1 (){
    int n;
    char a = 'A'; //il carattere va tra singoli apici, non virgolette (stringhe)
    
    printf ("hello world\n");
    
    return 0;
}

/*
C non è un linguaggio a oggetti, per le funzioni usa il linguaggio mtematico, e pure la sintassi (tipo le funzioni: 
f(arg)).Un linguaggio di programmazione di base fa cose molto generali, non risponde direttamente a tutte le esigenze, 
per quelle vengono utilizzate le funzioni, all'interno delle librerie o create da noi stessi. 
Una libreria è un pacchetto di funzionalità, fornito insieme al linguaggio, che permette di espandere le potenzialità, 
senza dover riscrivere tutte le funzioni da 0 ogni volta. le librerie si richiamano dall'include.
Nella libreria standard ci sono le funzioni base: input, output, lettura file, gestione stringhe etc etc.
La libreria std è fatta di tanti moduli, non serve includerla sempre, basta includere il modulo necessario. per l'input
e l'output, basta includere il pezzo che si occupa di ciò nella libreria standard: "standard i/o" (stdio).
Le librerie hanno formato .h, che va aggiunto sempre, ma spiegheremo in un altro momento.

dopo l'inclusione delle librerie, il linguaggio c include una mega funzione con tutto il prgoramma all'interno, di nome
standard "main" (main1 è voluto proprio per non essere il programma principale).
perché si scrive all'interno di una funzione e non diretto? Un sorgente c è fatto esclusivamente di funzioni, non di
comandi. Come in una stiva di un aereo si mettono le cose in valigia e non tutto buttato dentro, così su c si usano 
le funzioni. è una questione di ordine e fomra, non di sostanza. 
La funzione main è quella principale, da cui il programma parte. le altre fuznioni possono essere richiamate dal main, 
ma non viceversa.

riga7 e 8banali.
short e long: tipi numerici di dimensione specifica (interi). short fino a 65535, 2byte, long ha 8byte in complemento a 2.
char 1 byte, int 4, float 4 
*/