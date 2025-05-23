si introducono i cookies di sessioni per gestire lo stato di una connessione htto, che di suo sarebbe stateless

le sessioni sono o client o server side:
* server: il server prende l'identificatore del cookie e prende le info dal DB
* client: il client invia tutto tramite cookie

# session integrity
ci sono vari attacchi. il principale è l'hijacking: l'attaccante riesce a rubare il cookie alla vittima, e impersonificarla. 

come proteggiamo i cookies? in generale, i cookie possono essere scritti da js. i cookie però sono istanziati per origin (un sito non può leggere cookie di un altro per le policy SOP: same origin policy). Questo funziona a meno di vulnerabilità tipo XSS.
i cookie sono protetti fondamentalmente da due attrivuti: HttpOnly (non possono essere acceduti da js); Secure (sono spediti solamente tramite https. è necessario perché vengono inviati ad ogni richieesta indipendentemente dal canale, con questo li blocchi). 
Se ho un app che non è interamente deployata su https (per esempio sottodomini in http) io comunque devo settarli, perché per SOP, un sottodominio http può ricevere il coso
esempi:
* php di default è server side. nella variabile _SESSION, che funziona come dizionario, sono storati tutti i dati
* flask invece di default è client side. tutte le info sono salvate nel cookie e il cookie viene firmato per garantirne l'integrità. ANche in flask si può usare il server side con estensioni tipo Flask-Session

# SOP
same oriigin policy. meccanismo di difesa alla base di tutti i berowser. 
La sop ppermette di isolare domini diversi. i dati sono protetti da accessi anche in lettura da parte di script che girano su domini diversi.
definizione di origin? non è precisa: scheme/hostname/port secondo la definiizione originale, in realtà i browser lo fanno ognuno in modo diverso. Diciamo che per i cookie quantomeno implementano una versione rilassata: dominio ok, ma vegono condivisi co tutti gli schemi e tutte le porte, a volte anche coi sottodomini. 

Il webstorage invece applica la sop come da definizione. webstorage è un alternativa ai cookies. le cose messe lì prò non sono isolate da js: se ho un injection non posso proteggermi. anche a livello clientsid seve una logica js customm. 

le pagine web spesso includono contenuti da altri siti. la sop non impone limiti per inclusioni di altri domini. inclusi gli script. se foo..com carica uno script da bar.com, poi è foo ad eseguirlo, quindi per la sop è tutto ok. lo script remoto gira come se fosse suo. 

# Cross site scripting XSS
è l'attacco più famoso per quanto riguarda la client side security. ho uno script malevolo che viene caricato nell'origin del target e viene eseguito come se fosse nell'origin del target. il problema del web è che la superficie d'attacco è vastissima. 

In generale, l'attaccante identifica un posto dove inserire input utente arbitrario. lì prova a inserire uno script e vede se è interpretato come script o come stringa. 
categorie (non distinte): 
* reflected: lo script iniettato non viene salvato lato server, ma incluso nell'url
* persistent; più pericolose, veien salvato
* client e server - side

le reflect server side: nella barra di ricerca posso metterci uno script. quando la vittima clicca sul link, esso viene eseguito. chiaro che dobbiamo riuscire a convincere la vittima a cliccarci su quel link. 

persistent server side: non abbiam bisogno di convincere l'utente a cliccare su un link.  forum in cui si può postare i commenti, che suupporta html.. se supporta html con completa libertà, significa che possono anche metterci js. quando l'utente scrive il commento, esso viene salvato dal server, e tutti gli utenti caricano il documento. 

come ci si difende: 
* output encodig: dove processo l'input, prima di renderizzarlo faccio un encoding. (usa una libreria a riguardo). spesso troppo restrittivo
* input sanitization:  tolgo tutti i tag pericolosi. non è facile da usare perché ci possono essere jaibreak. meno restrittivo ma può essere pericoloso. 

# CSRF 
sfruttano il fatto che il cookie viene inviato a ogni richiesta che il browser fa: 
se un utente carica una pagina malevala e questa invia una richiesta a un sito benevolo, a questa richiesta verranno allegati i cookie della vittima, e quindi il sito benevolo processerà la richiesta malevola come una della vittima. 

difese server side: si evita di autenticare richieste solo tramite cookie (per esempio tramite referer checking). 
client side: si usa l'attributo SameSite. il problema è che alcuni browser non lo implementano correttamente.

referrer se mal implementata è facilmente bypassabile. si usano spesso invece i secret token, nei form hidden. la difesa si basa su sessioni server side. 
