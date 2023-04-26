#include "list.hpp"
#include "list.cpp"

int main(){
    list<double> x1;

    x1 += 5;
    x1 += 6.2;
    x1 += 12;

    list<double> x2; 
    x2 = x1;

}