#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <utility>
#include <random>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include<climits>
#include <ctime>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::setw;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

template<typename T>
ostream &print_vector(const vector<T> &v, ostream &os)
{
    if (v.size() > 0)
    {
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << endl;
    }

    return os;
}

long int my_round(double d)
{
    return (d > 0.0) ? (d + 0.5) : (d - 0.5);
}

class Money
{
public:
    enum Currency
    {
        USD, CHF, KYD
    };
    Money() : cents(0), cur(USD) { }
    Money(long int c) : cents(c), cur(USD) { }
    Money(int d, int c) : cents(d * 100 + c), cur(USD)
    {
        if (c >= 100)
        {
            error("cents must be between 0 and 99");
        }
    }
    Money(long int c, Currency cur_val) : cents(c), cur(cur_val) { }
    Money(int d, int c, Currency cur_val) : cents(d * 100 + c), cur(cur_val)
    {
        if (c >= 100)
        {
            error("cents must be between 0 and 99");
        }
    }
    int get_dollars() const
    {
        return cents / 100;
    }
    int get_cents() const
    {
        return cents % 100;
    }
    long int cents;
    Currency cur;
};

double exch_rate(Money::Currency c1, Money::Currency c2)
{
    switch (c1)
    {
    case Money::USD:
        switch (c2)
        {
        case Money::CHF:
            return 1.11;
        case Money::KYD:
            return 1.22;
        default:
            error("exch_rate: illegal combination of currencies");
        }
    case Money::CHF:
        switch (c2)
        {
        case Money::USD:
            return 0.91;
        case Money::KYD:
            return 1.1;
        default:
            error("exch_rate: illegal combination of currencies");
        }
    case Money::KYD:
        switch (c2)
        {
        case Money::USD:
            return 0.82;
        case Money::CHF:
            return 0.91;
        default:
            error("exch_rate: illegal combination of currencies");
        }
    default:
        error("exch_rate: illegal combination of currencies");
    }
}

Money operator+(const Money &a, const Money &b)
{
    if (a.cur == b.cur)
    {
        return Money(a.cents + b.cents, a.cur);
    }

    double d = exch_rate(a.cur, b.cur);

    return Money(a.cents + my_round(d * double(b.cents)), a.cur);
}

Money operator-(const Money &a, const Money &b)
{
    if (a.cur == b.cur)
    {
        return Money(a.cents - b.cents, a.cur);
    }

    double d = exch_rate(a.cur, b.cur);

    return Money(a.cents - my_round(d * double(b.cents)), a.cur);
}

Money operator-(const Money &m)
{
    return Money(-m.cents, m.cur);
}

Money operator*(int n, const Money &m)
{
    return Money(n * m.cents, m.cur);
}

Money operator*(const Money &m, int n)
{
    return n * m;
}

Money operator/(const Money &m, int n)
{
    if (n == 0)
    {
        error("division by zero");
    }
    double d = double(m.cents) / n;
    long int c = my_round(d);
    return Money(c, m.cur);
}

ostream &operator<<(ostream &os, Money::Currency cur)
{
    switch (cur)
    {
    case Money::USD:
        return os << "USD";
    case Money::CHF:
        return os << "CHF";
    case Money::KYD:
        return os << "KYD";
    }
}

ostream &operator<<(ostream &os, const Money &m)
{
    os << m.cur << m.get_dollars() << '.';
    if (abs(m.get_cents()) < 10)
    {
        os << '0';
    }
    os << abs(m.get_cents());
    return os;
}

istream &operator>>(istream &is, Money &m)
{
    double d;
    string s;
    is >> s >> d;
    if (!is)
    {
        return is;
    }
    if (!(s == "USD" || s == "CHF" || s == "KYD"))
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    int i2 = int(d);
    double d2 = (d - i2) * 100.0;
    int i3 = int(d2);
    Money::Currency cur;
    if (s == "USD")
    {
        cur = Money::USD;
    }
    else if (s == "CHF")
    {
        cur = Money::CHF;
    }
    else if (s == "KYD")
    {
        cur = Money::KYD;
    }
    m = Money(i2, i3, cur);
    return is;
}

int main()
{
    try
    {
        Money m1;
        Money m2(105);
        Money m3(5, 12);

        cout << "m1: " << m1 << endl;
        cout << "m2(105): " << m2 << endl;
        cout << "m3(5, 12): " << m3 << endl;
        cout << "-m3: " << -m3 << endl;

        cout << m2 << " + " << m3 << " = " << m2 + m3 << endl;
        cout << m2 << " - " << m3 << " = " << m2 - m3 << endl;
        cout << "5 * " << m2 << " = " << 5 * m2 << endl;
        cout << m2 << " * 5 = " << m2 * 5 << endl;

        cout << m3 << " - " << m2 << " = " << m3 - m2 << endl;

        cout << Money(1, 0) << " / 7 = " << Money(1, 0) / 7 << endl;
        cout << Money(0, 9) << " / 6 = " << Money(0, 9) / 6 << endl << endl;

        m1 = Money(7, 12, Money::USD);
        m2 = Money(100, 5, Money::CHF);
        m3 = Money(55, 12, Money::KYD);
        cout << "m1 = " << m1 << endl;
        cout << "m2 = " << m2 << endl;
        cout << "m3 = " << m3 << endl << endl;
        cout << m1 << " + " << m2 << " = " << m1 + m2 << endl;
        cout << m1 << " + " << m3 << " = " << m1 + m3 << endl;
        cout << m2 << " + " << m1 << " = " << m2 + m1 << endl;
        cout << m2 << " + " << m3 << " = " << m2 + m3 << endl;
        cout << m3 << " + " << m1 << " = " << m3 + m1 << endl;
        cout << m3 << " + " << m2 << " = " << m3 + m2 << endl;
        cout << m3 << " - " << m2 << " = " << m3 - m2 << endl;
        cout << 3 << " * " << m2 << " = " << 3 * m2 << endl;
        cout << m3 << " / " << 17 << " = " << m3 / 17 << endl;
    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        return 2;
    }
}
