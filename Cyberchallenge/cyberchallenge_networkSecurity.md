tcpdump: tipo wireshark, ma CLI
time src > dest: protocol bytes type of srv 

sniffing application: 
- analisi automatica per cracking (analizzo tutti i pacchetti in cerca di pattern di attacco, tipo in cerca di campi usr/psw in chiaro)
- analisi automatica di anomalie o intrusioni
- analisi di performance per cercare bottlenecks o simili
- logging dell'attività di rete

# wireshark
Tool grafico. esistono anche tshark (da terminale, per esempio integrabile con script bash) e pyshark (in python)
filtrare i pacchetti: seguono operatori logici (ip.src > 1.1.1.1)
follow tcp stream

# docker
"it works on my machine" -> "then we'll ship your machine"
docker è un sistema di virtualizzazione che si differice dalle VM perché riesce a semplificare lo stack di operazioni: ho l'host OS, quello che metto sopra non è u hypervisor, ma un engine che traduce le richieste che la tua app fa all'OS in richieste adatte a fare l'OS. Ogni container contiene tutto e solo cio che serve all'app
perché docker per la network security? 
si simulano più host/services senza avere l'infrastruttura fisica
si può simulare una rete
si può replicare un'infrastruttura esistente
dockerfile può costruire immagini custom. non sono già container, sono il "progetto". il docker file è il "progetto del progetto"