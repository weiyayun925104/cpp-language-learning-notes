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
    double d = 0;
    double d_conv = 0;
    double smallest = 0;
    double largest = 0;
    double sum = 0;
    vector<double> vals;
    int ctr = 0;
    string unit;
    bool is_first = true;
    bool is_valid = true;
    while (cin >> d && cin >> unit)
    {
        if (unit == "cm")
        {
            d_conv = d / 100;
        }
        else if (unit == "m")
        {
            d_conv = d;
        }
        else if (unit == "in")
        {
            d_conv = d * 0.0254;
        }
        else if (unit == "ft")
        {
            d_conv = d * 0.0254 * 12;
        }
        else
        {
            is_valid = false;
        }
        if (is_valid)
        {
            cout << d << ' ' << unit;
            if (d_conv < smallest || is_first)
            {
                smallest = d_conv;
                cout << " the smallest so far";
            }
            if (d_conv > largest || is_first)
            {
                largest = d_conv;
                cout << " the largest so far";
            }
            vals.push_back(d_conv);
            sum += d_conv;
            ++ctr;
            is_first = false;
        }
        else
        {
            cout << "invalid unit";
        }
        cout << endl;
        is_valid = true;
    }
    cout << "smallest value: " << smallest << " m\n";
    cout << "largest value: " << largest << " m\n";
    cout << "number of values: " << ctr << endl;
    cout << "sum of values: " << sum << " m\n";
    sort(vals.begin(), vals.end());
    cout << "values:" << endl;
    for (int i = 0; i < vals.size(); ++i)
    {
        cout << vals[i] << " m\n";
    }
    return 0;
}
