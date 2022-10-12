#include <stdio.h>

/*operatore condizionale ternario*/

/*
L'operatore ternario condizoinale è definito come 

expr_1 ? expre_2 : expr_3

con il seguente significato: se expr_1 è vera, viene valutata expr_2,
altrimenti viene valutata expr_3
*/
int main (){
    int a=0; //a = falso
    a ? printf("vero\n") : printf("falso\n");
    a=1;
    a ? printf("vero\n") : printf("falso\n");
    return 0;
}

int main1 (){
    int a=1, b=2, c=3;

    //trovare il massimo.
    a>b && a>c ? printf("a\n") : c>a && c>b ? printf("c\n") : printf("b\n");
    
    return 0;
}
