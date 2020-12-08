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

double ctok(double c)
{
    if (c < -273.15)
    {
        error("Temperature below absolute zero!");
    }
    double k = c + 273.15;
    return k;
}

double ktoc(double k)
{
    if (k < 0)
    {
        error("Temperature below absolute zero!");
    }
    double c = k - 273.15;
    return c;
}

int main()
{
    try
    {
        double temp = 0;
        char unit = 0;
        double t_conv = 0;
        char unit_conv = 0;

        cout << "Enter temperature to be converted and unit (C or K):\n";
        cin >> temp >> unit;
        if (unit == 'c' || unit == 'C')
        {
            t_conv = ctok(temp);
            unit_conv = 'K';
        }
        else if (unit == 'k' || unit == 'K')
        {
            t_conv = ktoc(temp);
            unit_conv = 'C';
        }
        else
        {
            error("Illegal unit, must be C or K");
        }
        cout << t_conv << ' ' << unit_conv << endl;
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
