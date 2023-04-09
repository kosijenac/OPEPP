#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s("123g"), t("12.3EUR");
    cout << stoi(s) << endl
         << stod(t) << endl;
}