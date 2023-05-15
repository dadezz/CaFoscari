/**
 * esercizio 1: sviluppare funzione merge
*/
#include<string>
using namespace std;
#include <stack>

#include<iostream>
struct Cell{
  int info;
  Cell* next;
};
typedef Cell* List;
void append(List& l, int elem) {
  if (l==nullptr) {
    l = new Cell{elem, nullptr};
  }
  else 
    append(l->next, elem);
}
void readlist(List& l) {
  int q, e;
  std::cin>>q;
  while (q>0) {
    std::cin>>e;
    append(l, e);
    q--;
  }
}
void destroy(List& l) {
  if (l) {
    destroy(l->next);
    delete l;
    l=nullptr;
  }
}
void printlist(List l) {
  if (l) {
    std::cout<<l->info<<std::endl;
    printlist(l->next);
  }
}


List merge(List l1, List l2) {
    List l3;
    if (l1 == nullptr and l2 == nullptr) return nullptr;
    List l = new Cell;
    if (l1 == nullptr) {
        l->info = l2->info;
        l->next = merge(l1, l2->next);
    }
    else if (l2 == nullptr) {
        l->info = l1->info;
        l->next = merge(l1->next, l2);
    }
    else{
        l->info = l2->info>l1->info ? l1->info : l2->info;
        l->next = l2->info>l1->info ? merge(l1->next, l2) : merge(l1, l2->next);
    }
    return l;
}

/**
 * esercizio 2: rendi lineare una lista circolare
*/
void linearize(List& l) {
    if (l == nullptr) return;
    if (l->next == l) {
        l->next = nullptr;
        return;
    }
    List aux = l;
    bool arrivato = false;
    while (aux->next) {
        if (aux->next == l) {
            aux->next = nullptr;
        }
        else aux = aux->next;
    }
}

/**
 * esercizio 3: parentesi bilanciate (maiuscole e minuscole) ABbCBbBbca
*/
bool bilanciata(string& s){
    bool condizione = true;
    stack<char> p;
    int i = 0;
    while(i<s.length() and condizione){
        if (s[i]<='Z') p.push(s[i]);
        else {
            if (s[i] != p.top()+32) {
                condizione = false;
            }
            if (p.empty()) condizione = false;
            else p.pop();
        }
        ++i;
    }
    if (p.empty() == false) condizione = false;
    return condizione;
}