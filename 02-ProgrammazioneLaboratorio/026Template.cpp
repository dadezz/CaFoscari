#include<iostream>

/**
 * GENERIC PROGRAMMING
 * Non focalizzarsi nel tipo di dati ma nell'algoritmo,scrivere una funzione che possa lavorare con qualsiasi tipo di dato
 * l'algoritmo non deve dipendere dal tipo di dato,contenitore generico
 * 
 * la programmazione generica,permette di usare un algoritmo quando volte si vuole in diversi tipi di dato.
 * C++ ha nella sua implementazione i templates.
 * si possono utilizzare in 2 modi :
 *     funzioni 
 *     classi
 * 
*/

/**
 * funzioni template
*/

template<typename T>
T max( const T& x , const T& y){
    return x > y ? x : y;
}

template<typename T , typename f>
bool is_eq(const T& x, const f& y){
    return x == y;
}

/**
 * classi template
*/
template<typename T , typename f>
struct mycont
{
    mycont(){}
    mycont( const T& val , const f& v) : m_val(val) , r_val(v){}
    void print(){ std::cout<<m_val<<" , "<<r_val<<std::endl;}
    void operator++(){ m_val -= 1;}
    int operator++(int){ int prev=m_val;m_val -= 6;return prev;}
    private:
        T m_val;
        f r_val;
};



int main(){
    int q = max<int>(3,4);
    float s = max<float>(3.12,1.1);
    char a = max<char>('a','b');
    if(is_eq((int)'a','a')) std::cout<<"funziona"<<std::endl;
    std::cout<<q<<" , "<<s<<" , "<<a<<std::endl;
    
    mycont<int,char> R(1,'a');
    R.print();
    R++;
    R.print();
    return 0;
}