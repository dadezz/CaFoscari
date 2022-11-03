#include<stdio.h>
#include <stdlib.h>
#include <string.h>


/*
CONVERTIRE STRINGA IN INPUT IN FORMATO B1FF
*/

int main(){

    char *str_in = (char*) malloc(100);
    printf("inserire stringa: ");
    for(unsigned int i=0;i<99&&(str_in[i]=getchar())!='\n';i++);
    
    str_in[99]='\0';
    str_in = (char*) realloc(str_in, strlen(str_in)+1);
    char *str_out = (char*) malloc(strlen(str_in)+11);
        if(str_in==NULL){
        return 1;
    }
   
    short cont = 0;
    for (cont; cont<strlen(str_in)-1; cont++){
        switch (str_in[cont]) {
            case 'A': case 'a':
                str_out[cont] = '4';
                break;
            case 'B': case 'b':
                str_out[cont] = '8';
                break;
            case 'E': case 'e':
                str_out[cont] = '3';
                break;
            case 'I': case 'i':
                str_out[cont] = '1';
                break;
            case 'O': case 'o':
                str_out[cont] = '0';
                break;
            case 'S': case 's':
                str_out[cont] = '5';
                break;
            default:
                if (str_in[cont]>='a' && str_in[cont]<='z') str_out[cont] = str_in[cont]-32;
                else str_out[cont] = str_in[cont];
                break;
            }
    }
    while (cont<strlen(str_in)+11){
        str_out[cont++] = '!';
    }
    str_out[++cont] = '\0';
    
    printf("%s\n", str_out);
    free(str_out);
    free(str_in);
    return 0;
}