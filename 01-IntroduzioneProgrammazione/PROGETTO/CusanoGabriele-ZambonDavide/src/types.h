/**
 * @file types.h
 * @authors Gabriele Cusano (897835), Davide Zambon (898103)
 * @date 02 feb 2023
 * @section TIPI
 * file header che contiene la dichiarazione dei tipi, condivisa da tutti i sorgenti.
*/

/**
 * vettore che porta con sé anche l'informazione sulla lunghezza.
 * Viene usato per memorizzare il percorso (sia definitivo che ausiliario).
 * @param data: array di interi
 * @param size: elementi dell'array
*/
typedef struct{
    int* data;
    size_t size;
} vector_t;

/**
 * vettore che porta con sé anche l'informazione sulla lunghezza utilizzata e disponibile.
 * Viene usato per memorizzare il corpo dello snake.
 * @param body: array delle posizioni
 * @param size: lunghezza dell'array utilizzata
 * @param capacity: lunghezza massima dell'array
*/
typedef struct vector {
    size_t size;
    size_t capacity;
    vector_t *body;
}snake;

/**
 * struttura che porta con sé la posizione in array monodimensionale
 * oppure bidimensionale 
 * @param pos: posizione monodimensionale (intero)
 * @param row: riga (intero)
 * @param col: colonna (intero)
*/
typedef struct{
    int pos;
    int row;
    int col;
} position_t;

/**
 * struttura che porta con sé le informazioni base della mappa di gioco
 * @param map: array di caratteri
 * @param row: quantità di righe
 * @param col: quantità di colonne
*/
typedef struct{
    char* map;
    int row;
    int col;
} board_t;

typedef int vdata_t;