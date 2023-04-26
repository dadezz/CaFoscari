#include <iostream>

template<typename T> class stack;
template <typename T>
class stack {
    public:
        stack(); //costruttore
        ~stack(); //distruttore
        stack(const stack<T>&); //copy constructor
        stack<T>& operator--(); //pop
        T& top() const; //reference all'elemento in cima
        stack<T>& operator+=(const T&); //push di un elemento in cima
        stack<T> operator+(const T&) const; //push di elemento su copia dello stack
        stack<T>& operator=(const stack<T>&); //copy assignment
        void print();
    private:
        struct cella {
            T info;
            cella* next;
        };
        cella* head;
};

template <typename T>
stack<T>::stack(){  //costrutore
    head = nullptr;
}

//Destructor: 
template <typename T>
stack<T>::~stack() {    
    while(head){
        cella* aux = head;
        head = head->next;
        delete aux;
    }
    head = nullptr;
}

//copy constructor
template <typename T>
stack<T>::stack(const stack<T>& rhs){
    if (rhs.head){
        head = new cella;
        head->info = rhs.head->info;
        head->next = nullptr;
        
        cella* rhs_aux = rhs.head->next;
        cella* aux = head;
        while(rhs_aux){
            cella* nuova = new cella;
            aux->next = nuova;
            nuova->next = nullptr;
            nuova->info = rhs_aux->info;
            aux = nuova;
            rhs_aux = rhs_aux->next;
        }
    }
}

//elimino prima cella
template <typename T>
stack<T>& stack<T>::operator--(){
    if (!head) return *this;
    cella* aux = head;
    head = head->next;
    delete aux;
    return *this;
}

//ritorno primo elemento
template <typename T>
T& stack<T>::top() const{
    //std::cout<<"sono in top. head->info = "<<head->info<<std::endl;
    return head->info;
}

//push di un elemento in cima (prepend)
template <typename T>
stack<T>& stack<T>::operator+=(const T& rhs){ 
    cella* nuova = new cella;
    nuova->info = rhs;
    nuova->next = head;
    head = nuova;
    return *this;
}

//ritorna un nuovo oggetto, dato dal mio oggetto più una cella nuova
template <typename T>
stack<T> stack<T>::operator+(const T& rhs) const{
    //creo la prima cella del nuovo oggetto, info = rhs
    stack<T> copia;
    cella* copia_head = new cella;
    copia.head = copia_head;
    copia.head->next = nullptr;
    copia.head->info = rhs;
    
    //copio le celle rimanenti di this
    cella* this_aux = head;
    cella* copia_aux = copia.head;
    while(this_aux){
        cella * nuova = new cella;
        nuova->info = this_aux->info;
        nuova->next = nullptr;
        copia_aux = copia_aux->next = nuova;
        this_aux = this_aux->next;
    }
    return copia;    
}

//copy assignment
template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& rhs){
    //caso autoassegnamento
    if (rhs.head == head) return *this;
    //svuoto la mia lista attuale
    while(head){
        cella* aux = head;
        head = head->next;
        delete aux;
    }
    //se esiste la seconda lista:
    if (rhs.head){
        //creo una nuova testa
        head = new cella;
        head->info = rhs.head->info;
        head->next = nullptr;
        
        //ci aggiungo tutti gli elementi successivi
        cella* rhs_aux = rhs.head->next;
        cella* aux = head;
        while(rhs_aux){
            cella* nuova = new cella;
            nuova->info = rhs_aux->info;
            nuova->next = nullptr;
            aux = aux->next = nuova;
            rhs_aux = rhs_aux->next;
        }
    }
    return *this;
}

template <typename T>
void stack<T>::print(){
    std::cout<<" [ ";
    cella* aux = head;
    while(aux){
        std::cout<<aux->info<<" ";
        aux = aux->next;
    }
    std::cout<<"]"<<std::endl;

}

int main(){
	
	int N {};
    N = 3;
	N *= 2;
	
	using T = int;
	
	stack<T> S1;
	
	T x,y;
	for(int i=0;i<N/2;++i){
		x = i;
        y = i+1;
		(S1 += x) += y;
	}

    std::cout<<std::endl<<"Ho inizializzato s1. printo la lista1: "; S1.print(); 

	
	stack<T> S2 = stack<T>{S1} + N;
	
	S2 = S2;
	std::cout<<"Ho inizializzato s2. printo la lista2: "; S1.print(); 

    std::cout<<std::endl<<"entro nel primo for: "<<std::endl;
	for(int i = 0; i<N-1;++i){
        std::cout<<"printo la lista1: "; S1.print();
        std::cout<<"printo la lista2: "; S2.print();
		std::cout << (--S1).top()++ << std::endl;
		S2 += S1.top();
	}

    std::cout<<std::endl<<"entro nel primo for: "<<std::endl;

	for(int i = 0; i<2*N;++i){
        std::cout<<"printo la lista1: "; S1.print();
        std::cout<<"printo la lista2: "; S2.print();
		
		std::cout << S2.top() << std::endl;
		--S2;
		
	}
	
	for(int i = 0; i<100;++i) --S2;
	
}