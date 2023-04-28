#include "list.hpp"
#include "list.cpp"

list<double> f(){
	list<double> x;
	return x;
}

int main(){
	list<double> x1;
	x1 += 5;
	x1 += 6.2;

	// copy constructor (+copy assignment perchè abbiamo definito
	//il constructor in termini dell'assignment)
	list<double> x2 = x1; 

	//copy elision: dovrebbe essere chiamato il move constructor, 
	//ma il compilatore implementa ottimizzazioni (copy elision
	//e costruisce direttamente l'oggetto x3 usando le istruzioni
	//presenti dentro f())
	list<double> x3 = f(); 

	//questa sintassi un po' più complicata non permette
	//al compilatore di effettuare copy elision. In effetti, 
	//qui viene chiamato il move constructor (+move assignment 
	//perchè abbiamo definito il constructor in termini 
	//dell'assignment)
	std::pair<list<double>,int> p = {f(),0}; //move constructor

	//qui viene chiamato:
	//1) move constructor di pair per costruire
	//la coppia {f(),0}; questo chiama il move constructor di 
	//list<double> (+move assignment collegato)
	//2) move assignment per copiare la coppia {f(),0} dentro a p2
	std::pair<list<double>,int> p2;
	p2 = {f(),0};

    list<double> l;
	l += 5;
	l+= 9;


	//nota: qui operator-> non ha senso su it, perchè il tipo 
	//di base non ha membri pubblici (vedi sotto per un esempio
	//in cui operator-> si può usare)

	auto it = l.begin();

	std::cout << *it << std::endl;
	++it;

	std::cout << *it << std::endl;
	++it;

	//dentro la guardia dell'if viene chiamato operator bool()
	if(not it) std::cout << "fine lista" << std::endl; 

	//esempio di uso foreach: qui dietro le quinte viene usato
	//il nostro iterator
	for(auto x : l) std::cout << x << "; ";

	std::cout << std::endl;


	//una lista di coppie
	list<std::pair<int,int>> l2;
	l2 += std::pair<int,int> {1,2};
	l2 += std::pair<int,int> {3,4};

	auto it2 = l2.begin();

	//esempio di utilizzo di operator->
	//nota: operator-> può essere usato solo se
	//Val (in questo caso, std::pair<int,int>) ha variabili/metodi pubblici
	//in questo caso, accediamo alla variabile first di std::pair<int,int>
	std::cout << it2->first << std::endl;

}