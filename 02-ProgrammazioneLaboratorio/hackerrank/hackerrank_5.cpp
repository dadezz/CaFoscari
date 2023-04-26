#include<iostream>
#include<string>

using namespace std;

/*Classe lista di stringhe ordinate alfabeticamente in modo
 * crescente. La lista e' doppiamente concatenata*/

class ListStrings{
public:
  ListStrings();
  ListStrings(ListStrings&& ls);
  ~ListStrings();
  void print_forward() const;
  void print_reversed() const;
  void add(const string& s);
  ListStrings& operator=(const ListStrings& ls);
  ListStrings operator+(const ListStrings& ls) const;
private:
  struct Cell{
    string info;
    Cell* next;
    Cell* prev;
  };
  Cell* head; //puntatore alla prima cella
  Cell* tail; //puntatore all'ultima cella
};


//Default constructor
ListStrings::ListStrings() {
  head = nullptr;
  tail = nullptr;
}


//Move constructor
ListStrings::ListStrings(ListStrings&& ls) {
  std::cout<<"Move costructor"<<endl;
  head = ls.head;
  tail = ls.tail;
  ls.head = nullptr;
  ls.tail = nullptr;
}

//stampa da head a tail
void ListStrings::print_forward() const{
  Cell* ptr=head;
  while (ptr) {
    cout<<ptr->info<<endl;
    ptr = ptr->next;
  }
}

//stampa da tail a head
void ListStrings::print_reversed() const{
  Cell* ptr=tail;
  while(ptr) {
    cout<<ptr->info<<endl;
    ptr=ptr->prev;
  }
}


//Destructor: 
ListStrings::~ListStrings() {    
    while(tail){
        Cell* aux = tail;
        tail = tail->prev;
        delete aux;
    }
}

bool minore (const string& stringa1, const string& stringa2) {
    // return true if string1 < string2;
    bool equal = true;
    bool minore = true;
    int i=0;
    while(equal and i<stringa1.size() and i<stringa2.size()){
        if (stringa1[i] != stringa2[i]) {
            equal = false;
            if (stringa1[i]>stringa2[i]) minore = false;
        }
        i++;
    }
    return minore;
}


void ListStrings::add(const string& s) {
    if (head == nullptr){
        head = new Cell;
        head->info = s;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
        return ;
    }
    if (minore(s, head->info)){
        Cell* aux = new Cell;
        aux->info = s;
        aux->next = head;
        aux->prev = nullptr;
        head->prev = aux;
        head = aux;
        return ;
    }
    if (minore(tail->info, s)){
        Cell* aux = new Cell;
        aux->info = s;
        aux->next = nullptr;
        aux->prev = tail;
        tail->next = aux;
        tail = aux;
        return ;
    }
    Cell* prima = head;
    Cell* seconda = head->next;
    bool inserita = false;
    while((seconda != nullptr) and (not inserita)){
        if (minore(prima->info, s) and minore(s, seconda->info)){
            Cell* nuova = new Cell;
            nuova->info = s;
            nuova->next = seconda;
            nuova->prev = prima;
            prima->next = nuova;
            seconda->prev = nuova;
            inserita = true ;
        }
        seconda = seconda->next;
        prima = prima->next;
    }
}
       
ListStrings& ListStrings::operator=(const ListStrings& ls) {
    if (head == ls.head) return *this;
    while(tail){
        Cell* aux = tail;
        tail = tail->prev;
        delete aux;
    }
    head = tail = nullptr;
    if (ls.head == nullptr) return *this;
    tail = head = new Cell;
    head->prev = head->next = nullptr;
    tail->info = ls.head->info;
    Cell* node = ls.head->next;
    while(node){
        Cell* nuova = new Cell;
        nuova->prev = tail;
        nuova->info = node->info;
        nuova->next = nullptr;
        tail = tail->next = nuova;
        node = node->next;
    }
    return *this;
}

ListStrings ListStrings::operator+(const ListStrings& ls) const {
    ListStrings res;
    Cell* node = head;
    while(node){
        res.add(node->info);
        node = node->next;
    }
    node = ls.head;
    while(node){
        res.add(node->info);
        node = node->next;
    }
    return res;
}

int main() {
  int n1,n2;
  string s;
  ListStrings ls1;
  ListStrings ls2;
  ListStrings res;

  cin >> n1;
  cin >> n2;

  for (; n1>0; n1--) {
    cin>>s;
    ls1.add(s);
  }

  for (; n2>0; n2--) {
    cin>>s;
    ls2.add(s);
  }

  res = ls1+ls2;

  cout<<"Stampo la prima lista"<<endl;
  ls1.print_forward();
  cout<<endl;
  ls1.print_reversed();
  cout<<"Stampo la seconda lista"<<endl;
  ls2.print_forward();
  cout<<endl;
  ls2.print_reversed();
  cout<<"Stampo la lista somma"<<endl;
  res.print_forward();
  cout<<endl;
  res.print_reversed();


  return 0;
}

