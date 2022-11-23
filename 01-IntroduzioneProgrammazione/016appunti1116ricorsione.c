/*
appunti 16 novembre 2022
*/
#include<stdio.h>
#include<stdlib.h>


// piccola parentesi interessante e utile sullo scanf
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
   else return v[l-1]%2==0 && tutti_pari1(v, l-1);
}

int main1(){ //sarebbe il main relativo alla funz sopra
    int x[] =  {2, 4, 6, 8, 10};
    printf("%d", tutti_pari1(x, 5));
    return 0;
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
    return 0;
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
     * sttinsieme, quindi bsta una sola delle due. (=> or logico).
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
    if (l==0 && t>0) return 0; //se sono arrivato alla fine dell'array e la somma non è ancora 0, ritorno false
    if (t==0) return 1; //se la somma arriva a zero, ho rislto e ritorno true
    if (v[l - 1] > t) return subset_sum(v, l-1, t); //skippo gli elementi tropo grandi
    return (subset_sum(v, l-1, t) || subset_sum(v, l-1, t-v[l-1]));
        //il famoso or logico di prima: o richiamo la funzione su tutti i valori meno l'ultimo escluso, oppure 
        //richiamo la funzione sempre con l'elemento in meno ma con il gap mancante corretto.
}

int main3(){
    int x[]={2, 4, 5, 6, 6, 11};
    printf("%d\n", subset_sum(x, 6, 25));
    return 0;
}

/**
 * Scrivere funzione ricorsiva che mi dica se una stringa è palindroma
*/
int pal(char* s, int l){
    //caso base: se l==1, return v[0] == v[l-1] 
    //passo induttivo: return pal(v+1, l-1)
    if (l<=1) return 1;
    else return s[0] == s[l-1] && pal(s+1, l-2);
}
int  main4(){
    char* s1 = "abcddcba";
    char* s2 = "abcdcba";
    char* s3 = "asdfghjk";
    char* s4 = "asdfghj";
    printf("palindroma pari: %d\n", pal(s1, 8));
    printf("palindroma dispari: %d\n", pal(s2, 7));
    printf("non palindroma pari: %d\n", pal(s3, 8));
    printf("non palindroma dispari: %d\n", pal(s4, 7));
    return 0;
}
/**
 * per la frase "i topi non avevano nipoti", come si risolve, dati gli spazi?
*/
int pal_space(char* s, int l){
    if (l<=1) return 1;
    else {
        if (s[0]==' ') return pal_space(s+1, l-1);
        else if (s[l-1]==' ') return pal_space(s, l-1);
        else return s[0] == s[l-1] && pal_space(s+1, l-2);
    }
}
int  main5(){
    char* s1 = "i topi non avevano nipoti";
    printf("%d\n", pal_space(s1, 25));
    return 0;
}

/*
 * Abbiamo una scorta infinita di pali di legno di 4 colori diversi con i quali dobbiamo costruire una staccionata
 * composta da n pali in tutto, con un solo vincolo: due pali dello stesso colore devono avere almeno altri due
 * pali di colore diverso a separarli. Scrivere una funzione che dato n restituisca il numero di configurazioni
 * possibili.
 * esempio: fence(1) = 4;
 *          fence(4) = 48;
*/
int fence(int n, int p, int pp){
    // logica: se non ho paletti, ho un solo modo di non mettere nulla. => caso base: if n==0, return 1.
    //      se metto un paletto, mi mancano n-1 paletti, mi interessa quindi sapere fence (n-1).
    //      per ogni opzione di colore del paletto 1, ho tot modi di mettere n-1 paletti.
    //      di conseguenza, la quantità di possibilità totali è la somma delle possibilità per le 4 opzioni.
    //      ora serve il vincolo: tra due paletti dello stesso colore servono due paletti di colore diverso.
    //      mi servono quindi due informazioni che mi mancano: colore del paletto precedente e colore del paletto pre-precedente
    //      quindi se p!=1 e pp!=1, posso mettere paletto di colore 1.
    //      ugualmente, se p!=2 e pp!=2 posso mettere paletto di colore 2, etc.
    //      la somma di tutte le combinazioni possibili mi da il risultato del problema.
    if (n==0) return 1;
    int sum = 0;
    if (p!=1 && pp!=1) sum += fence(n-1, 1, p);
    if (p!=2 && pp!=2) sum += fence(n-1, 2, p);
    if (p!=3 && pp!=3) sum += fence(n-1, 3, p);
    if (p!=4 && pp!=4) sum += fence(n-1, 4, p);
    return sum;
}
int main(){
    int n = 10;
    printf("%d\n", fence(n, 0, 0));
    return 0;
}

