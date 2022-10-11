/*

ASSEGNAMENTO - APPROFONDIMENTO

*/

#include<stdio.h>

int main1(){
    
    double a = 0.1;
    printf("lol, guarda qua: 0.1+0.1+0.1 fa 0.3? %d (0 significa no.)", a+a+a==0.3);

    /*La difficoltà di rappresentazione nell’esempio sopra è dovuta all’uso della base 2 nella rappresen‑
    tazione binaria. Così come non possiamo rappresentare il risultato di 1/3 (=0.3333...) in base 10 con
    un numero finito di cifre perché 3 non è un divisore della base 10, così non possiamo rappresentare
    0.1 = 1/10 = 1/(5*2) in base due con un numero finito di cifre perché 5 non è divisore della base 2.
    In questi casi, è una buona pratica non confrontare due numeri double/float con un operatore di
    uguaglianza, ma piuttosto misurare se la differenza tra i due numeri è inferiore ad una certa soglia
    di tolleranza. Ad esempio, in certe applicazioni, potremmo considerare due valori double equivalenti
    se la loro differenza è minore di 10^−9.*/

    float b = a = 1.0;

    /*L’assegnamento è un un’espressione così come la somma di due variabili. Questo significa che
    così come l’espressione a+b produce un valore corrispondente alla somma dei due addendi, anche
    l’espressione x = z produce un valore. Il valore prodotto corrisponde (anche nel tipo) all’espressione
    alla destra dell’operatore =. A differenza delle espressioni usuali, l’espressione di assegnamento ha il
    side‑effect (effetto collaterale) di cambiare il contenuto della memoria, memorizzando il contenuto
    dell’espressione a destra dell’operatore = nella locazione di memoria identificata dall’espressione a
    sinistra dell’operatore =.
    L'espressione qui sopra è del tutto equivalente a 
    
    float b = (a = 1.0);

    L'operatore è infatti associativo da destra a sinistra. prima viene valutato l'assegnamento a=1.0, che ha come valore 1.0
    (e come side effect la scrittura di 1.0 in memoria), poi viene valutata l'operazione b = [...], che ha ugualmente 
    valore 1.0.
    Poiché il valore risultate dall’espressione di assegnamento è un valore valido come tutti gli altri, a
    questo possiamo applicarci altre operazioni.

    */
    int c;
    b = 20;
    a = b + ( c = 10 );
    printf("a = %d \n", a);
    printf("b = %d \n", b);
    printf("c = %d \n", c);
    
    return 0;
}

int main2 (){
    /* 
    OPERATORI DI INCREMENTO E DECREMENTO
    L’operatore di incremento/decremento può essere sia suffisso che prefisso: i++ o ++i. Possiamo
    dire che entrambe le espressioni hanno un side‑effect, ovvero cambiano il contenuto della variabile
    i incrementandola di 1, e un valore prodotto che viene usato ai fini dell’espressione che contiene
    l’incremento. Nel caso prefisso, il valore prodotto è il valore della variabile incrementata, mentre nel
    caso suffisso il valore prodotto è il valore della variable senza alcuna modifica.
    Se consideriamo il codice seguente, al termine dell’esecuzione la variabile c contiene il valore 10,
    ovvero il contenuto di a prima dell’incremento, mentre la variabile d contiene il valore 11 ovvero il
    contenuto di b dopo l’incremento    
    
    a++ significa quindi "prendimi a, poi incrementalo di 1", ovvero restituisce il valore di a e POI incrementa.
    ++a significa quindi "dammi il valore di a incrementato di 1 e incrementa anche a".
    
    a++ ha come valore il contenuto della variabile e come side effect la scrittura in memoria del +1,
    ++a ha come valore il contenuto della variabile+1 e stesso side effect*/
    int a = 10, b = 20, c, d;
    c = a++;
    d = ++b;
    
    printf("a = %d \n", a);
    printf("b = %d \n", b);
    printf("c = %d \n", c);
    printf("d = %d \n", d);


    //cosa succede se faccio
    int i = 2;
    i = ++i + i++;
    i = i++ + 1;
    // ?
    /*In generale, è definito un ordinamento di valutazione per alcune espressioni del linguaggio, ma non
    per tutte. Nei casi sopra non è definito quale dei due incrementi viene eseguito per primo, o se
    l’incremento suffisso viene eseguito dopo l’assegnamento. E’ una mancanza nella definizione del lin‑
    guaggio. In questi casi, il comportamento viene deciso dal compilatore in base all’implementazione
    o da strategie di ottimizzazione del codice. Il risultato è quindi non definito: ogni compilatore e ogni
    esecuzione potrebbe portare a risultati diversi.
    Sono assolutamente da evitare questi casi di ambiguità, e in generale un uso spinto di espressioni
    complesse e compatte a scapito della leggibilità del codice.*/
}

/*
conversioni implicite ed esplicite
*/

int main(){
    char a = '5';
    int b = 9;
    int result = a+b;
    printf ("%d\n", result);
    //output = 62. La variabile char viene convertitio nel decimale ascii corrispondente (53).
    
    //double aa = 5.67;
    //result = aa+b;
    //printf ("%d\n", result);
    //output =  14. 
    /* è successo questo: il 9 (int) è stato convertito nel tipo superiore: 9.0 (double). 
    successivamente i due double son stati sommati: 9.0 + 5.67 = 14.67.
    Questo risultato è poi memorizzato su una variabile di tipo int, venendo quindi troncato in 14 (int)*/

    //posso essere sicuro del troncamento successivo e non della conversione da double a int facendo così:

    //double result_db = aa+b;
    //printf("%lf\n",result_db);

    /*La conversione segue quindi una GERARCHIA DEI TIPI:
    1. long double
    2. double
    3. float
    4. long
    5. int
    6. short
    7. char

    se mi trovo a fare operazioni tra tipi diversi, quello più "in basso" tra i due viene convertito "verso l'alto"

    */

    int prova = -9.0;
    /*come sappiamo, l'assignamento va da destra a sinistra. per cui, nel caso qua sopra, il numero 9.0 è float,
    ma viene assegnato in una variabile di tipo int, e conseguentemente convertito. 
    In questo caso, può accadere anche una "retrocessione"*/
    printf("%d\n", prova);
    printf("%lf", prova);
    return 0; 
}