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
using std::numeric_limits;
using std::common_type;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
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

template<typename T, typename U>
class Pair
{
public:
    Pair(const T &vt, const U &vu) : val1(vt), val2(vu) { }
    T val1;
    U val2;
};

class Symbol_table
{
public:
    double get(const string &s);
    void set(const string &s, double d);
    bool is_declared(const string &s);
    double declare(const string &s, double val);
    void print();
private:
    vector< Pair<string, double> > var_table;
};

double Symbol_table::get(const string &s)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].val1 == s) { return var_table[i].val2; }
    }
    error("Variable not found: " + s);
}

void Symbol_table::set(const string &s, double d)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].val1 == s)
        {
            var_table[i].val2 = d;
            return;
        }
    }
    error("Variable not found: " + s);
}

bool Symbol_table::is_declared(const string &s)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].val1 == s) { return true; }
    }
    return false;
}

double Symbol_table::declare(const string &s, double d)
{
    if (is_declared(s)) { error("Variable exists already: " + s); }
    var_table.push_back(Pair<string, double>(s, d));
    return d;
}

void Symbol_table::print()
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        cout << var_table[i].val1 << ": " << var_table[i].val2 << "\n";
    }
}

int main()
{
    try
    {
        Symbol_table st;
        st.declare("Pi", 3.14);
        st.declare("e", 2.72);
        st.print();
        cout << "Pi is " << st.get("Pi") << "\n";
        if (st.is_declared("Pi"))
        {
            cout << "Pi is declared\n";
        }
        else
        {
            cout << "Pi is not declared\n";
        }
        if (st.is_declared("nd"))
        {
            cout << "nd is declared\n";
        }
        else
        {
            cout << "nd is not declared\n";
        }
        st.set("Pi", 4.14);
        cout << "Pi is now " << st.get("Pi") << "\n";
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
