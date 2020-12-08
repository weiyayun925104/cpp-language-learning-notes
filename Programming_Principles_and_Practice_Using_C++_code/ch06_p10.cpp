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
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

double factorial(int n)
{
    if (n < 0)
    {
        error("factorial of a negative number is not defined");
    }
    if (n == 0)
    {
        return 1;
    }
    double prod = 1;
    for (int i = 1; i <= n; ++i)
    {
        prod *= i;
        if (prod > 1.0e+16)
        {
            error("factorial got too large");
        }
    }
    return prod;
}

double permutations(int a, int b)
{
    if (a < b)
    {
        error("for P(a,b), a cannot be smaller than b");
    }
    double prod = 1;
    for (int i = a - b + 1; i <= a; ++i)
    {
        prod *= i;
        if (prod > 1.0e+16)
        {
            error("number too large for permutation function");
        }
    }
    return prod;
}

double combinations(int a, int b)
{
    return permutations(a, b) / factorial(b);
}

int main()
{
    cout << std::fixed << std::noshowpoint << setprecision(0);
    try
    {
        int a = 0;
        int b = 0;
        cout << "Enter two integers to get permutations or combinations from:\n";
        while (cin >> a && cin >> b)
        {
            char ch = 0;
            cout << "(P)ermutations or (c)ombinations or (q)uit?\n";
            while (cin >> ch)
            {
                while (cin.get() != '\n')
                {
                    continue;
                }
                if (ch == 'q')
                {
                    break;
                }
                double res = 0;
                switch (ch)
                {
                case 'p':
                case 'P':
                    res = permutations(a, b);
                    cout << "P(" << a << ',' << b << ") = " << res << endl;
                    break;
                case 'c':
                case 'C':
                    res = combinations(a, b);
                    cout << "C(" << a << ',' << b << ") = " << res << endl;
                    break;
                default:
                    cout << "please enter 'p' or 'c' or 'q'\n";
                    break;
                }
                cout << "(P)ermutations or (c)ombinations or (q)uit?\n";
            }
            cout << "Enter two integers to get permutations or combinations from:\n";
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
