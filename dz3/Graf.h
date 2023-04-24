#ifndef GRAF_H
#define GRAF_H

#include <fstream>

class Graf {
    int n;
    int** bridovi;

public:
    typedef int vrh;
    Graf();
    Graf(int);
    Graf(std::ifstream&);
    ~Graf();
    bool ima_vrh(vrh);
    Graf& ispis();
    Graf optimalni(vrh, vrh);
};

#endif