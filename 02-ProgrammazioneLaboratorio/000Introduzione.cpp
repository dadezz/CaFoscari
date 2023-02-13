int main(){
/**
 * introduzione al cpp
 * 
 * L'utilizzo dei puntatori, rispetto al C diventa meno necessario,
 * c'è una diversa gestione della memoria, si può usare la programmazione in memoria dinamica spesso senz utilizzare i puntatori
 * È un linguaggio orientato agli oggetti
 * 
 * trade-off: la gestione implicita della memoria è facile da usare ma non ci si rende conto dell'utilizzo. Il free è automatizzato dal
 * linguaggio stesso, che controlla i garbage, vedendo mano a mano tutta la memoria occupata e liberando le celle allocate ma non necessarie
 * 
 * il prezzo della semplicità è che il garbage collector è un programma, richiede tempo e cpu.
 * C++ non ha bisogno di garbage collector (a differenza per esempio di py e java).
 * chi fa la free di una malloc? la gestione della mem dinamica non è scaricata al programmatore, vedremo in che modo.
 * 
 * Il linguaggio consente di mantenere molto di quello che deriva dal C, permettendo qquindi di avere una buona efficienza ma anche una buona 
 * usabilità in termini di complicatezza
*/

/**
 * abbiamo un tipo elementare nuovo: bool. 
 * Gli altri tipi primitivi sono definiti in modo uguale al C.
 * 
 * Ricordiamo tre definizioni: 
 * un tipo di dato è un insieme di valori su cui vengono definite delle operazioni. 
 * Un oggetto è un area di memoria dotata di tipo, secondo la definizione standard di c++ (quindi non l'istanza di una classe).
 * Una variabile è un oggetto a cui viene assegnato un identificatore.
*/

//int *p = malloc(100); ho 2 oggetti: uno è la memoria allocata che mi tiene il puntatore p (ed è una variabile), l'altro è la memoria allocata
                        // dalla malloc, che però non avendo identificatore non è una variabile

/**
 * il cpp si porta dietro dal C la tipizzazione. se assegnassi
*/

int a;
double b = 3.14;
a = b;

/**
 * in C avrei probabilmente problemi, in C++ c'è casting implicito sempre. in questo caso, se il cambio di tipo porta perdita di informazioni, 
 * si dice che fa narrowing (3,14 diventa 3). non ci sono avvisi, è da stare attenti a sta forma
 * 
 * c'è un controllo in inizializzazione:
 * 
 * lo standard di compilaizone deve essere >= 2014 (flag : c++14)
*/

int k = 12.3; // fa casting con narrowing
int k{12.3}; //controlla questo problema

/**
 * puntatori
 * 
 * int* p è equivalente a int *p, ma se in C è buona norma usare il tipo di dx, in c++ si tende a usare il tipo a sx.
 * 
 * 
*/




}