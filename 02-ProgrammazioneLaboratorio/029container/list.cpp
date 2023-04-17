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
