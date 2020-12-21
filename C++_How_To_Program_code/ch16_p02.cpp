#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
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
#include <limits>
#include <type_traits>
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
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::vector;
using std::list;
using std::set;
using std::multiset;
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
using std::streampos;
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
using std::ios_base;
using std::ios;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::right;
using std::flush;
using std::numeric_limits;
using std::common_type;
using std::reverse;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
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

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}

class Roman_int
{
public:
    Roman_int();
    Roman_int(int n);
    int as_int() const;
    void set_val(int v);
private:
    int val;
};

// N = 0 I = 1 V = 5 X= 10 L= 50 C = 100 D = 500 M = 1000
const char N = 'N';
const char I = 'I';
const char V = 'V';
const char X = 'X';
const char L = 'L';
const char C = 'C';
const char D = 'D';
const char M = 'M';

bool is_valid_char(char ch);
int get_value(char ch);
bool counter_illegal(int counter, char ch);
int roman_int_to_int(const string &s);


Roman_int::Roman_int() : val(0) { }

Roman_int::Roman_int(int n) : val(n) { }

int Roman_int::as_int() const
{
    return val;
}

void Roman_int::set_val(int v)
{
    val = v;
}

Roman_int operator+(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() + r2.as_int());
}

Roman_int operator-(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() - r2.as_int());
}

Roman_int operator-(const Roman_int &r)
{
    return Roman_int(-r.as_int());
}

Roman_int operator*(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() * r2.as_int());
}

Roman_int operator/(const Roman_int &r1, const Roman_int &r2)
{
    if (r2.as_int() == 0)
    {
        error("division / by zero");
    }
    return Roman_int(r1.as_int() / r2.as_int());
}

Roman_int operator%(const Roman_int &r1, const Roman_int &r2)
{
    if (r2.as_int() == 0)
    {
        error("division % by zero");
    }
    return Roman_int(r1.as_int() % r2.as_int());
}

bool operator==(const Roman_int &r1, const Roman_int &r2)
{
    return r1.as_int() == r2.as_int();
}

bool operator!=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r1 == r2);
}

bool operator<(const Roman_int &r1, const Roman_int &r2)
{
    return r1.as_int() < r2.as_int();
}

bool operator>(const Roman_int &r1, const Roman_int &r2)
{
    return r2 < r1;
}

bool operator<=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r2 < r1);
}

bool operator>=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r1 < r2);
}

bool is_valid_char(char ch)
{
    return ch == N || ch == I || ch == V || ch == X || ch == L || ch == C || ch == D || ch == M;
}

ostream &operator<<(ostream &os, const Roman_int &r)
{
    int val = r.as_int();
    if (val == 0)
    {
        return os << N;
    }
    if (val < 0)
    {
        os << '-';
        val = -val;
    }

    while (val >= 1000)
    {
        os << M;
        val -= 1000;
    }
    if (val >= 900)
    {
        os << C << M;
        val -= 900;
    }
    else if (val >= 500)
    {
        os << D;
        val -= 500;
    }
    else if (val >= 400)
    {
        os << C << D;
        val -= 400;
    }
    while (val >= 100)
    {
        os << C;
        val -= 100;
    }
    if (val >= 90)
    {
        os << X << C;
        val -= 90;
    }
    else if (val >= 50)
    {
        os << L;
        val -= 50;
    }
    else if (val >= 40)
    {
        os << X << L;
        val -= 40;
    }
    while (val >= 10)
    {
        os << X;
        val -= 10;
    }
    if (val == 9)
    {
        os << I << X;
        val -= 9;
    }
    else if (val >= 5)
    {
        os << V;
        val -= 5;
    }
    else if (val == 4)
    {
        os << I << V;
        val -= 4;
    }
    while (val >= 1)
    {
        os << I;
        --val;
    }
    return os;
}

