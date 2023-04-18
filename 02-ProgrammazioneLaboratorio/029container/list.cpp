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
*/

/**
 * creeremo un container di una lista<val> single linked, che finisce a nullptr.
 * teniao puntatore ahead e a tail
 * 
 * vogliamo sovrascrivere <<, >>, +=, !=, ==, [], 
*/

#include "list.hpp"

template<typename Val>
list<Val>::list() : m_front(nullptr), m_back(nullptr){};

template<typename Val>
list<Val>::list(Val v) : list() {
    m_back = m_front = new node {v, nullptr};
    // sostituibile con push_front(v);
};

template<typename Val>
list<Val>::~list(){
    while (not empty()) pop_front();    
};

template<typename Val>
typename list<Val>::node const* list<Val>::front() const {
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