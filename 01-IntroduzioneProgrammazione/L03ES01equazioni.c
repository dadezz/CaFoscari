#include<stdio.h>
#include<math.h>

int main(){
    float a = 9, b = 0, c = 0;  //coefficienti (a !=0 per ipotesi)
    float x1=0, x2=0;   //risultati

    float delta = sqrtf(powf(b,2) - 4*a*c);
    if (delta > 0) {
        x1 = (-b + delta)/(2*a);
        x2 = (-b - delta)/(2*a);
        printf("i risultati sono: x1 = %.2f, x2 = %.2f", x1, x2);
    }
    else if (delta == 0) {
        x1 = (-b)/(2*a);
        printf("il risultato e': x = %.2f", x1);
    }   
    else printf("Non ci sono soluzioni nel campo dei reali");
    
    return 0;
}