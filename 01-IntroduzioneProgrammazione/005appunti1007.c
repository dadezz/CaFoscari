#include<stdio.h>
/*
10 ottobre 2022
blocch, scope, funzioni
*/

// def scope: parte del programma in cui la chiamata di una variabile (nome) è valida,
// ovvero ci si può riferire ad essa. si parla quindi di annidamento di blocchi e funzioni, 
// di variabili globali etc.
// c'è una regola fondamentale: le variabili si vedono SOLAMENTE nel bloco dove sono state dichiarate.

void f(){
    int x = 8; 
    int z = 9;
    printf("x = %d\n", x);
    /*
    la variabile x è la stessa del main? no.
    come per la regola sopra, questa x è visibile esclusivamente in questa funzione
    e la x nel main è visibile esclusivamente nel blocco del main.
    */
}

int x = 45; //questa variabile è dichiarata nel blocco più esterno di tutti, nel quale sono annidati
            //tutti gli altri. Ergo, è una variabile globale (visibile in tutti i blocchi)

int g = 63;

int main1 (){
    int x = 10;
    int d = g;  //è legale? sì: g è variabile globale e si vede all'interno di questo blocco.
                //blocco: pezzo di codice di piu righe tra parentesi graffe
    int t = z;  //legale? no: z è stata dichiarata nella funzione "f" sopra, blocco separato da questo,
                // z non è quindi visibile.
    if (x<16){
        int y = x+1;
        printf("printf y=%d\n", y);
        x += 3; //variabile x visibile nel blocco, ambiente annidato nell
                //ambiente dove è stata inizializzata
    }
    printf("x = %d\n", x); //fuori dal blocco dell'if: non viene aggiunto 3 se non è minore di 16
    printf("y = %d\n", 7); //fuori dal blocco dell'if. La variabile esiste solo la dentro, su
                           //questa riga non esiste: errore.
    /*
    Se l'if è falso viene letteralmente skippato. di conseguenza, x non cambia e y non viene proprio
    dichiarata, quindi non esiste e non si può usare/stampare.    
    
    Interessante notare che, sebbene x sia effettivamente minore di 16 e quindi il blocco venga eseguito,
    y comunque non è visibile. perché?
    c'è una regola fondamentale: le variabili si vedono SOLAMENTE nel bloco dove sono state dichiarate. 
    Quindi, dopo il blocco dell'if, la variabile y viene distrutta e nell'ambiente esterno non è più visibile
    */
    return 0;
}

void ff(){
    if (0){
        int w;
        if (0){
            int v;
            if (0){
                int t;
            }
            w = t-1; 
            /*
            la variabile w è visibile. (a colpo d'occhio, basta guardare l'indentazione).
            la variabile t non è visibile. Perché dichiarata nel blocco dell'if, che è stato chiuso,
            successivamente è stata quindi distrutta. (anche qui, t è stata dichiarata "a destra" di quando
            viene usata e quindi di nuovo grazie all'indentazione si può intuire).
            */
        }
    }
}

/*
Cosa succede se c'è una variabile globale (o in un blocco esterno) e dopo la si ridichiara?
Ci sono due possbilità, a seconda del linguaggio di programmazione. Alcuni "mettono in ombra" quella globale, 
facendo funzionare nel blocco solo quella nuova. Nel caso di C non è così, non si può dichiarare di nuovo una variabile
dichiarata in precedenza (e visibile dal blocco dove si sta lavorando). il programma non compila.
*/


int main (){
    int xx;
    scanf("%d\n", &xx);

    if (xx % 2 == 0){   
        //modulo: operatore binario (ovvero opera su due operandi)
        printf("pari\n");
    }
    else printf("dispari\n");

    return 0;
}