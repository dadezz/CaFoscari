2011-2012 inizio delle reti neurali

l'idea è trarre ispirazione da una rete neurale biologica. un neurone è una "cosa" che ha collegamenti con neuroni da uci arrivano altri segnali, il neurone fa cose e spara un output verso altri neuroni tramite l'assone

{x1, x2, x3} -> f(X) -> y1

tutti i neuroni sono uguali? se tutte le componenti fossero identiche tra loro, verrebbe fuori un output poco interessante. di fatto sono identici, ma ogni arco, che ha un dato input, ha un peso diverso. da cui, ogni feature ha peso diverso a seconda del neurone a cui arriva. la F(X) è uguale per tutti invece. 

i neuroni sono organizzati a livelli. ogni neurone di un libelllo è collegato con tutti i neuroni dei livelli adiacenti. non con sé stesso e non con neuroni di livelli non adiacenti.

il trainin gome funziona? 
prendo un istanza, a do al sistema e vedo qual è il suo output. confronto le etichette. la differenza mi dà un errore, il sistema lo prende, lo processa e lo dà in pasto per ritunare il sistema. quando ho smesso di tunare, quella si chiama un epoca. il training quindi non tuna le fnzioni, ma i pesi. 

la libreria che useremo è keras. la più usata è pytorch, ma intanto useremo questa. 

la rete neurale è una grande funzione con i parametri che devo trovare, che sono i pesi. espongo la rete a un input, i neuroni elaborano e producono un output. confronto la predizione con l'etichetta reale, la misura di quanto sia lontana è una loss function (per esempio una foresta o la distanza euclidea).

la misura di distanza standard per una classificazione binaria è la binary cross-entropy loss, che praticamente è una specie di misura di distanza tra due distribuzioni di probabilità
non si usa l'accuracy perché mi dice solo se è giusto o sbagliato, senza dirmi di quanto, e oltretutto non è derivabile (cosa che vedremo ci servirà).

