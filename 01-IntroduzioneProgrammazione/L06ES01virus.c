/*
Un virus dal nome sconosciuto si sta diffondendo aumentando la popolazione
contagiata del 2% ogni giorno. Ad oggi i contagiati sono 1000. Calcolare il
numero di contagi giorno per giorno per i prossimi 3 mesi. Tra quanto tempo i
contagi supereranno i 10,000 casi?
*/

#include <stdio.h>

int main (){
    //parte modificabile del programma (dati di partenza)
    float contagiati_iniziali = 1000.0f;
    int giorni_di_stima = 3*30;     
    int casi_da_superare = 10000;
    float moltiplicatore_casi = 0.02f; //2 %

    //inizio programma vero e proprio
    float contagiati_stimati = contagiati_iniziali;
    
    //calcolo numero di contagi giorno per giorno
    for (int i=1 ; i <= giorni_di_stima ; i++){
        contagiati_stimati += (contagiati_stimati*moltiplicatore_casi);
        printf("giorno %d, contagiati stimati: %f\n", i, contagiati_stimati);
    }

    //calcolo dei giorni necessari per superare tot casi:
    int contatore_giorni = 0;
    contagiati_stimati = contagiati_iniziali;   //riporto al valore iniziale la stima
    while (contagiati_stimati < casi_da_superare){
        contagiati_stimati += (contagiati_stimati*moltiplicatore_casi);
        contatore_giorni++;
    }

    if (contatore_giorni==0) printf("i %d casi sono già stati superati\n", casi_da_superare);
    else printf("per superare i %d casi, si stima manchino %d giorni\n", casi_da_superare, contatore_giorni);

    return 0;
}