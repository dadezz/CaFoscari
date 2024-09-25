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
