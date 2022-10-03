#include<stdio.h>

int main (){
    //A quanti anni, settimane e giorni corrispondono 2048 giorni?
    int tempo = 2048;
    int anni = tempo/365;
    tempo = tempo%365;
    int settimane = tempo/52;
    tempo = tempo%52;

    printf("2048 giorni corrispondono a: %d anni, %d settimane, %d giorni", anni, settimane, tempo);
    return 0;
}