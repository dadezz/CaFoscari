#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include <iostream>


void stampa(std::vector<int[26]> v, int N){
    for (int i=0; i<N; i++){
        for (int j=0; j<26; j++){
            std::cout<<v[i][j];
        }
        std::cout<<std::endl;
    }
}

bool compare_array(int v1[26], int v2[26]){
    bool ho_trovato_un_dispari = false;

    bool ho_trovato_un_mismatch = false;

    for (int i=0; i<26; i++) {
        //std::cout<<v1[i]+v2[i]%2<<"   "<<std::boolalpha<<ho_trovato_un_dispari;
        if (v1[i]+v2[i]%2 == 1){
            if (ho_trovato_un_dispari)return false;
            else ho_trovato_un_dispari = true;
        }

        if ((v1[i] == 0 && v2[i] != 0) || (v2[i] == 0 && v1[i] != 0)){
            if (ho_trovato_un_mismatch)return false;
            else ho_trovato_un_mismatch = true;
        }
    }
    bool trovato=false;
    int index = 0;
    for (int i=0; i<26 && !trovato; i++){
        if (v1[i] != v2[i]) {
            trovato = true;
            index = i;
        }
    }
    if (trovato) {
        bool maggiore = v1[index] > v2[index];
        for (int i=index; i<26; i++) {
            if (v1[i] != v2[i]){
                if ((v1[i] > v2[i]) != maggiore) {
                    if ((v1[i] + v2[i]) %2 == 0) return false;
                }
            }
        }
    }
    return true;
}
bool isPalindrome(const std::string& str) {
    // Two pointers to iterate from both ends of the string
    size_t left = 0;
    size_t right = str.length() - 1;

    // Continue comparing characters until the pointers meet
    while (left < right) {
        // Compare characters (ignoring case)
        if (str[left] != str[right]) {
            return false; // Characters don't match, not a palindrome
        }
        left++;
        right--;
    }
    return true; // All characters matched, it's a palindrome
}

int palindrome(std::string v1, std::string v2){
    std::string v3 = v1+v2;
    int count = 0;
    //std::cout<<v3<<std::endl;
    if (isPalindrome(v3)) {
        count++;
        
    }
    v3 = v2+v1;
    //std::cout<<v3<<std::endl;
    if (isPalindrome(v3)) {
        count++;
        //
        };
    return count;
}


int main(){
    int N;
    std::cin>>N; //numero di stringhe
    std::vector<std::string> v (N);
    std::vector<int[26]> capra (N); //arrray delle frequenze

    int counter = 0;

    for (int i=0; i<N; i++){
        std::cin>>v[i];
    }
    for (int i = 0; i<N; i++){
        for (size_t j=0; j<v[i].length(); j++){
            capra[i][v[i][j]-97]++;
        }
    }

    /*for (int i=0; i<N; i++){
        for (int j=0; j<26; j++){
            std::cout<<capra[i][j];
        }
        std::cout<<std::endl;
    }*/

    for(int i=0; i<N; i++){ //ciclo esterno controlla l'array con tutte le altre passate nel ciclo interno
        for (int j=i+1; j<N; j++){
            bool possible_match = compare_array(capra[i], capra[j]);
            //std::cout<<std::boolalpha<<possible_match<<std::endl;
            if (possible_match){
                counter += palindrome(v[i], v[j]);
            }
        }
    }

    std::cout<<counter;  
}