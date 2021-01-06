#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
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
#include <initializer_list>
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
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
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
using std::begin;
using std::end;
using std::initializer_list;

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

int main(int argc, const char *argv[])
{
    try
    {
        vector<int> vi = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto iter = vi.begin();
        while(iter != vi.end())
        {
            if(*iter % 2)
            {
                iter = vi.insert(iter, *iter);
                iter += 2;
            }
            else
            {
                iter = vi.erase(iter);
            }
        }
        for(auto &i : vi)
            cout << i << " ";
        cout << endl;

        vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto begin = v.begin();
        while(begin != v.end())
        {
            ++begin;
            begin = v.insert(begin, 42);
            begin += 2;
        }
        for(auto &i : v)
            cout << i << " ";
        cout << endl;

        v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        auto it = v.begin();
        while(it != v.end())
        {
            if(*it % 2)
            {
                it = v.insert(it, *it);
                it += 2;
            }
            else { ++it; }
        }
        for(auto &i : v)
            cout << i << " ";
        cout << endl;

        vector<int> ivec;
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;
        for(vector<int>::size_type ix = 0; ix != 24; ++ix)
            ivec.push_back(ix);
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;
        ivec.reserve(50);
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;
        while(ivec.size() != ivec.capacity())
            ivec.push_back(0);
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;
        ivec.push_back(42);
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;
        ivec.shrink_to_fit();
        cout << "ivec: size: " << ivec.size()
             << " capacity: " << ivec.capacity() << endl;

        vector<char> vch = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '!', '!' };
        char *cp = &vch[0];
        string str1(vch.cbegin(), vch.cend());
        string str2(cp, vch.size());
        cout << str1 << endl;
        cout << str2 << endl;

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
