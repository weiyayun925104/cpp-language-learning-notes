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
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
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

template<typename T>
T *clone(const T *tp)
{
    return tp->clone();
}

template<typename T>
class Ptr
{
public:
    Ptr() : refptr(new size_t(1)), p(nullptr) { }
    Ptr(T *t) : refptr(new size_t(1)), p(t) { }
    Ptr(const Ptr<T> &h) : refptr(h.refptr), p(h.p)
    {
        ++*refptr;
    }

    Ptr<T> &operator=(const Ptr<T> &);
    ~Ptr();

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ptr");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ptr");
    }

    void make_unique()
    {
        if (*refptr > 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p != nullptr ? clone(p) : nullptr;
        }
    }

    void print()
    {
        cout << (void *)p << ": " << (void *)refptr << ", " << *refptr << endl;
    }
private:
    T *p;
    size_t *refptr;
};

template<typename T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.refptr;
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template<typename T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

class Tracer
{
private:
    int val;
public:
    Tracer() : val(0)
    {
        cout << "Tracer()\n";
    }
    Tracer(int n) : val(n)
    {
        cout << "Tracer(int n)\n";
    }
    Tracer(const Tracer &arg) : val(arg.val)
    {
        cout << "Tracer(const Tracer &arg)\n";
    }
    Tracer &operator=(const Tracer &arg)
    {
        cout << "operator=(const Tracer &arg)\n";
        if (this == &arg) { return *this; }
        val = arg.val;
        return *this;
    }
    ~Tracer()
    {
        cout << "~Tracer()\n";
    }
    int & get()
    {
        return val;
    }
    const int & get() const
    {
        return val;
    }
};

template<>
inline Tracer *clone<Tracer>(const Tracer *pt)
{
    return new Tracer(*pt);
}

void f1()
{
    Ptr<Tracer> p1(new Tracer());
    Ptr<Tracer> p2(new Tracer(5));
    Ptr<Tracer> p3(p2);
    p1.print();
    p2.print();
    p3.print();
    p1 = p3;
    p1.print();
    p2.print();
    p3.print();
    cout << (*p1).get() << ", " << p2->get() << ", " << (*p3).get() << endl;
}

void f2()
{
    Ptr<Tracer> p1(new Tracer());
    Ptr<Tracer> p2(new Tracer(5));
    Ptr<Tracer> p3(p2);
    error("Exception!");
}

int main(int argc, const char *argv[])
{
    try
    {
        f1();
        f2();

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
