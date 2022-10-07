/*
SCOPINg E FUNZIONI

Funzioni:
https://en.cppreference.com/w/c/language/functions 
Una funzione è un costrutto che associa un compound statement (il corpo della
funzione) ad un identificatore (il nome della funzione),
Le funzioni possono accettare zero o più parametri che vengono inizializzati con
gli argomenti usati al momento della chiamata (tempo di esecuzione).
Le funzioni possono avere un return statement che definisce il valore “prodotto”
dalla funzione e restituito al chiamante;
Il tipo speciale void viene usato per specificare nessun parametro / valore di
ritorno.



Scope
https://en.cppreference.com/w/c/language/scope
Ci sono 2 scope principali:
● file scope: identificatori dichiarati all’esterno di qualunque blocco sono visibili
dal punto della dichiarazione fino alla fine del file.
● block scope: identificatori dichiarati nella dichiarazione di una funzione o
all’interno di un blocco sono visibili dal punto della dichiarazione fino alla fine
del blocco corrispondente.
I blocchi possono essere annidati (nested).
*/


int variabile = 1; //questa variabile si chiama globale, è visibile in tutti i blocchi

int funzione_somma (arg1, arg2){ 
    //la funzione va inizializzata con il tipo che restituisce (intero in questo caso)
    //il nome della funzione è quello con cui la si richiama nel resto del programma.
    //si inseriscono nelle parentesi tonde gli (eventuali) argomenti da processare
    //le parentesi graffe racchiudono il compound statement che elabora il tutto


    int risultato = arg1+arg2; //come da definizione di scope, questa variabile, dichiarata
                               //in questo ambiente (blocco) NON è visibile all'esterno.

    return risultato; //restituisco il risultato
}

void funzione_inutile (){
    printf("ciao"); //non esiste il return, il void è il tipo particolare di che non lo richiede
}   

void funzione2(argomento){
    if (argomento>1){
        return;
        //il return serve, in generale, a uscire dalla funzione. In questo caso, se argomento>1
        //il comando "printf" non viene proprio eseguito, perché si esce dal blocco.
    }
    printf("dlfkub\n");
}

int main (){
    
    int argomento = 1;
    funzione2(argomento); //print
    argomento += 1;
    funzione2(argomento); //nulla
    
    //N.B. non è necessario che i nomi delle variabili tra i due blocchi corrispondano:
    //avrò infatti lo stesso risultato facendo così:

    int z = 1;
    funzione2(z);
    z += 1;
    funzione2(z);

    {
        int w = 2;
    }
    // qua fuori il w non esiste, perché dichiarato in un blocco "piu interno"
    variabile += 1; //questa variabile è la stessa dichiarata globalmente, quindi in un
                    //bloco più esterno. di conseguenza è lecito usarla, è visibile

    /*
    risultato = funzione_somma (24, 12); 
    questa riga non posso scriverla, perché "risultato" è dichiarata solo nella funzione,
    che ha un blocco separato da questo.

    Non posso nemmeno scirvere
    int risultato = funzione_somma (24, 12);
    perché il nome di questa variabile è già usato per un altro oggetto. o questa o quella della funzione
    devono cambiare nome, non posso dichiarare due volte lo stesso nome, anche se separati (in C, altri linguaggi
    gestiscono diversamente il conflitto).
    */

    z = funzione_somma (24, 12);
    printf("%d\n", z);

    //la roba della dichiarazione delle variabili, non vale solo per le funzioni, ma per qualsiasi blocco.
    //se dichiaro una variabile dentro un if, fuori da questo if NON ESISTE la variabile.

    //ultima regola: come le variabili vanno dichiarate PRIMA che vengano usate, così le funzioni vanno dichiarate
    //prima di essere chiamate all'interno del main. 
    // (a dirla tutta, alcuni compilatori sistemano da soli questo errore, ma è formalmente sbagliato).

    return 0;
}