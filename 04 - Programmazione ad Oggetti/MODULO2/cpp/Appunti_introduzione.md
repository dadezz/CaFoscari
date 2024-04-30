# C++

È un linguaggio enormemente più difficile di Java. 
inizieremo con lo standard del 2003, aggiungendo man mano cose fino al c++20.

È un linguaggio multiparadigma e con tanti stili. in primis è compatibile con C (procedurale imperativo). Inizieremo comunque con la parte OOP di c++. Perché una volta imparata non dovremo più usarla in quanto fa schifo xD. C++ è una figata ma l'OOP non è il top, molto più interessante il generic programming.
Nato per aggiungere gli oggetti a C, ormai quasi nessuno li usa più. Lo stile classico di programmazione c++ non è più OOP.
Estendendo C, c++ ha i pointer espliciti.

Naming convention: tutto snake case

in c++ OOP ci sono solo private, protected, public.

Inizializzazione dei campi: in java è `animal (int w) {weight = w;}`. In c++ si può dare ma non si fa. meglio usare le liste di inizializzazione. La sintassi è nome metodo (senza tipo di ritorno), aperta tonda, parametri, chiusa tonda, due punti, nome campo e tra parentesi l'espressione con cui inizializzare il campo, separati da virgola. si chiude con le graffe.

Un metodo per essere overridabile deve avercelo abilitato esplicitamente. come? con `virtual`

```cpp

#include <iostream>

class animal {
    // a differenze di java, public e private sono a blocchi, non da specificare per ogni campo
private:
    int weight;
    double speed;

public:
    animal (int w, double sp) : weight(w), speed(sp) {}
    animal(const anoimal& a) : weight(a.weight), speed(a.speed) {}
    int get_weight() {
        return weight;
    }

    virtual void eat(const animal& a){  // di base passo tutto per const reference. poi eventualmente tolgo const o addirittura la reference
        // metodo virtual -> overridabile. si chiama virtual per via della virtual table (solo quelli con override è necessario siano in virtual table)
    }
};


```

come ereditare/ estendere classe?

```cpp
class dog : public animal {

}
```

cosa vuol dire public/private/protected? è la subsumption. In java siamo abituati che chiunque può subsumere dog a animal. con private, posso far subsumere solo io, evitando che altri sappiano che sono sottotipo. etc con gli altri modificatori di visibilità

tornando a parlare di liste di inizializzazione, in cpp non assegni i campi, li costruisci.
ci sono due modi per costruire un oggetto

```cpp
typename animal* a1 = new animal(7, 2.34); // new ritorna un pointer. viene costruito nello heap

// quando dichiaro una variabile di tipo int, in cpp alloca memoria nello stack e costruisce a 0
// in pratica, in Cpp non si dichiara mai, ma si costruisce sempre col default constructor (in C non viene inizializzata, in cpp si)
int a;

// ecco che 
typename animal a2; 
// non va bene perché non ho ancora definito un costruttore senza parametri.

typename animal a2(7, 2.34); // viene costruito sullo stack
```

copy constructor. qual è la differenza tra ste due righe?

```cpp
animal a3(a2);
typename animal* a4 = new typename animal(a2);
```

il primo è sullo stack, il secondo sullo heap;
riga 73: sto passando un animal sullo stack, non pointer. la semantica l'ho definita io ed è il copy constructor. ora si capisce il percHé della lista di inizializzazione:
sto invocando i costruttori dei miei campi; in particolare il copy constructor di ogni campo

come fa cpp il polimorfismo?

```cpp
class dog : public animal {
    private:
        bool has_pedigree;
    public: 
        dog(int w, double sp, bool ped) : animal(w, sp), has_pedigree(ped) {}
        void eat(const animal& a){
            weight += a.weight / 2; // mi serve che weight diventi protected
                                    // a.weight è inaccessibile: in cpp il campo protected lo è SOLO per this: gli altri come te non lo possono vedere. Mi tocca usare un getter, unico modo
            has_pedigree = !a.has_pedigree; // non esiste has_pedigree: sta mangiando un animal non un dog
        }

        // in cpp-11 si puo mettere alla fine la keyword override per avvisare il compilatore
        // se vglio continuare a permettere l'override devocontinuare a mettere virtual. non mettere nulla equivale a scrivere final in java
}
```

in cpp non si usano i getter, si usano degli access methods che possono essere utlizzati anche come left value

```cpp
    const int& weight() const {
        return weight;
    }
    int& weight() {
        return weight;
    }
```
qual è la semantica del primo? ritorno il valore non come copia, ma ritorno esattamente il mio campo. con const garantisco che non venga cambiato.
il metodo successivo cambia, non è più const (il this) -> chi riceve può modificarmi il campo

subsumption: i valori non subsumono, reference e pointer si
