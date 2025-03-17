# http
protocollo di trasferimento per ipertesti
## messaggi
> **metodo**    risorsa   versione    \n
> [host / cookies]
>
> body

## risposta
> versione CodiceDiStato
>
# pwntoools
Modulo python che offre strumenti per connettersi e interagire da remoto con un altro host, permette di 
* connetterrsi da remoto
* inviare butes
* ricevere bytes, interagire manualmente con l'host

permette di fare packing e unpacking di valori e indirizzi da 8, 16, 32, 64 bit. usando eventualmente bit di padding, utile per inviare interi e non stringhe. posso scegliere se little o big endian, di default è little

pwntools:elf
estrarre info da un file elf e interagire con un processo. l'interazione avviene come col modulo tubes, le info che si ottengono sono indirizzi di funzioni, indirizi nelle sezzioni got e plt, indisizzi di stringhe di bytes

# comandi:
* file : stampa info sul file (arch, stripped, 32/64 bit, linking etc)
* strings: mostra tutte le stringhe di caratteri stampabili
* ldd: mostra librerie linkate dinamicamente
* readelf: analizza un elf -h header -s imboli -S sezioni etc
* objdump: simile, , permette di disassemblare il codice (da binario passa a assembly)
* gdb: debugger, a noi interessa per C. permette di monitorare e modificare il flusso di esecuzione (breakpoints). posso vedere lo stato del programma ad ogni punto
  * per far partire l'exec si usa run
  * per mettere breakpoint b
  * start simile a run e si derma subito
  * continue va fino al prox break
  * next un passo alla volta
  * si possono vedere i registri con info registers
  * si possono cambiare i valori dei registri con set reg = val
  * si vede la memoria con x/nfu (numero di blocchi, formato dell'output, numero di byte per blocco). di default è /1xw.
  * si possono installare delle estensioni che lo rendono migiore: owngdb:
    * permette di vedere info in modo migliore. disassemmbly, stack, registri, heao, vmmap, telescope
  *  gef , peda
*  ghidra:
   *  aprire un eseguibille e vedere da un lato le istruzioni in assembly e anche un decompilato