#include<stdio.h>
#include"004gestione_io.c"
#include<stdlib.h>


//funzione contenuta in gestione_io, stampa il labirinto.
extern void print_lab(char x[][19], int righe, int colonne, int *punteggio);
//funzione contenuta in gestione_io, controlla il carattere in input
extern void scanf_lab(char *x);
//funzione contenuta in gestione_io, muove 'o' a seconda del a,s,d,w.
extern void controllo_input(char x[][19], int *riga_o, int *col_o, int carattere_in_input, _Bool *gioco,int *numero_dollari);
//funzione contenuta in gestione_io, inserisce N dollari in posizioni randomiche nel labirinto
extern void inserisci_dollari (int bonus, char s[][19]);
//funzione contenuta in gestione_io, inserisce N ! in posizioni randomiche nel labirinto
extern void inserisci_imprevisti (int imprevisti, char s[][19]);


int main (){

    char carattere_in_input = '*';  //variabile su cui viene salvato il carattere di input usato per spostarsi
    int punteggio = 100;            //(i passi necessari sono circa una 50ina)
    int bonus = 10;                 //quanti dollari devono esserci nel labirinto.
    int imprevisti = 3;             //quanti ! devono esserci nel labirinto.
    int numero_dollari = 0;         //variabile che conta la quantita di bonus raccolti
    _Bool gioco = 1;                //"sei nel gioco?" diventa false quando riesce ad arrivare alla colonna 18 (così si ferma il while)
    int riga_o = 1, col_o = 0;      //coordinate di 'o', inizializzate alla partenza (struttura_labirinto[1]

    char struttura_labirinto [][19] =  {{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},  //a[0][0],  a[0][1],  a[0][2] etc
                                        {'o',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#'},  //a[1][0],  a[1][1],  a[1][2] etc
                                        {'#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[2][0],  a[2][1],  a[2][2] etc
                                        {'#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[3][0],  a[3][1],  a[3][2] etc
                                        {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[4][0],  a[4][1],  a[4][2] etc
                                        {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#'},  //a[5][0],  a[5][1],  a[5][2] etc
                                        {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[6][0],  a[6][1],  a[6][2] etc
                                        {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[7][0],  a[7][1],  a[7][2] etc
                                        {'#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[8][0],  a[8][1],  a[8][2] etc
                                        {'#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[9][0],  a[9][1],  a[9][2] etc
                                        {'#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' '},  //a[10][0], a[10][1], a[10][2] etc
                                        {'#',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[11][0], a[11][1], a[11][2] etc
                                        {'#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[12][0], a[12][1], a[12][2] etc
                                        {'#',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#',' ',' ','#'},  //a[13][0], a[13][1], a[13][2] etc
                                        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}}; //a[14][0], a[14][1], a[14][2] etc

    inserisci_dollari(bonus, struttura_labirinto); 
    inserisci_imprevisti(imprevisti, struttura_labirinto);   

/*LOGICA PER INSERIRE i dollari a casissimo dentro al labirinto (pseudocodice).
for i in range numero_di_dollari_che_ voglio : meglio usare un while, così posso incrementare solo se il dollaro finisce dove non c'è un cancelletto
    a, b = randint (10)(19)
    if struttura_labirinto[a][b] != '#';
         struttura_labirinto[a][b] = '$'
    print_lab(struttura_labirinto, 15, 19); //stampo il labirinto


DOPODICHÉ
if struttura_labirinto[riga_o (+-1)][col_o (+-1)] = '$':
    numero_dollari ++.

A FINE PROGRAMMA 
punteggio += (dollari*3)
*/

    //corpo del gioco. tutto va avanti obv finché non finisce


    while (gioco){                                                                              // il gioco va avanti finché il bool 'gioco' è vero (si falsifica all'uscita del labirinto).
        print_lab(struttura_labirinto, 15, 19, &punteggio);                                                 // mostro lo stato attuale del labirinto. notare che (voluto) l'ultima mossa
                                                                                                // non verrà mai mostrata, ma viene solo stampato messaggio di vittoria.
        printf("Inserisci la prossima mossa: \n");                                              // chiedo la mossa successiva
        scanf_lab(&carattere_in_input);                                                         // e la scanfo.
        punteggio -= 1;                                                                         // a prescindere dalla correttezza della mossa (muro, non comando sbagliato), tolgo un punto.
        system("clear");                                                                        // pulisco lo schermo del terminale, in modo da dare l'illusione di un movimento in tempo reale
        controllo_input(struttura_labirinto, &riga_o, &col_o, carattere_in_input, &gioco, &numero_dollari);      // eseguo la logica del gioco (effettivo movimento)
        printf("punteggio attuale: %d, \nbonus raccolti: %d\n", punteggio, numero_dollari);                                                              // printo il punteggio derivante dalla mossa appena fatta.                                                                
        
    }

    printf("punteggio finale: punteggio + 3 punti per ogni bonus = %d ", 3*numero_dollari + punteggio);

    return 0;                                                                                   // Fine del programma.
}