#include <stdio.h>

int main (){
  //conversione da decimale a binario
  int decimale = 22; //decimale che voglio 
  int risultato, resto; // risultato della divisione intera e resto
  int lista_bit[] = {0,0,0,0,0,0,0,0}, contatore = 0; //suppongo 8 bit necessari (contatore serve nel do while)
  /*
  Prendo il numero di partenza, lo divido per due, registro il resto della divisione (0 o 1). Il risultato della 
  divisionelo divido nuovamente per due e registro il resto. Continuo così fino a che la divisione non mi darà 
  come risultato 0 (notare che in questo ultimo caso il resto sarà sempre 1).
  Il corrispondente in binario sarà dato da tutti i resti trovati, letti dall'ultimo al primo.

  In questo caso:
  22/2 = 11 | resto 0
  11/2 = 5  | resto 1
  5/2  = 2  | resto 1
  2/2  = 1  | resto 0
  1/2  = 0  | resto 1   qui mi fermo.

  Dal primo all'ultimo, i resti formano il numero binario. quindi 22 = 10110 in base 2
  */
  do {  
    resto = decimale%2; // resto
    decimale /= 2;      //divisione
    lista_bit[contatore] = resto; //registro il resto
    contatore += 1;               //contatore dell'array dove metto i resti
  } while (decimale !=0 && contatore<8);  //controllo lo 0 come risultato e il numero massimi di bit

  for (int i = 7; i >= 0; i--){   //leggo l'array al contrario
    printf("%d", lista_bit[i]);   //stampo infine il numero (8 bit, al massimo i primi saranno zeri)
  }

  return 0;
}