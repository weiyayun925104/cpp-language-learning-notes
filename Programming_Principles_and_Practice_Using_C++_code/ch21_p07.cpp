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

template<typename Ran, typename T>
bool my_binary_search(Ran first, Ran last, const T &val)
{
    if (first == last)
    {
        return false;
    }
    Ran p = first + (last - first) / 2;
    if (*p == val)
    {
        return true;
    }
    Ran p2 = p;
    ++p2;
    if (*p < val && p2 != last)
    {
        return my_binary_search(p2, last, val);
    }
    if (*p > val)
    {
        return my_binary_search(first, p, val);
    }
    return false;
}

template<typename Bid>
Bid middle(Bid first, Bid last)
{
    if (first == last)
    {
        error("first==last in middle");
    }

    int dist = 0;
    Bid p = first;
    while (p != last)
    {
        ++p;
        ++dist;
    }
    p = first;
    for (int i = 0; i < dist / 2; i++)
    {
        p++;
    }
    return p;
}

template<typename Bid, typename T>
bool my_binary_bid_search(Bid first, Bid last, const T &val)
{
    if (first == last)
    {
        return false;
    }
    Bid p = middle(first, last);
    if (*p == val)
    {
        return true;
    }
    Bid p2 = p;
    ++p2;
    if (*p < val && p2 != last)
    {
        return my_binary_bid_search(p2, last, val);
    }
    if (*p > val)
    {
        return my_binary_bid_search(first, p, val);
    }
    return false;
}

template<typename Iter>
void print(Iter first, Iter last)
{
    while (first != last)
    {
        cout << *first << '\n';
        ++first;
    }
}

int main()
{
    try
    {
        vector<int> vi;
        for (int i = 0; i < 20; ++i)
        {
            vi.push_back(2 * i);
        }
        cout << "Vector:\n";
        print(vi.begin(), vi.end());

        cout << "Enter int to find (-1 to exit): ";
        int i;
        while (cin >> i && i != -1)
        {
            cout << i << " is " << (my_binary_search(vi.begin(), vi.end(), i) ? "" : "not ") << "in vi.\n";
            cout << "Enter int to find (-1 to exit): ";
        }

        list<int> li(20);
        copy(vi.begin(), vi.end(), li.begin());
        cout << "\nList:\n";
        print(li.begin(), li.end());

        cout << "Enter int to find (-1 to exit): ";
        while (cin >> i && i != -1)
        {
            cout << i << " is " << (my_binary_bid_search(li.begin(), li.end(), i) ? "" : "not ") << "in li.\n";
            cout << "Enter int to find (-1 to exit): ";
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
