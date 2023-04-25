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
    bool ima_vrh(vrh);
    const Graf& ispis() const;
    const Graf& optimalni(vrh, vrh) const;
};

#endif