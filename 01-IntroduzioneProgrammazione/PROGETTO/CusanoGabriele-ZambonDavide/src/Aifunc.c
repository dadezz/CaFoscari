/**
 * @file Aifunc.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section IA
 * Il computer, nel limite massimo di un minuto, deve trovare il percorso migliore (o quello che
 * più gli si avvicina). Sono stati implementati 2 algoritmi:
 * (1) “numeretti”: A partire dalla cella iniziale, a cui si dà
 * valore 1, si assegna valore 2 alle celle vuote adiacenti, e così via, ogni volta si incrementa di uno.
 * Così facendo, si arriva alla fine col numero di passi minore in assoluto, ma non vengono
 * prese in considerazione le celle speciali. 
 * (2) funzione ricorsiva: ad ogni passo esplora tutti i possibili percorsi nelle quattro direzioni,
 * calcolando per ognuno il punteggio e restituendo il migliore. 
 * 
 * Il problema dell'efficienza computativa della (2) viene mitigato in 2 modi:
 * (1) riduzione: La mappa viene modificata tramite euristiche 
 * (quali per esempio riempire di muri i vicoli ciechi opassaggi di larghezza maggiore di 1) 
 * che intaccano solo il funzionamento del trapano e solo in piccola parte, dando quindi un enorme vantaggio 
 * a fronte di una penalizzazione statisticamente bassa sul punteggio finale. 
 * (2) Troncamento: Al raggiungimento del minuto, viene restituito il percorso migliore finora trovato. 
*/
#ifndef _HEADERS_
#define _HEADERS_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include"types.h"
#endif //_HEADERS_

#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "func.h"
#endif //_FUNCTIONS_

//#define DEBUG

time_t start; //tempo di clock al momento della partenza
time_t end; //tempo di clocl al momento attuale
double cpu_time_used;   //end-start / clock_per_sec
int p_max;  //variabil che tiene conto del mgkior punteggio finora trovato

/**
 * primo dei due metodi per la risoluzione IA
 * @param map labirinto
 * @param path puntatore al path su cui salvare il percors trovato
 * @param inizio posizione di inizio
 * @param fine posizione di fine
*/
void numeretti(board_t *map, vector_t *path, position_t inizio, position_t fine){
    
    //creo copia di interi del labirinto 
    int* m =  (int*) calloc(map->col * map->row, sizeof(int));
    for (int i=0; i<map->col*map->row; i++) {
        if (map->map[i] == '#') m[i] = -1;
        else if (map->map[i] == 'o') m[i] = 1;
        else m[i] = 0;
    }

    bool esplorazione = true; //continuo a controllare finché non finisco le caselle disponibili da esplorare
    int zyzz = 0; //numero di passi, variabile più importante dell'algoritmo
    while (esplorazione){
        zyzz++;
        for (int i=0; i<map->col * map->row; i++){
            //controllo tutte le posizioni che hanno zyzz attuale
            if (m[i]==zyzz){
                /**
                 * la prima parte dell'and controlla che si stia all'interno del campo, 
                 * la seconda controlla se ho uno spazio vuoto o un nodo che ho raggiunto con un'altra via più lunga.
                 * (si noti che questo caso ha senso controllarlo solo se ci sono modificatori di zyzz, tipo dollari)
                 * se le due condizioni soddisfatte, ci metto il zyzz successivo.
                */
                if ((i+1 < map->col*map->row) && (m[i+1]==0)) m[i+1] = zyzz+1;
                if ((i+map->col < map->col*map->row) && (m[i+map->col]==0)) m[i+map->col] = zyzz+1;
                if ((i-map->col > 0) && (m[i-map->col]==0)) m[i-map->col] = zyzz+1;
                if ((i-1 > 0) && (m[i-1]==0)) m[i-1] = zyzz+1;
            }
        }
        if (m[fine.col +  fine.row*map->col] == zyzz) esplorazione = false; //zyzz è sempre il numero di passi minore, per cui se arrivo alla fine, posso tranquillamente smettere di esplorare
    }
    
    // Arrivo alla parte finale: path è la strada che devo fare.
    // so già che sarà lunga zyzz (passi)
    path->size = zyzz;
    //ovviamente, prima e ultima posizione del percorso saranno inizio e fine
    path->data[0] = inizio.col + inizio.row*map->col;
    path->data[path->size-1] = fine.col +  fine.row*map->col;

    
    //ora vado a ritroso sempre verso il numero minore e fillo path->
    for (int i=path->size-2; i>0; i--){
        int min = zyzz; //zyzz è sicuramente maggiore della cella adiacente col valore minore
        if (m[path->data[i+1]+1] < min && m[path->data[i+1]+1] > 0) {       
            /** chiarisco: i è l'indice attuale in path, che contiene la coordinata della cella dove devo andare.
             * di conseguenza, path[i+1] è la coordinata della cella dove mi trovo ora.
             * m[path[i+1]] è lo zyzz della cella dove sto ora. conseguentemente, m[path[i+1]+1] è lo zyzz della cella "sopra" a quella dove sto.
             * controllo quindi se è uno zyzz minore di quello dove sono (e in realtà degli altri disponibili, sto cercando il minimo).
            */
            min = m[path->data[i+1]+1];
            path->data[i] = path->data[i+1]+1;
        }
        if (m[path->data[i+1]+map->col]<min && m[path->data[i+1]+map->col]>0) {
            min = m[path->data[i+1]+map->col];
            path->data[i] = path->data[i+1]+map->col;
        }
        if (m[path->data[i+1]-map->col]<min && m[path->data[i+1]-map->col]>0) {
            min = m[path->data[i+1]-map->col];
            path->data[i] = path->data[i+1]-map->col;
        }
        if (m[path->data[i+1]-1]<min && m[path->data[i+1]-1]>0) {
            min = m[path->data[i+1]-1];
            path->data[i] = path->data[i+1]-1;
        }
    }
    int bonus = 0;
    for(int i=0; i<path->size; i++){
        if(map->map[path->data[i]] == '$') bonus++;
        if(map->map[path->data[i]] == '!') bonus = bonus/2;
    }
    p_max = 1+1000-path->size+10*bonus; // il +1 iniziale è dovuto al fatto che nel path ci sono sia inizio che fine (la size è 1 in più)

    printf("*******     SOLUZIONE TROVATA!      *******\n\n");
    printf("Un possibile percorso è questo:\n");
    stampa_direzioni(*path, *map);
    printf("\nil punteggio che si ottiene è: %d\n\n", p_max);
    stampa_piu(*map, *path);
    printf("\nOra vedo di calcolarne un altro che abbia un punteggio migliore,\nci vorrà un minuto al massimo\n\n\n");
}

