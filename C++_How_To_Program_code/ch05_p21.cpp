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

std::string getDay(int day)
{
    switch (day)
    {
    case 1:
        return "first";
    case 2:
        return "second";
    case 3:
        return "third";
    case 4:
        return "fourth";
    case 5:
        return "fifth";
    case 6:
        return "sixth";
    case 7:
        return "seventh";
    case 8:
        return "eighth";
    case 9:
        return "ninth";
    case 10:
        return "tenth";
    case 11:
        return "eleventh";
    case 12:
        return "twelfth";
    default:
        return "";
    }
}

void printVerse(int day)
{
    switch (day)
    {
    case 12:
        std::cout << "12 Drummers Drumming" << std::endl;
    case 11:
        std::cout << "Eleven Pipers Piping" << std::endl;
    case 10:
        std::cout << "Ten Lords a Leaping" << std::endl;
    case 9:
        std::cout << "Nine Ladies Dancing" << std::endl;
    case 8:
        std::cout << "Eight Maids a Milking" << std::endl;
    case 7:
        std::cout << "Seven Swans a Swimming" << std::endl;
    case 6:
        std::cout << "Six Geese a Laying" << std::endl;
    case 5:
        std::cout << "Five Gold Rings" << std::endl;
    case 4:
        std::cout << "Four Calling Birds" << std::endl;
    case 3:
        std::cout << "Three French Hens" << std::endl;
    case 2:
        std::cout << "Two Turtle Doves" << std::endl;
    case 1:
        cout << ((day > 1) ? "and a" : "A") << " Partridge in a Pear Tree\n";
    default:
        break;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        for (int i = 1; i <= 12; i++)
        {
            std::cout << "\nOn the " << getDay(i) << " day of Christmas\nmy true love sent to me:\n";
            printVerse(i);
        }
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
