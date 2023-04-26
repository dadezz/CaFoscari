#include <iostream>
#include<iomanip>
#include <unistd.h>


double radice(double n, unsigned int k, double min, double max) {
    //n è il numero di cui trovare la radice
    //k è l'indice della radice (quarata, cubica, etc)
    std::cout<<"chiamata di funzione: n= "<<n<<" k= "<<k<<" min= "<<min<<" max= "<<max<<std::endl;
    double res = (max+min)/k;
    double res_exp = res;
    for (int i = 1; i<k; i++){
        res_exp *= res;
    }
    sleep(1);
    std::cout<<"res: "<<res<<std::endl;
    std::cout<<"res^2: "<<res_exp<<std::endl;
    if (res_exp >= n){
        if (res_exp - n < 0.0001) return res;
        else return radice(n, k, min, res);
    }
    else{
        if (n - res_exp < 0.0001) return res;
        else return radice(n, k, res, max);
    }
    
}

int main(){
    double input;
    unsigned int indice;

    std::cin>>input;
    std::cin>>indice;
    
    std::cout<<std::setprecision(5)<<radice(input, indice, 1.0, input);
    
    return 0;
}