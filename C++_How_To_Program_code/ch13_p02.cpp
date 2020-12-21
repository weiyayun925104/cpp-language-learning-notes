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
using std::right;
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

const int LIM = 20;

struct planet
{
    char name[LIM];
    double population;
    double g;
};

const char *file = "planets.dat";

inline void eatline()
{
    while (std::cin.get() != '\n') continue;
}

int main(int argc, const char *argv[])
{
    try
    {
        planet pl;
        cout << fixed << right;

        ifstream fin;
        fin.open(file, ios_base::in | ios_base::binary);
        if (fin.is_open())
        {
            cout << "Here are the current contents of the "
                 << file << " file:\n";
            while (fin.read((char *)&pl, sizeof pl))
            {
                cout << setw(20) << pl.name << ": "
                     << setprecision(0) << setw(12) << pl.population
                     << setprecision(2) << setw(6) << pl.g << endl;
            }
            fin.close();
        }

        ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);
        if (!fout.is_open())
        {
            cerr << "Can't open " << file << " file for output:\n";
            exit(EXIT_FAILURE);
        }

        cout << "Enter planet name (enter a blank line to quit):\n";
        cin.get(pl.name, 20);
        while (pl.name[0] != '\0')
        {
            eatline();
            cout << "Enter planetary population: ";
            cin >> pl.population;
            cout << "Enter planet's acceleration of gravity: ";
            cin >> pl.g;
            eatline();
            fout.write((char *)&pl, sizeof pl);
            cout << "Enter planet name (enter a blank line to quit):\n";
            cin.get(pl.name, 20);
        }
        fout.close();

        fin.clear();
        fin.open(file, ios_base::in | ios_base::binary);
        if (fin.is_open())
        {
            cout << "Here are the new contents of the "
                 << file << " file:\n";
            while (fin.read((char *)&pl, sizeof pl))
            {
                cout << setw(20) << pl.name << ": "
                     << setprecision(0) << setw(12) << pl.population
                     << setprecision(2) << setw(6) << pl.g << endl;
            }
            fin.close();
        }
        cout << "Done.\n";

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
