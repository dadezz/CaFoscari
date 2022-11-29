#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void stampa_char(char* map, int r, int c){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
        printf("%c ", map[i*c+j]);
        }
        printf("\n");
    }
}
void stampa_int(int* map, int r, int c){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            if (map[i*c+j]>=0 && map[i*c+j]<10) printf(" %d   ", map[i*c+j]);
            else printf("%d   ", map[i*c+j]);
        }
        printf("\n");
    }
}
int find_char(char* map, int size, char c_to_be_found){
    //trova la posizione di un carattere specifico all'interno della mappa
    for (int i=0; i<size; i++) if (map[i]==c_to_be_found) return i;
}


/**
 *
 * 
 * la logica è questa. faccio copia del labirinto, come int*, a tutti i muri e i ! dò valore -1 e dò -2 ai $
 * (-1 e -2) solo per comodità, va bene qualsiasi numero segnaposto (negativo). 
 * dò valore 0 a tutte le celle vuote, e valore 1 alla cella di partenza e mi salvo su variabile esterna al ciclo il valore 1, chiamiamola ZYZZ.
 * Ora faccio un mega ciclo che controlla tutte le celle del labirinto. Ogni volta che trova una cella con valore corrispondente a ZYZZ, guarda se 
 * nelle sue vicinanze (NORD; SUD; EST; OVEST) c'è una cella con valore == 0 o con valore > ZYZZ. 
 * in questa cella viene messo il valore zyzz+1 e, alla fine del ciclo, zyzz viene +=1. 
 * il controllo finisce quando si arriva alla fine del ciclo che non ci sono più posti disponibili per mettere ulteriori zyzz.
 * Così facendo, quello che avviene è letteralmente un conteggio dei passi: utilizzando tutto il labirinto, quanti passi servono per arrivare al posto finale.
 * Il percorso più breve lo si trova facilmente, guardando, a partire dalla cella finale, le celle adiacenti che hanno il minor valore possibile.
 * Per esempio, se la cella finale ha ZYZZ=100, guardo in direzione E, O, S, N il più basso zyzz che trovo, e mi sposto in quella cella lì. Ovviamente, si arriverà a ZYZZ=1 nella cella iniziale.
 * 
 * Posso anche trattare, in realtà non in modo del tutto corretto, ma probabilistico, i $ e i !. Posso infatti dire che se trovo un dollaro, il prossimo zyzz è -10 invece di +1 (e in questo caso
 * devo cambiare anche zyzz globale) e se trovo un ! il prossimo zyzz sarà +5 (solo quello della cella).
 * 
*/

