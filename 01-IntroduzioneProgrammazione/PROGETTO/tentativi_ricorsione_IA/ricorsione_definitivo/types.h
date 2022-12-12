#ifndef DEBUG
#define DEBUG  0/*PORLO = 1 PER STAMPARE DEBUG, = 0 PER COMPILAZIONE NORMALE*/
#endif

#ifndef FLATTENED
#define FLATTENED 1 /*PORLO = 1 PER MAPPA MONODIMENSIONALE, = 0 PER MAPPA BIDIMENSIONALE
    nota: la parte "riduzione" al momento esiste solo per flattened
*/
#endif


#define DATA_STRUCTS
typedef struct{
    int* data;
    size_t size;
} vector_t;
typedef struct{
    int row;
    int col;
} position_t;
#if FLATTENED
typedef struct{
    char* map;
    int row;
    int col;
} board_t;
#endif
#if !FLATTENED
typedef struct {
    char** map;
    int row;
    int col;
} board_t;
typedef struct {
    int* col;
    int* row;
    size_t size;
} p_vec_t;
#endif
