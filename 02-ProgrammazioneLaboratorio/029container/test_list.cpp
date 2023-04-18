#include "list.hpp"
#include "list.cpp"

int main(){
    list<double> l1;
    //read_list<double>(l1);

    list<double> l2;

    std::cout<<"liste uguali? "<<(l1==l2)<<std::endl;
    std::cout<<l1<<std::endl;
    l1.push_back(8.3);

}