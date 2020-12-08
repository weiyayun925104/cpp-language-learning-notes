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
class S
{
public:
    S() : val(T()) { }
    S(const T &d) : val(d) { }
    T &operator=(const T &d)
    {
        val = d;
        return val;
    }
    T &get()
    {
        return val;
    }
    const T &get() const
    {
        return val;
    }
    void set(const T &d)
    {
        val = d;
    }
private:
    T val;
};

template<typename T>
istream &operator>>(istream &is, S<T> &ss)
{
    T v;
    cin >> v;
    if (!is)
    {
        return is;
    }
    ss.set(v);
    return is;
}

template<typename T>
void read_val(T &v)
{
    cin >> v;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &d)
{
    os << "{ ";
    for (int i = 0; i < d.size(); ++i)
    {
        os << d[i];
        if (i < d.size() - 1)
        {
            os << ", ";
        }
    }
    os << " }";
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
    while (cin >> temp && cin >> ch2 && ch2 == ',')
    {
        v_temp.push_back(temp);
    }
    if (ch2 != '}')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    v_temp.push_back(temp);

    d = v_temp;
    return is;
}

int main()
{
    try
    {
        S<int> s_int(5);
        S<char> s_char('x');
        S<double> s_dbl(3.14);
        S<string> s_strg("Hello,World!");
        vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        S< vector<int> > s_vec_int(vec);

        cout << "s_int: " << s_int.get() << "\n";
        cout << "s_char: " << s_char.get() << "\n";
        cout << "s_dbl: " << s_dbl.get() << "\n";
        cout << "s_strg: " << s_strg.get() << "\n";
        for (int i = 0; i < s_vec_int.get().size(); ++i)
        {
            cout << "s_vec_int[" << i << "]: " << s_vec_int.get()[i] << "\n";
        }
        cout << s_vec_int.get() << "\n";

        s_int.set(55);
        s_char.set('y');
        s_dbl.set(4.14);
        s_strg.set("Peter Smith");
        vec[1] = 22;
        s_vec_int.set(vec);
        cout << "\ns_int: " << s_int.get() << "\n";
        cout << "s_char: " << s_char.get() << "\n";
        cout << "s_dbl: " << s_dbl.get() << "\n";
        cout << "s_strg: " << s_strg.get() << "\n";
        for (int i = 0; i < s_vec_int.get().size(); ++i)
        {
            cout << "s_vec_int[" << i << "]: " << s_vec_int.get()[i] << "\n";
        }
        cout << s_vec_int.get() << "\n";

        s_int = 66;
        s_char = 'z';
        s_dbl = 5.14;
        s_strg = "Mike Pence";
        vec[1] = 33;
        s_vec_int = vec;
        cout << "\ns_int: " << s_int.get() << "\n";
        cout << "s_char: " << s_char.get() << "\n";
        cout << "s_dbl: " << s_dbl.get() << "\n";
        cout << "s_strg: " << s_strg.get() << "\n";
        for (int i = 0; i < s_vec_int.get().size(); ++i)
        {
            cout << "s_vec_int[" << i << "]: " << s_vec_int.get()[i] << "\n";
        }
        cout << s_vec_int.get() << "\n";

        const S<int> c_s_int(5);
        cout << "\nc_s_int: " << c_s_int.get() << "\n";

        cout << "\ns_int: ";
        read_val(s_int);
        cout << "s_char: ";
        read_val(s_char);
        cout << "s_dbl: ";
        read_val(s_dbl);
        cout << "s_strg: ";
        read_val(s_strg);
        cout << "\ns_int: " << s_int.get() << "\n";
        cout << "s_char: " << s_char.get() << "\n";
        cout << "s_dbl: " << s_dbl.get() << "\n";
        cout << "s_strg: " << s_strg.get() << "\n\n";

        cout << "\ns_vec_int: ";
        read_val(s_vec_int);
        cout << "\ns_vec_int: " << s_vec_int.get() << "\n";
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
