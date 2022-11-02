/*
la scorsa volta abbiamo visto la malloc. 
oggi vediamo stringhe
*/

#include <stdio.h>
#include <stdlib.h>

int main1(){
    char a = 'a';
    char b = 65;

    //i char hanno doppia natura di int e char, secondo la codifica corrispondente (ascii)
    //nell'alfabeto i caratteri sno consecutivi, in termini di intero corrispondente
    //le stringhe sono seqenze di caratteri
    char *s = "questa è una stringa"; //è giusto, puntatore = array.
    printf("%c \n", *s);
    printf("%s \n", s); //con %s stampo direttamente una stringa.

    //c'è una differenza fondamentale tra array di caratteri e stringhe: queste ultime non sono modificabili, ma in sola lettura.
    //non si può quindi fare a[2]='x'; 
    char z[] = "fuyjk"; //altro modo di creare una stringa, con logica array. in questo caso, pure scrittura.
}

    
//come funziona la gestione della dimensione?

void my_print(char *s ){
    for (int i=0, len = 0; i < len; i++){ //qual è len?
        printf("%c", s[i]);
    }
    printf("\n");

    //la convenzione vuole che ci sia un caratttere speciale di terminazione stringa: \0
    for (int i=0; i!= '\0'; i++){ 
        printf("%c", s[i]);
    }
    printf("\n");
}

//quindi in realta mi viene allocato goni volta un byte in più: \0, che non si vede.
//esercizio: scrivere una f che, data una stringa s, restituisca una nuova stringa senza minuscole.

char* f(char *s){
    /* si può usare ascii per controllare, scorrendo la stringa, ogni carattere */
    char *new_s = malloc(strlen(s)+1);
    int j=0;

    for (int i=0; s[i]!='\0'; i++) if ( !(s[i]>='a' || s[i]<='z') ) new_s[j++] = s[i];
    new_s[j]= '\0';

    //posso ora disallocare la memoria non usata dopo il \0
    //(potevo allocare giusto già contando con un for la grandezza necessaria)
    new_s = (char*) realloc(new_s, j+1);
}

int main (){
    char *s = "BUon GioRNo a TUtTi!";
    char *new_s = f(s);
    printf("%s\n", new_s);
}