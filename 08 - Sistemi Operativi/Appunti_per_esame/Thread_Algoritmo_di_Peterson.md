```c
thread T0 {                              thread T1 { 
  ....                                      ....  
  pronto[0] = true;                         pronto[1] = true;
  turno=1;                                  turno=0;
  while(pronto[1] && turno != 0) {}         while(pronto[0] && turno != 1) {}    
  < sezione critica >                       < sezione critica >   
  pronto[0] = false;                        pronto[1] = false;
  ....                                      ....  
}                                         }
```

quando il thread i-esimo vuole entrare pone a true la variabile pronto[i] per segnalare all’altro thread la sua volontà di accedere. Successivamente cede il turno all’altro thread e cicla a vuoto se l’altro thread è pronto e se non è il proprio turno. Quando esce dalla sezione critica, il thread pone a false pronto[i] per indicare che non ha più bisogno della sezione critica.

È possibile risolvere il problema della sezione critica puramente in software ma tali soluzioni presentano alcune problematiche importanti:

I cicli while “a vuoto” (busy waiting) consumano inutilmente tempo di CPU. Su macchine con un solo core questo problema è particolarmente rilevante. Su più core diventa più accettabile in quanto i vari core dovrebbero comunque attendere che il thread in sezione critica esca;
Le soluzioni richiedono l’uso di diverse variabili globali e un sequenza precisa di esecuzione delle istruzioni. I compilatori e i processori attuali rimaneggiano e riordinano le istruzioni in modo da migliorare la performance. L’utilizzo di soluzioni software di sincronizzazione richiede che tali ottimizzazioni siano disabilitate per evitare di compromettere la correttezza del codice di ingresso e uscita dalla sezione critica.
