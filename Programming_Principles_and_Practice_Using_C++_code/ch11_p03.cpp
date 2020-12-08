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

enum num_format
{
    decimal, octal, hexadecimal
};

ostream &operator<<(ostream &os, num_format nf)
{
    switch (nf)
    {
    case decimal:
        return os << "decimal\t";
    case octal:
        return os << "octal\t";
    case hexadecimal:
        return os << "hexadecimal";
    default:
        error("illegal value of number_format");
    }
}

void printnum(int n, num_format nf)
{
    cout << showbase;
    switch (nf)
    {
    case decimal:
        cout << dec << setw(12) << n;
        break;
    case octal:
        cout << oct << setw(12) << n;
        break;
    case hexadecimal:
        cout << hex << setw(12) << n;
        break;
    }
    cout << ' ' << nf << "\tconverts to " << dec << setw(12) << n << ' ' << decimal << endl;
}

int main()
{
    try
    {
        cout << "Enter space-separated integers in decimal, octal or hexadecimal notation" << endl
             << "(using 0 and 0x prefixes), any letter to finish:" << endl;
        int n = 0;
        char ch;
        while (cin >> ch)
        {
            if (ch == '0')
            {
                if (cin.get(ch))
                {
                    if (ch == 'x')
                    {
                        cin >> hex >> n;
                        printnum(n, hexadecimal);
                    }
                    else if (isdigit(ch))
                    {
                        cin.unget();
                        cin >> oct >> n;
                        printnum(n, octal);
                    }
                    else
                    {
                        cin.unget();
                        printnum(0, octal);
                    }
                }
                else
                {
                    printnum(0, octal);
                    break;
                }
            }
            else if (isdigit(ch))
            {
                cin.unget();
                cin >> dec >> n;
                printnum(n, decimal);
            }
            else
            {
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
