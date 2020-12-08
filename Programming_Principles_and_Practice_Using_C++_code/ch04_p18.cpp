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
    cout << "Enter coefficients a, b and c of ax^2 + bx + c = 0:\n";
    double a = 0;
    double b = 0;
    double c = 0;
    while (cin >> a && cin >> b && cin >> c)
    {
        double delta = b * b - 4 * a * c;
        if (delta < 0)
        {
            cout << "Sorry, no complex math here - can't solve that! Try again:\n";
        }
        else if (delta == 0)
        {
            double x = -b / (2 * a);
            cout << "Just one solution: x = " << x << endl;
        }
        else
        {
            double x1 = (-b + sqrt(delta)) / (2 * a);
            double x2 = (-b - sqrt(delta)) / (2 * a);
            cout << "Two solutions: x1 = " << x1 << ", x2 = " << x2 << endl;
        }
    }
}
