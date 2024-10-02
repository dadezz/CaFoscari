# Programmazione android
* java: è un java con altre robe invece di jdk, abbastanza complicato
* kotlin: simile a kotlin e al tempo stesso ben diversi. Semanticamente sono uguali

Android ha un IDE tutto suo molto consigliato: Android Studio

## Android studio
Ha un emulatore di android dentro.

### UI walk through
File -> new project: ci sono già alcuni template. INteressante che a sx si possa selezionare phone/wear/television/automotive. 

Scegliendo un template, vengono generati in automatico alcuni sorgenti. 
**activity**: ogni "schermata" ha il suo codice.

Dietro una interfaccia, il codice fa qualcosa quando i pulsanti sono premuti. La gestione della pressione dei tasti è delegata al SO, che ti dà questo servizio.
Lo sviluppo di un app non è monolitico, il codice è tutto sparpagliato in tanti moduli separati diversi, che vengono invocati alla bisogna. Gli input vengono dispatchati dal sistema operativo, non sono on the top of the user. il livello di granularità di un app android è estremamente granulare, funziona a API.
Zero algo, zero logica, zero loop. Solo API code.

**Minimum SDK**: il sistema minimo supportato: col tempo android si è evoluto, e alcune feature (API) esistonoo solo da una versione in poi del SO.

## device manager
emulatore di vari dispositivi andorid. fornisce vari modelli con vari aspect ratio. Nella seconda schermata chiede una image con cui far girare l'amulatore

## fragment
sottoregioni di un activity (che sono schermate intere).
* floating button: non vincolati al layout, in foreground, sprite.
* button

# app
tre directory:
* java: sorgenti organizzati in packages
* res: resources:
  * drawable: grafica (icone, png etc)
  * values: xml con descrizione delle stringhe , colori e variabili locali
  * ... : in generale, tutto ciò che non è codice
* manifest: i manifest sono files speciali con configurazione dei comportamenti globali dell'app. per ora ignorabili. Qui dentro si scrivono i nomi dell'app, i permessi, i dispositivi supportati etc.

## Java
ignoriamo le seconde due (contengono due tipi di test: unit test e android test). Nella prima ci sono i sorgenti.
### main activity
classe principale da cui partono gli altri metodi
deve ereditare AppCompactActivity
* onCreate: override del padre. come prima riga chiami la versione vecchia: estende il codice vecchio.

prox volta vediamo bene cosa fanno

# Lezione 2
il render grafico del design non è in java, ma è dato da config in xml. È figo perché si può fare anche drag n drop delle parti grafiche e android studio genera l'xml.

vabbe ne parleremo, partiamo col codice.

# Codica java
ogni schermata è chiamata activity. Ogni schermata ha sottoragioni chiamate fragment.
Per ogni activity c'è un sorgente (e una classe).
qualsiasi etivity estende al superclasse AppCompactActivity.

Cuore di tutto è il metodo onCreate. Fa partire l'applicazione ("quando quest'activity viene creata"). Nel amnifest c'è scritto qual'è la prima schermata. la disegna e poi dispatcha il metodo oncreate di quell'activity. 
Nel metodo quindi cosa va messo? inizializzo ciò che devo.Quel metodo non èche loopa continuamente in attesa di un click.
nella onCreate inizializzo dei listener: chiamo un api agganciata a un botone. Se verrà premuto il bottone, il sistema chiama la lambda che c'è messa dentro.

```java
binding.fab.setOnClickListener(new View.OnClickListener() {
    @override
    public void onClick(View view){
        Snackbar.make(view, "replace with your own action", Snackbar.LENGHT_LONG)
                .setAnchorView(R.id.fab)
                .setAction("Action", null).show();
    }
})
```

si programma a suon di callback. è tutto spezzettato in metodi. Sto impostando il listener del mbottone di nome fab (nome che ho scelto io). 
chiamando questo metodo e passandogli un anonymous class. Dentro al metodo posso scriverci quello che voglio. 
make guardalo nella doc. setanchor è il punto su cui viene disegnato, setaction è cosa fai.

binding? H tipo ActivityMainBinding. è una classe generata dall'ide. in particolare, dall'xml. posso battezzare quello che ci metto con un nome, che poi mi ritrovo nel codice java (il famoso fab, per esempio).

XML scrive configurazioni ad albero
### coordinator layout
contiene tutto. 
match_parent negli attributi cos'è? fammi il layout grande come tutto o schermo. il cooridnator layout cos'è?
notare che nell xml non c'è alcuna coordinata. android si è inventato un modo per dire come vengono idistribuiti i vari tocchi dell'app. È un modo automatico di distribuire le cose al'intrno della schermata

Quandoscrivo un programma separo l'aspetto delle cose da come appare.

#### floating action  button (esempio):
è definito dalla libreria di android (che definisce decine di migliaia di elementi). è definita a package quindi per definirlo devo dire tutto il path.
attributi:
* id: nome che gli dò (nome dentro al sorgente java). Se non mi serve quel coso in java, non mi serve il nome
* layout_width e height: quanto largo e alto la componente bottone. wrap content-> grande come il disegno originale contenuto. si può fare ovunque, anche ricorsivamente, è potente
* gravity: dove alloggia
* margin: quanto margine deve avere dal bordo dello schermo
* srcCompat: immagine da disegnare