/*
Appunti 10 ottobre 2022


CICLO FOR

*/

#include <stdio.h>

/* dire se n è primo. Ovvero devo controllare tutti i numeri da 2 a n-1 se sono divisori di n, ovvero se hanno resto zero.*/

void is_prime_vecchio_stile (int N){
    int x = 2;
    if (x<N && N%x==0){
        printf("Niente da fare");
    }
    else {
        x = x+1;
        if  (x<N && N%x==0){
            printf("Niente da fare");
        }
        //else if etc etc, copincollo i blocchi di prima.

        /*
        
        [...]
        
        */

        /*...   indentazione   ...*/        else printf("primo.");
    }    
}

/*
Ci serve quindi un modo per ripetere questa cosa del ripetere i blocchi automaticamente. 
introduco quindi la sintassi del ciclo for:

for (expr[1]; bool[2]; expr[3]){
    statement;
}

[2] La seconda espressione (bool) è la più importante tra le tre. è la condizione che, se verificata, decreta l'entrata dentro al ciclo.
    Deve quindi contenere una condizione che può assumere i valori vero o falso (e simili: anche risultati 1 e 0).
    Di base, la condizione è vera, ciò significa che il ciclo vuoto for (;;){"statement"} è perfettamente legittimo, ed è un ciclo sempre vero, infinito.
    La condizione viene valutata all'inizio di ogni iterazione, non alla fine. Se risulta vera, entro nel ciclo, altrimenti skippo il blocco in toto.
[3] Il terzo blocco è un'espressione qualsiasi che voglio che sia eseguita alla fine di ogni iterazione del ciclo. Tipicamente è qualcosa che cambi valore
    a una variabile che "conta" le iterazioni nel ciclo, spesso è infatti nella forma i+=1. Da precisare comunque che può essere letteralmente qualsiasi
    espressione: contatore, printf, richiamo di un altra funzione etc etc. qualsiasi cosa.
[1] Il primo blocco viene eseguito una volta sola, all'inizio del ciclo (non di ogni singola iterazione). Di norma viene usato per dichiarare e inizializzare 
    la variabile contatore, quella che viene modificata nel terzo blocco. 

Ciò che si dichiara dentro al ciclo cessa di esistere alla fine del blocco. Volendo si potrebbe infatti dichiarare la variabile contatore fuori dal ciclo, ma
risulta più efficiente farlo nel blocco [1], perché viene eliminata la variabile quando non serve più.
L'unico modo per uscire dal ciclo è che la condizione nel blocco [2] risulta falsa.
*/

void is_prime (int N){
    _Bool primo = 1;
    for (int x=2; primo && x<N; x+=1){ // Se trovo un divisore, è inutile che continui il ciclo, quindi nella condizione [2] controllo se ho già scoperto se è o meno primo
        if (N%x==0) primo = 0;
    }
    if (primo) printf("il numero è primo.\n");
    else printf("niente da fare.\n");
}



int main (){
    is_prime(7);
    return 0;
}
