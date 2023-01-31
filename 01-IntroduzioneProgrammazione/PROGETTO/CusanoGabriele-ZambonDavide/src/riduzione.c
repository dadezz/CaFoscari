/**
 * @file riduzione.c
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section FUNZIONI DI RIDUZIONE
 * Il labirinto viene ridotto di dimensioni tramite euristiche, per esempio
 * riempiendo di muri i vicoli ciechi o i passaggi di lunghezza maggiore di 2
 * viene tenuto conto in parte della funzione del trapano, infatti esistono 3 tipologie di muri:
 *      '3', '#', '@'
 * il primo è un muro attraversabile in presenza del trapano, ma che non toglie trapani disponibili
 * il secondo è un muro normale, 
 * il terzo è un muro in nessun caso attraversabile.
 * 
 * A seconda della situazione, viene assegnata alla cella un tipo differente di muro.
*/
#ifndef  _HEADERS_
#define  _HEADERS_
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include"types.h"
#endif // _HEADERS_

#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "func.h"
#endif //_FUNCTIONS_


position_t trapano;

bool mappe_diverse(board_t map1, board_t map2){
    /**
     * controlla semplicemente se le due mappe sono uguali tra loro, cella per cella
    */
    for (int i = 0; i<map1.col*map2.row; i++){
        if (map1.map[i] != map2.map[i]){
            return true;
        }
    }
    return false;
}

bool muro(board_t map, int p){
    /**
     * al posto di fare ogni volta l'if con i 2 OR, basta chiamare questa funzione, 
     * che ritorna true se la cella in questione è un qualche tipo di muro (#, 3, @)
     * @param p: posizione da controllare
    */
    if (map.map[p] == '#' || map.map[p] == '3' || map.map[p] == '@')
        return true;
    else return false;
}

bool vicolo_cieco (board_t map, int i){
    /**
     * se una data posizione è circondata da muri, tranne che da un solo lato, allora questa è un vicolo cieco, e si può
     * tranquillamente evitare di prendere in considerazione nell'esploraizione.
     * la funzione ritorna proprio questo:
     * @return true se è un vicolo cieco, false altrimenti
     * @param i: posizione da controllare
    */
    if (muro(map, i+1) && muro(map, i+map.col) && muro(map, i-1) && !muro(map, i-map.col) ||
        muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && muro(map, i-map.col) ||
        muro(map, i+1) && !muro(map, i+map.col) && muro(map, i-1) && muro(map, i-map.col) ||
        !muro(map, i+1) && muro(map, i+map.col) && muro(map, i-1) && muro(map, i-map.col)){
        return true;
    }
    else return false;
}

bool angolo_libero(board_t map, int i){
    /**
     * Angolo libero:
     * #####            #####
     *     #   diventa     3# perché non ha senso esplorare quella cella
     *     #                #
     * @param i: posizione da controllare
    */
    if ( (muro(map, i+1) && muro(map, i-map.col) && !muro(map, i-1) && !muro(map, i+map.col) && !muro(map, i+map.col-1)) ||
         (muro(map, i-1) && muro(map, i-map.col) && !muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i+map.col+1)) ||
         (muro(map, i-1) && muro(map, i+map.col) && !muro(map, i+1) && !muro(map, i-map.col) && !muro(map, i-map.col+1)) ||
         (muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && !muro(map, i-map.col-1))   ){
            return true;
         }
    else return false;
}

bool doppia_fila(board_t map, int i){
    /**
     * elimina una fila di celle vuote nel caso ce ne siano di adiacenti (corridoi a due celle di larghezza, diventano corridoi a una cella)
     * @param i: posizione da controllare
    */
    if (muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && muro(map, i+1+map.col) && !muro(map, i+map.col-1) && !muro(map, i-1-map.col) && muro(map, i-map.col+1) ||
        !muro(map, i+1) && !muro(map, i+map.col) && !muro(map, i-1) && muro(map, i-map.col) && !muro(map, i+1+map.col) && !muro(map, i+map.col-1) && muro(map, i-1-map.col) && muro(map, i-map.col+1) ||
        !muro(map, i+1) && !muro(map, i+map.col) && muro(map, i-1) && !muro(map, i-map.col) && !muro(map, i+1+map.col) && muro(map, i+map.col-1) && muro(map, i-1-map.col) && !muro(map, i-map.col+1) ||
        !muro(map, i+1) && muro(map, i+map.col) && !muro(map, i-1) && !muro(map, i-map.col) && muro(map, i+1+map.col) && muro(map, i+map.col-1) && !muro(map, i-1-map.col) && !muro(map, i-map.col+1) ){
        return true;
    }
    else return false;
}

bool muraglia(board_t map, int i){
    /**
     * se un muro in posizione i è circondato da altri muri, definisco che è in una muragia, e ritorno true
     * @param i: posizione da controllare
    */
    if (muro(map, i+1) && 
        muro(map, i-1) && 
        muro(map, i+map.col) && 
        muro(map, i-map.col)
        ){
            return true;
    }
    else return false;
}

