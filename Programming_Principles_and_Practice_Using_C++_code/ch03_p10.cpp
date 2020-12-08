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
    string operation;
    double d1 = 0;
    double d2 = 0;
    double res = 0;
    cout << "Please enter an operation (+, -, *, /, plus, minus, mul, div) followed by two operands\n";
    while (cin >> operation && cin >> d1 && cin >> d2)
    {
        if (operation == "+" || operation == "plus")
        {
            res = d1 + d2;
        }
        else if (operation == "-" || operation == "minus")
        {
            res = d1 - d2;
        }
        else if (operation == "*" || operation == "mul")
        {
            res = d1 * d2;
        }
        else if (operation == "/" || operation == "div")
        {
            if (d2 == 0)
            {
                operation = "divzero";
            }
            else
            {
                res = d1 / d2;
            }
        }
        else
        {
            operation = "unknown";
        }
        if (operation == "unknown")
        {
            cout << "I don't know this operator!\n";
        }
        else if (operation == "divzero")
        {
            cout << "No division by zero!\n";
        }
        else
        {
            cout << d1 << ' ' << operation << ' ' << d2 << " = " << res << '\n';
        }
        cout << "Please enter an operation (+, -, *, /, plus, minus, mul, div) followed by two operands\n";
    }
    return 0;
}
