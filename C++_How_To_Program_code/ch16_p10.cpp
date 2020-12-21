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

int **initializeTable2D(int tableWidth, int tableLength)
{
    int **p_p_table2D = new int *[tableWidth];
    for (int j = 0; j < tableWidth; j++)
    {
        p_p_table2D[j] = new int[tableLength];
    }
    return p_p_table2D;
}

void disposeTable2D(int **p_p_table2D, int tableWidth)
{
    for (int j = 0; j < tableWidth; j++)
    {
        delete[] p_p_table2D[j];
    }

    delete[] p_p_table2D;
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

void printTable(int tableWidth, int tableLength, int tableRow, int ***p_p_table, int maxEntrySize)
{
    string horizontalBar = " _";
    for (int i = 0; i < tableWidth; i++)
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

    for (int i = 0; i <= tableWidth; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j <= tableLength; j++)
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
            for (int j = 0; j <= tableLength; j++)
            {
                if (j == 0)
                {
                    cout << i - 1;
                }
                else
                {
                    string value = numberWithPadding(p_p_table[tableRow - 1][i - 1][j - 1], maxEntrySize);
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
        int tableLength = 10;
        int tableWidth = 10;
        int tableHeight = 10;

        cout << "Please specify the size of the multiplication table (Default is 10x10x10): \n";
        cout << "Table length:";
        cin >> tableLength;

        cout << "Table width:";
        cin >> tableWidth;

        cout << "Table height:";
        cin >> tableHeight;


        int ***p_p_table3D;
        p_p_table3D = new int **[tableHeight];

        for (int i = 0; i < tableHeight; i++)
        {
            p_p_table3D[i] = initializeTable2D(tableWidth, tableLength);
        }


        for (int i = 0; i < tableHeight; i++)
        {
            for (int j = 0; j < tableWidth; j++)
            {
                for (int k = 0; k < tableLength; k++)
                {
                    p_p_table3D[i][j][k] = i * j * k;
                }
            }
        }
        int maxEntrySize = (tableWidth - 1) * (tableLength - 1) * (tableHeight - 1);

        int displayPlane = 1;
        while (displayPlane != 0)
        {
            cout << "Please specify which 2D table plane to print from the 3D table of " << tableHeight << " layers (0 to quit): \n";
            cout << "Current layer is: " << displayPlane << '\n';
            cin >> displayPlane;
            if (displayPlane == 0)
            {
                continue;
            }
            if (displayPlane < 0 || tableHeight < displayPlane)
            {
                cout << "You have selected a plane index that is out of bounds. Please try again.\n";
                continue;
            }
            printTable(tableWidth, tableLength, displayPlane, p_p_table3D, maxEntrySize);
        }

        for (int i = 0; i < tableHeight; i++)
        {
            disposeTable2D(p_p_table3D[i], tableWidth);
        }
        delete[] p_p_table3D;

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
