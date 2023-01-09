#include <stdlib.h>
#include <stdio.h>

char* est (char* str){

    return str;
}


int main(){
    char* str1 ="ukjyvsrkjuv";
    str1 = "kjsyv";
    printf("%s\n", str1);

    //str1[5] = 'b';

    printf("%s\n", str1);

    char a[] = {'a', 'b', 'c'};
    a[1] = 'z';

    printf("%s\n", a);

    char* str2;
    str2 = est(str1);

    for (int i =0 ;i <6; i++){
        printf("str2 [%d]: %c \n", i, str2[i]);
    }


    return 0;
}