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