int main(){
    int r = 10, c = 7; //righe, colonne
    char map[] =  {'#','#','#','#','#','#','#',
                   'o',' ',' ',' ',' ',' ','#',
                   '#','#',' ','#','#',' ','#',
                   '#',' ',' ','#','#',' ','#',
                   '#',' ','#','#','#',' ','#',
                   '#',' ',' ','#','#',' ','#',
                   '#','#',' ','#','#',' ','#',
                   '#',' ',' ','#','#',' ','#',
                   '#',' ',' ',' ',' ',' ','_',
                   '#','#','#','#','#','#','#'};

    //ricavo le coordinate di inizio e fine
    int inizio = find_char(map, c*r, 'o');
    int fine = find_char(map, c*r, '_');
    int bonus = 0;
    int imprevisti = 0;
    
    stampa_char(map, r, c); //stampo il labirinto
   
   
    /**
     * creo copia del interi fatta da interi.
     * il muro ha valore -1,
     * lo spazio e la fine hanno valore 0, 
     * la o ha valore 1 (non servirebbe, ma risparmio un passaggio)
    */
    int* m =  (int*) calloc(c*r, sizeof(int));
    for (int i=0; i<c*r; i++) {
        if (map[i] == '#') m[i] = -1;
        else if (map[i] == ' ') m[i] = 0;
        else if (map[i] == '_') m[i] = 0;
        else m[i] = 1;
    }
    
    
    bool esplorazione = true; //continuo a controllare finché non finisco le caselle disponibili da esplorare
    int zyzz = 0; //numero di passi, variabile più importante dell'algoritmo

    while (esplorazione){
        zyzz++;
        for (int i=0; i<c*r; i++){
            //controllo tutte le posizioni che hanno zyzz attuale
            if (m[i]==zyzz){
                
                /**
                 * la prima parte dell'and controlla che si stia all'interno del campo, 
                 * la seconda controlla se ho uno spazio vuoto o un nodo che ho raggiunto con un'altra via più lunga.
                 * (si noti che questo caso ha senso controllarlo solo se ci sono modificatori di zyzz, tipo dollari)
                 * se le due condizioni soddisfatte, ci metto il zyzz successivo.
                */
                if ((i+1 < c*r) && ((m[i+1] > zyzz+1) || (m[i+1]==0))) m[i+1] = zyzz+1;
                if ((i+c < c*r) && ((m[i+c] > zyzz+1) || (m[i+c]==0))) m[i+c] = zyzz+1;
                if ((i-c > 0) && ((m[i-c] > zyzz+1) || (m[i-c]==0))) m[i-c] = zyzz+1;
                if ((i-1 > 0) && ((m[i-1] > zyzz+1) || (m[i-1]==0))) m[i-1] = zyzz+1;
            }
        }
        if (m[fine] == zyzz) esplorazione = false; //zyzz è sempre il numero di passi minore, per cui se arrivo alla fine, posso tranquillamente smettere di esplorare
        
        #ifdef DEBUG
        printf("\n");
        stampa_int(m, r, c);
        #endif
    }
   
    // Arrivo alla parte finale: path è la strada che devo fare.
    // so già che sarà lunga zyzz (passi) + la quantità di bonus e imprevisti presi, moltiplicati per quanto facevano cambiare zyzz.
    int* path = (int*) calloc(zyzz-5*imprevisti+5*bonus, sizeof(int));
    size_t pat_size = zyzz;

    //ovviamente, prima e ultima posizione del percorso saranno inizio e fine
    path[0] = inizio;
    path[pat_size-1] = fine;


    for (int i=pat_size-2; i>0; i--){
        int min = zyzz; //zyzz è sicuramente maggiore della cella adiacente col valore minore
        if (m[path[i+1]+1] < min && m[path[i+1]+1] > 0) {       
            /** chiarisco: i è l'indice attuale in path, che contiene la coordinata della cella dove devo andare.
             * di conseguenza, path[i+1] è la coordinata della cella dove mi trovo ora.
             * m[path[i+1]] è lo zyzz della cella dove sto ora. conseguentemente, m[path[i+1]+1] è lo zyzz della cella "sopra" a quella dove sto.
             * controllo quindi se è uno zyzz minore di quello dove sono (e in realtà degli altri disponibili, sto cercando il minimo).
            */
            min = m[path[i+1]+1];
            path[i] = path[i+1]+1;
        }
        if (m[path[i+1]+c]<min && m[path[i+1]+c]>0) {
            min = m[path[i+1]+c];
            path[i] = path[i+1]+c;
        }
        if (m[path[i+1]-c]<min && m[path[i+1]-c]>0) {
            min = m[path[i+1]-c];
            path[i] = path[i+1]-c;
        }
        if (m[path[i+1]-1]<min && m[path[i+1]-1]>0) {
            min = m[path[i+1]-1];
            path[i] = path[i+1]-1;
        }
    }
    printf("\n");
    for (int i=0; i<pat_size; i++) printf(" %d ", path[i]);
    printf("\n");

    char* direzioni = (char*) malloc(sizeof(char)*pat_size-1);
    for (int i=0; i<pat_size-1; i++){
        if (path[i+1]-path[i] == 1) direzioni[i] = 'E';
        else if (path[i+1]-path[i] == -1) direzioni[i] = 'W';
        else if (path[i+1]-path[i] == c) direzioni[i] = 'S';
        else direzioni[i] = 'N';
    }   
    printf("\n");
    for (int i=0; i<pat_size-1; i++)printf("%c ", direzioni[i]);
}