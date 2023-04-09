#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<string, int, string, double> proizvod;

proizvod najjeftiniji(vector<proizvod>& unos, const string& naziv)
{
    proizvod current(make_tuple("", -1, "", -1.0));
    double price = __DBL_MAX__;
    for (proizvod pr : unos)
        if (naziv == get<0>(pr) && get<3>(pr) / get<1>(pr) < price) {
            current = pr;
            price = get<3>(pr) / get<1>(pr);
        }
    return current;
}

int main()
{
    vector<proizvod> katalog;
    string line;
    while (getline(cin, line)) {
        string naziv, masa, proizv, cijena;
        stringstream ss(line);
        getline(ss, naziv, ';');
        getline(ss, masa, ';');
        getline(ss, proizv, ';');
        getline(ss, cijena, ';');
        katalog.push_back(make_tuple(naziv, stoi(masa), proizv, stod(cijena)));
    }
    cin.clear();
    string query;
    getline(cin, query);
    proizvod kandidat = najjeftiniji(katalog, query);
    if (get<1>(kandidat) == -1)
        cout << "Ne postoji proizvod s tim nazivom." << endl;
    else
        cout << "Naziv: " << get<0>(kandidat) << endl
             << "Gramaza: " << get<1>(kandidat) << " g" << endl
             << "Proizvodi: " << get<2>(kandidat) << endl
             << "Cijena: " << get<3>(kandidat) << " EUR" << endl;
}