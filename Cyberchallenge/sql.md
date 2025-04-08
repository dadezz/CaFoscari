# sql injection
## categorie
* in band i dati sono esfiltrati direttamente dove l'attacco è eseguito
* blind: il risultato non è visibile nella pagina
* out of band: dati esfiltrati tramite side channel
### in band: 
* dirette: direttamente visibili nella pagina
* error-based: visibili in messaggi d'errore

    ```sql
    ' and 1=convert(int, select 1 table_name from information_schema.tables)
    ```
* union-based: combina multiple select
    si può defnire il numero di colonne per esempio unendole con null.
    poi si può guardare il tipo, a tentativi
### blind
* boolean based: cerca di far ritornare alla pagina risultati differenti in base al risultato della query
    si basano su un oracolo booleano. 
    ```sql
    select * from products where prod_name = "$input"
    ```
    on success, la pagina ritorna product in stock, on error ritorna out of stock.
    sta cosa per esempio si può fare carattere per carattere un bruteforce su una password.
    sti attacchi vanno automatizzati
* time based: si basano nel causare del delay nelle risposte: se l'attacco ha successo si vedrà un delay
    sfruttano il tempo di risposta. usando la stessa query di prima: mettendo in input `x' or sleep(3)`. ugualmente si possono guardare carattere per carattere le password, guardando con le sleep se il carattere è corretto. sono le più difficili da usare perché possono dare falsi positivi

## step 
dopo aver capito se è exploitabile, va capito qual è il DBMS usato. questo perché non tutti hanno la stessa sintassi. per esempio sleep() è mysql, su postgre è pgsleep(). 
con `select @@version``, se è mysql, viene fuori. In mysql i nomi di tabelle e clonne sono mantenuti in information_schema


1. detect
2. understand vulnerability type
3. detect DBMS
4. examine the database
5. exploit

## stacked queries
è figo, perché se ho la possiblità di fare più query posso fare rce -> usare alcune query per esempio di postgre che copiano qualcosa sul programma. posso copiare del bash per esempio e aprirmi una reverse shell

# logic vulnerability
vulnerabilità sulla logica di esecuzione, non di tipo tecnico. Se gli orm prevengono le injection, niente previene queste-

* il tipo più comune è causato da false assunzioni dello sviluppatpre -> broken access (utenze coi ruoli mal definiti) -> privilege escalation verticale
* IDOR: un'altra molto presente. acccade quando un identificativo può essere usato per accedere a varie cose senza controlli. privilege -> privlege escalation orizzontale (rubo altri utenti)
* un altra roba è quando l'input è validato solo in front end, in quel caso si può mandare direttamente una richiesta a backend
