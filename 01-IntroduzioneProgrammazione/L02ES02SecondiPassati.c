#include <stdio.h>

int main (){
  // Dati 3 interi corrispondenti a ore, minuti e secondi, visualizzare il numero di
  // secondi trascorsi dall’inizio della giornata
  int ore = 12, minuti = 24, secondi = 36;  // Assegnamento di prova
  int seconditot = 3600*ore + 60*minuti + secondi;

  printf("secondi totali da inizio giornata: %d", seconditot);

  return 0;
}