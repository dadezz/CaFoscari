/**
 * VARIE LEZIONI SARANNO SU STO FILE
 * 
 * CONTAINER CON TEMPLATE
 * 
 * ++ overloading operatori
 * ++ iteratori
 * ++ templates
 * ++ copy constructor
 * ++ move constructor
 * 
 * ++ iteratori
*/

/**
 * creeremo un container di una lista<val> single linked, che finisce a nullptr.
 * teniao puntatore ahead e a tail
 * 
 * vogliamo sovrascrivere <<, >>, +=, !=, ==, [], 
*/

#include "list.hpp"

//default constructor
template<typename Val>
list<Val>::list() : m_front(nullptr), m_back(nullptr){};

//costruttore di lista con una sola cella
template<typename Val>
list<Val>::list(Val v) : list() {
    m_back = m_front = new node {v, nullptr};
    // sostituibile con push_front(v);
}

//distruttore
template<typename Val>
list<Val>::~list(){
    while (not empty()) pop_front();    
}

//move assigment
template<typename Val>
list<Val>& list<Val>::operator=(list<Val> && rhs){
    if (this != &rhs){
        //free all memory allocated to this
        while(not empty()) pop_front();
        m_front = rhs.m_front;
        m_back = rhs.m_back;

        rhs.m_front = rhs.m_back = nullptr; //fondamentale, percHé poi viene chiamato il distruttore, rischio di distruggere il mio oggetto
    }
    return *this;
}

//move constructor
template<typename Val>
list<Val>::list(list<Val>&& rhs){
    //posso sfruttare il move assigment
    /**
     * *this = rhs;   se lasciassi così, rhs è lvalue, chiamerebbe il copy assignment
     *                devo convertirlo in rvalue
    */

    *this = std::move(rhs); //move è una funzione della std lib che fa un cast fra i due tipi
}

//copy constructor:
//list<Val> l1 {l2};
//list<Val> l1 = l2;
//list<Val> l1(l2);
template<typename Val>
list<Val>::list(list<Val> const& rhs) : list() {
	//*this += rhs; //alternativa: uso operator+=
	std::cout << "copy constructor called" << std::endl;
	*this = rhs; //copy assignment
}


//copy assignment
template<typename Val>
list<Val>& list<Val>::operator=(list<Val>const& rhs){
	std::cout << "copy assignment called" << std::endl;
	if(this != &rhs){
		while(not empty()) pop_front();
		*this += rhs;
	}
	return *this;
}

//move assignment
template<typename Val>
list<Val>& list<Val>::operator=(list<Val>&& rhs){
	std::cout << "move assignment called" << std::endl;
	if(this != &rhs){
		//free all memory allocated to this
		while(not empty()) pop_front();
		m_front = rhs.m_front;
		m_back = rhs.m_back;
		rhs.m_front = rhs.m_back = nullptr;
	}
	return *this;
}

template<typename Val>
typename list<Val>::node const * list<Val>::front() const {
    return m_front;
};

template<typename Val>
typename list<Val>::node const* list<Val>::back() const {
    return m_back;
};

template<typename Val>
void list<Val>::push_front(Val v){
    if (empty()){
        m_front = m_back = new node(v, nullptr);
        return;
    }
    m_front = new node {v, m_front};
};

template<typename Val>
void list<Val>::push_back(Val v){
    if (empty()){
        push_front(v);
        return;
    }
    m_back->next = new node{v, nullptr};
    m_back = m_back->next;
}

template<typename Val>
bool list<Val>::empty() const {
    return m_front == m_back == nullptr;
}

template<typename Val>
void list<Val>::pop_front(){
    if (empty()) return;
    node* aux = m_front;
    m_front = m_front->next;
    delete aux;
    if (m_front == nullptr) m_back = nullptr;
}

template<typename Val>
void list<Val>::pop_back(){
    if(m_front == m_back) pop_front();
    else {
        auto ptr = m_front;
        while(ptr->next != m_back) ptr = ptr->next;
        delete ptr->next;
        m_back = ptr;
        ptr->next = nullptr;
    }
}

template<typename Val>
bool list<Val>::operator==(list<Val> const& rhs) const{
    auto ptr1 = front();
    auto ptr2 = rhs.front;
    while(ptr1 or ptr2){
        if ((ptr1 and not ptr2) or (!ptr1 and ptr2) or (ptr1->val != ptr2->val))  return false;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;21
    }
}

template<typename Val>
bool list<Val>::operator!=(list<Val> const& rhs) const{
    return not (*this == rhs);
}

template<typename Val>
list<Val>& list<Val>::operator+=(list<Val> const& rhs){
    auto ptr = rhs.front();
    while(ptr){
        push_back(ptr->val);
        ptr=ptr->next;
    }
    return *this;
}

