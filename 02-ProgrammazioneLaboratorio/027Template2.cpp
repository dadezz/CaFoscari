/**
 * CONTINUAZIONE TEMPLATE 
 * 
 * cosa succede quando si compila un codice con template? il compilatore per noi genera il codice coi tipi giusti
 * 
 * abusi?
 * se si inizializza su N tipi, si moltiplica il codice di N volte.
 * È facile scrivere codice compatto che poi il compilatore fa esplodere in assembly
 * 
 * DIFFERENZE TRA MACRO E TEMPLATE
 * 
 * in C è solo sostituzione di codice, in fase di precompilazione, nei template avviene in fase di compilazione.
 * Oltretutto, i template sono un sistema turing completo, il compilatore stesso può eseguire codice coi template
 * 
 * Il compilatore può offrire specializzazioni più efficienti a seconda del tipo. Anche noi possiamo implementare in modo differente le operazioni 
 * a seconda del tipo che ci viene passato.
 * 
 * 
*/
#include<iostream>

/**
 * PARTE VECCHIA
template<typename T>
T max( const T& x , const T& y){
    return x > y ? x : y;
}

template<typename T , typename f>
bool is_eq(const T& x, const f& y){
    return x == y;
}

template<typename T , typename f>
struct mycont
{
    mycont(){}
    mycont( const T& val , const f& v) : m_val(val) , r_val(v){}
    void print(){ std::cout<<m_val<<" , "<<r_val<<std::endl;}
    void operator++(){ m_val -= 1;}
    int operator++(int){ int prev=m_val;m_val -= 6;return prev;}
    private:
        T m_val;
        f r_val;
};



int main(){
    int q = max<int>(3,4);
    float s = max<float>(3.12,1.1);
    char a = max<char>('a','b');
    if(is_eq((int)'a','a')) std::cout<<"funziona"<<std::endl;
    std::cout<<q<<" , "<<s<<" , "<<a<<std::endl;
    
    mycont<int,char> R(1,'a');
    R.print();
    R++;
    R.print();
    return 0;
}
*/
#include <vector>
template<typename T>
struct m_container{
    m_container() : m_data(nullptr), m_size(0){}
    ~m_container(){
        if(m_data) delete [] m_data;
    }

    template<typename Z>
    //t mette a disposizione membri "first" e "second"
    // T x;
    // x.first;
    // x.second;
    // il primo item va al first di x, il secondo va al second

    //esesmpio:  se items = {1, 2, 3, 4, 5, 6}
    // voglio che m_data sia un array lungo 3
    // m.data[0].first = 1;
    // m.data[0].second = 2;
    // m.data[1].first = 3;
    // m.data[1].second = 4;
    // etc
    void build_from(Z const* items, uint64_t n_items){
        //prendo in input un array<z> e ci riempio la mia variavile data
        m_size = n_items/2;
        m_data = new T[m_size];
        for(uint64_t i=0; i!=m_size; i++, items+=2){
            m_data[i].first = *items;
            m_data[i].second = *items+1;
        }
        //obv sta roba non funzia con tutti i tipi, T deve avere due campi first e second
    }

    void print(){
        //  questa funzione è probelmatica, non tutti i tipi hanno 
        // gli operatori di stream definiti
        for(uint64_t i=0; i<m_size;i++){
            std::cout<<m_data[i]<<" ";
        }
        std::cout<<std::endl;
    }
    private:
        T* m_data;
        uint64_t m_size;
};

typedef std::pair<int, int> my_pair;

std::ostream& operator<<(std::ostream& lhs, my_pair const& rhs){
    lhs<<"("<<rhs.first<<","<<rhs.second<<")";
    return lhs;
}

int main(){
    m_container<my_pair> x;
    std::vector<double> vec{1, 2, 3, 4, 5, 6};

    x.build_from<double>(vec.data(), vec.size());
    x.print();
    return 0;
}

/**
 * TEMPLATE NONTYPE
*/

template<typename T = double, int N = 100>
//è parametrizzata in base a un tipo e a un numero (conosciuto in fase di compilazione)
// se non viene passato tipo o N, viene automaticamente interpretato come duble e 100
struct myseq{
    private:
        T vec[N];
    public:
        void set(int i, T value){
            vec[i] = value;
        }
        T get(int i){
            return vec[i];
        }
};