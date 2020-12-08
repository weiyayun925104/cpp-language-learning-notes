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

bool is_palindrome(const string &s)
{
    string s_cp;
    for (int i = s.size() - 1; i >= 0; --i)
    {
        s_cp.push_back(s[i]);
    }
    if (s == s_cp)
    {
        return true;
    }
    return false;
}

bool is_palindrome(const char s[], int n)
{
    char *s_cp = new char[n + 1];
    s_cp[n] = 0;
    for (int i = 0; i < n; ++i)
    {
        s_cp[n - 1 - i] = s[i];
    }

    if (strcmp(s, s_cp))
    {
        delete[] s_cp;
        return false;
    }

    delete[] s_cp;
    return true;
}

bool is_palindrome(const char *first, const char *last)
{
    char *s_cp = new char[last - first + 2];
    char *s_cp_ptr = s_cp;
    while (last >= first)
    {
        *s_cp_ptr = *last;
        ++s_cp_ptr;
        --last;
    }
    *s_cp_ptr = '\0';

    if (strcmp(first, s_cp))
    {
        delete[] s_cp;
        return false;
    }

    delete[] s_cp;
    return true;
}

istream &read_word(istream &is, char *buffer, int max)
{
    is.getline(buffer, max);
    return is;
}

int main()
{
    try
    {
        string s;
        while (getline(cin, s, '\n') && s != "")
        {
            cout << s << " is";
            if (!is_palindrome(s))
            {
                cout << " not";
            }
            cout << " a palindrome\n";
        }

        const int max = 128;
        char s2[max];
        while (read_word(cin, s2, max) && strlen(s2) > 0)
        {
            cout << s2 <<  " is";
            if (!is_palindrome(s2, strlen(s2)))
            {
                cout << " not";
            }
            cout << " a palindrome\n";
        }

        while (read_word(cin, s2, max) && strlen(s2) > 0)
        {
            cout << s2 << " is";
            if (!is_palindrome(&s2[0], &s2[strlen(s2) - 1]))
            {
                cout << " not";
            }
            cout << " a palindrome\n";
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
