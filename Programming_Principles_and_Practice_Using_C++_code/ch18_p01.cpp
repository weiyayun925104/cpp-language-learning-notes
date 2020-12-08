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

char *strdupl(const char *s)
{
    if (s == nullptr)
    {
        return nullptr;
    }

    int n = 0;
    const char *p = s;
    while (*p != '\0')
    {
        ++n;
        p++;
    }

    char *s_cpy = new char[n + 1];

    char *s_cpy_ptr = s_cpy;
    while (*s != '\0')
    {
        *s_cpy_ptr++ = *s++;
    }
    *s_cpy_ptr = '\0';
    return s_cpy;
}


const char *findx(const char *s, const char *x)
{
    if (x == nullptr || *x == '\0')
    {
        return nullptr;
    }
    if (s == nullptr || *s == '\0')
    {
        return nullptr;
    }
    for (int i = 0; * (s + i) != '\0'; ++i)
    {
        if (*(s + i) == *x)
        {
            int j = 1;
            for (; * (x + j) != '\0'; ++j)
            {
                if (*(s + i + j) == '\0')
                {
                    return nullptr;
                }
                if (*(s + i + j) != *(x + j))
                {
                    break;
                }
            }
            if (*(x + j) == '\0')
            {
                return (s + i);
            }
        }
    }
    return nullptr;
}

int strcomp(const char *s1, const char *s2)
{
    if (s1 == nullptr || s2 == nullptr)
    {
        error("Null pointer sent to strcomp()");
    }
    for (int i = 0; ; ++i)
    {
        if (*(s1 + i) == '\0' && *(s2 + i) != '\0')
        {
            return -1;
        }
        else if (*(s1 + i) == '\0' && *(s2 + i) == '\0')
        {
            return 0;
        }
        else if (*(s1 + i) != '\0' && *(s2 + i) == '\0')
        {
            return 1;
        }
        else
        {
            if (*(s1 + i) < * (s2 + i))
            {
                return -1;
            }
            else if (*(s1 + i) > *(s2 + i))
            {
                return 1;
            }
        }
    }

    return 0;
}

void print_str(const char *s)
{
    if (s == nullptr)
    {
        error("Cannot print from null pointer");
    }
    while (*s != '\0')
    {
        cout << *s++;
    }
}

int main()
{
    try
    {
        char s[] = "Test";
        char *s_cpy = strdupl(s);
        print_str(s_cpy);
        cout << "\n";
        delete[] s_cpy;

        char s2[] = "This is a test phrase";
        char x[] = "test";
        cout << "s: " << s2 << "\n";
        cout << "x: " << x << "\n";
        print_str(findx(s2, x));
        cout << "\n";

        string a;
        string b;
        while (cin >> a && cin >> b)
        {
            int comp = strcomp(a.c_str(), b.c_str());
            switch (comp)
            {
            case -1:
                cout << a << " < " << b << "\n";
                break;
            case 0:
                cout << a << " == " << b << "\n";
                break;
            case 1:
                cout << a << " > " << b << "\n";
                break;
            default:
                error("invalid result returned by strcmp");
                break;
            }
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