int get_value(char ch)
{
    switch (ch)
    {
    case N:
        return 0;
    case I:
        return 1;
    case V:
        return 5;
    case X:
        return 10;
    case L:
        return 50;
    case C:
        return 100;
    case D:
        return 500;
    case M:
        return 1000;
    default:
        error("illegal letter used: " + string(1, ch));
    }
}

bool counter_illegal(int counter, char ch)
{
    switch (ch)
    {
    case N:
    case V:
    case L:
    case D:
        return counter > 1;
    case I:
    case X:
    case C:
    case M:
        return counter > 3;
    default:
        error("counter_illegal: invalid character " + string(1, ch));
    }
}

int roman_int_to_int(const string &s)
{
    if (s.size() == 0)
    {
        error("roman_to_int: empty string");
    }
    if (s.size() == 1)
    {
        return get_value(s[0]);
    }

    int counter = 1;
    int val = get_value(s[s.size() - 1]);

    for (int i = s.size() - 2; i >= 0; --i)
    {
        if (s[i] == s[i + 1])
        {
            ++counter;
            if (counter_illegal(counter, s[i]))
            {
                error("illegal repetition of letter: " + string(1, s[i]));
            }
        }
        else
        {
            counter = 1;
        }

        if (get_value(s[i]) < get_value(s[i + 1]))
        {
            if ((s[i] == I || s[i] == X || s[i] == C) && get_value(s[i + 1]) <= 10 * get_value(s[i]))
            {
                val -= get_value(s[i]);
            }
            else
            {
                error("illegal use of " + string(1, s[i]));
            }
        }
        else
        {
            val += get_value(s[i]);
        }
    }
    return val;
}

istream &operator>>(istream &is, Roman_int &r)
{
    is.exceptions(is.exceptions() | std::ios_base::badbit);

    string s;
    char ch;

    while (is.get(ch))
    {
        if (is_valid_char(ch))
        {
            s += ch;
        }
        else
        {
            is.putback(ch);
            break;
        }
    }

    int val = roman_int_to_int(s);
    r.set_val(val);
    return is;
}

void test_output()
{
    cout << Roman_int(0) << " equals " << Roman_int(0).as_int() << endl;
    cout << Roman_int(1) << " equals " << Roman_int(1).as_int() << endl;
    cout << Roman_int(4) << " equals " << Roman_int(4).as_int() << endl;
    cout << Roman_int(5) << " equals " << Roman_int(5).as_int() << endl;
    cout << Roman_int(8) << " equals " << Roman_int(8).as_int() << endl;
    cout << Roman_int(9) << " equals " << Roman_int(9).as_int() << endl;
    cout << Roman_int(10) << " equals " << Roman_int(10).as_int() << endl;
    cout << Roman_int(48) << " equals " << Roman_int(48).as_int() << endl;
    cout << Roman_int(81) << " equals " << Roman_int(81).as_int() << endl;
    cout << Roman_int(99) << " equals " << Roman_int(99).as_int() << endl;
    cout << Roman_int(105) << " equals " << Roman_int(105).as_int() << endl;
    cout << Roman_int(2014) << " equals " << Roman_int(2014).as_int() << endl;
    cout << Roman_int(-2014) << " equals " << Roman_int(-2014).as_int() << endl;
    cout << Roman_int(1499) << " equals " << Roman_int(1499).as_int() << endl << endl;
    cout << Roman_int(1) << " + " << Roman_int(3) << " = " << Roman_int(1) + Roman_int(3) << endl;
    cout << Roman_int(15) << " * " << Roman_int(37) << " = " << Roman_int(15)*Roman_int(37) << endl;
    cout << Roman_int(105) << " - " << Roman_int(207) << " = " << Roman_int(105) - Roman_int(207) << endl;
    cout << -Roman_int(7) << " * " << Roman_int(5) << " = " << -Roman_int(7)*Roman_int(5) << endl;
    cout << Roman_int(15) << " / " << Roman_int(5) << " = " << Roman_int(15) / Roman_int(5) << endl;
}

int main(int argc, const char *argv[])
{
    try
    {
        test_output();

        return 0;
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
