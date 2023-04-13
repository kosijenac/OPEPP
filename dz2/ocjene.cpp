#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef string jmbag;
typedef string predmet;

int main()
{
    map<jmbag, map<predmet, double>> tablica;
    vector<predmet> predmeti;
    string unos;
    while (cin >> unos) {
        predmeti.push_back(unos);
        ifstream popis(unos + ".txt");
        string line;
        while (getline(popis, line)) {
            stringstream ss(line);
            jmbag mb;
            ss >> mb;
            int sum = 0, count = 0, n;
            while (ss >> n) {
                sum += n;
                count++;
            }
            auto rez = tablica.find(mb);
            if (rez != tablica.end())
                rez->second.insert(make_pair(unos, count ? ((double)sum / count) : -1));
            else {
                map<predmet, double> singleton;
                singleton.insert(make_pair(unos, count ? ((double)sum / count) : -1));
                tablica.insert(make_pair(mb, singleton));
            }
        }
    }
    ofstream izlaz("izvjestaj.txt");
    izlaz << "\t\t";
    for (predmet pr : predmeti)
        izlaz << "\t" << pr;
    izlaz << endl;
    for (auto par : tablica) {
        izlaz << par.first;
        for (predmet pr : predmeti) {
            auto rez = par.second.find(pr);
            double avg = rez == par.second.end() ? -1 : rez->second;
            if (avg == -1)
                izlaz << "\t" << setw(pr.length()) << "-";
            else
                izlaz << "\t" << setw(pr.length()) << setprecision(3) << avg;
        }
        izlaz << endl;
    }
}