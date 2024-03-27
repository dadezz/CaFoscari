class Insieme {
    public:
        Insieme();
        Insieme(const Insieme& set);
        ~Insieme();
        void inserisci(int val);
        void cancella(int val);
        bool contiene(int val) const;
        int numElementi() const;
        Insieme unione(const Insieme& I_2) const;
        Insieme intersezione(const Insieme& I_2) const;
        Insieme differenza(const Insieme& I_2) const;
        void stampa() const;
    private:
        struct Impl;
        Impl* pimpl;
};
