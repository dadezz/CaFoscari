/*Si scriva in C++ (specificando quale revisione del linguaggio si intende adottare) una classe generica matrix che
rappresenta matrici bidimensionali di valori di tipo T, dove T `e un tipo templatizzato. Tale classe deve comportarsi
come un valore, implementando lo stile della value-oriented programming e della generic programming. Inoltre
deve aderire al concept denominato Container da STL.*/

#include <vector>
using std::pair;
using std::vector;


template <class T>
class matrix {
private:
    vector<T> field;
    size_t c;

public:
    // costruttore di default
    matrix() : field(), c() {};
    // costruttore utile
    matrix(size_t rows, size_t cols) : field(rows*cols), c(cols) {};
    matrix(size_t rows, size_t cols, const T& filler) : field(rows*cols, filler), c(cols) {};
    // costruttore per copia
    matrix(const matrix<T>& ref) : field(ref.field), c(ref.c) {};
    // distruttore
    ~matrix(){};
    // operatore di assegnamento
    matrix<T>& operator=(const matrix<T>& ref) {
        field = ref.field;
        c = ref.c;
        return *this;
    }
    // operatore di accesso tramite riga e colonna: implementare 2 overload (const e non-const) di operator()
    const T& operator(size_t row, size_t col) const {
        return field[row * c + col];
    }
    T& operator(size_t row, size_t col) {
        return field[row * c + col];
    }
    //member type iterator, const_iterator, value_type, reference, const_reference e pointer;
    typedef T value_type;
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    //metodi begin() ed end(): 2 overload (const e non-const) per poter iterare tutta la matrice come
    //un unico container lineare dall’angolo superiore sinistro all’angolo inferiore destro come se fosse piatta;
    iterator begin() {
        return field.begin();
    }
    iterator end() {
        return field.end();
    }
    const_iterator begin() const {
        return field.begin();
    }
    const_iterator end() const {
        return field.end();
    }
    //altri metodi che si ritengono utili
    pair<size_t, size_t> size() const noexcept {
        return pair<size_t, size_t>{c, field.size/c};
    }
    matrix<T>& operator+(const matrix<T>& ref) const{
        if (this->size() != ref.size())
            throw std::invalid_argument("Matrices must be of the same size");
        matrix<T> ret(size().first, size().second);
        auto it = begin();
        auto ref_it = ref.begin();
        auto ret_it = ret.begin();
        while(it != end()){
            *ret_it = *it + *ref_it;
            it++; ref_it++; ret_it ++
        }
        return ret;
    }
};

