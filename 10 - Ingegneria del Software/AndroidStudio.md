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

## binding
Un oggetto solo di tipo ActivityMainBinding (è il nome dell'xml senza underscore). nessuno fa la new, viene dato dal metodo inflate: metodo statico che è uno pseudocostruttore. l'oggetto viene messo su un campo privato della classe: _binding_.
Perché quella specie di costruttore si chiama inflate? nella UX significa che la disegni per la prima volta. da qui, per motivi storici, inflate vuol dire che crea l'activity per la prima volta

### setonclicklistener
è un metodo del binding che fa qualcosa quando si clicca. ci sono un sacco di `setOn-Listener`: longclick, drag, FocusChange etc. Si trovano tutti nella documentzione, c'è enrome spazio di personalizzazione per ogni evento anche raro si può fare qualcosa.

## altri metodi dell'activity
la oncreate è importantissima e inizializza l'activity.
Il resto sono metodi che non hanno a che vedere col ciclo di vita dell'activity
* `onCreateOptionsMenu`: chiama questo metodo quando viene creato per la prima volta il menu (cioè serve a popolarlo)
* `onOptionsItemSelected`: quando qualcuno clicca una voce del menu. Il parametro che passa è il nome della voce del menu

In pratica sto simulando un linguaggio di programmazione orintato agli eventi con un linguaggio OOP. 

# Ciclo di vita activity
guardare il diagramma sul sito di sviluppo android.
percHé le activity hanno ciclo di vita?

se guardiamo la classe MainActivity, non ci sono costruttori. nessuna new. Le activity non le devo mai costruire con la new. sono sotto il controllo di costruzione del sistema operativo. Quando viene distrutta? 
quando cambia activity? ha senso, ed è così, ma fa una piccola ottimizzazione. Ci sono 3 livelli di costruzione e, simmetricamente, 3 di distruzione.
Quando è ora di fare l'activity, lo costruisce e butta in memoria. per quello esiste onCreate(), perché non avrei modo di personalizzare  il costruttore, essendo esso delegato all'OS. Dopodiché, in botta, chiama anche onStart() e onResume(). poi l'activity sta runnando. Se l'activity viene spostata dallo scehrmo e vado in una seconda schermata, quella vecchia viene pausata onPause() e messa in background. se passa nu po' di tempo, essa va in onStop, se passa ancora tempo, viene distrutta onDestroy().
Ho quindi dei gradienti per decidere come gestire le varie pause e distruzioni delle activity.

I metodi sono definiti dalla classe che si eredita e si deve fare l'override. onCreate è l'unica per cui è obbligatorio fare override. Non per motivi sintaticci, a java non frega un cazzo, è android che vuole che la overridi.
A noi probabilmente non servirà sta roba, considerare comunque che si complica non poco lo sviluppo, perché servono dei flag che controllano a che livello si è su ogni metodo, facendo una o l'altra roba.

# Naming Convention
Le activity si chiamano NomeActivity (Pascal Case). nome di metodi e campi camelcase. l'activity ha un layout. l'xml si chiama in snake e si chiama activity_nome

# listener - thread rendere UI
per fare cose normali, tipo cambiare png al bottone quando lo clicco, fa tutto android con gli xml. ma se invece voglio cambiare qualcos'altro o fare roba particolarmente strana? mi tocca usare direttamente il Runnable del thread.

mettiamo che quando clicco il floating button voglio che cambi la scritta dell'altro buttone di nome "button" 
```java
binding.fab.setOnClickListener(new View.onClickListener(){
  @Override
  public void onClick(View view){
    runOnUiThread(() -> binding.button.setText("Franco"))
  }
});
```

ogni volt che bisogna fare qualcosa di tipo "render" che non è scrivibile nel XML, vademandato al thread di render.

# cambiare activity
come faccio a scoprire come si fa? 
cerco su google "how to change activity android".

BTW, c'è un API apposta. non posso chiamare la onCreate dell'altra activity. in java normale sta roba potrei farla, ma android non me lo permette.

```java
binding.button.setOnClickListener(new View.onClickListener(){
  @Override
  public void onClick(View view){
    startActivity(new Intent(MainActivity.this, MyOtherActivity.class));
  }
});
```
è un metodo di nome startActivity, che prende un argomento di tipo intent, il cui costruttore ha due argomenti. il primo ha tipo this (la acctvity presente) il secondo ha tipo class della seconda activity.
ovvero si specifica chi sono io e chi voglio diventare. chi sono io è il this, chi voglio diventare è la classe (va per reflection).
Cos'è intent? rappresenta l'intenzione di fare qualcosa. fa parte del meccaniscmo base per comnicare tra activity.
Cosa posso comunicare? posso inventarmi quello che voglio, volendo (c'è un dictionary che posso popolare). per far partire un'activity però basta chiamare l'API (che è un metodo ereiitato, tra l'altro, in this).

Regola della programmazione moderna è: se cambia solo qualcosa uso i fragment, altrimenti cambio l'activity (ma solo se cambia molto). una volta esistevano solo le activity, quindi si cambiavano solo quelle e non c'èerano i fragment. si può fare ma è scoodo e un po' deprecato.

# fragment
il fragment può essere grande anche come tutta la schermata, così da cambiare l'intera schermatar senza dover cabiare activity.

il fragment dell'applicazione di default inizia sotto "First Fragment". dentro ha una scroll view, un botton e un testo. poi c'è un secondo fragment, che è il titolo sopra "first fragment" e "second fragment". questo è quello che viene cambiato alla pressione del pulsante.

## codice del fist fragment:
a cosa seve il codice? così come per le activity, serve quando parte e quando muore.
la classe FirstFragment estende (DEVE estendere) la classe Fragment di android.
al suo interno c'è un campo che ha loo stesso ruolo nell'activity: il binding, così da usare tutti i cosetti esistenti nel xml.
nell'esempio questi nomi sono `button_fiest`, `textview_first`.

metodo
```java
public void onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle SavedInstanceState){
    binding = FragmentFirstBinding.inflate(inflater, container, false);
    return binding.getRoot();
  }
```
fa la stessa roba del metodo onCreate() delle activity. Ha un nome diverso perché ha un diverso numero di argomenti

il metodo onviewcreated viene chiamato dopo oncreateview. perchésono due metodi diversi e non un unico che contiene entrambi?
se renderizzo cose complicate, magari ci metto qualcosa, e voglio disegnare qualcosa DOPO che ho renderizzato. 
tipo, sto renderizzando roba che dipende da file scaricati da un server, e ho un bottone che deve essere premibile solo DOPO che li ho scaricati.

probabilmente sta roba gli è venuto in mente dopo un po' e solo dopo la ideazione dei fragment. infatti sulle activity non è così anche se servirebbe. amen

ugualmente, fragment non ha bisogno di chiamare il super nell'onCreate, però ne ha bisogno in ondestroy. amen si fa così. dopo la ondestroy assegno null al binding così chiamo il garbage collector.
Perché viene fatto?
è possibile che in java un assegnamento dia un errore di compilazione? solo coi tipi diversi. non è questo il caso. e allora? l'operatore di assegnamento si può sempre fare in java; il problema è android. 
i fragment non hanno lo stesso ciclo di vita delle activity, hanno solo 1 livello invece di 3. siccome nello heap in caso di riassegnamento non sanno se è nuovo, in pausa, o altro, nel dubbio il "distruttore" setta manualmente a null.

`onViewCreated`: contiene il setonclicklistener. qual è la lambda che coniene?
si intuisce che naviga sul secondo fragment

`R.` R è una classe generata, che sta per resources. tutto ciò che va dentro al cartellone res è raggruppato a static class innestate per poter usare le robe dentro le varie cartelle in java come fossero oggetti
NavHostFragment: il fragment (io) 