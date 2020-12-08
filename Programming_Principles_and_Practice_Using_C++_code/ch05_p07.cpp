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

double a, b, c;
bool do_check;

double found(double x)
{
    if (!do_check)
    {
        return x;
    }
    else
    {
        const double epsilon = 1e-7;
        double e = a * x * x + b * x + c;
        if (e == 0)
        {
            return x;
        }
        if (epsilon < e)
        {
            cout << "poor root; off by " << e << endl;
        }
        else if (e < -epsilon)
        {
            cout << "poor root; off by " << e << endl;
        }
        return x;
    }
}

void quad_solver()
{
    while (cin >> a && cin >> b && cin >> c)
    {
        if (a == 0)
        {
            if (b == 0)
            {
                cout << "no root (x isn't used)\n";
            }
            else
            {
                cout << "x = " << found(-c / b) << endl;
            }
        }
        else if (b == 0)
        {
            double ca = -c / a;
            if (ca == 0)
            {
                cout << "x = 0\n";
            }
            else if (ca < 0)
            {
                cout << "no real roots\n";
            }
            else
            {
                cout << "two real roots: x = " << found(sqrt(ca)) << " and " << found(-sqrt(ca)) << endl;
            }
        }
        else
        {
            double delta = b * b - 4 * a * c;
            if (delta == 0)
            {
                cout << "one real root: " << found(-b / (2 * a)) << endl;
            }
            else if (delta < 0)
            {
                cout << "no real roots\n";
            }
            else
            {
                cout << "two real roots: " << found((-b + sqrt(delta)) / (2 * a)) << " and " << found((-b - sqrt(delta)) / (2 * a)) << endl;
            }
        }
        cout << "Enter coefficients for quadratic equation a*x^2 + b*x + c = 0\n";
    }
}

int main()
{
    try
    {
        cout << "Should your solutions be checked?\n";
        char check = 0;
        cin >> check;
        if (check == 'y' || check == 'Y')
        {
            do_check = true;
        }
        else if (check == 'n' || check == 'N')
        {
            do_check = false;
        }
        else
        {
            error("answer not recognised (try 'y' or 'n')");
        }
        cout << "Enter coefficients for quadratic equation a*x^2 + b*x + c = 0\n";
        quad_solver();
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
