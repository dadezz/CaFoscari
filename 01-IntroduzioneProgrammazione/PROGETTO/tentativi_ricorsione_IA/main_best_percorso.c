#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>
int last_index(int *x){
    return v_size(x)-1;
}
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
    return i-1;
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

bool punto_valido(char* map, int position, int* percorso, int T, int c){
    //un punto è valido se non ci sono passato sopra prima e se non è un muro
    if (position<0 || position > 60) return false;
    if (position-percorso[last_index(percorso)] == 1) if (position%c == 0) return false;//verso destra
    else if (position-percorso[last_index(percorso)] == c) {
        printf("eh ghe sboro");
        if (position > 10*c) return false; //verso giu
    }
    else if (position-percorso[last_index(percorso)] == -1) if (position%c == c-1) return false; //verso sx
    else if (position-percorso[last_index(percorso)] == -c) if (position < 0) return false; //verso su

    if (T==0) return map[position] != '#' && not_in(percorso, position, v_size(percorso));
    else return not_in(percorso, position, v_size(percorso));
}

void elimina_piu(int* percorso, int x){
    //quando torno indietro, elimino gli ultimi passi che ho fatto dall'array, sovrascrivendoli con zeri
    int s = v_size(percorso);
    for (int i = x+1; i<s; i++) percorso[i] = 0;
}

int max(int *x){
    int max = x[0];
    for (int i=1; i<4; i++) if (x[i]>max) max=x[i];
    return max;
}

int max_p = 0;
int numero_percorsi(char* map, int position, int fine, int c, int *percorso, int z, int S, int T, int *path, int *pathh){
    //funzione effettiva
    //sleep(1);
    stampa_piu(map, 10, c, percorso, v_size(percorso));
    printf("position: %d\n", position);
    printf("max: %d ", max_p);
    printf("[ ");
    for(int j=0; j<v_size(pathh); j++) printf(" %d ", pathh[j]); 
    printf(" ]\n");
    printf("size vett: %d\n", v_size(percorso));
    printf("i: %d\n", z);
    printf("[ ");
    for(int j=0; j<v_size(percorso); j++) printf(" %d ", percorso[j]); 
    printf(" ]\n");
    printf("numero bonus: %d\n", S);

    //Casi base
    if (position==fine) return 1000-z+10*S;
    if (position != fine && stuck(map, c, position)) {
        return 0;
    }
    //passi induttivi
    if (punto_valido(map, position, percorso, T, c)){
        if (map[position] == '$') S++;
        if (map[position] == '!') S = S/2;
        if (map[position] == 'T') T+=3;
        if (map[position] == '#') T-=1;
        percorso[z] = position;
        int direzioni[] = {position+1, position+c, position-c, position-1};
        int punteggi[4];

        for (int i = 0; i<4; i++){
            punteggi[i] = numero_percorsi(map, direzioni[i], fine, c, percorso, z+1, S, T, path+1, pathh);
            if (punteggi[i]>max_p){
                printf("\n SONO DENTRO L'IF. punteggi[i]: %d, max_p: %d", punteggi[i], max_p);
                max_p = punteggi[i];
                for (int i = 0; i<v_size(percorso); i++) pathh[i] = percorso[i];
            }
            elimina_piu(percorso, z);
        }
        for (int i=0; i<4; i++) printf("punteggio %d: %d\n", i, punteggi[i]);
        int a = max(punteggi);

        printf("massimo dei punteggi: %d", a);

        return a;
    }
    else return 0;
}

int main(){
    
    int default_rows = 10, default_columns = 6, size = 0;
    char default_map[] =  {'#','#','#','#','#','#',
                           'o',' ','#',' ',' ','#',
                           '#',' ','#',' ',' ','#',
                           '#','$','#',' ',' ','#',
                           '#',' ','#','#','#','#',
                           '#','T','!',' ',' ','#',
                           '#','#','#',' ','#','#',
                           '#',' ','#',' ','#','#',
                           '#',' ','$',' ',' ','_',
                           '#','#','#','#','#','#'};
    
    int* percorso = (int*)calloc(default_columns*default_rows, sizeof(int));
    int* path = (int*) calloc(default_columns*default_rows, sizeof(int));
    int* pathh = (int*) calloc(default_columns*default_rows, sizeof(int));
    int inizio = find_char(default_map, default_columns*default_rows, 'o');
    int fine = find_char(default_map, default_columns*default_rows, '_');
    //int max = 0;
    int percorsi_possibili = numero_percorsi(default_map, inizio, fine, default_columns, percorso, 0, 0, 0, path, pathh);
    printf("\n percorsi possibili: %d\n", percorsi_possibili);
    bool f = false;
    for (int j=0; j<default_columns*default_rows && !f; j++){
        if (pathh[j] == fine || pathh[j] == 0) {
            f = true;
        }
        ++size;
    }

    path = realloc(pathh, size*sizeof(int));
    for(int i=0; i<size; i++) printf("%d -> ",pathh[i]);
    printf("\n");
    stampa_piu(default_map, 10, default_columns, path, v_size(pathh));
    free(percorso);
    free(path);
    return 0;
    
}