#include <iostream>
#include <vector>
#include <algorithm>


int main(){
    int N;
    std::cin>>N;
    std::vector<std::pair<int, int>> v(1000001, std::make_pair(0, 0));
    //first = entrati, 
    //second = usciti
    for (int i=0; i<N; i++){
        int X, Y;
        std::cin>>X;
        std::cin>>Y;
        if (X == 1) v[Y].first += 1;
        else v[Y].second += 1;
    }
    int persone_presenti = 0;
    int max = persone_presenti;
    for (int i=0; i<1000001; i++){
        persone_presenti = persone_presenti - v[i].second;
        persone_presenti = persone_presenti + v[i].first;
        if (persone_presenti>max) max=persone_presenti;
    }
    std::cout<<max;
}