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
    int count;
    cin >> count;
    string name;
    cin >> name;

    int c2 = count + 2;
    string s2 = name + " Jr. ";

    int c3 = count - 2;
    int age = -100;

    cout << count << ", "
         << name << ", "
         << c2 << ", "
         << s2 << ", "
         << c3 << ", "
         << age << endl;

    cout << "please enter a floating-point value: ";
    double n;
    cin >> n;
    cout << "n == " << n
         << "\nn+1 == " << n + 1
         << "\nthree times n == " << 3 * n
         << "\ntwice n == " << n + n
         << "\nn squared == " << n *n
         << "\nhalf of n == " << n / 2
         << "\nsquare root of n == " << sqrt(n)
         << endl;

    cout << "please enter your first and second names\n";
    string first;
    string second;
    cin >> first >> second;
    name = first + ' ' + second;
    cout << "Hello, " << name << '\n';

    if (first == second)
    {
        cout << "that's the same name twice\n";
    }
    else if (first < second)
    {
        cout << first << " is alphabetically before " << second << '\n';
    }
    else
    {
        cout << first << " is alphabetically after " << second << '\n';
    }
}
