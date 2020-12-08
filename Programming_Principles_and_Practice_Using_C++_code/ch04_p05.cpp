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
    cout << "Enter two double values and character (+, -, * or /)\n";
    double val1 = 0;
    double val2 = 0;
    char op = ' ';
    while (cin >> val1 && cin >> val2 && cin >> op)
    {
        switch (op)
        {
        case '+':
            cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << ".\n";
            break;
        case '-':
            cout << "The difference of " << val1 << " and " << val2 << " is " << val1 - val2 << ".\n";
            break;
        case '*':
            cout << "The product of " << val1 << " and " << val2 << " is " << val1 *val2 << ".\n";
            break;
        case '/':
            cout << "The ratio of " << val1 << " and " << val2 << " is " << val1 / val2 << ".\n";
            break;
        default:
            cout << "This is not a valid operation (use +, -, * or /)\n";
            break;
        }
    }
}
