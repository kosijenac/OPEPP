#ifndef POLINOM_H
#define POLINOM_H

#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class Polinom;

template <typename T>
ostream& operator<<(ostream&, const Polinom<T>&);
template <typename T>
istream& operator>>(istream&, Polinom<T>&);
template <typename T>
Polinom<T> operator+(const Polinom<T>&, const Polinom<T>&);
template <typename T>
Polinom<T> operator-(const Polinom<T>&, const Polinom<T>&);
template <typename T>
Polinom<T> operator*(const Polinom<T>&, const Polinom<T>&);
template <typename T>
Polinom<T> operator/(const Polinom<T>&, const Polinom<T>&);
template <typename T>
Polinom<T> operator%(const Polinom<T>&, const Polinom<T>&);

template <typename T>
class Polinom {
    friend ostream& operator<< <T>(ostream&, const Polinom<T>&);
    friend istream& operator>><T>(istream&, Polinom<T>&);
    template <typename U>
    friend Polinom<U> operator+(const Polinom<U>&, const Polinom<U>&);
    template <typename U>
    friend Polinom<U> operator-(const Polinom<U>&, const Polinom<U>&);
    template <typename U>
    friend Polinom<U> operator*(const Polinom<U>&, const Polinom<U>&);
    template <typename U>
    friend Polinom<U> operator/(const Polinom<U>&, const Polinom<U>&);
    template <typename U>
    friend Polinom<U> operator%(const Polinom<U>&, const Polinom<U>&);

public:
    Polinom();
    Polinom(unsigned);
    operator bool() const;
    Polinom& operator=(initializer_list<T>);
    Polinom& operator+=(const Polinom&);
    Polinom& operator-=(const Polinom&);
    Polinom& operator*=(const Polinom&);
    Polinom& operator/=(const Polinom&);
    Polinom& operator%=(const Polinom&);
    Polinom& operator++();
    Polinom& operator--();
    Polinom operator++(int);
    Polinom operator--(int);
    Polinom operator-() const;
    T& operator[](size_t);
    T operator[](size_t) const;
    double operator()(double) const;
    int stupanj() const; //-1 za nul-polinom
private:
    shared_ptr<map<unsigned, T>> koeficijenti;
};

/* ISPOD NAPISATI SVE POTREBNE DEFINICIJE */

template <typename T>
T& Polinom<T>::operator[](size_t i) { return (*this)[i]; }

template <typename T>
T Polinom<T>::operator[](size_t i) const
{
    auto it = (*(this->koeficijenti)).find(i);
    return (it == end(*(this->koeficijenti))) ? 0 : it->second;
}

template <typename T>
Polinom<T>::Polinom(unsigned deg)
{
    static normal_distribution<T> n(0., 1.);
    static default_random_engine e(time(0));
    this->koeficijenti = make_shared<map<unsigned, T>>(map<unsigned, T>());
    for (int i = 0; i <= deg; i++)
        (*this)[i] = n(e);
}

template <typename T>
Polinom<T>::Polinom() { this->koeficijenti = make_shared<map<unsigned, T>>(map<unsigned, T>()); }

template <typename T>
Polinom<T>::operator bool() const { return !(*(this->koeficijenti)).empty(); }

template <typename T>
int Polinom<T>::stupanj() const { return (*this) ? rbegin(*(this->koeficijenti))->first : -1; }

template <typename T>
ostream& operator<<(ostream& os, const Polinom<T>& p)
{
    if (!p)
        os << "0";
    else
        for (auto koef : *(p.koeficijenti))
            os << showpos << koef.second << "x^" << koef.first;
    return os;
}

template <typename T>
istream& operator>>(istream& is, Polinom<T>& p)
{
    p = Polinom<T>();
    string line;
    getline(is, line);
    stringstream ss(line);
    T koef;
    size_t i;
    while (ss >> koef >> i)
        p[i] += koef;
    for (auto& k : *(p.koeficijenti))
        if (k.second == 0)
            (*(p.koeficijenti)).erase(k.first);
    // int sign = line.find_first_of("+-#"), pow = line.find("x^");
    // while (pow != string::npos) {
    //     T koef = (T)line.substr(sign, pow - sign);
    //     sign = line.find_first_of("+-#", pow + 2);
    //     p[stoi(line.substr(pow + 2, sign - pow - 2))] += koef;
    // }
    return is;
}

template <typename T>
Polinom<T> operator+(const Polinom<T>& p, const Polinom<T>& q)
{
    Polinom<T> r(max(p.stupanj(), q.stupanj()));
    for (auto& koef : *(r.koeficijenti)) {
        koef.second = p[koef.first] + q[koef.first];
        if (koef.second == 0)
            (*(r.koeficijenti)).erase(koef.first);
    }
    return r;
}

template <typename T>
Polinom<T> Polinom<T>::operator-() const
{
    Polinom<T> r(this->stupanj());
    for (auto& koef : *(r.koeficijenti)) {
        koef.second = -(*this)[koef.first];
        if (koef.second == 0)
            (*(r.koeficijenti)).erase(koef.first);
    }
    return r;
}

template <typename T>
Polinom<T> operator-(const Polinom<T>& p, const Polinom<T>& q) { return p + (-q); }

template <typename T>
Polinom<T> operator*(const Polinom<T>& p, const Polinom<T>& q)
{
    Polinom<T> r(p.stupanj() + q.stupanj());
    for (auto& koef : *(r.koeficijenti)) {
        koef.second = 0;
        for (int i = 0; i <= koef.first; i++)
            koef.second += (p[i] * q[koef.first - i]);
        if (koef.second == 0)
            (*(r.koeficijenti)).erase(koef.first);
    }
    return r;
}

template <typename T>
Polinom<T>& Polinom<T>::operator=(initializer_list<T> list)
{
    int deg = 0;
    for (auto koef : list) {
        if (koef)
            koeficijenti[deg] = koef;
        deg++;
    }
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator+=(const Polinom& p)
{
    *this = (*this) + p;
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator-=(const Polinom& p)
{
    *this = (*this) - p;
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator*=(const Polinom& p)
{
    *this = (*this) * p;
    return *this;
}

/* Primjer1:
template<typename T>
Polinom<T>::Polinom() {
        ...
} */

/* Primjer2:
template<typename T>
Polinom<T> operator+(const Polinom<T> &lp,
                     const Polinom<T> &dp) {
        ...
} */

/* Primjer3:
template<typename T>
Polinom<T> Polinom<T>::operator--(int) {
        ...
} */

#endif