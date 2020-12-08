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

map<string, int> clean_txt(const string &fname)
{
    ifstream ifs(fname);
    if (!ifs)
    {
        error("Can not open file " + fname);
    }
    ostringstream oss;

    char ch;
    while (ifs.get(ch))
    {
        if (ispunct(ch) && ch != '\'')
        {
            ch = ' ';
        }
        oss << char(tolower(ch));
    }

    map<string, int> words;
    istringstream iss(oss.str());
    string w;
    while (iss >> w)
    {
        if (w == "can't")
        {
            ++words["cannot"];
        }
        else if (w == "shan't")
        {
            ++words["shall"];
            ++words["not"];
        }
        else if (w == "won't")
        {
            ++words["will"];
            ++words["not"];
        }
        else if (w == "let's")
        {
            ++words["let"];
            ++words["us"];
        }
        else if (w == "'" || w.size() == 2 && w[0] == '\'')
        {
            // do nothing, don't add word
        }
        else if (w.size() >= 3 && *(w.end() - 2) == '\'')
        {
            switch (w.back())
            {
            case 'd':
                ++words["would"];
                ++words[w.substr(0, w.size() - 2)];
                break;
            case 'm':
                ++words["am"];
                ++words[w.substr(0, w.size() - 2)];
                break;
            case 's':
                ++words["is"];
                ++words[w.substr(0, w.size() - 2)];
                break;
            case 't':
                ++words["not"];
                ++words[w.substr(0, w.size() - 3)];
                break;
            default:
                break;
            }
        }
        else if (w.size() >= 4 && *(w.end() - 3) == '\'')
        {
            switch (*(w.end() - 2))
            {
            case 'l':
                ++words["will"];
                ++words[w.substr(0, w.size() - 3)];
                break;
            case 'r':
                ++words["are"];
                ++words[w.substr(0, w.size() - 3)];
                break;
            case 'v':
                ++words["have"];
                ++words[w.substr(0, w.size() - 3)];
                break;
            default:
                break;
            }
        }
        else
        {
            ++words[w];
        }
    }

    typedef map<string, int>::iterator Iter;
    for (Iter p = words.begin(); p != words.end(); ++p)
    {
        Iter q = p;
        ++q;
        if (q != words.end() && q->first[0] == p->first[0]
                && q->first.size() == p->first.size() + 1
                && q->first == p->first + "s")
        {
            q = words.erase(q);
        }
    }

    return words;
}

int main()
{
    try
    {
        string ifname = "ch21_p13_in.txt";
        map<string, int> words = clean_txt(ifname);
        typedef map<string, int>::iterator Iter;
        for (Iter p = words.begin(); p != words.end(); ++p)
        {
            cout << setw(12) << left << p->first << '\t' << p->second << '\n';
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
