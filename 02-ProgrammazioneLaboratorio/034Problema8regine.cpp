/**
 * devo mettere 8 regine in una scacchiera 8*8 senza che si minaccino tra loro. Posso?
 * se sì, mostro il risultato.
 * 
 * obv, ricorsivo.
 * 
 * Che struttura dati posso usare?
 * una matrice 8x8 di short: {0: libero e non sotto scacco; 1: libera ma sotto scacco; -1: cella con una regina}
 * 
 * Algoritmo:
 * quando prendo in considerazione le colonne, ho una regina per ognuna. quindi se non riesco a metterne neanche una sulle varie righe, 
 * allora non ho un risultao valido.
 * suppongo quindi di avere la fatina della ricorsione che mi aiuta a trovare la soluzione sulla scacchiera di 7 colonne e 8 righe.
 * questa fatina mi dice " si sono riuscito" oppure "no nun se po'fa".
 * 
 * quindi:
 * provo a mettere la regina in A1. chiamo la fatina. la ricorsione ci prova. se la ricorsione ci riesce ottimo ho la sooluzione, 
 * se non ci riesce sposto la regina in A2 e ci riprovo. facico uguale finché non trovo la sol al problema o finché non metto la regina in A8 
 * e scopro che non si può fare.
 * 
 * La ricorsione che permette di fare un tentativo e se questo non va a termine tornare sui propri passi e riprovare da un'altra parte, si chiama backtracking
 * [ LMAO È QUEL CHE ABBIAMO FATTO COL LABIRINTO MUUUUHHHH CHE SCOPERTAAAA ] XD
 * 
 * Quando tolgo la regina, devo segnare sulla scacchiera che le celle non disponibili diventano disponibili. problema: può essercene un'altra che ancora la 
 * controlla. Con la codifica che abbiamo scelto, non so se la cella è controllata solo da lei o anche da altre.
 * 
 * la codifica non favorisce il backtracking: ogni volta che levo la regina dovrei controllare tutte le altre cosa controllano.
 * 
 * posso cambiare la codifica mettendo n al posto di 1: la cella è libera ma sotto scacco da n regine. quando metto la regina incremento di 1
 * tutte le celle su colonna, riga, diagonali. idem quando la levo decremento di 1.  
 * 
*/
#include <vector>
using std::vector;

enum Azione {rimuovi = -1, aggiungi = 1};


void posiziona(vector<vector<short>> & scac, short row, short col, Azione az){
    for (int i = 0; i<8; i++){
        for (int j = 0; j<8; j++){
            if (i==row && j==col && az == aggiungi)
                scac.at(i).at(j) = -1;
            else if (i == row or j==col or (i-row==j-col) or (i+j == row+col)) scac.at(i).at(j) += az;
        }

    }
}

bool regina(vector<vector<short>> & scac, short col){
    // inizio con test esistenziale
    if (col == 8) return true;
    bool found = false;
    short row = 0;
    while (row<8 && !found){
        if (scac.at(row).at(col) == 0) {
            posiziona(scac, row, col, aggiungi); 
            found = regina(scac, col+1);
            if (!found) {
                row++;
                posiziona(scac, row, col, rimuovi);
            }
        }
        else row++;
    }
    return found;
}

/**
 * PROBLEMA: dato un vector di int, dire se si può formare una somma s con n addendi
*/

bool trova_somma (const vector<int> & v, int s , int add, int pos){
    bool ris;
    ris = trova_somma(v, s-v.at(pos), add-1, pos+1) or trova_somma(v, s, add, pos+1);
    return ris;
}