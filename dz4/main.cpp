// #include "Polinom.h"
#include <initializer_list>
#include <iostream>
/* gornju liniju zamijenite donjom ako
   testirate parametriziranu verziju */
#include "Polinom-template.h"

using namespace std;

int main()
{
    // Polinom p1(5), p, q;
    /* gornju liniju zamijenite donjom ako
       testirate parametriziranu verziju */
    Polinom<float> p1(5), p, q;
    cout << "Slucajno generirani polinom:\n"
         << p1 << endl;
    // cin >> p1;
    // cout << "Ucitani polinom: " << p1
    //      << " (stupanj polinoma: " << p1.stupanj()
    //      << ")" << endl;

    // p = { 2, 3, 0, 0, 5 };
    // p[6] = 1;
    // q = { 0, 0, 2, -1, 4 };
    // cout << "p(x) = " << p << endl;
    // cout << "q(x) = " << q << endl;
    // cout << "(-q)(x) = " << -q << endl;
    // cout << "p(2.3) = " << p(2.3) << endl;
    // cout << "(p++)(x) = " << p++ << endl;
    // cout << "(++p)(x) = " << ++p << endl;
    // cout << "(q--)(x) = " << q-- << endl;
    // cout << "(--q)(x) = " << --q << endl;

    // cout << "(p+q)(x) = " << p + q << endl;
    // cout << "(p-q)(x) = " << p - q << endl;
    // cout << "(p*q)(x) = " << p * q << endl;
    // cout << "(p/q)(x) = " << p / q << endl;
    // cout << "(p%q)(x) = " << p % q << endl;

    // cout << "p += q => p(x) = " << (p += q) << endl;
    // cout << "p -= q => p(x) = " << (p -= q) << endl;
    // cout << "p *= q => p(x) = " << (p *= q) << endl;
    // cout << "p /= q => p(x) = " << (p /= q) << endl;
    // cout << "p %= q => p(x) = " << (p %= q) << endl;

    // q = { 0 };
    // cout << "q(x) = " << q << endl;
    // if (q)
    //     cout << "q nije nul-polinom" << endl;
    // else
    //     cout << "q je nul-polinom" << endl;
    // cout << "(p/q)(x) = ";
    // try {
    //     cout << p / q << endl;
    // } catch (runtime_error greska) {
    //     cout << greska.what() << endl;
    // }
    // cout << "(p%q)(x) = ";
    // try {
    //     cout << p % q << endl;
    // } catch (runtime_error greska) {
    //     cout << greska.what() << endl;
    // }

    return 0;
}
