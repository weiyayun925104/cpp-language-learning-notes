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
    {
        int a = 3;
        a = 4;
        int b = a;
        b = a + 5;
        a = a + 7;
        cout << a << ", " << b << endl;
    }

    {
        string a = "alpha";
        a = "beta";
        string b = a;
        b = a + "gamma";
        a = a + "delta";
        cout << a << ", " << b << endl;
    }

    {
        int y = 8;
        int x;

        x = 9;
        cout << x << ", " << y << endl;

        string t = "howdy!";
        string s;

        s = "G'day";
        cout << s << ", " << t << endl;
    }

    string previous = " ";
    string current;
    while (cin >> current)
    {
        if (previous == current)
        {
            cout << "repeated word: " << current << '\n';
        }
        previous = current;
    }
}
