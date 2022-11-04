/*
APPUNTI 04 NOVEMBRE 2022
*/


#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//non si possono buttare via elementi di un array, bisogna usare trucchi
//vediamo esempio di array dove devo scartare elementi superiori a 5.

//un esempio è:  connto gli elementi da tenere e creo secondo array con la giusta quantita di celle.
//ritorno poi un pointer. sta cosa va fatta in memoria, non nei registri.
//servirà quindi ritornare il pointer e la sua lunghezza. per returnare due cose, devo aggiungere parametro in input
//di tipo pointer (ma è la lezione della volta scortsa lol, se continua così skippo sta parte di appunti).


int main1(){

    srand(time(NULL));
    size_t len;
    scanf("%d", &len);

    //float a[len]; //non  si può sempre fare sta cosa, dipende dal dialetto.
                    //sarebbe infatti da usare la malloc

    int* a = (int*) malloc (len*sizeof(int));

    //se len è zero, la malloc ritorna NULL


    for (int i=0; i<len; i++){
        a[i]=rand()%100;
    }

    int sum = 0;
    for (int i=0; i<len; i++){
        sum+=a[i];
    }

    //avg ritorna nan se len 0
    float avg = ((float)sum)/len;

    int max=INT_MIN, min = INT_MAX; //funziona se len 0, ma terribile risultato.
    

    //int max=a[0], min=a[0];
    //dereferenzio il pointer NULL, ovvero vado a prendere il primo byte (pos NULL) della ram.
    //vado quindi a prendere una cosa che non posso usare. in teoria non posso accedere, ma se 
    //dereferenzio il nulll, il compilatore fa un trucchetto e mi ritorna 0, ma dovrebbe crasharmi il prog.

    for(int i=1; i<len; i++){
        if(a[i]>max) max = a[i];
        else if (a[i]<min) min = a[i];
    }


    return 0;
}