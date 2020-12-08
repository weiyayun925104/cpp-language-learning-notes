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
void f(vector<T> &v1, const vector<T> &v2)
{
    for (int i = 0; i < v1.size(); ++i)
    {
        if (i == v2.size())
        {
            break;
        }
        v1[i] += v2[i];
    }
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

int main()
{
    try
    {
        vector<int> v1;
        for (int i = 0; i < 10; ++i)
        {
            v1.push_back(i);
        }
        cout << "v1: " << v1 << "\n";
        vector<int> v2;
        for (int i = 0; i < 8; ++i)
        {
            v2.push_back(i);
        }
        cout << "v2: " << v2 << "\n";
        f(v1, v2);
        cout << "After: " << v1 << "\n\n";

        v2.push_back(15);
        v2.push_back(16);
        v2.push_back(17);
        cout << "New v2: " << v2 << "\n";
        f(v1, v2);
        cout << "After: " << v1 << "\n\n";

        vector<string> vs1;
        vs1.push_back("one");
        vs1.push_back("two");
        vs1.push_back("three");
        vs1.push_back("four");
        cout << "vs1: " << vs1 << "\n";
        vector<string> vs2;
        vs2.push_back(" ONE");
        vs2.push_back(" TWO");
        vs2.push_back(" THREE");
        cout << "vs2: " << vs2 << "\n";
        f(vs1, vs2);
        cout << "After: " << vs1 << "\n";
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