bool adiacente_chiocciola_tre(board_t map, int i){
    /**
     * se un muro è adiacente a una chiocciola, e la chiocciola ha muri attorno, ritorno true
     *   #
     *  3@ 
     *   #
    */
    if (map.map[i+1] == '@' && muro(map, i+map.col+1) && !muro(map, i-1) && muro(map, i-map.col+1) ||
        muro(map, i+1+map.col) && map.map[i+map.col] == '@' && muro(map, i-1-map.col) && !muro(map, i-map.col) ||
        !muro(map, i+1) && muro(map, i+map.col-1) &&map.map[i-1] == '@' && muro(map, i-map.col-1) ||
        muro(map, i+1-map.col) && !muro(map, i+map.col) && muro(map, i-map.col-1) && map.map[i-map.col] == '@'){
        return true;
    }
    else return false;
}

bool adiacente_chiocciola_muro(board_t map, int i){
    /**
     * se un muro è adiacente a una chiocciola, e la chiocciola ha muri attorno, ritorno true
     *   #
     *  #@ 
     *   #
    */
    if (map.map[i+1] == '@' && muro(map, i+map.col) && !muro(map, i-1) && muro(map, i-map.col) ||
        muro(map, i+1) && map.map[i+map.col] == '@' && muro(map, i-1) && !muro(map, i-map.col) ||
        !muro(map, i+1) && muro(map, i+map.col) &&map.map[i-1] == '@' && muro(map, i-map.col) ||
        muro(map, i+1) && !muro(map, i+map.col) && muro(map, i-1) && map.map[i-map.col] == '@'){
        return true;
    }
    else return false;
}

void isola_oggetti(board_t map){
    /**
     * funzione che mi serve per lasciare camminabili le celle adiacenti agli oggetti speciali, 
     * perché possono servirmi per raggiungerli ($, T) o evitarli (!)
    */
    if (trapano.col == -1){
        //se non sono presenti trapani:
        for (int i=0; i<map.col*map.row; i++){
            //per ogni cella del labirinto:
            if (map.map[i] != '#' && map.map[i] != ' ' && map.map[i] != '2'){
                //se essa è un oggetto speciale, preservo gli spazi tutto intorno a lei mettendoci dei due 
                //(perché le riduzioni intaccano gli spazi, non altri caratteri, è un modo per evitare che vengano considerati)
                if(map.map[i+1] == ' ') map.map[i+1] = '2';
                if(map.map[i+map.col] == ' ') map.map[i+map.col] = '2';
                if(map.map[i+1+map.col] == ' ') map.map[i+1+map.col] = '2';
                if(map.map[i+map.col-1] == ' ') map.map[i+map.col-1] = '2';
                if(map.map[i-1] == ' ') map.map[i-1] = '2';
                if(map.map[i-map.col] == ' ') map.map[i-map.col] = '2';
                if(map.map[i-1-map.col] == ' ') map.map[i-1-map.col] = '2';
                if(map.map[i-map.col+1] == ' ') map.map[i-map.col+1] = '2';
            }
        }
    }
    else {
        //se invece ci sono i trapani,
        for (int i=0; i<map.col*map.row; i++){
            //per ogni cella del labirinto:
            if (i< trapano.row*map.col+trapano.col){
                //se mi trovo in una cella precedente a quella del trapano (euristica non del tutto corretta per via del flattening)
                //do per buono di non aver ancora raccolto il trapano, quindi lascio intatte anche le celle diagonali
                if (map.map[i] != '#' && map.map[i] != ' ' && map.map[i] != '2'){
                    if(map.map[i+1] == ' ') map.map[i+1] = '2';
                    if(map.map[i+map.col] == ' ') map.map[i+map.col] = '2';
                    if(map.map[i+1+map.col] == ' ') map.map[i+1+map.col] = '2';
                    if(map.map[i+map.col-1] == ' ') map.map[i+map.col-1] = '2';
                    if(map.map[i-1] == ' ') map.map[i-1] = '2';
                    if(map.map[i-map.col] == ' ') map.map[i-map.col] = '2';
                    if(map.map[i-1-map.col] == ' ') map.map[i-1-map.col] = '2';
                    if(map.map[i-map.col+1] == ' ') map.map[i-map.col+1] = '2';
                }
            }
            else {
                //altrimenti lascio intatte solo quelle adiacenti per lato
                if (map.map[i] != '#' && map.map[i] != ' ' && map.map[i] != '2'){
                    if(map.map[i+1] == ' ') map.map[i+1] = '2';
                    if(map.map[i+map.col] == ' ') map.map[i+map.col] = '2';
                    if(map.map[i-1] == ' ') map.map[i-1] = '2';
                    if(map.map[i-map.col] == ' ') map.map[i-map.col] = '2';
                }
            }
        }
    }
}

