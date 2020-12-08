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

char *cat_dot(const char *s1, const char *s2)
{
    const char *p = s1;
    int ctr = 0;
    while (*p != '\0')
    {
        ++ctr;
        ++p;
    }
    p = s2;
    while (*p != '\0')
    {
        ++ctr;
        ++p;
    }

    char *res = new char[ctr + 2];

    p = s1;
    char *res_ptr = res;
    while (*p != '\0') { *res_ptr++ = *p++; }
    *res_ptr++ = '.';
    p = s2;
    while (*p != '\0') { *res_ptr++ = *p++; }
    *res_ptr = '\0';

    return res;
}

char *cat_dot2(const char *s1, const char *s2, const char *s3)
{
    const char *p = s1;
    int ctr = 0;
    while (*p != '\0')
    {
        ++ctr;
        ++p;
    }
    p = s2;
    while (*p != '\0')
    {
        ++ctr;
        ++p;
    }
    p = s3;
    while (*p != '\0')
    {
        ++ctr;
        ++p;
    }

    char *res = new char[ctr + 1];

    p = s1;
    char *res_ptr = res;
    while (*p != '\0') { *res_ptr++ = *p++; }
    p = s3;
    while (*p != '\0') { *res_ptr++ = *p++; }
    p = s2;
    while (*p != '\0') { *res_ptr++ = *p++; }
    *res_ptr = '\0';

    return res;
}

int main()
{
    try
    {
        char *res = cat_dot("Niels", "Bohr");
        cout << res << "\n";
        delete[] res;

        res = cat_dot2("Niels", "Bohr", " dot ");
        cout << res << "\n";
        delete[] res;

        char a[] = "Niels";
        char b[] = "Bohr";
        res = cat_dot(a, b);
        cout << res << "\n";
        delete[] res;

        const char *ap = "Niels";
        const char *bp = "Bohr";
        res = cat_dot(a, b);
        cout << res << "\n";
        delete[] res;

        char *as = new char[6];
        for (int i = 0; i < 6; ++i) { as[i] = ap[i]; }
        char *bs = new char[5];
        for (int i = 0; i < 5; ++i) { bs[i] = bp[i]; }
        res = cat_dot(as, bs);
        cout << res << "\n";
        delete[] res;
        delete[] bs;
        delete[] as;
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
