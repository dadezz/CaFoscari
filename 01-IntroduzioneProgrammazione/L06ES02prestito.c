/*
Claudio ha bisogno di un prestito di €10,000, e ha ricevuto due offerte da due banche diverse.
In entrambi i casi Claudio può scegliere la durata del prestito e restituire la cifra dovuta in un
unica soluzione al termine del prestito. La cifra totale da restituire è calcolata in questo modo:
- offerta A) dopo 𝑚 mesi 10,000 ⋅ 1.02𝑚
- offerta B) dopo 𝑚 mesi 10,000 ⋅log2(𝑚+2)
Claudio non ha ancora deciso quale sia la durata 𝑚 migliore per lui, anche se di sicuro vuole
chiudere il mutuo in meno di 10 anni. Per decidere ha però bisogno di sapere quale sia la
durata oltre la quale l'offerta A) diventa meno conveniente dell'offerta B).
Qual è il primo mese 𝑚 in cui l'offerta A) è meno conveniente dell'offerta B)?
*/

#include<stdio.h>
#include<math.h>

int main (){
    float prestito = 10000.0f;
    float mesi = 1.0f;
    float cifra_da_restituire_banca_A = prestito*(powf(1.02f, mesi));
    float cifra_da_restituire_banca_B = prestito*(log2f(mesi+2));

    for ( ; cifra_da_restituire_banca_A < cifra_da_restituire_banca_B; mesi+=1){
        cifra_da_restituire_banca_A = prestito*(powf(1.02f, mesi));
        cifra_da_restituire_banca_B = prestito*(log2f(mesi+2));
        //printf("mese: %f, banca A: %f, banca B: %f\n", mesi, cifra_da_restituire_banca_A, cifra_da_restituire_banca_B);
    }

    printf ("la banca B sarà più conveniente dopo %.1f mesi\n", mesi);
    if (mesi/12 > 10) printf("prima dei dieci anni, saràsempre più conveniente l'offerta A");

    return 0;
}