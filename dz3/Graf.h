#ifndef GRAF_H
#define GRAF_H

#include <fstream>

class Graf {
    int n;
    int** bridovi;
    void init_bridovi(bool);

public:
    typedef int vrh;
    Graf();
    Graf(int);
    Graf(std::ifstream&);
    Graf(const Graf&);
    Graf& operator=(const Graf&);
    Graf(Graf&&) noexcept;
    Graf& operator=(Graf&&) noexcept;
    ~Graf();
    // Necemo setter za n jer bi mijenjanje n dok su bridovi vec postavljeni uzrokovalo nedef. ponasanje,
    int getBrVrhova() const;
    int getBrid(vrh, vrh) const;
    void setBrid(vrh, vrh, int);
    bool ima_vrh(vrh) const;
    const Graf& ispis() const;
    const Graf& optimalni(vrh, vrh) const;
    /**
     * Iako metode `ispis` i `optimalni` ne mijenjaju objekt, implementiramo i nekonstantne varijante
     * kako bi mogle vratiti referencu na nekonstantni objekt kako bismo omogucili ulancavanje metoda
     * koje mijenjaju objekt na objektima koji nisu const. Npr. `Obj.ispis().metodaKojaMijenjaObj();`
     */
    Graf& ispis();
    Graf& optimalni(vrh, vrh);
};

#endif