/**
 * max element in a vector
 * @return il valore più alto contenuto in un vettore (non l'indice)
*/
int max(vector_t x){
    int max = x.data[0];
    for (int i=1; i<x.size; i++) if (x.data[i]>max) max=x.data[i];
    return max;
}

/**
 * un punto è valido se non ci sono passato sopra prima e se non è un muro
 * @return true se il punto è valido
 * @param map labirinto
 * @param p posizione che voglio controllare 
 * @param percorso lista delle posizioni già controllate
 * @param T numero di trapani disponibili (se > 0, un muro è punto valido)
*/
bool punto_valido(board_t map, position_t p, vector_t percorso, int T){    
    if (T==0) return map.map[p.row*map.col + p.col] != '#' && map.map[p.row*map.col + p.col] != '@' && map.map[p.row*map.col + p.col] != '3' && not_in(percorso, p, map);
    else return map.map[p.row*map.col + p.col] != '@' && not_in(percorso, p, map);
}

/**
 * quando torno indietro, elimino gli ultimi passi che ho fatto dall'array, sovrascrivendoli con zeri
 * @param percorso lista delle posizioni
 * @param x indice da cui iniziare a eliminare i passi
*/
void elimina_passi(vector_t *percorso, int x){
    for (int i = x+1; i<percorso->size; i++) {
        percorso->data[i] = 0;
    }
}

/**
 * cambio il punteggio_max ogni e aggiorno path ogni volta che trovo un 
 * percorso migliore del migliore precedentemente trovato
 * @param punteggio nuovo punteggio
 * @param path percorso migliore da aggiornare
 * @param percorso percorso appena trovato
*/
void scambia_punteggio_max(int punteggio, vector_t *path, vector_t *percorso){
    if (punteggio > p_max){
        p_max = punteggio;
        path->size = percorso->size;
        for (int i = 0; i<percorso->size; i++) {
            path->data[i] = percorso->data[i];
        }
    }
}

