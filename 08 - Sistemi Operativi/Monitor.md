# Monitor in Java

La difficoltà nel programmare coi semafori:
1. sincronizzazione è decentralizzata nell'applicazione (qual è la logica?)
2. complicata la gestione di wait dentro le sezioni critiche (letori-scrittore)

Monitor: 
sono un costrutto linguistico, quindi integrati nel linguaggio, che servono a semplificre la programmazione multithread. Sono molto simili alle classi come idea, infatti nel suo paper per certi versi sembra stia parlando di OOP. Infatti, sono modulari e contengono:
* dati (variabili) condivisi
* funzioni per accedere ai dati

Costringi il progorammatore a incapsulare la programmazione multithreading in un unico punto, in modo che non sia sparsa in giro come per i semafori. 
**i monitor sono in mutua esclusione** --> di fatto sono in una sezione critica. solo un thread accede al modulo. viene fatto gratuitamente, non deve trovae il modo di farlo il programmatore.
Non ci basta la mutua esclusione, mi serve anche sincronizzazione: nei monitor abbiamo variabili speciali che si chiamano conditions, sembrano semafori sempre rossi (code). Ci sono poi due funzioni:
- wait: sempre bloccante
- signal/notify sbloccano il primo thread in coda (se la coda è vuota non fanno nulla)

