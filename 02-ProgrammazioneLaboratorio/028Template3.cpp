/**
 * spceializzazioen su template
 * 
 * il vector della stdlib in bool ha un implementazione diversa rispetto al vector double. 
 * Il vector di bool non alloca un byte per ogni bool, ma un solo bit: Nbit -> N/64 unit64_t, più maschere varie per
 * lavorare a livello di bit
 * 
 * bisogna specializzare la classe template per un tipo 
*/
#include<utility>
#include<iostream>



template<typename T>
void print(T const& x){
    std::cout<<x<<std::endl;
    std::cout<<"f generica"<<std::endl;
}

//versione specializzata per std::pair<int, int>
template<> 
void print(std::pair<int, int> const& x){
    //questa è la cosiddetta specializzazione totale, ovvero la lista dei parametri in template rimane vuote
    std::cout<<"spec"<<std::endl;
    std::cout<<"( "<<x.first<<", "<<x.second<<" )"<<std::endl;
}

//idem con le classi
template<typename T>
struct A{
    public:
        A(){std::cout<<"costruisco classe con tmplt generico"<<std::endl; }
    private:
        T m_val;
};

template<>
struct A<int>{
    public:
        A(){ std::cout<<"costruisco classe con tmplt int"<<std::endl; }
    private:
        int m_val;
        double x;
};

