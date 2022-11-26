#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int fibo(int *values, size_t v_size){
  int count = 0;
  if (v_size == 0) return 0;
  if (*values != 0) count++;
  return fibo(values+1, v_size-1);
}

int controllo_pattern(char* dna_str, char* pattern, size_t size){
    int uguale = 1;
    for (int i=0; i<size && uguale; i++) if (dna_str[i]!=pattern[i]) uguale = 0;
    return uguale;
}
size_t pattern_counting(char* dna_str, char* pattern) {
    size_t count = 0;
    size_t z=strlen(pattern);
    if ((strlen(dna_str) == z) && !strcmp(dna_str, pattern)) return 1;
    else if ((strlen(dna_str) == z) && strcmp(dna_str, pattern)) return 0;
    if (controllo_pattern(dna_str, pattern, z)) return 1+pattern_counting(dna_str+1, pattern);
    else return pattern_counting(dna_str+1, pattern);
}
size_t pattern_counting1(char* dna_str, char* pattern) {
    //CONTROLLA QUI PLEASE
    size_t size_pattern = strlen(pattern);
    size_t size_dna = strlen(dna_str);
    size_t c=0;
    for(int i=0; i<size_dna; i++) {
        if(dna_str[i]==pattern[0]){
            for(int k=1; k<size_pattern; k++) {
                unsigned l=1;       //ecco l'errore: hai messo l'inizializzazione dentro al for, torna a 1 ogni volta
                if(dna_str[i+k]==pattern[k]){
                    l++;
                }
                if(l==size_pattern){
                    c++;
                    printf("ciao ");
                }
            }
        }
    }
    
    for (int i=0; i<size_dna; i++) {
        printf("%c ", dna_str[i]);
    }
    
    printf(" SP %u ", size_pattern);
    printf(" SD %u ", size_dna);
    return c;
}

int MCD(int a, int b){
    if (b>a){
        int tmp=b;
        b=a;
        a=tmp;
    }
    if (b==0) return a;
    return MCD(b, a%b);
}

bool pairwise_coprime(int* values, size_t v_size) {
    if (v_size == 1) return true;
    return MCD(values[0],values[1]) == 1 && pairwise_coprime(values+2, v_size-2);
}

bool find(int* v, size_t v_size, int m) {
    if (v_size == 1 && v[0] == m) return true;
    if (v_size == 1 && v[0] != m) return false;
    if (v[(v_size/2)]==m)return true;
    if (v[(v_size/2)]<m) return v_size%2==0 ? find(v+(v_size/2), v_size/2, m) : find(v+(v_size/2), v_size/2+1, m);
    if (v[(v_size/2)]>m) return v_size%2==0 ? find(v, v_size/2, m): find(v, v_size/2+1, m);
}

int max(int a, int b){
    if (a>b) return a;
    else return b;
}
unsigned best_combination1(unsigned b, unsigned* v, size_t n) {
    if (n==0) return 0;
    if (b==0) return 0;

    //skippo l'elemento se questo è piu grande del budget residuo 
    // nella mia idea, quindi, aumento di uno l'indice del vettore, ma non so come cambiare n
    if (v[0]>b) return best_combination1(b, v+5, n-1);

    //se l'oggetto è parte della soluzione, passo direttamente alla riga successiva, 
    //ovvero vado alla posizione (n-1)*5, e decremento di uno n
    int caso_oggetto_in_subset = v[0]+best_combination1(b-v[0], v+5, n-1);
   
    //se l'oggetto non fa parte della soluzione, passo a quello successivo, ma non so come gestire n
    int caso_ogg_not_in_subset = best_combination1(b, v+5, n-1);

    //alla fine trovo il massimo possibile tra le soluzioni
    return max(caso_ogg_not_in_subset, caso_oggetto_in_subset);
}

unsigned MAX(unsigned * v, unsigned b){
    unsigned a=0;
    printf("dentro a max: ");
    int i = 0;
    for (; i<5;i++) if (v[i]>a && v[i]<=b) {a=v[i]; printf("i: %d ", i);}
    printf(" trovato %u \n", a);
    return a;
}
unsigned best_combination(unsigned b, unsigned* v, size_t n) {
    if (n==0) return 0;
    printf("%u    %u    %u\n", MAX(v,b), best_combination(b-MAX(v,b), v+5, n-1), b);
    return MAX(v,b)+best_combination(b-MAX(v,b), v+5, n-1);
}
int main(){
  char v[]={'a','a','t', 't','t','t','a','\0'};
  char p[]={'t','t','t','\0'};
 // printf("%d\n",MCD(3,6));
  //int prova[]={1,2,3,7,8,10,11};
  //int prova[3*5]={1,7,2,8,15,2,5,4,5,8,5,10,12,8,4};
  //printf("%d\n", best_combination(34, prova, 3));
  //printf("%d\n", find(prova,7,11));
 //printf("%d\n", pairwise_coprime(prova,8));
  size_t n_occ = pattern_counting1(v,p);
  printf("%d\n", n_occ);
  return 0;
}