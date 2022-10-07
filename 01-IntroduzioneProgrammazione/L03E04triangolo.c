#include<stdio.h>
#include<math.h>

int main (){
    float a=10.0f, b=12.0f, c=16.0f; // lati
    //Date le lunghezze di tre segmenti, dire se questi possono formare un triangolo.
    if (((a+b)>c) && ((a+c)>b) && ((c+b)>a)) {
        printf("yes, buddie!");
    
        //Date le lunghezze di tre segmenti, dire se questi possono formare un triangolo rettangolo.
        float ipotenusa = a;      //l'ipotenusa è sicuramente il più lungo di questi tre lati
        if (b>ipotenusa) ipotenusa = b;
        if (c>ipotenusa) ipotenusa = c;
        if (ipotenusa == sqrtf(a*a + b*b)) printf(" ed è pure rettangolo!");
        else printf(" ma sfortunatamente non è rettangolo...");
    }
    return 0;
}
