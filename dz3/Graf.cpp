#include "Graf.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdlib.h>

Graf::Graf() { }
Graf::Graf(int n) { }
Graf::Graf(std::ifstream& fs)
{
    fs >> n;
    bridovi = (int**)malloc(n * sizeof(int*));
    for (vrh i = 0; i < n; i++) {
        bridovi[i] = (int*)malloc(n * sizeof(int));
        for (vrh j = 0; j < n; j++)
            bridovi[i][j] = __INT_MAX__;
    }
    std::string line;
    while (getline(fs, line)) {
        std::stringstream ss(line);
        int first, second, price;
        ss >> first >> second >> price;
        bridovi[first][second] = price;
    }
}
Graf::~Graf()
{
    for (vrh i = 0; i < n; i++)
        free(bridovi[i]);
    free(bridovi);
}
bool Graf::ima_vrh(vrh x)
{
    // for (vrh i = 0; i < n; i++)
    //     if (bridovi[i][x] != __INT_MAX__ || bridovi[x][i] != __INT_MAX__)
    //         return true;
    // return false;
    return 0 <= x && x < n;
}
Graf& Graf::ispis()
{
    for (vrh i = 0; i < n; i++)
        for (vrh j = 0; j < n; j++)
            if (bridovi[i][j] != __INT_MAX__)
                std::cout << "(" << i << "," << j << ") = " << bridovi[i][j] << std::endl;
    return *this;
}
Graf Graf::optimalni(vrh a, vrh b)
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
    // std::cout << udaljenost[b] << std::endl;
    if (udaljenost[b] == __INT_MAX__) {
        std::cout << "Ne postoji put od " << a << " do " << b << "." << std::endl;
        free(udaljenost);
        free(prethodnik);
        return *this;
    }
    for (vrh v = 0; v < n; v++) {
        vrh u = prethodnik[v];
        // std::cout << udaljenost[u] << "," << bridovi[u][v] << "," << udaljenost[v] << std::endl;
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