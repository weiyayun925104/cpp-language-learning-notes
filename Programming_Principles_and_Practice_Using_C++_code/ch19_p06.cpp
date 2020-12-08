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

template<typename T>
class Number
{
private:
    T val;
public:
    Number() : val(T()) { }
    Number(const T &v) : val(v) { }
    Number(const Number<T> &arg) : val(arg.val) { }
    Number &operator=(const Number<T> &arg)
    {
        if (this == &arg) { return *this; }
        val = arg.val;
        return *this;
    }
    T & get()
    {
        return val;
    }
    const T & get() const
    {
        return val;
    }
};

template<typename T>
Number<T> operator+(const Number<T> &v1, const Number<T> &v2)
{
    return Number<T>(v1.get() + v2.get());
}

template<typename T>
Number<T> operator-(const Number<T> &v1, const Number<T> &v2)
{
    return Number<T>(v1.get() - v2.get());
}

template<typename T>
Number<T> operator*(const Number<T> &v1, const Number<T> &v2)
{
    return Number<T>(v1.get() * v2.get());
}

template<typename T>
Number<T> operator/(const Number<T> &v1, const Number<T> &v2)
{
    return Number<T>(v1.get() / v2.get());
}

template<typename T>
Number<T> operator%(const Number<T> &v1, const Number<T> &v2)
{
    return Number<T>(v1.get() % v2.get());
}

template<class T>
ostream &operator<<(ostream &os, const Number<T> &v)
{
    os << v.get();
    return os;
}

int main()
{
    try
    {
        cout << "int:\n";
        Number<int> i1;
        Number<int> i2 = 2;
        Number<int> i3(i2);
        Number<int> i4;
        i4 = i2;
        Number<int> i5 = 5;
        cout << "i1 (default constructed): " << i1 << "\n";
        cout << "i2 (constructed with argument): " << i2 << "\n";
        cout << "i3 (copy constructed from i2): " << i3 << "\n";
        cout << "i4 (copy assigned  from i2): " << i4 << "\n";
        cout << "i5 (constructed with argument): " << i5 << "\n";
        cout << "i2 + i5 = " << i2 + i5 << "\n";
        cout << "i5 - i2 = " << i5 - i2 << "\n";
        cout << "i2 * i5 = " << i2 *i5 << "\n";
        cout << "i5 / i2 = " << i5 / i2 << "\n";
        cout << "i5 % i2 = " << i5 % i2 << "\n";

        cout << "\ndouble:\n";
        Number<double> d1;
        Number<double> d2 = 2.2;
        Number<double> d3(d2);
        Number<double> d4;
        d4 = d2;
        Number<double> d5 = 5.5;
        cout << "d1 (default constructed): " << d1 << "\n";
        cout << "d2 (constructed with argument): " << d2 << "\n";
        cout << "d3 (copy constructed from d2): " << d3 << "\n";
        cout << "d4 (copy assigned  from d2): " << d4 << "\n";
        cout << "d5 (constructed with argument): " << d5 << "\n";
        cout << "d2 + d5 = " << d2 + d5 << "\n";
        cout << "d5 - d2 = " << d5 - d2 << "\n";
        cout << "d2 * d5 = " << d2 *d5 << "\n";
        cout << "d5 / d2 = " << d5 / d2 << "\n";

        cout << "\nchar:\n";
        Number<char> c1;
        Number<char> c2 = 'x';
        Number<char> c3(c2);
        Number<char> c4;
        c4 = c2;
        Number<char> c5 = 'C';
        cout << "c1 (default constructed): " << c1 << "\n";
        cout << "c2 (constructed with argument): " << c2 << "\n";
        cout << "c3 (copy constructed from c2): " << c3 << "\n";
        cout << "c4 (copy assigned  from c2): " << c4 << "\n";
        cout << "c5 (constructed with argument): " << c5 << "\n";

        cout << "\nstring:\n";
        Number<string> s1;
        Number<string> s2("xxx");
        Number<string> s3(s2);
        Number<string> s4;
        s4 = s2;
        Number<string> s5("ABCD!");
        cout << "s1 (default constructed): " << s1 << "\n";
        cout << "s2 (constructed with argument): " << s2 << "\n";
        cout << "s3 (copy constructed from s2): " << s3 << "\n";
        cout << "s4 (copy assigned  from s2): " << s4 << "\n";
        cout << "s5 (constructed with argument): " << s5 << "\n";
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
