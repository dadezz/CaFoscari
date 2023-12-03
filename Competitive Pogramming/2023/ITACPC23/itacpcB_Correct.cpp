#include <iostream>

int main(){
    int Length;
    std::cin>>Length;
    int altitude = 3000;
    int aux;
    for (int i=0; i<Length; i++){
        std::cin>>aux;
        altitude += aux;
    }
    std::cout<<altitude;
}