void riduci(board_t map){
    /**
     * Se trovo degli angoli liberi o delle doppie file, li rendo muri.
     * Uso dei '3': mi serve differenziarli dai muri normali perché il passaggio non toglie "trapani",
     * ma è comunque vietato nel caso in cui non ci siano trapani disponibili.
     * 
     * Angolo libero:
     * #####            #####
     *     #   diventa     3# perché non ha senso esplorare quella cella
     *     #                #
     * 
     * Doppia fila:
     * ####             ####
     *    #               3#
     * #  #  diventa    # 3#  perché non ha senso esplorare il percorso parallelo
     * #  #             # 3#
    */
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if (angolo_libero(map, i)) {
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if (doppia_fila(map,i)) { 
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
    }
}

void elimina_vicoli_ciechi(board_t map){
    /**
     * controlla ripetutamente la mappa finché vede la presenza di vicoli ciechi, e li elimina.
     * il controllo di cosa è un vicolo cieco è demandato alla funzione apposita
    */
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = map.col; i < (map.col*map.row-map.col); i++){
            if(map.map[i] == ' '){
                if(vicolo_cieco(map, i)){
                    map.map[i] = '3';
                    trovato = true;
                }
            }
        }
    }
}

void elimina_orfani(board_t map){
    /**
     * controlla ogni cella della mappa.
     * se trova celle calpestabili non raggiungibili (circondate da muri) le sostituisce con un 3
    */
    for (int i=0; i<map.col*map.row; i++){
        if (map.map[i] == ' '){
            if (muro(map, i+1) && muro(map, i+map.col) && muro(map, i-1) && muro(map, i-map.col))
                map.map[i] = '3';
        }
    }
}

void rimetti_spazi(board_t map){
    /**
     * sostituisce i 2 con gli spazi, per poi ritornare la mappa ridotta e pronta per essere data in pasto alla ricorsione
    */
    for (int i = 0; i<map.row*map.col; i++){
        if (map.map[i] == '2') map.map[i] = ' ';
    }
}

void elimina_tre_inutili(board_t map){
    /**
     * elimina '3' e muri che sono adiacenti a chiocciole, e in quanto tali con molta probabilità possono diventare chiocciole anche quelli.
     * un muro cosi fatto:
     * 
     *   #
     *  3@ 
     *   #
     * 
     * nel 90% dei casi, non ha senso attraversarlo (sono euristiche, non certezze matematiche)
     * si potrebbe pensare che invece sia necessario attraversarlo per evitare di aggirarlo, ma ancora, nel 90% dei casi,
     * per via di quali sono le altre euristiche, una situazione del genere non si viene a formare. 
     * in alcuni casi sì, servirebbe, ma sono statisticamente minoritari
    */
    bool trovato = true;
    while(trovato){
        trovato = false;
        for (int i = 0; i < (map.col*map.row); i++){
            if(map.map[i] == '#'){
                if (i<map.col || i>map.row*map.col-map.col || i%map.col == 0 || i%map.col == map.col-1){
                    map.map[i] = '@';
                    trovato = true;
                }
                if(muraglia(map, i) || adiacente_chiocciola_muro(map, i)){
                    map.map[i] = '@';
                    trovato = true;
                }
            }
            else if(map.map[i] == '3'){
                if(muraglia(map, i) || adiacente_chiocciola_tre(map, i)){
                    map.map[i] = '@';
                    trovato = true;
                }
            }
        }
    }
}

void riduzione(board_t map){
    /**
     * piccolo metodo che, attraverso euristiche, riduce la quantità di posti da esplorare per trovare il percorso migliore
     * (se c'è un canale di larghezza due, lo mette di larghezza uno, se c'è un vicolo cieco, lo riempie di muri etc.)
     * 
     * un muro # è attraversabile solo se si possiede il trapano, e si perde un utilizzo quando lo si supera
     * un muro 3 è attraversabile solo se si possiede il trapano, ma non se ne perde l'utilizzo
     * un muro @ non è mai attraversabile.
    */
    trapano = find_char(&map, 'T'); //mi serve per discriminare il comportamento di "isola oggetti"
    
    isola_oggetti(map); //lascio libertà di movimento attorno a tutte le celle speciali ($, !, T)
    board_t copia_map = copia_mappa(&map); //mi serve una copia della mappa per continuare a ridurre finché non ci sono più possibilità di riduzione
    do {
        for(int i=0; i<copia_map.row*copia_map.col; i++){
            copia_map.map[i] = map.map[i];
        }
        riduci(map); //tolgo doppie file e angoli liberi
        elimina_vicoli_ciechi(map); //elimino i vicoli ciechi riempiendoli di muri
        elimina_orfani(map);    //elimino gli spazi circondati da muri
    } while(mappe_diverse(map, copia_map)); //finché trovo ancora di queste situazioni
    free(copia_map.map);
    elimina_tre_inutili(map); //se posso, tutti i 3 e i muri che non serve attraversare, li faccio diventare chiocciole.
    rimetti_spazi(map); //rimetto gli spazi per far funzionare la ricorsione
}