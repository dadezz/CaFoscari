#include <vector>
#include <iostream>
#include <string>

using std::cout; using std::vector; using std::cin; using std::string; using std::endl;



vector<int> fill_with_primes(int size) {
    vector<int> v; 

    if (size == 0) return v;
    v.push_back(2);

    if (size == 1){
        //preferisco hardcodare questa condizione, così che nel ciclo, se parto da un numero dispari posso saltare di due in due
        //invece che controllare ogni numero
        return v;
    }
    v.push_back(3); //ora ho un dispari in partenza
    
    for (int i = 2; i<size; i++){
        
        int x = v.at(v.size()-1)+2; //mi serve partire dall ultimo numero primo trovato +2
        bool primo = true;
        bool hoaggiunto = false;
        while(primo && !hoaggiunto){
            
            int j = 0;
            while(primo && j<v.size()){
               
                if (x % v.at(j) == 0) {
                    primo = false;
                    cout<<"x: "<<x<<" j: "<<j<<" v.at(j): "<<v.at(j)<<endl;
                }
                j++; //j 2
            }
            if (primo){
                v.push_back(x);
                hoaggiunto = true;
            }
            else {
                x+=2;
                primo=true;
            }
        }
    }
    return v;
}


int main(){
    vector<int> v;
    v = fill_with_primes(12);
}