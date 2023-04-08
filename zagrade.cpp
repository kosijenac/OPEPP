#include <iostream>
#include <stack>
#include <string>

#define GOOD "ISPRAVNO"
#define BAD "NIJE ISPRAVNO"

using namespace std;

int main()
{
    string input;
    stack<char> zagrade;

    // Koristimo getline za slucaj da postoje razmaci u izrazu.
    getline(cin, input);

    for (char& c : input) {

        // Gledamo samo zagrade, sve ostale znakove zanemarujemo.
        // Svaku otvorenu zagradu stavljamo na stog, a za svaku
        // zatvorenu gledamo je li njena odgovarajuca otvorena
        // zagrada na vrhu stoga, te ako je skidamo ju.
        if (c == '(' || c == '[' || c == '{')
            zagrade.push(c);

        if (c == ')' || c == ']' || c == '}') {

            // Prvo provjerimo da je stog neprazan, jer inace
            // metoda top() moze imati nedefinirano ponasanje.
            if (!zagrade.empty() && (zagrade.top() == '(' && c == ')' || zagrade.top() == '[' && c == ']' || zagrade.top() == '{' && c == '}'))
                zagrade.pop();
            else {
                cout << BAD << endl;
                return 0;
            }
        }
    }
    // Jos treba provjeriti da je stog neprazan, jer inace znaci
    // da ima otvorenih zagrada koje nigdje nisu zatvorene.
    if (zagrade.empty())
        cout << GOOD << endl;
    else
        cout << BAD << endl;
    return 0;
}
