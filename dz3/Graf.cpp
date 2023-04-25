#include "Graf.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>

Graf::Graf()
{
    n = 0;
    bridovi = nullptr;
}
void Graf::init_bridovi(bool setToMax = true)
{
    bridovi = (int**)malloc(n * sizeof(int*));
    for (vrh i = 0; i < n; i++) {
        bridovi[i] = (int*)malloc(n * sizeof(int));
        if (setToMax)
            for (vrh j = 0; j < n; j++)
                bridovi[i][j] = __INT_MAX__;
    }
}
Graf::Graf(int br_vrhova)
{
    n = br_vrhova;
    init_bridovi();
}
Graf::Graf(std::ifstream& fs)
{
    std::string n_str;
    getline(fs, n_str);
    n = stoi(n_str);
    init_bridovi();
    std::string line;
    while (getline(fs, line)) {
        std::stringstream ss(line);
        int first, second, price;
        ss >> first >> second >> price;
        bridovi[first][second] = price;
    }
}
Graf::Graf(const Graf& original)
    : n(original.n)
{
    init_bridovi(false);
    for (vrh i = 0; i < n; i++)
        for (vrh j = 0; j < n; j++)
            bridovi[i][j] = original.bridovi[i][j];
}
Graf& Graf::operator=(const Graf& rhs)
{
    if (this == &rhs)
        return *this;
    for (vrh i = 0; i < n; i++)
        free(bridovi[i]);
    free(bridovi);
    n = rhs.n;
    init_bridovi(false);
    for (vrh i = 0; i < n; i++)
        for (vrh j = 0; j < n; j++)
            bridovi[i][j] = rhs.bridovi[i][j];
    return *this;
}
Graf::Graf(Graf&& donor) noexcept
    : n(donor.n)
    , bridovi(donor.bridovi)
{
    donor.n = 0;
    donor.bridovi = nullptr;
}
Graf& Graf::operator=(Graf&& rhs) noexcept
{
    if (this == &rhs)
        return *this;
    for (vrh i = 0; i < n; i++)
        free(bridovi[i]);
    free(bridovi);
    n = rhs.n;
    bridovi = rhs.bridovi;
    rhs.n = 0;
    rhs.bridovi = nullptr;
    return *this;
}
Graf::~Graf()
{
    // std::cout << "I'm a destructor!" << std::endl;
    for (vrh i = 0; i < n; i++)
        free(bridovi[i]);
    free(bridovi);
}
int Graf::getBrVrhova() const { return n; }
int Graf::getBrid(vrh a, vrh b) const { return ima_vrh(a) && ima_vrh(b) ? bridovi[a][b] : __INT_MAX__; }
void Graf::setBrid(vrh a, vrh b, int cijena) { bridovi[a][b] = cijena; }
bool Graf::ima_vrh(vrh x) const
{
    // Ako ne zelimo promatrati izolirane vrhove, odkomentiramo donji dio.
    // for (vrh i = 0; i < n; i++)
    //     if (bridovi[i][x] != __INT_MAX__ || bridovi[x][i] != __INT_MAX__)
    //         return true;
    // return false;
    return 0 <= x && x < n;
}
const Graf& Graf::ispis() const
{
    for (vrh i = 0; i < n; i++)
        for (vrh j = 0; j < n; j++)
            if (bridovi[i][j] != __INT_MAX__)
                std::cout << "(" << i << "," << j << ") = " << bridovi[i][j] << std::endl;
    return *this;
}
const Graf& Graf::optimalni(vrh a, vrh b) const
{
    int* udaljenost = (int*)malloc(n * sizeof(int));
    vrh* prethodnik = (vrh*)malloc(n * sizeof(vrh));
    for (vrh i = 0; i < n; i++) {
        udaljenost[i] = __INT_MAX__;
        prethodnik[i] = -1;
    }
    udaljenost[a] = 0;
    for (int _ = 1; _ < n; _++)
        for (vrh i = 0; i < n; i++)
            for (vrh j = 0; j < n; j++)
                if (bridovi[i][j] != __INT_MAX__ && udaljenost[i] != __INT_MAX__
                    && udaljenost[i] + bridovi[i][j] < udaljenost[j]) {
                    udaljenost[j] = udaljenost[i] + bridovi[i][j];
                    prethodnik[j] = i;
                }
    if (udaljenost[b] == __INT_MAX__) {
        std::cout << "Ne postoji put od " << a << " do " << b << "." << std::endl;
        free(udaljenost);
        free(prethodnik);
        return *this;
    }
    for (vrh v = 0; v < n; v++) {
        vrh u = prethodnik[v];
        if (u >= 0 && udaljenost[u] + bridovi[u][v] < udaljenost[v]) {
            std::cout << "Postoji negativan ciklus!" << std::endl;
            free(udaljenost);
            free(prethodnik);
            return *this;
        }
    }
    std::cout << "Optimalni put od " << a << " do " << b << " ima cijenu " << udaljenost[b] << ".";
    std::cout << "\nIspis optimalnog puta (unatrag): ";
    for (vrh v = b; v != a; v = prethodnik[v])
        std::cout << v << ", ";
    std::cout << a << std::endl;
    free(udaljenost);
    free(prethodnik);
    return *this;
}
// Kako su metode ispis i optimalni iste neovisno o konstantnosti, donje dvije dobivamo castanjem.
Graf& Graf::ispis() { return const_cast<Graf&>(const_cast<const Graf*>(this)->ispis()); }
Graf& Graf::optimalni(vrh a, vrh b)
{
    return const_cast<Graf&>(const_cast<const Graf*>(this)->optimalni(a, b));
}