/**
 * funzione ricorsiva
 * @param map labirinto di gioco ridotto
 * @param percorso array per memorizzare tutti i percorsi di esplorazione
 * @param path array per memorizzare il percorso migliore
 * @param position la posizione da cui faccio partire l'esplorazione a ogni chiamata
 * @param fine posizione di fine ricorsione, caso base
 * @param contatore conta i passi effettuati 
 * @param bonus contatore $
 * @param T contatore T
 * @param map_orig labirinto di gioco senza riduzione
*/
int best_percorso(board_t map, vector_t *percorso, vector_t *path, position_t position, position_t fine, int contatore, int bonus, int T, board_t *map_orig){
    #ifdef DEBUG
    stampa_piu(map, *percorso);
    sleep(1);
    printf("\npercorso: \n");
    for (int i=0; i<percorso->size; i++){
        printf("%d ", percorso->data[i]);
    }
    printf("\n");
    printf("\npath: \n");
    for (int i=0; i<path->size; i++){
        printf("%d ", path->data[i]);
    }
    printf("\n");
    #endif
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        //caso base: è passato troppo tempo
    if (cpu_time_used > 59) {
        //libero percorso, non mi serve più
        //printf("\nSto elaborando . . .\n");
        free(percorso->data);
        free(percorso);

        //calcolo la lunghezza effettiva del path e realloco di conseguenza
        size_t size = 0;
        for (int j=0; j<path->size; j++) {
            size++;
            if (path->data[j] == 0) break;
        }
        path->size = size;
        path->data[size-1] = fine.col + fine.row*map.col;
        path->data = realloc(path->data, path->size*sizeof(int));
        if (path->data == NULL) errore ();

        //stampo le posizioni
        printf("*******     SOLUZIONE TROVATA!      *******\n\n");
        printf("\nHo trovato quest'altro percorso:\n");
        stampa_direzioni(*path, map); // stampo i movimenti che ho fatto (nord, sud, etc)

        //stampo il labirinto
        printf("\n");
        stampa_piu(*map_orig, *path);
        printf("il punteggio a esso relativo è pari a %d\n", p_max);
        printf("Grazie di aver giocato ;)\n");
        //libero il resto
        free(path->data);
        free(path);
        free(map.map);
        free(map_orig->map);
        free(map_orig);
        exit(EXIT_SUCCESS);
    }

    //Caso base: sono arrivato alla fine
    if (position.col == fine.col && position.row == fine.row) return 1000-contatore+10*bonus;
    //Caso base: sto facendo troppi passi
    if (contatore > map.row*map.col/2) return 0;

    if (punto_valido(map, position, *percorso, T)){
        //aggiorno il conteggio delle celle speciali, nel caso ci sia capitato sopra
        if (map.map[position.row*map.col + position.col] == '$') bonus++;
        if (map.map[position.row*map.col + position.col] == '!') bonus = bonus/2;
        if (map.map[position.row*map.col + position.col] == 'T') T+=3;
        if (map.map[position.row*map.col + position.col] == '#') T-=1;
        //scrivo la posizione in cui sono nel percorso
        percorso->data[contatore] = position.row*map.col + position.col;
        //vettore che prende i risultati dei percorsi trovati nelle 4 direzioni
        vector_t punteggi;
        punteggi.size = 4;
        punteggi.data = calloc(sizeof(int), punteggi.size);
        
        /**
         * punteggi.data:
         * indice 0: vado a destra (col+1)
         * indice 1: vado giu (riga+1)
         * indice 2: vado a sinistra(col-1)
         * indice 3: vado su (riga-1)
         * 
         * il metodo è lo stesso, commento uno solo dei 4 indici
        */
        if (++position.col >= map.col || !punto_valido(map, position, *percorso, T)) punteggi.data[0] = 0; 
            //se la posizione è fuori dai muri o non è un punto valido (muro, anche a seconda della presenza o meno dei trapani)
        else punteggi.data[0] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, map_orig);
            //chiamo la ricorsione in direzione destra. notare che la posizione è già aggiornata(++posizione.col). 
            //aumento di uno il contatore di passi effettuati
        position.col--;
            //riporto a com'era la posizione
        scambia_punteggio_max(punteggi.data[0], path, percorso);
            //se il punteggio che ho trovato risulta migliore del punteggio trovato finora, scambio p_max e path
        elimina_passi(percorso, contatore);
            //elimino da percorso gli ultimi passi che ho fatto (così da poterli sovrascrivere con gli altri percorsi successivi)

        if (++position.row >= map.row || !punto_valido(map, position, *percorso, T)) punteggi.data[1] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, map_orig);
        position.row--;
        scambia_punteggio_max(punteggi.data[1], path, percorso);
        elimina_passi(percorso, contatore);

        if (--position.col < 0 || !punto_valido(map, position, *percorso, T)) punteggi.data[2] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, map_orig);
        position.col++;
        scambia_punteggio_max(punteggi.data[2], path, percorso);
        elimina_passi(percorso, contatore);

        if (--position.row < 0 ||!punto_valido(map, position, *percorso, T)) punteggi.data[3] = 0;
        else punteggi.data[1] = best_percorso(map, percorso, path, position, fine, contatore+1, bonus, T, map_orig);
        position.row++;
        scambia_punteggio_max(punteggi.data[3], path, percorso);
        elimina_passi(percorso, contatore);

        int a = max(punteggi);
        free(punteggi.data);
        return a; //ritorno il punteggio massimo tra i 4 percorsi trovati
    }
    else return 0;
}

