#include <iostream>
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
	    list(list<Val> const&); //copy constructor //const lvalue reference
        ~list(); // destructor
        list(list<Val>&&); //move constructor

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
        list<Val>& operator=(list<Val> && rhs); //move assigment: steal resources from rhs and assign them to the left operand
        list<Val>& operator=(list<Val> & rhs); //move assigment: steal resources from rhs and assign them to the left operand

        //copy assignment
        //x = y;
        //l1 = l2 = l3 = l4
        //l1 = (l2 = (l3 = l4))
        list<Val>& operator=(list<Val>const&);

        //move assignment
        //x = get_some();
        //semantics: steal resources from rhs and assign them
        //to the left operand (after freeing x)
        list<Val>& operator=(list<Val>&& rhs); //input: rvalue reference

        struct iterator{
            public:
                //tipi pubblici di list<Val>::iterator
                using iterator_category = std::forward_iterator_tag;
                using value_type = Val;
                using pointer = Val*;
                using reference = Val&;

                iterator(node*);//costruttore (serve a list<Val>::begin() e list<Val>::end())
                reference operator*() const; //*it
                //list<std::pair<int,int>> l;
                //l += std::pair<int,int> {1,2};
                //auto it = l.begin();
                //it->first;
                pointer operator->() const;
                iterator& operator++();//prefix increment   ++it
                iterator operator++(int);//postfix increment   it++

                bool operator==(iterator const&) const; //it1 == it2
                bool operator!=(iterator const&) const; //it1 != it2
                operator bool() const; //if(it)    è la sintassi così, definisco il casting

            private:
                node* m_ptr;
        };
        iterator begin();
	    iterator end();
};