template<typename Val>
list<Val>& list<Val>::operator+=(Val const& rhs){
    push_back(rhs);
    return *this;
}

template<typename Val>
Val& list<Val>::operator[](uint64_t i){
    //l'operator [] non  è safe, non lancia eccezione se i > size
    uint64_t pos = 0;
    auto ptr = front();
    while(pos++ < i){
        ptr = ptr->next;
    }
    return ptr->val;
}

template<typename Val>
Val const& list<Val>::operator[](uint64_t i) const {
    //l'operator [] non  è safe, non lancia eccezione se i > size
    uint64_t pos = 0;
    auto ptr = m_front;
    while(pos++ < i){
        ptr = ptr->next;
    }
    return ptr->val;
}

template<typename Val>
std::ostream& operator<<(std::ostream& os, list<Val> const & list){
    if (list.empty()) return os;
    for (auto ptr = list.m_front; ptr != nullptr; ptr = ptr->next){
        os<<ptr->val;
        if(ptr->next) os << " -> ";
    }
    return os;
}

template<typename Val>
list<Val>& list<Val>::operator--(){
    //prefix. rimuovo prima cella lista
    pop_front();
    return *this;
}

template<typename Val>
list<Val>& list<Val>::operator--(int){
    //prefix. rimuovo prima cella lista
    pop_back();
    return *this;
}

template <typename Val>
void read_list(list<Val>& list) {
    uint64_t list_size = 0;
    Val v;
    std::cin >> list_size;                       // first read list_size
    for (uint64_t i = 0; i != list_size; ++i) {  // then value by value
        std::cin >> v;
        list.push_back(v);
    }
}

template <typename Val>
std::ostream& operator<<(std::ostream& os, list<Val> const& list) {
    if (list.empty()) return os;
    for (auto ptr = list.front(); ptr != nullptr; ptr = ptr->next) {
        os << ptr->val;
        if (ptr->next) os << " -> ";
    }
    return os;
}


//prefix decrement:  --l1
template<typename Val>
list<Val>& list<Val>::operator--(){
	//semantica: rimuovo la prima cella della lista e restituisco
	//un reference alla lista
	pop_front();
	return *this;
}

//postfix decrement:  l1--
template<typename Val>
list<Val>& list<Val>::operator--(int){
	//semantica: rimuovo l'ultima cella della lista e restituisco
	//un reference alla lista corrente
	pop_back();
	return *this;
}

// -------- implementazione di iterator :


template<typename Val>
list<Val>::iterator::iterator(node* p) : m_ptr(p) {}


//*it = 5
template<typename Val>
typename list<Val>::iterator::reference 
list<Val>::iterator::operator*() const{
	//restituire reference al Val contenuto nella cella 
	//puntata da m_ptr
	return m_ptr->val;
}

//nota: su list<int> l; l'operatore -> non ha senso (int è primitivo)
template<typename Val>
typename list<Val>::iterator::pointer 
list<Val>::iterator::operator->() const{
	//restituire un puntatore al Val contenuto nella cella 
	//puntata da m_ptr
	return &(m_ptr->val);
}


//prefix increment: ++it
//semantica: incrementa it (cella successiva) e restituisci it
template<typename Val>
typename list<Val>::iterator& 
list<Val>::iterator::operator++(){
	m_ptr = m_ptr->next;
	return *this;
}


//postfix increment: it++
//semantica: restituisci it e poi incrementalo
template<typename Val>
typename list<Val>::iterator 
list<Val>::iterator::operator++(int){
	iterator it = {m_ptr};
	++(*this);
	return it;
}


template<typename Val>
bool list<Val>::iterator::operator==(typename list<Val>::iterator const& rhs) const{
	//it1 == it2
	//true se e solo se it1 e it2 puntano alla stessa area di memoria 
	//dentro il container
	return m_ptr == rhs.m_ptr;
}

template<typename Val>
bool list<Val>::iterator::operator!=(typename list<Val>::iterator const& rhs) const{
	//it1 != it2
	//true se e solo se it1 e it2 puntano a due celle diverse 
	//dentro il container
	return m_ptr != rhs.m_ptr;
}

//cast da iterator a bool
//usati per esempio in guardie booleane: if(it)
template<typename Val>
list<Val>::iterator::operator bool() const {
	//true se e solo se l'iteratore punta ad una cella
	//non nullptr della lista
	return m_ptr != nullptr;
}


template<typename Val>
typename list<Val>::iterator 
list<Val>::begin(){
	//restituisco un nuovo iterator alla prima cella della lista
	return {m_front};
}

template<typename Val>
typename list<Val>::iterator 
list<Val>::end(){
	//restituisco un nuovo iterator alla cella nullptr
	return {nullptr};
}
