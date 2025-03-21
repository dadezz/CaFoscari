# Diffie-Hellman e crittografia asimmetrica

## Crittografia asimmetrica

il problema della crittorgafia simemtrica è lo scambio delle chiavi. Se non c'è un canale di comunicazione esistente sicruro, non c'è modo di essere sicuri che la chiave non venga vvista da terzi, al massimo sarebbe da trovarsi di persona.
Altro problema: se ci sono N persone che devono comunicare, e vogliono comunicare tra di loro anche a coppie, non c'è altro modo se non quelo di creare una chiave per ogni coppia, e anche qui ogni coppia dovrebbe trovarsi. Cioè, la chiave deve essere diversa per ogni persona con cui parlo. figurarsi cosa significa se devo parlare con 1000 persone (e ognuno deve ricordarsi N-1 chiave)

Soluzione banalissima è una trusted third party che gestisce le chiavi tra utenti. 
tra A e il tezo (TTP) c'è un canale, idem tra ttp e b. a parla con ttp col suo canale e ttp inoltra a c sul suo canale
* il ttp deve essere sempre raggiungibile
* singolo point of failure molto pericoloso
* ttp vede in chiaro tutte le comunicazioni -> attaccante o pressioni governative

## Diffie Hellman
permette di arrivare ad avere una chiave condivisa tra due interlocutori con un canale di comunicazione vulnerabile inizialmente. alla fine del processo arrivano ad avere una chiave condivisa che nessun altro potrà aver intercettato
* A e Bob scelgono pubblicamente un numeroo primo *p* e un generatore appartenente a N, minore di p
* alice e bob generano *a* e *b*, appartenenti al range [2,p]. 
* Alice calcola $A = g^a \mod p$ e analiogamente fa Bob con B
* Alice conosce a e B, così può calcolare $B^a = g^{ab} \mod p$
* bob conosce b e A così può calcolare simmetricamente $A^b = g^{ab} \mod p$
* così **entrambi hanno $g^{ab}$, che è il loro segreto, partendon solamente da rispettivamente da *p, g, a, B* e *p, g, b, A*.

La sicurezza non è molto efficiente: un p di 1024 bits equivale alla stessa difficoltà di bruteforce di un cifrario simmetrico con 80 bit di chiave. 
per avere una sicurezza simile a AES128 servono 3072. Con chiavi su curve ellittiche, 256 bit equivalgono di nuovo a AES 128

### MITM
Alice vuole iniziare una counicazione con bob. Alice genera una chiave e la stabilisce con Eve che si è messo in mezzo. stessa roba fa bob con eve. Alice manda mess, Eve lo decifra, lo legge (o anche modifica) e lo ricifra con la chiave di bob. NOn c'è modo di garantire che la persona con cui stai parlando sia effettivamente quella che ti aspetti.

## Crittografia Asimmetrica
finora abbiamo visto
* chiave simmetrica
* chiave simmetrica + scambio sicuro
  
Ora parliamo di crittografi a chiave pubblica. Non si parla più di chiave condivisa, ma di due chiavi diverse.
Si prende una chiave privata, usata per decifrare messaggi cifrati o per firmare un messaggio.
Da essa si deriva la chiave pubblica, usata per cifrare i messaggi e per verificare la firma.
Non c'è quindi bisogno di un TTM, non bisogna avere fiducia in terze parti. Risolve anche il problema di autenticazione: se sono sicuro della tua chiave pubblica, posso verificare la firma/certificato digitale. Ovviamente la premessa è che nessuno abbia scambiato la chiave.

Per fare questo, non deve esserci possibilità di ricavare la chiave privata da quella pubblica (funzioni one-way: facili in un verso, intrattabili da invertire). 
Riusciamo a:
* garantire confidenzialità
* garantire autenticazione
* garantire l'integrità del messaggio, con un mix dei due intelligente (cifro il messaggio e lo firmo pure)

