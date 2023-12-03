#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <iostream>

int main(){
    int N;
    std::cin>>N; //numero di stringhe
    std::vector<std::string> v (N);
    std::vector<int[26]> capra (N);
    for (int i=0; i<N; i++){
        for (int j=0; j<26; j++){
            std::cout<<capra[i][j];
        }
        std::cout<<std::endl;
    }
    for (int i = 0; i<N; i++){
        for (int j=0; j<v[i].length(); j++){
            capra[i][v[i][j]-97]++;
        }
    }
}