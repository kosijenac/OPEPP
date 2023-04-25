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
    int getBrVrhova() const;
    int getBrid(vrh, vrh) const;
    void setBrid(vrh, vrh, int);
    bool ima_vrh(vrh) const;
    const Graf& ispis() const;
    const Graf& optimalni(vrh, vrh) const;
    Graf& ispis();
    Graf& optimalni(vrh, vrh);
};

#endif