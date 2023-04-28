/**
 * ITERATORI:
 * generalizzazione dei puntatori.
 * I puntatori permettono di accedere all'elemento dell'array e, aggiungendo uno, scorrerlo.
 * 
 * Gli iteratori generalizzano questa idea su ogni container.
 * Non è banale perché per esempio le liste non sono consecutive in memoria, ma si può
 * specificare che il ++ o il +1 funzioni come puntatore next.
 * 
 * Per esempio, un idea è usare gli iteratori per rendere invisibili le differenze tra
 * le implementazioni del container (tipo ista o vector).
 * se faccio iteratore++, nel caso del vector passa alla cella successiva, nel caso 
 * della lita invece va alla cella puntata dal campo next.
 * 
 * Van quindi implementati gli operatori * (dereferenziazione) e +/++/+=.
 * 
 * si possono usare in un for:
 *       for (iterator it = x.begin(); it != x.end(); ++it){
 *              cout <<  *it  << endl;
 *       }
 * 
 *  oppure, come zuchero sintaticco:
 * 
 *      for (auto val : x){
 *          cout << val ;
 *      }
 * 
 * possiamo modificare gli elementi nell'oggetto, esattamente come coi puntatori: *it = 3;
 * 
 * 
 * Nella standard library, gli algoritmi lavorano sugli iteratori, così non c'è bisogno di personalizzare l'algoritmo per ogni
 * tipo diverso di container, basta che siano implementati gli iteratori. non mi interessa sapere come sono 
 * strutturati i container, a me algoritmo, funziono sempre allo stesso modo.
 * 
 * std::sort(v.begin(), v.end())  ->  per esempio std::sort funziona sui iteratori.
 * 
 * 
 * TYPES:
 *  - input iterator: permette di leggere i byte senza tornare indietro e non può modificare gli elementi a cui punta
 *  - output: analogo, ma può solo scriverli
 *  - forward iterator: permette di andare avanti e basta, per esempio nelle liste non double linked
 *  - bidirectional iterator: posso accedere sia all'elemento successivo che a quello precedente
 *  - random access iterator: potente, permette di saltare a una cella qualsiasi
 *  - contiguos iterator: come i precedenti, ma hanno la garanzia che le celle in memoria siano aiacenti
 * 
 * Questa qui sopra è una gerarchia: dal basso verso l'alto, ogni tipo è anche il tipo-1 (esclusi input e output, che hanno
 * la stessa priorità).
 * 
 * A seconda del tipo di iteratore, alcuni algoritmi sono implementabili, altri no. 
*/
