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
    double x = 1.5;
    double y = x;
    double z = 2.0 + x;

    cout << x << ", " << y << ", " << z << endl;

    char c1 = 'x';
    int i1 = c1;
    int i2 = 'x';
    char c2 = i1;

    cout << c1 << ", " << i1 << ", " << i2 << ", " << c2 << endl;

    double d1 = 2.3;
    double d2 = d1 + 2;

    cout << d1 << ", " << d2 << endl;

    if (d1 < 0)
    {
        error("d1 is negative");
    }

    int a = 20000;
    char c = a;
    int b = c;

    cout << a << ", " << b << ", " << c << endl;

    if (a != b)
    {
        cout << "oops!: " << a << "!=" << b << '\n';
    }
    else
    {
        cout << "Wow! We have large characters\n";
    }

    {
        double d = 0;
        while (cin >> d)
        {
            int i = d;
            char c = i;
            int i2 = c;
            cout << d << ", " << i << ", " << c << ", " << i2 << endl;
        }

        double x = 2.7;
        int y = x;
        int a = 1000;
        char b = a;
        cout << x << ", " << y << ", " << a << ", " << int(b) << endl;
    }

}