### RSA
Torna l'elevamento a potenza con modulo.
per invertire sta cosa serve la scomposizione in fattori primi, sempre non trattabile
definiamo:
$$ \phi(n) = ({n \in \N : x<n \land gcd(x, n) = 1}) $$ 
è importante da ricorda re che 
* $ \phi(p) = p-1 $
* $ \phi(ab)  = \phi(a)\phi(b) $
* $ n = p*q $
* da cui $ \phi(n) = (p-1)*(q-1) $ù
il teorema di eulero fermat ci dice che se a e n sono coprimi,$ a^{\phi(n)} = 1 mod n $

ciò signfica che, sempre modulo n, $ a^x = a^y \implies x=n \mod \phi(n) $

#### algoritmo
1. prendo due numeri primi p, q
2. computo $ n = p*q $, il nostro modulo
3. computo $ phi(n) = (p.1)(q-1) $
4. scelgo un esopnente $ e >1 $ compreso tra $ 2,  phi(n) $ e che sia coprimo di n. $ e $ è la nostra chiave pubblica.
5. derivo d risolvendo l'equazione $ e*d = 1 \mod \phi(n) $

ora: 
$ M $ è il messaggio in chiaro come fosse un intero. un mio amico prende la mia chiave pubblica $ e $ per computare $ c = M^e \mod n $. C è il messaggio cifrato
io ricevo $ C $ e calcolo $ C^d \mod n $, e ricevo di nuovo $ M $

Nella pratica, vengono usati alcuni valori specifici di $ e $ per renderlo più efficiente (nella rappresentazione binaria deve essere abbastanza piccolo e con pochi "1" nella rappresentazione binaria. spesso si usa $ 65537 = 2^{16} +1 $) 

##### In python:
è comodo perchè `int` ha lunghezza arbitraria nativamente e contiene la funziona `pow(base, exp, modulus)` che oltre ad avere già il modulo, calcola anche l'inverso modulare se l'esponente è -1

```py
from Crypto.Util.number import getStrongPrime

p, q = getStrongPrime(1024), getStrongPrime(1024)
n, phi = p*q, (p-1)*(q-1)
e, d = 65537, pow(65537, -1, phi)

def encrypt(pt) : 
    return pow(pt, e, n)

def decrypt(ct): 
    return pow(ct, d, n)
```
#### attacchi
cosa potrebbe andare storto?
la sicurezza risiede nel fatto che è difficile fattorizzare n = pq.
**cosa succede se due numeri primi sono vicini tra loro?**
possiamo prendere il punto medio tra p e q, chiamiamolo a. la distanza pa = aq = b. 
quindi, $ p = a-b $ e $ q = a+b $ 
da cui $ N = pq = (a-b)(a+b) = a^2 -b^2 $. cioè esiste il quadrato di qualcosa che differisce da N di un altro quadrato. possiamo andare alla ricerca di numeri che sono il quadrato di qualcosa che si avvicinino a N e calcolare la differenza con N. Nel momento in cui troviamo che il risultato della differenza è un quadrato perfetto, abbiamo di fatto fattorizzato N e risolto p e q.
**riutilizzo dei numeri primi**
supponiamo di generare:
1. $ N_1  = p\cdot q $
2. $ N_2 = p \cdot r $
calcolo $ \gcd(a, b) $ e ho risolto

se il target genera molte chiavi, è conveniente continuare a testare gli mcd delle varie coppie, dal momento che c'è una probabilità via via crescente di riutilizzo dei primi.

**riutilizzo del modulo**
Se usiamo lo stesso esponente, non succede nulla.
se usiamo esponenti diversi, siam fottuti

* supponiamo di aver usato $ (N, e_1), (N, e_2) $ per cifrare lo stesso testo. otteniamo $ c_1,c_2 $
* supponiamo di aver usato $ xgcd(e_1,e_2) = (1,u,v) $ : questo significa che $ u*e_1 + v*e_2 = GCD $
* da qui il trick: $ c_1^u \cdot c_2^v = m^{e_1u} \cdot m^{e_2v} = m(\mod n) $