# Memoria condivisa
## Thread
Componente di esecuzione di un processo (parte dinamica). La parte di memoria e di risorse non fa parte dei thread. Infatti, un processo può avere tanti thread, che condividono le stesse risorse, senza duplicarle
### Produttore - Consumatore
```c
void Produttore() {
    while (1){
        // produce dati


    }
}
void Consumatore() {
    while(1){
        d = ...
        // consuma dati
    }
}
```

vogliamo implementare questo meccanismo in due modi diversi: uno è col message passsing (send-receive  /  porte  /  pipe), l'ltro è in memoria condivisa.

#### message passing
```c
void Produttore() {
    while (1){
        //mando messaggio d sulla porta A
        send(A, d);
    }
}
void Consumatore() {
    while(1){
        // consuma i dati in indirizzo d sulla porta A
        receive (A, &d);
    }
}
```

sta roba è ok, l'abbiamo già vista nelle pipe, anche con tutti i dettagli su a/sincrono.

#### Memoria condivisa
Pensiamo di avere un buffer di dimensione illimitata. Come realizzo lo scambio di info tra i due thread? 
Ricordiamo l'esempio del ristorante. C'è una barra infinita a cui si appendono le comande. Il cameriere è il produttore, che mette le comande sulla barra. L'unica roba che deve ricordarsi è l'indice a cui ha appeso l'ultima comanda.
```c
data_t buffer[infinito];
int inserisci = 0;
Produttore(){
    while (1){
        buffer[inserisci++] = d;
    }
}
```
Sto scrivendo in memoria, senza syscall.
c'è  un problema però. Il consumatore non può leggere roba che non esiste, serve busy waiting. Questo perché non voglio scomodare il sistema operativo che ti sospenda
```c
int preleva = 0;
Consumatore(){
    while(!){
        while(preleva == inserisci) {} //  busy waiting: preleva non supera mai inserisci
        d = buffer[preleva++];
    }
}
```

Ora. sta roba è giusta ma non implementabile, in quanto non esiste memoria infinita. Si può simulare la coda con un buffer circolare.

```c
Produttore(){
    while (1){
        buffer[inserisci] = d;
        (++inserisci) % max;
    }
}

Consumatore(){
    while(!){
        while(preleva == inserisci) {} //  busy waiting: preleva non supera mai inserisci
        d = buffer[preleva];
        (++preleva) % max;
    }
}
```

manca un ltima cosa:se il buffer si riempie vado a sorascrivere i foglietti. La send deve essere asincrona finché il buffer è vuoto, quando si riempie devo aspettare che venga letto. 
Non posso mettere la stessa condizione sennò all'inizio, che sono uguali, nessuno fa nulla e si blocca il programma. Un trucchetto è fermarmi una cella prima.
```c
Produttore(){
    while (1){
        while((inserisci+1)%max == preleva) {}
        buffer[inserisci] = d;
        (++inserisci) % max;
    }
}
```

Non è la cosa ideale, ma funziona.Ha il difetto che è busy waiting e che spreca una cella. Per la cella si può risolvere con un flag che ti dica se puoi o meno leggere/scrivere. Il modo più semlice, ovvio ed effcieitne di avere il flag è usare un contatore che segni quante celle sono piene (e incremento/decremento in scrittura/lettura).
Il problema di sta soluzione è che è sbagliata, lol. Preleva e inserisci sono modificate indipendentemente, mentre contatore è acceduto da entrambi. C'è competizione tra i due thread che rischia di creare inconsistenze sui dati.
### Race Condition
due thread modificano la stessa variabile possono creare interferenze o inconsistenze. Questo perché?
leggo dalla ram dentro un registro -> opero nei registri -> scrivo. Quando faccio contatore++, faccio
```
load contatore, r1  // passaggio 1a
r1 = r1 + 1  // passaggio 2a
store contatore, r1 // passaggio 3a
```
questo lo fanno entrambi i thread (i registri non interferiscono). Cosa può andare storto? per esempio in memoria il contatore vale 10, se faccio un ++ e un --, mi aspetto che alla fine valga 10. 
```
load contatore, r1  // passaggio 1b
r1 = r1 - 1  // passaggio 2b
store contatore, r1 // passaggio 3b
```
cosa succede in sequenza 1a - 123b - 2a - 3a? in memoria viene fuori alla fine 11,  non 10. Non sono operazioni atomiche.
Provare per credere: fare due thread, da 1M di cicli ciascuno, con incremento e decremento, alla fine la variabile non vale 0. 
Serve quindi fare sta cosain memoria.
***DEFINIZIONE***: Il problema di dover proteggere il codice che modifica dati condivisi da race condition prende il nome di **Sezione critica**