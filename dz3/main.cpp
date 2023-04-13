#include "Graf.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* Graf f(const Graf& G) {
    Graf H = G;
    return H;
} */

int main()
{
    string naziv;
    cout << "Unesite naziv datoteke (bez .txt): ";
    cin >> naziv;
    ifstream dat(naziv + ".txt");
    if (!dat) {
        cout << "Ne mogu otvoriti datoteku "
             << naziv << ".txt!" << endl;
        return -1;
    }
    Graf G(dat);
    /* Graf J;
    const Graf H(G);
    J = J = H;
    G = f(J); */
    Graf::vrh pocetni, zavrsni;
    cout << "Unesite pocetni vrh: " << endl;
    cin >> pocetni;
    cout << "Unesite zavrsni vrh: " << endl;
    cin >> zavrsni;
    if (!G.ima_vrh(pocetni) || !G.ima_vrh(zavrsni))
        cout << "Neki od unesenih vrhova"
                " nije u grafu!"
             << endl;
    else {
        cout << "Ispis grafa:" << endl;
        G.ispis().optimalni(pocetni, pocetni).optimalni(pocetni, zavrsni);
        /* H.ispis().optimalni(pocetni,pocetni)
            .optimalni(pocetni,zavrsni); */
    }

    return 0;
}
