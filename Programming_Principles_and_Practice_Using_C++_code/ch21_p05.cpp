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

template<typename In, typename T>
int my_count(In first, In last, const T &val)
{
    int ctr = 0;
    while (first != last)
    {
        if (*first == val)
        {
            ++ctr;
        }
        ++first;
    }
    return ctr;
}


template<typename In, typename Pred>
int my_count_if(In first, In last, const Pred &p)
{
    int ctr = 0;
    while (first != last)
    {
        if (p(*first))
        {
            ++ctr;
        }
        ++first;
    }
    return ctr;
}

template<typename T>
class Less_than
{
private:
    T val;
public:
    Less_than(const T &v) : val(v) { }
    bool operator()(const T &x) const
    {
        return x < val;
    }
};

template<typename T>
class Greater_than
{
private:
    T val;
public:
    Greater_than(const T &v) : val(v) { }
    bool operator()(const T &x) const
    {
        return x > val;
    }
};

bool odd(int i)
{
    return i % 2 != 0;
}

template<typename In, typename T>
In my_find2(In first, In last, const T &val)
{
    In p = first;
    while (p != last)
    {
        if (*p == val)
        {
            return p;
        }
        ++p;
    }

    if (*p == val)
    {
        return p;
    }

    return first;
}

template<typename In, typename T>
int my_count2(In first, In last, const T &val)
{
    int count = 0;
    while (first != last)
    {
        if (*first == val)
        {
            ++count;
        }
        ++first;
    }
    if (*first == val)
    {
        ++count;
    }
    return count;
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 engine(seed);

    try
    {
        vector<int> vi;
        for (int i = 0; i < 30; ++i)
        {
            vi.push_back(nrand_two(0, 100, engine));
        }
        cout << "vi:\n";
        cout << vi << endl;
        typedef vector<int>::iterator vi_it;
        cout << "Enter int to search for and count (-1 to quit): ";
        int val;
        while (cin >> val)
        {
            if (val == -1)
            {
                break;
            }
            vi_it it = my_find2(vi.begin(), vi.end() - 1, val);
            int count = my_count2(vi.begin(), vi.end() - 1, val);
            if (*it != val)
            {
                cout << val << " is not in vi.\n";
            }
            else
            {
                cout << val << " is at index " << it - vi.begin()
                     << " (occurs " << count << " time" << (count == 1 ? "" : "s")
                     << ").\n";
            }
            cout << "Enter int to search for and count (-1 to quit): ";
        }
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
