#ifndef GRAF_H
#define GRAF_H

#include <fstream>

class Graf {
public:
    typedef int vrh;
    Graf();
    Graf(int);
    Graf(std::ifstream&);
    bool ima_vrh(vrh);
    Graf& ispis();
    Graf optimalni(vrh, vrh);

private:
};
#endif
