#include <iostream>
#include <string>

using namespace std;

char Jmbag_get_CD(string jmbag)
{
    if (jmbag.length() != 10 && jmbag.length() != 9)
        return 'X';
    else
        for (int n = 0; n < 9; n++)
            if (!isdigit(jmbag[n]))
                return 'X';
    static int JmbagPlaceWeights[] = { 2, 3, 4, 5, 1, 2, 3, 4, 5 };
    int sum = 0;
    int digit;
    for (int n = 0; n < 9; n++) {
        digit = jmbag[n] - '0';
        sum += digit * JmbagPlaceWeights[n];
    }
    int controlDigit = 11 - (sum % 11);
    if (controlDigit == 10)
        return 'X';
    else if (controlDigit == 11)
        controlDigit = 0;
    return controlDigit + '0';
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Uporaba: " << argv[0] << " JMBAG_bez_kontrolne_znamenke" << endl;
        return -1;
    }
    char CD = Jmbag_get_CD(argv[1]);
    if (CD == 'X') {
        cout << "Neispravan unos." << endl;
        return -2;
    }
    cout << "Kontrolna znamenka je " << CD << "." << endl;
    cout << "Cjelokupni JMBAG glasi: " << argv[1] << CD << endl;
}