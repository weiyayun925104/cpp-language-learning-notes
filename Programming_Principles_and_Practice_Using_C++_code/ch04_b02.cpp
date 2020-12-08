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
    {
        int a = 0;
        int b = 0;
        cout << "Please enter two integers\n";
        cin >> a >> b;

        if (a < b)
        {
            cout << "max(" << a << "," << b << ") is " << b << "\n";
        }
        else
        {
            cout << "max(" << a << "," << b << ") is " << a << "\n";
        }
    }

    {
        const double cm_per_inch = 2.54;
        int length = 1;
        char unit = ' ';
        cout << "Please enter a length followed by a unit (c or i):\n";
        cin >> length >> unit;

        cout << std::fixed;
        if (unit == 'i')
        {
            streamsize prec = cout.precision();
            cout << length << "in == " << setprecision(2) << cm_per_inch *length << setprecision(prec) << "cm\n";
        }
        else if (unit == 'c')
        {
            streamsize prec = cout.precision();
            cout << length << "cm == " << setprecision(2) << length / cm_per_inch << setprecision(prec) << "in\n";
        }
        else
        {
            cout << "Sorry, I don't know a unit called '" << unit << "'\n";
        }
    }

    {
        const double cm_per_inch = 2.54;
        int length = 1;
        char unit = 'a';
        cout << "Please enter a length followed by a unit (c or i):\n";
        cin >> length >> unit;
        cout << std::fixed;
        streamsize prec;
        switch (unit)
        {
        case 'i':
            prec = cout.precision();
            cout << length << "in == " << setprecision(2) << cm_per_inch *length << setprecision(prec) << "cm\n";
            break;
        case 'c':
            prec = cout.precision();
            cout << length << "cm == " << setprecision(2) << length / cm_per_inch << setprecision(prec) << "in\n";
            break;
        default:
            cout << "Sorry, I don't know a unit called '" << unit << "'\n";
            break;
        }
    }

    {
        cout << "Please enter a digit\n";
        char a;
        cin >> a;

        switch (a)
        {
        case '0':
        case '2':
        case '4':
        case '6':
        case '8':
            cout << a << " is even\n";
            break;
        case '1':
        case '3':
        case '5':
        case '7':
        case '9':
            cout << a << " is odd\n";
            break;
        default:
            cout << a << " is not a digit\n";
            break;
        }
    }

    {
        int a = 7;
        int b = 4;

        if (a <= b) { }
        else
        {
            int t = a;
            a = b;
            b = t;
        }
        cout << a << ", " << b << endl;
    }

    {
        for (int i = 0; i < 10; ++i)
        {
            cout << i << '\t' << (i * i) << '\n';
        }
        cout << endl;
        for (int i = 0; i < 10; i += 2)
        {
            cout << i << '\t' << (i * i) << '\n';
        }
    }
}
