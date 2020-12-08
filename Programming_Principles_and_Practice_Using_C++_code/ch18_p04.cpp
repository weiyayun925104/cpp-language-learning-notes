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

char *strdupl(const char *s, int num_max)
{
    if (s == nullptr || num_max <= 0)
    {
        return nullptr;
    }

    int n = 0;
    const char *p = s;
    while (n < num_max && *p != '\0')
    {
        ++n;
        p++;
    }

    char *s_cpy = new char[n + 1];

    char *s_cpy_ptr = s_cpy;
    int i = 0;
    while (i < n && *s != '\0')
    {
        *s_cpy_ptr++ = *s++;
        ++i;
    }
    *s_cpy_ptr = '\0';
    return s_cpy;
}

const char *findx(const char *s, const char *x, int num_max_s, int num_max_x)
{
    if (x == nullptr || *x == '\0' || num_max_x <= 0)
    {
        return nullptr;
    }
    if (s == nullptr || *s == '\0' || num_max_s <= 0)
    {
        return nullptr;
    }
    for (int i = 0; i < num_max_s && * (s + i) != '\0'; ++i)
    {
        if (*(s + i) == *x)
        {
            int j = 1;
            for (; j < num_max_x && * (x + j) != '\0'; ++j)
            {
                if ( (i + j) >= num_max_s || *(s + i + j) == '\0')
                {
                    return nullptr;
                }
                if (*(s + i + j) != *(x + j))
                {
                    break;
                }
            }
            if (j >= num_max_x || *(x + j) == '\0')
            {
                return (s + i);
            }
        }
    }
    return nullptr;
}

int strcomp(const char *s1, const char *s2, int num_max_s1, int num_max_s2)
{
    if (s1 == nullptr || s2 == nullptr)
    {
        error("Null pointer sent to strcomp()");
    }
    if (num_max_s1 <= 0 || num_max_s2 <= 0)
    {
        error("num_max <= 0 sent to strcomp()");
    }
    int n = (num_max_s1 < num_max_s2 ? num_max_s1 : num_max_s2) + 1;
    for (int i = 0; i < n; ++i)
    {
        if ( ( i >= num_max_s1 || *(s1 + i) == '\0' ) && ( i < num_max_s2 && *(s2 + i) != '\0' ) )
        {
            return -1;
        }
        else if ( ( i >= num_max_s1 || *(s1 + i) == '\0' )  && ( i >= num_max_s2 || *(s2 + i) == '\0' ) )
        {
            return 0;
        }
        else if ( ( i < num_max_s1 && *(s1 + i) != '\0' )  && ( i >= num_max_s2 || *(s2 + i) == '\0' ) )
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

void print_str(const char *s, int num_max)
{
    if (s == nullptr)
    {
        error("Cannot print from null pointer");
    }
    int i = 0;
    while (i < num_max && *s != '\0')
    {
        cout << *s++;
        ++i;
    }
}

int main()
{
    try
    {
        char a[] = "test";
        char *a_dpl = strdupl(a, 5);
        print_str(a_dpl, 5);
        cout << "\n";
        char b[] = { 't', 'e', 's', 't' };
        char *b_dpl = strdupl(b, 4);
        print_str(b_dpl, 4);
        cout << "\n";
        delete[] b_dpl;
        delete[] a_dpl;

        char s[] = "xxxtestxxx";
        char x[] = "test";
        const char *sub = findx(s, x, 11, 5);
        print_str(sub, 11);
        cout << "\n";
        char s2[] = { 'x', 'x', 't', 'e', 's', 't', 'x', 'x' };
        char x2[] = { 't', 'e', 's', 't' };
        const char *sub2 = findx(s2, x2, 8, 4);
        print_str(sub2, 6);
        cout << "\n";

        char str1[] = "atest";
        char str2[] = "btest";
        cout << str1 << " strcomp " << str2 << " is " << strcomp(str1, str2, 6, 6) << "\n";
        char str3[] = { 't', 'e', 's', 't', '1' };
        char str4[] = { 't', 'e', 's', 't', '1', 'a' };
        print_str(str3, 5);
        cout << " strcomp ";
        print_str(str4, 6);
        cout << " is " << strcomp(str3, str4, 5, 6) << "\n";
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
