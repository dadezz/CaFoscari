#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define DEBUG 0

bool palindrome_rec(char* s, int len){
    if (len <= 2) {
        if (s[0] == s[len-1]) return true;
        else return false;
    }
    return (s[0] == s[len-1]) && palindrome_rec (s+1, len-2);
}


bool palindrome (char* s){
    return palindrome_rec (s, strlen(s));
}


#if DEBUG
int main(){
    char* s = "asddsa";
    char* s2 = "asdfga";
    char* s3 = "asdedsa";

    printf("true/false: %d\n", palindrome(s));
    printf("true/false: %d\n", palindrome(s2));
    printf("true/false: %d\n", palindrome(s3));
}
#endif 