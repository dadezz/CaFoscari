#include<stdio.h>
#include<stdlib.h>
#define righe 15
#define colonne 19


int avanti(int posizione, int direzione){
    switch (direzione){
        case 1:
            return posizione - colonne;
        case 2:
            return posizione +1;
        case 3:
            return posizione + colonne;
        case 4:
            return posizione - 1;
    }
}

int destra(int posizione,int  direzione){
    switch (direzione){
        case 1:
            return posizione +1;
        case 2:
            return posizione + colonne;
        case 3:
            return posizione -1;
        case 4:
            return posizione - colonne;
    }
}

void stampa(int direzione){
    switch (direzione){
        case 1:
            printf("N ");
            break;
        case 2: 
            printf("E ");
            break;
        case 3: 
            printf("S ");
            break;
        case 4: 
            printf("O ");
            break;
        }
}

int main(){    

    int posizione = 1*colonne + 0; //RIGA*colonne + COLONNA (matrice[i][j] = matrice[riga][colonna])
    _Bool siamo_in_gioco = 1;
    int direzione = 2;
        // 1 = Nord  = alto;
        // 2 = Est   = destra;
        // 3 = Sud   = basso;
        // 4 = Ovest = sinistra

    char struttura_labirinto[] =  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',  //a[0][0],  a[0][1],  a[0][2] etc
                                   ' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',  //a[1][0],  a[1][1],  a[1][2] etc
                                   '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[2][0],  a[2][1],  a[2][2] etc
                                   '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[3][0],  a[3][1],  a[3][2] etc
                                   '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[4][0],  a[4][1],  a[4][2] etc
                                   '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',  //a[5][0],  a[5][1],  a[5][2] etc
                                   '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[6][0],  a[6][1],  a[6][2] etc
                                   '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[7][0],  a[7][1],  a[7][2] etc
                                   '#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ','#','#',' ',' ','#',  //a[8][0],  a[8][1],  a[8][2] etc
                                   '#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[9][0],  a[9][1],  a[9][2] etc
                                   '#',' ',' ','#',' ',' ','#',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ',' ',  //a[10][0], a[10][1], a[10][2] etc
                                   '#',' ',' ','#',' ',' ','#',' ','#',' ','#',' ','#',' ',' ','#',' ',' ','#',  //a[11][0], a[11][1], a[11][2] etc
                                   '#',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[12][0], a[12][1], a[12][2] etc
                                   '#',' ',' ',' ',' ','#','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',  //a[13][0], a[13][1], a[13][2] etc
                                   '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',}; //a[14][0], a[14][1], a[14][2] etc    
    /*
    * logica del gioco:
    *
    * il pallino è orientato in una direzione, in questo modo si può interpretare il concetto di "destra" e di "avanti":
    * 
    * casistiche direzione:
    *       caso 1 (nord):
    *           destra = posizione + 1;
    *           avanti = posizione - colonne;
    *       caso 2 (est):
    *           destra = posizione + colonne;
    *           avanti = posizione +1;
    *       caso 3 (sud):
    *           destra = posizione - 1;
    *           avanti = posizione + colonne;
    *       caso 4 (ovest):
    *           destra = posizione - colonne;
    *           avanti = posizione - 1;
    * 
    * Bon. definito il concetto di destra, vediamo il movimento:
    * 
    * se destra == '#' e avanti == ' ':
    *       ovvero: posizione = avanti.
    * se destra == '#' e avanti == '#':
    *       direzione -=1 (in senso antioriario, ovviamente da 1 si passa a 4).
    * se destra == ' ' e avanti == ' ':
    *       direzione += 1 (in senso orario, ovviamente da 4 si passa a 1);
    * 
    * */
    
    for (int  i=0; siamo_in_gioco; i++){
        if      (struttura_labirinto[destra(posizione, direzione)] == '#' && struttura_labirinto[avanti(posizione, direzione)] == ' ') {
            posizione = avanti(posizione, direzione);
            stampa(direzione);
            if((posizione%colonne) == (colonne-1)) siamo_in_gioco = 0;
        }
        else if (struttura_labirinto[destra(posizione, direzione)] == '#' && struttura_labirinto[avanti(posizione, direzione)] == '#') {
            direzione = (direzione != 1) ? (direzione - 1) :  4;
        }
        else if (struttura_labirinto[destra(posizione, direzione)] == ' ') {
            direzione = (direzione != 4) ? (direzione + 1) :  1;
            posizione = avanti(posizione, direzione);
            stampa(direzione);
            if((posizione%colonne) == (colonne-1)) siamo_in_gioco = 0;
        }
        else printf("non so cosa fare\n");
    }
    return 0;
}