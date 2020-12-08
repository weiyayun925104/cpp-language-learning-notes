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

class Int
{
private:
    int val;
public:
    Int() : val(0) { }
    Int(int v) : val(v) { }
    Int(const Int &arg) : val(arg.val) { }
    Int &operator=(const Int &arg)
    {
        val = arg.val;
        return *this;
    }
    int get() const
    {
        return val;
    }
};

Int operator+(const Int &v1, const Int &v2)
{
    return Int(v1.get() + v2.get());
}

Int operator-(const Int &v1, const Int &v2)
{
    return Int(v1.get() - v2.get());
}

Int operator*(const Int &v1, const Int &v2)
{
    return Int(v1.get() * v2.get());
}

Int operator/(const Int &v1, const Int &v2)
{
    return Int(v1.get() / v2.get());
}

ostream &operator<<(ostream &os, const Int &v)
{
    os << v.get();
    return os;
}

int main()
{
    try
    {
        Int i1;
        Int i2 = 2;
        Int i3(i2);
        Int i4;
        i4 = i2;
        Int i5 = 6;
        cout << "i1 (default constructed): " << i1 << "\n";
        cout << "i2 (constructed with argument): " << i2 << "\n";
        cout << "i3 (copy constructed from i2): " << i3 << "\n";
        cout << "i4 (copy assigned  from i2): " << i4 << "\n";
        cout << "i5 (constructed with argument): " << i5 << "\n";
        cout << "i2 + i5 = " << i2 + i5 << "\n";
        cout << "i5 - i2 = " << i5 - i2 << "\n";
        cout << "i2 * i5 = " << i2 *i5 << "\n";
        cout << "i5 / i2 = " << i5 / i2 << "\n";
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
