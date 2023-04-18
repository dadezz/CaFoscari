#include <iostream>;
#pragma once


template<typename Val>
class list{
    private:
        struct node{
            Val val;
            node* next;
        };
        node* m_front;
        node* m_back;
    public:
        list(); // default constructor
        list(Val v); // list of one element
        ~list(); // destructor

        node const* front() const; // return pointer to const first cell
        node const* back() const; // return pointer to const last cell

        void push_front(Val v); // adds v at the beginning of the list
        void push_back(Val v); // adds v at the endof the list

        void pop_front(); //removes first element of the list
        void pop_back(); //removes last element of the list

        bool empty() const; // true !if the list is empty

        bool operator==(list<Val>const & rhs) const ; // check if *this is equal to rhs: l1 == l2 -> l1 is this, l2 is rhs
        bool operator!=(list<Val>const & rhs) const ; // check if *this is not equal to rhs: l1 != l2 -> l1 is this, l2 is rhs

        list<Val>& operator+=(list<Val> const& rhs); // list += list : append rhs to *this, without modifying rhs
        list<Val>& operator+=(Val const& rhs); // list += Val : append rhs to *this, without modifying rhs. equals to push_back
        Val& operator[](uint64_t i); // list[i]: Val reference in i position (not const: list[i] = x allowed)
        Val const& operator[](uint64_t i) const; // list[i]: Val reference in i position, const.
        list<Val>& operator--(); // PREFIX removes first element (equals to pop-front)
        list<Val>& operator--(int); // POSTFIX removes first element (equals to pop-front)

};