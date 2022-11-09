#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void ins_bonuses (int bonus, char* map, int columns){       //inserisce in modo casuale dei dollari (in realtà è casuale solo la prima volta perché manca i seed, poi saranno sempre nella stessa posizione)
    int i = 0, j = 0;                                   //coordinate dei futuri dollari
    while (i<bonus && j<bonus){                         //bonus è il numero di dollari che volgio inserire
        int x = (rand() % 13)+1;                        //posizione random per la riga
        int y = (rand() % 18)+1;                        // e per la colonna
        if (s[x][y] != '#') {                           //controllo che in quella posizoine non ci sia un muro
            s[x][y] = '$';                              //se è così, inserisco il dollaro
            j++;                                            
            i++;
        }
    }
}

void mod_ai (char* map, int rows, int columns){} // AI MODE LOGIC BLOCK

void mod_interactive(char* map, int rows, int columns){ // INTERACTIVE MODE LOGIC BLOCK
    
    char input_char = '0'; 
        //variabile che raccoglie il carattere in input
    int points = 100, qt_bonuses = 10, qt_taxes = 3, bonuses = 0, taxes = 0; 
        //punti del gioco, quantità di bonus e imprevisti nel gioco, quantità di bonus e imprevisti racccolti
    int position = columns;
        //prima colonna seconda riga = array[columns]
    _Bool game = 1;
        //sei nel gioco?

    ins_bonuses(qt_bonuses, map);
    ins_taxes(qt_taxes, map);
} 

int ask_mod(){} // ASKING MODE

