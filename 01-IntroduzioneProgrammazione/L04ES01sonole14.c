//Sono le ore 14:00, dato un timer impostato tra 38 ore, a che ora suonerà la sveglia?
#include<stdio.h>

int main(){
    int ore = 14;
    int timer = 38;
    int sveglia = ore+timer;
    while (sveglia >= 24){
        sveglia -= 24;
    }
    printf("sveglia impostata per le %d:00", sveglia);

    return 0;
}