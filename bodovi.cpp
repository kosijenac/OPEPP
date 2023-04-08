#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct natjecatelj {
    string zaporka;
    vector<int> bodovi;
    string ime;
};

int main()
{
    unordered_map<string, natjecatelj> natjecatelji;
    string line;
    while (getline(cin, line)) {
        natjecatelj novi;
        stringstream ss(line);
        string rijec;
        getline(ss, rijec, ' ');
        novi.zaporka = rijec;
        for (int i = 0; i < 5; i++) {
            getline(ss, rijec, ' ');
            novi.bodovi.push_back(stoi(rijec));
        }
        getline(ss, rijec);
        novi.ime = rijec;
        natjecatelji.insert(make_pair(novi.zaporka, novi));
    }
    for (int i = 0; i < natjecatelji.bucket_count(); i++) {
        if (natjecatelji.bucket_size(i) == 0)
            continue;
        cout << "Pretinac br. " << i << ": ";
        unordered_map<string, natjecatelj>::local_iterator it;
        for (it = natjecatelji.begin(i); it != natjecatelji.end(i); ++it) {
            cout << "Zaporka: " << it->first << ", Bodovi: ";
            for (int j = 0; j < 5; j++)
                cout << it->second.bodovi.at(j) << ", ";
            cout << "Ime: " << it->second.ime << endl;
        }
        cout << endl;
    }
    cout << "Unesite zaporku natjecatelja: ";
    string query;
    cin >> query;
    natjecatelj& target = natjecatelji.find(query)->second;
    for (int i = 0; i < 5; i++)
        cout << "Bodovi na " << (i + 1) << ". zadatku: " << target.bodovi.at(i) << endl;
    cout << "Ime i prezime: " << target.ime << endl;
}