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
using std::fstream;
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

int numberOfPaddingItems(int number, int maxSize)
{
    string numberAsString = to_string(number);
    string maxSizeAsString = to_string(maxSize);

    return (maxSizeAsString.length() - numberAsString.length());
}

string numberWithPadding(int number, int maxSize)
{
    string numberAsString = to_string(number);
    string zeros;
    int paddingCount = numberOfPaddingItems(number, maxSize);
    if (paddingCount > 0)
    {
        for (int i = 0; i < paddingCount; i++)
        {
            zeros += '0';
        }
        numberAsString = zeros + numberAsString;
    }
    return numberAsString;
}

void printBoard(int tableSize, int **p_p_table, int maxEntrySize)
{
    string horizontalBar = " _";
    for (int i = 0; i < tableSize; i++)
    {
        horizontalBar += "__";
        int paddingCount = numberOfPaddingItems(1, maxEntrySize);
        if (paddingCount > 0)
        {
            for (int j = 0; j < paddingCount; j++)
            {
                horizontalBar += "_";
            }
        }
    }

    for (int i = 0; i <= tableSize; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j <= tableSize; j++)
            {
                if (j == 0)
                {
                    cout << " ";
                }
                else
                {
                    cout << " " << numberWithPadding(j - 1, maxEntrySize);
                }
            }
            cout << "\n";
        }
        else
        {
            cout << horizontalBar << "\n";
            for (int j = 0; j <= tableSize; j++)
            {
                if (j == 0)
                {
                    cout << i - 1;
                }
                else
                {
                    string value = numberWithPadding(p_p_table[i - 1][j - 1], maxEntrySize);
                    cout << "|" << value;
                }
            }
            cout << "|\n";
        }
    }
    cout << horizontalBar << "\n\n";
}

int main(int argc, const char *argv[])
{
    try
    {
        int tableSize = 10;

        cout << "Please specify the size of the multiplication table (Default is 10x10): ";
        cin >> tableSize;

        int **p_p_table;
        p_p_table = new int *[tableSize];

        for (int i = 0; i < tableSize; i++)
        {
            p_p_table[i] = new int[tableSize];
        }

        for (int i = 0; i < tableSize; i++)
        {
            for (int j = 0; j < tableSize; j++)
            {
                p_p_table[i][j] = i * j;
            }
        }
        int maxEntrySize = (tableSize - 1) * (tableSize - 1);
        printBoard(tableSize, p_p_table, maxEntrySize);

        for (int i = 0; i < tableSize; i++)
        {
            delete [] p_p_table[i];
        }
        delete [] p_p_table;

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
