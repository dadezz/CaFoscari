#include<stdio.h>

void scan(int *righe , int *colonne){
    scanf("%d",righe);
    scanf("%d",colonne);
}


void inserimento(char* vet, int *righe, int *colonne){//creazione campo/inserimento
    //int pos = 1;
    
    for (size_t j = 0; j < *righe; ++j){
        size_t i=0;
        //for(; i<*colonne+1 && (vet[i+j*(*colonne)]=getchar())!='\n' ;i++);
        //if (vet[i] != '\n') break;
        for(;i<*colonne;i++){
            //vet[(i + j*(*colonne))] = getchar();
            while ((vet[(i + j*(*colonne))] = getchar())=='\n'); //cumme cazz iè pussibbile?
            //vet[(i + j*(*colonne))] = getchar();
            
        }

    }
}

/*
  i + j*colonne
  
  j = 0:
    0 + 0*4
    1 + 0*4
    2 + 0*4
    3 + 0*4
  j = 1
    0 + 1*4 4
    1 + 1*4 5
    2 + 1*4 6
    3 + 1*4 7
  j = 2:
    0 + 2*4 8
    1 + 2*4 9
    2 + 2*4 10
    3 + 2*4 11
    


*/

void print(char* vet , int *righe , int *colonne){

      for (size_t i = 0; i < (*righe) * (*colonne); i++)
      {
       // printf("%c %d\n",vet[i],i);

         if (vet[i] != '\n')
         {
          printf("%c %d\n",vet[i],i);

         }
          
        
      }
      
}