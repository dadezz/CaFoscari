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

### Sezione Critica
progettare la sezione critica significa cosa fare prima e dopo. Proviamo a risolverlo a livello prettamente software: senza appoggiarsi a sistema operativo o a hardware. (anche perché se sto programmando il sistema operativo la vedo dura usare le chiamate a OS).
Vediamo oggi la soluzione software, poi modificata con istruzioni hardware speciali. 
Lavoriamo solo con 2 thread (poi è generalizzabile, ma per semplicità pensiamo solo a 2).

L'idea più semplice è usare un flag booleano che mi dice se c'è o meno qualcuno in sezione critica. DI norma prende il nome di lock (anche nei file, se apro un file ci metto un lock che mi blocca l'apertura da parte di altri).

metto un lock che inizialmente è false, diventa true se la risorsa è occupata

```c
Bool_t lock = false;
while(lock){}
lock = true;
// ... sezione critica ...
lock = false;
```

c'è lo stesso problema di prima però. codice parallelo legge e scrive la stessa variabile condivisa. Le stesse race condition che vogliamo evitare vengono fuori nelle guardie d'accesso.

Al posto di dire libero o non livbero posso creare una specie di turno. la variabile tiene in memoria di chi è il turno
```c
while(turno!=0){}
// ...
```
ma chi è che dà il turno?
```c
// thread 0
while(turno!=0){}
// sez critica
turno = 1;
////////////////7////
// thread 1
while(turno!=0){}
// sez critica
turno = 0;
```
la differenza è la condizione nel while. nel caso del lock, la condizione è la stessa, nel caso del turno ognuno ha la sua porta.
Pensa ai tornelli: la soluzione col lock è un tornello che si apre ma possono passare anche in due se si schiacciano, il caso col turno invece è mutualmente esclusiva. una porta che scorre su due binari: entra uno o entra l'altro. La cosa brutta di sta roba è che sono obbligati ad alternarsi. Non è sempre un bene che solo un thread alla volta possa entrare in sezione critica. se l'altro non la sta usando è inutile che rimanga bloccata. SOno necessarie quindi due proprietà:
* **mutex - mutua esclusione**: solo un thread alla volta può accedere alla sezione critica
* **progress** : se la sezione critica è libera, un thread deve potervi accedere.

con questa solo la mutex è rispettata, serve una via di mezzo.

Serve che ognuno abbia la sua condizione personale E ci sia un controllo sulla risorsa se è usata o meno. Uso due booleani. devo indebolire la condizione del while.

Se il primo thread è pronto a entrare, il secondo deve aspettare,
```c
// thread 1:
pronto[0] = true;
while(pronto[1]){}
//sezione
pronto[0] = false;

//thread 2:
pronto[1] = true;
while(pronto[0]){}
//sezione
pronto[1] = false;
```

* Dà mutex questa soluzione? si, non è possibile che entrambi entrino insieme. due varaibili diverse, e ognuno ne setta solo una.
* il progresso c'è? il progresso c'è, perché è solo all'entrata della sezione che setto se lo sto usando.

c'è un bug, lol. Entrambi settano il pronto a true in contemporanea -> entrambi aspettano all'inifinito -> stallo, deadlock. Il processo va killato (peggio della starvation).

ricapitolando:
* il lock era sbagliato
* il turno era giusto ma faceva aspettare troppo
* il pronto era giusto per entrambe le cose ma a rischio stallo.

#### Algoritmo di peterson
Una delle soluzioni più semplici per risolvere mutex, progress e assenza di stalli. Posso unire le ultime due soluzioni, mettendo un turno. Nel while, per indebolire la condizione devo mettere un and: mi blocco quando l'altro è pronto e non è il mio turno, altrimenti proseguo. È necessario settarlo il turno o posso lasciarlo sempre 0? funziona già a lasciarlo sempre 0: nel caso di stallo ha sempre priorità lo 0. Però teoricamente funziona. Per renderlo pià equo posso settare il turno oltre al pronto

```c
// thread 0
pronto[0] = true;
turno = 1;
while(pronto[1] && turno != 0){}
// sezione critica
pronto[0] = false;
```
Sto algo garantisce tuttte e tre le proprietà.

Se abbiamo una soluzione che funziona, percHé ci interessano altre soluzioni? per il busy waiting. Si noti che in architettura multi-core, non è così terribile. Altro problema sono le ottimizzazioni dei compilatori, che pensano solo alla sequenza del codice, non è che possono vedere la correttezza del multithreading, servono direttive per il compilatore (che tralaltro sono penalizzanti dal pov della performance). Queste ottimizzazioni rompono la correttezza dell'algoritmo, per cui si tende a usare istruzioni OS o hardware.

#### Istruzione speciale hardware

L'architettura offre un'istruzione macchina che fa in modo indivisibile un'operazione che di norma non lo è (vale per tutte le architetture attuali). Il problema è in particolare in scrittura e lettura. In particolare l'istruzione che ci interessa è la test&set. Sta funzione è definita (a livello macchina, mica in C, è per capire) così, va intesa come istruzione indivisibile, non accade nient'altro nel frattempo. Notare che va in accesso in memoria: lock del bus di memoria, accesso esclusivo finché non eseguo sta cosa -> ineffieicnte (anche se, dal moemnto che me lo offre l'hardware mi aspetto che sia fatta nel modo migliore possibile)
```c
test&set(Bool_t &x){
    tmp = *x;
    *x = true;
    return tmp;
}
```

Ecco che ora il Lock torna ad avere un senso (più facile e leggibile)
```c
Bool_t lock = false;
while(test&set(&lock)){}
// sezione critica
lock = false;
```

Un'ottimizzazione è
```c
Bool_t lock = false;
while(test&set(&lock)){
    while(lock){}
}
// sezione critica
lock = false;
```
in sto modo il loop busy waiting viene fatto solo sulla lettura di lock, più efficiente di test and set.

Figo intel, che offre
```XCHG(bool *x, bool *y){
    tmp = *x;
    *x = *y;
    *y = tmp
}