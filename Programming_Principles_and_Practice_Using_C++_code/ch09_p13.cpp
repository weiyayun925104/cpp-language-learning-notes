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

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

class Rational
{
public:
    Rational() : numer(0), denom(1) { }
    Rational(int n) : numer(n), denom(1) { }
    Rational(int n, int d) : numer(n), denom(d)
    {
        normalise();
    }

    int get_numer() const
    {
        return numer;
    }
    int get_denom() const
    {
        return denom;
    }
    double conv_double() const
    {
        return double(numer) / denom;
    }

    void normalise()
    {
        if (denom == 0)
        {
            error("denominator is zero");
        }
        if (denom < 0)
        {
            denom = -denom;
            numer = -numer;
        }
        int n = gcd(numer, denom);
        if (n > 1)
        {
            numer /= n;
            denom /= n;
        }
    }

private:
    int numer;
    int denom;
};

Rational operator+(const Rational &r1, const Rational &r2);
Rational operator-(const Rational &r1, const Rational &r2);
Rational operator*(const Rational &r1, const Rational &r2);
Rational operator/(const Rational &r1, const Rational &r2);
bool operator==(const Rational &r1, const Rational &r2);
bool operator!=(const Rational &r1, const Rational &r2);
ostream &operator<<(ostream &os, const Rational &r);

Rational operator+(const Rational &r1, const Rational &r2)
{
    Rational r(r1.get_numer()*r2.get_denom() + r1.get_denom()*r2.get_numer(),
               r1.get_denom()*r2.get_denom());
    r.normalise();
    return r;
}

Rational operator-(const Rational &r1, const Rational &r2)
{
    Rational r(r1.get_numer()*r2.get_denom() - r1.get_denom()*r2.get_numer(),
               r1.get_denom()*r2.get_denom());
    r.normalise();
    return r;
}

Rational operator*(const Rational &r1, const Rational &r2)
{
    Rational r(r1.get_numer()*r2.get_numer(), r1.get_denom()*r2.get_denom());
    r.normalise();
    return r;
}

Rational operator/(const Rational &r1, const Rational &r2)
{
    Rational r(r1.get_numer()*r2.get_denom(), r1.get_denom()*r2.get_numer());
    r.normalise();
    return r;
}

bool operator==(const Rational &r1, const Rational &r2)
{
    return r1.get_numer() * r2.get_denom() == r1.get_denom() * r2.get_numer();
}

bool operator!=(const Rational &r1, const Rational &r2)
{
    return !(r1 == r2);
}

ostream &operator<<(ostream &os, const Rational &r)
{
    return cout << '(' << r.get_numer() << '/' << r.get_denom() << ')';
}

int main()
{
    try
    {
        Rational r1;
        Rational r2(5);
        Rational r3(7, 3);
        cout << "r1: " << r1 << endl
             << "r2: " << r2 << endl
             << "r3: " << r3 << endl;

        cout << "5/3 + 7/2 = " << Rational(5, 3) + Rational(7, 2) <<
             " = " << (Rational(5, 3) + Rational(7, 2)).conv_double() << endl;
        cout << "8/5 - 40/7 = " << Rational(8, 5) - Rational(40, 7) <<
             " = " << (Rational(8, 5) - Rational(40, 7)).conv_double() << endl;
        cout << "10/11 * 17/18 = " << Rational(10, 11) * Rational(17, 18) <<
             " = " << (Rational(10, 11) * Rational(17, 18)).conv_double() << endl;
        cout << "(5/7) / (1/3) = " << Rational(5, 7) / Rational(1, 3) <<
             " = " << (Rational(5, 7) / Rational(1, 3)).conv_double() << endl;

        if (r1 == Rational(0, 1))
        {
            cout << "r1 == 0/1" << endl;
        }
        if (Rational(1, 2) == Rational(2, 4))
        {
            cout << "1/2 == 2/4" << endl;
        }
        if (r2 != r2)
        {
            cout << "r2 != r2" << endl;
        }

        cout << r3 << " = " << r3.conv_double() << endl;
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
