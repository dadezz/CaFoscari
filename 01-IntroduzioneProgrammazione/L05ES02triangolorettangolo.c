/*
Scrivere una funzione che dati 3 lunghezze che restituisca 1 se possono
essere i lati di un triangolo rettangolo e 0 altrimenti
*/

#include<stdio.h>
#include<math.h>

int triangolo (float a, float b, float c){
    if (((a+b)>c) && ((a+c)>b) && ((c+b)>a)){
        
        float ipotenusa = a;      //l'ipotenusa è sicuramente il più lungo di questi tre lati
        if (b>ipotenusa) ipotenusa = b;
        if (c>ipotenusa) ipotenusa = c;
        if (ipotenusa == sqrt(a*a + b*b + c*c - ipotenusa*ipotenusa)){ //siccome non so quale sia la variabile ipotenusa, sommo tutte e la sottraggo
            return 1;
        }
    }
    return 0;
}

