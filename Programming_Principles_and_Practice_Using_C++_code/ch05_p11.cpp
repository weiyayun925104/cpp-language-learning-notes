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
#include <cstring>
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
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int main()
{
    try
    {
        char largest = 0;
        cout << "Do you just want to find the largest Fibonacci number (y/n)?\n";
        cin >> largest;
        if (!(largest == 'y' || largest == 'n' || largest == 'Y' || largest == 'N'))
        {
            error("Please enter either 'y' or 'n'");
        }
        vector<int> fib;
        fib.push_back(1);
        fib.push_back(1);
        if (largest == 'n' || largest == 'N')
        {
            int n = 0;
            cout << "How many Fibonacci numbers do you want to see?\n";
            cin >> n;
            if (n < 10)
            {
                error("Please enter a number >= 10");
            }
            for (int i = 2; i < n; ++i)
            {
                fib.push_back(fib[i - 1] + fib[i - 2]);
            }

            cout << "Fibonacci numbers:\n";
            for (int i = 0; i < n; ++i)
            {
                cout << fib[i] << endl;
            }
        }
        else
        {
            while (fib[fib.size() - 1] + fib[fib.size() - 2] > fib[fib.size() - 1])
            {
                fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
            }
            cout << "The biggest Fibonacci number to fit in an int is " << fib[fib.size() - 1] << endl;
        }

        return 0;
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception!\n";
        return 2;
    }
}
