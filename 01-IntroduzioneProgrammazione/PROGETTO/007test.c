#include<stdio.h>
#include "008test_ext.c"
#include<stdlib.h>





extern void scan(int *righe , int *colonne);
extern void inserimento(char* vet, int *righe, int *colonne);
extern void print(char* vet , int *righe , int *colonne);

int  main(){
    /*int prova[][lunghezza] = {1,2,3,4,
                            1,2,3,4,
                            1,2,3,4,
                            1,2,3,4};
    */
    
    int righe;
    int colonne;
    scan(&righe,&colonne);

    char* prova = (char*) malloc((righe*colonne)*sizeof(char));
    printf(" righe casso %d\n",righe);
    printf(" colonne minchia %d\n",colonne);
    if(prova != NULL) printf("ok \n");
    if(prova == NULL) return 1;

    inserimento(prova,&righe,&colonne);
    print(prova, &righe, &colonne);
     
    return 0;

}