#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>

int find_char(char* map, int size, char c_to_be_found){
    //trova la posizione di un carattere specifico all'interno della mappa
    for (int i=0; i<size; i++) if (map[i]==c_to_be_found) return i;
}

bool stuck(char *map, int c, int position){
    //controllo se sono arrivato in un vicolo cieco
    if ((map[position+1] == '#' || map[position+1] == '+') &&
        (map[position+c] == '#' || map[position+c] == '+') &&
        (map[position-1] == '#' || map[position-1] == '+') &&
        (map[position-c] == '#' || map[position-c] == '+')) return true;
    else return false;
}
bool not_in(int* percorso, int position, size_t size){
    //controllo se sono già passato sull'attuale posizione
    //( => no loop infiniti )
    bool a = true;
    for (int i=0; i<size && a; i++) if (percorso[i] == position) a = false;
    return a;
}
int v_size(int* percorso) {
    // quanti passi ho fatto finora (l'array è enorme ed è a tutti 0, mi tengo solo la lunghezza utile con le cose dentro)
    bool fine = false;
    int i;
    for (i = 0; i<70 && !fine; ++i) if (percorso[i] == 0) fine = true;
    return i;
}
void stampa_piu(char* map, int r, int c, int* percorso, size_t s){
    //stampo il labirinto, compresi i più del percorso, senza però modificare la mappa
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            if (not_in(percorso, i*c+j, s)) printf("%c ", map[i*c+j]);
            else printf("+ ");
        }
        printf("\n");
    }
}

bool punto_valido(char* map, int position, int* percorso){
    //un punto è valido se non ci sono passato sopra prima e se non è un muro
    return map[position] != '#' && not_in(percorso, position, v_size(percorso));
}

void elimina_piu(int* percorso, int x){
    //quando torno indietro, elimino gli ultimi passi che ho fatto dall'array, sovrascrivendoli con zeri
    int s = v_size(percorso);
    for (int i = x+1; i<s; i++) percorso[i] = 0;
}

int numero_percorsi(char* map, int position, int fine, int c, int *percorso, int z){
    //funzione effettiva
    sleep(1);

    /********** DEBUG **********
     * stampa_piu(map, 10, c, percorso, v_size(percorso));
     * printf("position: %d\n", position);
     * printf("size vett: %d\n", v_size(percorso));
     * printf("i: %d\n", z);
     * printf("[ ");
     * for(int j=0; j<v_size(percorso); j++) printf(" %d ", percorso[j]); 
     * printf(" ]\n");
    *****************************/
    //Casi base
    if (position==fine) return 1;
    if (position != fine && stuck(map, c, position)) {
        return 0;
    }
    //passi induttivi
    if (punto_valido(map, position, percorso)){
        percorso[z] = position;
        int tot=0;
        int direzioni[] = {position+1, position+c, position-c, position-1};

        for (int i = 0; i<4; i++){
            //percorso[i] = position;
            tot += numero_percorsi(map, direzioni[i], fine, c, percorso, z+1);
            //for (int i=position+1; i<10*c; i++) if (map[i] == '+') map[i] = ' ';
            elimina_piu(percorso, z);
        }
        printf("percorsi trovati finora: %d\n", tot);
        return tot;
    }
    else return 0;
}

int main(){
    
    int default_rows = 10, default_columns = 6;
    char default_map[] =  {'#','#','#','#','#','#',
                           'o',' ','#',' ',' ','#',
                           '#',' ','#',' ',' ','#',
                           '#',' ','#',' ',' ','#',
                           '#',' ','#','#','#','#',
                           '#',' ',' ',' ',' ','#',
                           '#',' ','#',' ','#','#',
                           '#',' ','#',' ','#','#',
                           '#',' ',' ',' ',' ','_',
                           '#','#','#','#','#','#'};
    
    int* percorso = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');
    int percorsi_possibili = numero_percorsi(default_map, inizio, fine, default_columns, percorso, 0);
    printf("\n percorsi possibili: %d\n", percorsi_possibili);
    free(percorso);
    return 0;
    
}