/**
 * funzione che sviluppa il gioco la modalità IA
 * @param grid mappa su cui si vuol giocare
*/
void mod_ai (board_t *map){
    /**
     * MODALITÀ AI :
     * faccio partire un cronometro.
     * per prima cosa faccio partire un cronometro.
     * Trovo in modo sufficientemente veloce un percorso buono, non per forza il migliore, ma comunque una valida alternativa.
     * Lo faccio col metodo dei numeretti, la cui logica è questa:
     * 
     * faccio copia del labirinto, come int*, a tutti i muri e i ! dò valore -1 e dò -2 ai $
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
     * poi, per tre minuti al massimo (motivo del cronometro), faccio partire la ricorsione, che usa una mappa ridotta con euristiche
     * (quali caselle ha poco senso includere nei possibili percorsi), per vedere se in quel lasso di tempo trova un candidato
     * migliore come percorso col miglior punteggio. 
     * Alla fine il path prescelto è quello col punteggio minore.
    */
    printf("Activity started ;)\n");
    start = clock();

    //trovo inizio e fine. se fallisco, libero memoria allocata e esco dal programma
    position_t inizio = find_char(map, 'o');
    position_t fine = find_char(map, '_');
    if (inizio.col == -1 || fine.col == -1) {
        free(map->map);
        printf("inizio o fine non trovati\n");
        exit(EXIT_FAILURE);
    }

    //path è l'array con il percorso definitivo.
    //quando viene trovato un percorso con punteggio maggiore del 
    //precedente, path assume i valori di percorso corrispondente
    vector_t *path;
    path = malloc(sizeof(vector_t));
    path->size = map->row * map->col; //massima lunghezza possibile
    path->data = (int*)calloc(path->size, sizeof(int));
    if (path->data == NULL) errore ();
    
    /**
     * CHIAMATA FUNZIONE "NUMERETTI"
    */
    numeretti(map, path, inizio, fine);
    //ora path è aggiornato.

    /**
     * DA QUI IN POI LA PARTE DI RICORSIONE
    */
    //percorso è l'array con tutte le coordinate del percorso tentato per ogni albero
    //(quindi cambia a ogni chiamata di funzione ricorsiva)
    vector_t *percorso;
    percorso = malloc(sizeof(vector_t));
    percorso->size = map->row * map->col; //massima lunghezza possibile
    percorso->data = (int*)calloc(percorso->size, sizeof(int));
    if (!percorso->data) errore ();

    board_t nuova_map = copia_mappa(map); //vado a lavorare con le euristiche su una copia della mappa 
        //(stavolta non è puntatore perché avevo già le funzioni pronte su struct normali)
    for (int i=0; i<map->row*map->col; i++){
        nuova_map.map[i] = map->map[i];
    }
    riduzione(nuova_map);    //applico un po' di euristiche per ridurmi i possibili percorsi da controllare ricorsivamente



    //chiamata di funzione
    best_percorso(nuova_map, percorso, path, inizio, fine, 0, 0, 0, map);

    //libero percorso, non mi serve più
    free(percorso->data);
    free(percorso);

    //calcolo la lunghezza effettiva del path e realloco di conseguenza
    size_t size = 0;
    for (int j=0; j<path->size; j++) {
        size++;
        if (path->data[j] == 0) break;
    }
    path->size = size;
    path->data[size-1] = fine.col + fine.row*map->col;
    path->data = realloc(path->data, path->size*sizeof(int));
    if (path->data == NULL) errore ();

    //stampo le posizioni
    printf("*******     SOLUZIONE TROVATA!      *******\n\n");
    printf("\nHo trovato quest'altro percorso:\n");
    stampa_direzioni(*path, *map); // stampo i movimenti che ho fatto (nord, sud, etc)

    //stampo il labirinto
    printf("\n");
    stampa_piu(*map, *path);
    printf("il punteggio a esso relativo è pari a %d\n", p_max);
    printf("Grazie di aver giocato ;)\n");

    //libero il resto
    free(path->data);
    free(path);
    free(map->map);
    //free(map);
}

