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
    int length = 20;
    int width = 40;
    int area = length * width;

    cout << length << ", " << width << ", " << area << endl;

    length = 99;

    {
        int perimeter = (length + width) * 2;
        cout << length << ", " << width << ", " << perimeter << endl;
    }

    {
        int perimeter = length * 2 + width * 2;
        cout << length << ", " << width << ", " << perimeter << endl;
    }

    {
        int perimeter = length + width / 2;
        cout << length << ", " << width << ", " << perimeter << endl;
    }

    const double pi = 3.14159265359;
    int r = 7;
    int v = 2 * pi / r;
    cout << pi << ", " << r << ", " << v << endl;

    const int max = 17;
    int val = 19;

    cout << max << ", " << val << endl;
    cout << max + 2 << ", " << val + 2 << endl;

    int a = 0;

    ++a;
    a += 1;
    a = a + 1;
    cout << a << endl;

    double d = 2.5;
    int i = 2;

    double d2 = d / i;
    int i2 = d / i;
    cout << d2 << ", " << i2 << endl;

    d2 = d / i + 1;
    i2 = d / i + 1;
    cout << d2 << ", " << i2 << endl;

    {
        double dc;
        cin >> dc;
        double df = 9 / 5 * dc + 32;
        cout << dc << ", " << df << endl;
    }

    {
        double dc;
        cin >> dc;
        double df = 9.0 / 5 * dc + 32;
        cout << dc << ", " << df << endl;
    }
}
