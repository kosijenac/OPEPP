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
T& Polinom<T>::operator[](size_t i) { return (*(this->koeficijenti))[i]; }

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
    for (size_t i = 0; i <= deg; i++)
        (*this)[i] = n(e);
}

template <typename T>
Polinom<T>::Polinom() { this->koeficijenti = make_shared<map<unsigned, T>>(map<unsigned, T>()); }

template <typename T>
Polinom<T>::operator bool() const { return !(*(this->koeficijenti)).empty(); }

template <typename T>
int Polinom<T>::stupanj() const { return (*this) ? rbegin(*(this->koeficijenti))->first : -1; }

template <typename T>
double Polinom<T>::operator()(double x) const
{
    int deg = this->stupanj();
    double result = (*this)[deg];
    for (deg = deg - 1; deg >= 0; deg--)
        result = result * x + (*this)[deg];
    return result;
}

template <typename T>
ostream& operator<<(ostream& os, const Polinom<T>& p)
{
    if (!p)
        os << "0";
    else
        for (auto koef : *(p.koeficijenti))
            os << showpos << koef.second << "x^" << koef.first << noshowpos;
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
    char sign, x, pot;
    while (ss >> sign >> koef >> x >> pot >> i)
        p[i] += (sign == '-' ? -koef : koef);
    for (auto& k : *(p.koeficijenti))
        if (k.second == 0)
            (*(p.koeficijenti)).erase(k.first);
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
Polinom<T> operator-(const Polinom<T>& p, const Polinom<T>& q)
{
    Polinom<T> r(max(p.stupanj(), q.stupanj()));
    for (auto& koef : *(r.koeficijenti)) {
        koef.second = p[koef.first] - q[koef.first];
        if (koef.second == 0)
            (*(r.koeficijenti)).erase(koef.first);
    }
    return r;
}

template <typename T>
Polinom<T> Polinom<T>::operator-() const { return Polinom<T>() - (*this); }

template <typename T>
Polinom<T> operator*(const Polinom<T>& p, const Polinom<T>& q)
{
    Polinom<T> r(p.stupanj() + q.stupanj());
    for (auto& koef : *(r.koeficijenti)) {
        koef.second = 0;
        for (size_t i = 0; i <= koef.first; i++)
            koef.second += (p[i] * q[koef.first - i]);
        if (koef.second == 0)
            (*(r.koeficijenti)).erase(koef.first);
    }
    return r;
}

template <typename T>
Polinom<T> operator/(const Polinom<T>& p, const Polinom<T>& q)
{
    if (!q)
        throw runtime_error("Nije dozvoljeno dijeljenje s nul-polinomom!");
    Polinom<T> r, t = p, m;
    while (t.stupanj() >= q.stupanj()) {
        m[t.stupanj() - q.stupanj()] = rbegin(*t.koeficijenti)->second / rbegin(*q.koeficijenti)->second;
        t -= m * q;
        r += m;
        m = Polinom<T>();
    }
    return r;
}

template <typename T>
Polinom<T> operator%(const Polinom<T>& p, const Polinom<T>& q)
{
    if (!q)
        throw runtime_error("Nije dozvoljeno dijeljenje s nul-polinomom!");
    Polinom<T> t = p, m;
    while (t.stupanj() >= q.stupanj()) {
        m[t.stupanj() - q.stupanj()] = rbegin(*t.koeficijenti)->second / rbegin(*q.koeficijenti)->second;
        t -= m * q;
        m = Polinom<T>();
    }
    return t;
}

template <typename T>
Polinom<T>& Polinom<T>::operator=(initializer_list<T> list)
{
    *this = Polinom<T>();
    int deg = 0;
    for (T koef : list) {
        if (koef)
            (*this)[deg] = koef;
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

template <typename T>
Polinom<T>& Polinom<T>::operator/=(const Polinom& p)
{
    *this = (*this) / p;
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator%=(const Polinom& p)
{
    *this = (*this) % p;
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator++()
{
    (*this)[0]++;
    return *this;
}

template <typename T>
Polinom<T>& Polinom<T>::operator--()
{
    (*this)[0]--;
    return *this;
}

template <typename T>
Polinom<T> Polinom<T>::operator++(int)
{
    Polinom<T> p = *this;
    ++*this;
    return p;
}

template <typename T>
Polinom<T> Polinom<T>::operator--(int)
{
    Polinom<T> p = *this;
    --*this;
    return p;
}

#endif