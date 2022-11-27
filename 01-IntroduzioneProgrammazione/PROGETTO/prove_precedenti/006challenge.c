#include<stdio.h>
#include<stdlib.h>
#include"005prova_ia.c"

// le due funzioni qui sotto esistono già in libreria, le ho ricreate a puro scopo didattico
// più roba faccio, più imparo e più mi vien naturale programmare

int lunghezza_stringa(char stringa[]){
    _Bool finita = 0;
    int accum = 0;
    for (int i = 0; !finita; i++){
        if (stringa[i]!='\0') accum++;
        else finita = 1;
    }
    return accum;
}

int confronta_stringhe(char* stringa1, char* stringa2){
    _Bool sono_uguali = 1;
    if (lunghezza_stringa(stringa1) != lunghezza_stringa(stringa2)) return 0;
    else {
        for (int i=0; i<lunghezza_stringa(stringa1) && sono_uguali; i++){
            if (stringa1[i] != stringa2[i]) sono_uguali = 0;
        }
        return sono_uguali;
    }
    
}

void giocachallenge(int rows, int columns, char* labirinto){
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ///                                         NOTA BENE                                                //
    ///             TUTTO STO ROBO È IN REALTÀ SEMPLICE FUNZIONE IA, QUANDO UNISCO SISTEMO               //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    // Ah, inoltre, ci sono conflitti tra colonne, righe e i due define, quindi per non aver problemi, nella
    // prova di funzionamento usero direttamente 15, 19 e il labirinto che già ho creato. tanto non cambia nulla,
    // è solo per vedere se funzionano come argv di input 
    
    int posizione = 1*columns + 0; 
    _Bool siamo_in_gioco = 1;
    int direzione = 2;

    for (int  i=0; siamo_in_gioco; i++){
        if      (labirinto[destra(posizione, direzione)] == '#' && labirinto[avanti(posizione, direzione)] == ' ') {
            posizione = avanti(posizione, direzione);
            stampa(direzione);
            if((posizione%colonne) == (colonne-1)) siamo_in_gioco = 0;
        }
        else if (labirinto[destra(posizione, direzione)] == '#' && labirinto[avanti(posizione, direzione)] == '#') {
            direzione = (direzione != 1) ? (direzione - 1) :  4;
        }
        else if (labirinto[destra(posizione, direzione)] == ' ') {
            direzione = (direzione != 4) ? (direzione + 1) :  1;
            posizione = avanti(posizione, direzione);
            stampa(direzione);
            if((posizione%colonne) == (colonne-1)) siamo_in_gioco = 0;
        }
        else printf("non so cosa fare\n");
    }

}

int main(int argc, char* argv[]){

    if (argc<5) {
        printf("vez, non hai messo abbastanza argomenti\n");
        return 0;
    }
    else if (argc>5){
        printf("vez, hai messo troppi argomenti\n");
        return 0;
    }
    if (!confronta_stringhe(argv[1], "--challenge")){
        printf("vez, non riconosco il primo argomento che hai messo\n");
        return 0;
    }
    if (atoi(argv[2])==0 || atoi(argv[3])==0){
        printf("vez, non hanno molto senso i valori che hai scritto di righe e/o colonne\n");
        return 0;
    }

    if (confronta_stringhe(argv[1], "--challenge")) {
        int rows = atoi(argv[2]);                           //le avrei chiamate rghe e colonne lol, ma va in conflitto con il define di prova_ia... sistmerò
        int columns = atoi(argv[3]);
        giocachallenge(rows, columns, argv[4]);
    }

    return 0;
}




// funzia alla perfezione provare per credere.
/* 
gcc challenge.c  -o a.out && ./a.out --challenge 15 19 "###################   #  #  #     #  ##  #  #  #  #  #  ##  #  #  #  #  #  ##  #     #  #  #  ##  #     #  #     ##  #     #  #  #  ##  #     #  #  #  ##  #     #  # ##  ##  #  #  #  #  #  ##  #  #    ##  #   #  #  # # # #  #  ##     # ##  #  #  ##    ##  #  #  #  ####################"
*/


//non so di preciso come ci venga fornito il labirinto, probabilmente però riga per riga, non come argv ma successivamente come input. vado quindi  su challenge2 a fare questa cosa.
// mi serviranno i codici di test e test_exe.


