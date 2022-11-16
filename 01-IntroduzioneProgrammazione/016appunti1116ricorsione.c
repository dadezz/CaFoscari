/*
appunti 16 novembre 2022
*/
#include<stdio.h>
#include<stdlib.h>


//interessante sullo scanf
void scannnnnnn(){
    char* stringa;
    scanf("%s", &stringa);
    
    scanf("%[^\n]s", &stringa);

    /**
     * nello scanf, se inserisco [adfag] posso dire quali sono i caratteri che voglio siano
     * rilevati dalla stringa, se inizia con ^ scelgo quali voglio siano esclusi. per esempio, 
     * normalmente lo spazio interrompe lo scan della stringa. 
     * Però usando %[^\n]s posso prendere tutti i caratteri inseriti finché non trovo un a capo.
     * In quel momento, lo scan della stringa si interrompe.
    */
}

// Continuo sulla ricorsione
int tutti_pari1(int* v, size_t l){
    /**
     * caso bse: unico elemento del vettore è pari
     * passo induttivo: ultimo(v) && pari(v, l-1);
    */

   if (l==1) return v[0]%2==0;
   else return v[l-1]%2==0 && tutti_pari(v, l-1);
}

int main1(){
    int x[] =  {2, 4, 6, 8, 10};
    printf("%d", tutti_pari(x, 5));
}

int tutti_pari(int* v, size_t l){
    /**
     * caso bse: unico elemento del vettore è pari
     * passo induttivo: ultimo(v) && pari(v, l-1);
    */
   printf("QUI\n");
   if (l==1) return v[0]%2==0;
   else return v[l-1]%2==0 && tutti_pari(v, l-1);
}

int main2(){
    int x[] =  {2, 4, 6, 8, 10};
    /*
    * a seconda dell'input, il "QUI" verrà stampato divrerso numero di volte.
    * questo è dovuto al cosiddetto short-circuiting.
    * per esempio, se l'ultimo elemento è dispari, il compilatore C non esegue nemmeno la chiamata di funzine
    * perché non ce n'è la necessità: se l'elemento a sinistra è dispari, l'and logico non tornerà mai true.
    * Attenzione quindi se si mette cose del tipo
    * if (booleano || save_to_database())
    * perché se il booleano è true,il save to database non verrà mai eseguito, comportando perdita di lavoro.* 
    * se si ha a cuore l'efficienza, si può anche cercare di scrivere a sinistra l'operazione ché è più probabilmente 
    * vera o falsa, cosiì da non dover eseguire la seconda parte, e risparmiare cicli di cpu.
    */
    printf("%d", tutti_pari(x, 5));
}

/*
 * PASSIAMO ALLA PARTE DIFFICILE DELLA RICORSIONE
 * SUBSET_SUM:
 * int v[], int t -> esiste sottinsieme di v con somma pari a t (non sottoseq, sottinsieme).
*/

_Bool subset_sum(int* v, size_t l, int t){
    /**
     * si noti subito che é praticamente impossibile implementarlo iterativamente.
     * 
     * Vediamo quale dovrebbe essere la logica.
     * 
     * la chiave è individuare i casi base e dividere in sottoproblemi.
     * SUggerimeno: assumere che esista un oracolo che sappia risolvere il sottoprblema.
     * secondo passo: individuare il sottoproblema corretto
     * terzo: trovare un pezzetto dell'input che si possa valutare facilmente (caso base)
     * quarto:eseguire merge tra caso base e oracolo.
     * 
     * posso dividere: se l'ultimo elemento non è dentro l'array, esiste il subset sum 
     * all'interno del vettore v(-1)?
     * E se invece l'ultimo elemento appartiene, cosa devo trovare? una sottosequenza che trovi una somma di
     * t-last_element. ovvero, se ho da trovare somma = 50, se l'elemento è dentro, per esempio è 5, devo trovare 
     * subset sum del resto dell'array,con somma 45.
     * 
     * subs (vett, lung, t): 
     *      caso 1: subs(v[], l-1, t)           [ovvero v[l-1] non appartiene alla soluzione]
     *      caso 2: subs(v[], l-1, t-v[l-1])    [ovvero v[l-1] appartiene alla soluzione]
     * 
     * ho trovato i sottoproblemi, ora li devo mergiare. 
     * devo dire true se c'è un sottinsieme che fa somma t. la prima funzione mi dice prorpio quello, quindi
     * basta che una delle due mi dica true per poter rispondere true.
     * 
     * o è vera la prima e trovo la somma nel sottinsieme, o è vera la secoda e trovo un elemento più il gap nel
     * sttinsieme, quindi bsta una sola delle due.
     * 
     * Ma i casi base? 
     * abbiamo solo ciamato la funzione, ma quando dobiamo fermarci?
     * cosa cambia nella chiamata ricorsiava? V rimane ugugale quindi non ritorna un problema più piccolo, di 
     * conseguenza non può portare a un caso base.
     * 
     * Cosa succede se la lunghezza è 0? Non esiste sottinsieme, quindi return false.
     * l diventa 0 perché lo sto decrementando, mi manca sapere se l'ho trovato oppure no.
     * L'altra grandezza che cambia è t. è un caso interessante quello in cui t diventa 0, che fondamentalmente 
     * significa aver trovato ciò che si cercava. è la oarte mancante. Non basta che l sia 0, ma serve l sia 0 E
     * manchi un gap alla somma (t!=0). 
     * 
     * 
     * abbaimo risolto il problema  con due if e due chiamate di funzione.
     * 
     * casi su cui ragionare: t=0, numeri negativi
     * [tip: dipende anche se l'insieme vuoto lo consideriamo come somma 0 o meno]
    */
}

int main(){
    int x[]={2, 4, 5, 6, 6, 11};
    printf("%d\n", subset_sum(x, 6, 25));
    return 0;
}

