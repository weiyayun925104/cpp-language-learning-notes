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

class Useless
{
private:
    int n;
    char *pc;
    static int ct;
    void ShowObject() const;
public:
    Useless();
    explicit Useless(int k);
    Useless(int k, char ch);
    Useless(const Useless &f);
    Useless(Useless &&f);
    ~Useless();
    Useless operator+(const Useless &f) const;
    Useless &operator=(const Useless &f);
    Useless &operator=(Useless &&f);
    void ShowData() const;
};

int Useless::ct = 0;

Useless::Useless()
{
    ++ct;
    n = 0;
    pc = nullptr;
}

Useless::Useless(int k) : n(k)
{
    ++ct;
    pc = new char[n];
}

Useless::Useless(int k, char ch) : n(k)
{
    ++ct;
    pc = new char[n];
    for (int i = 0; i < n; i++)
    {
        pc[i] = ch;
    }
}

Useless::Useless(const Useless &f) : n(f.n)
{
    ++ct;
    pc = new char[n];
    for (int i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
}

Useless::Useless(Useless &&f) : n(f.n)
{
    ++ct;
    pc = f.pc;
    f.pc = nullptr;
    f.n = 0;
}

Useless::~Useless()
{
    delete[] pc;
}

Useless &Useless::operator=(const Useless &f)
{
    std::cout << "copy assignment operator called:\n";
    if (this == &f)
    {
        return *this;
    }
    delete[] pc;
    n = f.n;
    pc = new char[n];
    for (int i = 0; i < n; i++)
    {
        pc[i] = f.pc[i];
    }
    return *this;
}

Useless &Useless::operator=(Useless &&f)
{
    std::cout << "move assignment operator called:\n";
    if (this == &f)
    {
        return *this;
    }
    delete[] pc;
    n = f.n;
    pc = f.pc;
    f.n = 0;
    f.pc = nullptr;
    return *this;
}

Useless Useless::operator+(const Useless &f) const
{
    Useless temp = Useless(n + f.n);
    for (int i = 0; i < n; i++)
    {
        temp.pc[i] = pc[i];
    }
    for (int i = n; i < temp.n; i++)
    {
        temp.pc[i] = f.pc[i - n];
    }
    return temp;
}
void Useless::ShowObject() const
{
    std::cout << "Number of elements: " << n;
    std::cout << " Data address: " << (void *) pc << std::endl;
}

void Useless::ShowData() const
{
    if (n == 0)
    {
        std::cout << " (object empty)";
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            std::cout << pc[i];
        }
    }
    std::cout << std::endl;
}

int main(int argc, const char *argv[])
{
    try
    {
        {
            Useless one(10, 'x');
            Useless two = one + one;
            cout << "object one: ";
            one.ShowData();
            cout << "object two: ";
            two.ShowData();
            Useless three, four;
            cout << "three = one\n";
            three = one;
            cout << "now object three = ";
            three.ShowData();
            cout << "and object one = ";
            one.ShowData();
            cout << "four = one + two\n";
            four = one + two;
            cout << "now object four = ";
            four.ShowData();
            cout << "four = move(one)\n";
            four = std::move(one);
            cout << "now object four = ";
            four.ShowData();
            cout << "and object one = ";
            one.ShowData();
        }

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
