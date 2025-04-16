viene data una macchina virtuale 

ogni team ha una toolbox e può collegarcisi tramite ssh e vpn
tutti hanno gli stessi identici servizi. bisogna trovare le vulnerablità sui servizi (guardando il poprio si vede il codice sorgente anche degli altri)

come si trovano le flag:
c'è un game system, un bot, che usa i nostri servizi. li usa in maniera lecita. scrive la flag da qualche parte e controlla se riusciamo a leggerla. lo fa a ogni tick.
cos'è u tick? un round di 2 minuti. 
quindi ci sono continuamente nuove flag da leggere e difendere -> il tutto va automatizzato. 
lo scopo è 
1. trova vulnerabilità
2. scrivere script che le sfruttano sulle altr macchine
3. patchare le proprie di vulnerabilità
4. il game system controlla di continuo se i servizi sono su, non posso renderlo inutilizzabile (non posso bloccare tutti gli accessi per bloccare gli altri team)
5. sulla scoreboard si vedono i risultati e se i servizi sono su

il punteggio si misura sia su quanto attacchi che su quanto difendi. è più importante avere un servizio su che avercelo sicuro (la sla toglie molto di più che la flag persa)


prima roba da fare: 
una repo di git da tenere in locale e committare lo stato iniziale della mcchina. iniziamo a patchare da qui, così per ogni modifica che spacca qualcosa basta rollbackare

not team: team che non risoolverà mai gli attaccchi. serve a vedere se l'exploit funziona. lo script vieme dato a un servizio automatico che sxploita tutto.
**TULIP**:
webapp che mostra il traffico, come fosse wireshark, ma piùù specifico per le ctf, riconosce le flag e fa anche il reply attack (manda le richieste esattamente come le ricevi: le vulnerabilità sono uguali per tutti)

la cosa peggiore è perdere l'uptime. appena si entra sul server, si entra in tutte le cartelle della home (ticcket, capp, ccmanager ) e si starta it: git init, git add, git commit. ogni volta xche si patcha qualcosa, si committa again. gira tutto su docker: modifica il codice -> 
```sh
ocker compose down
docker compose up --build -d
```

con rsync ti tiri giù tutti i file

come accedere:
```sh
sudo wg-quick up nomefile.conf
ssh root@   10.60.76.1
```
destructive farm:

non filtrare l'output, ocn regex già riconoscono le flag. la print deve avere opzione flush=true. l'ip da attaccare lo si ritrova negli argomenti
il client passa come argv gli ip ed esegue i comandi. poi parsa l'output e le mette in coda nel nostro server. è poi il server che prende le flag in coda e le invia al flag checker.

```sh
http://10.60.76.1:54321/
lasciate user vuoto
password: Fqf3dzUsqCBXT1qoCso1KiQFrZs2ggqF
```

template exploit per destructive farm:

```py
#!/usr/bin/env python3

import random
import string
import sys
import requests
import json
from pwn import *
from Crypto.Hash import SHA256
import sys


host = sys.argv[1]
print("I need to attack a team with host: {}".format(host))

service = 'NOME_SERVIZIO_API'

# Server supplying the flag's ids
server = 'http://10.10.0.1:8081/flagIds?service='+service


# requesting flags ids
response = requests.get(server)
data = response.json()

# for every host the APIs returns 5 ids 
# (runnin 5 exploit on the same host)
for i in range(5):

    # id to use for the service
    id = data[service][host][i]
    print(id)
    
    # EXPLOIT here

    print("<FLAG>", flush=True)
```

tulip ci si può accedere con ssh a


screen: terminale che conntinua a girae anche quando si spegne quello che l'ha creato
`screen -S nome'

flag ids are avaiable at 10.10.0.1:8081/flagids. si possono aggiungere i filtri: `?service=foobar&team=1&round=5`

per spostare file:
```sh
scp -r root@10.60.76.1:/root/<cartellaDaPrendere> ./cartellaTua/
```

ip tulip
http://91.99.62.1:2234/