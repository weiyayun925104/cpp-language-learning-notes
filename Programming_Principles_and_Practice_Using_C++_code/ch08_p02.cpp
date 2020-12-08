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
#include <utility>
#include <random>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
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
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::search;
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
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

void print(const string &label, const vector<int> &v)
{
    cout << label << " (" << v.size() << "): {\n";
    int i;
    for (i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i < v.size() - 1)
        {
            cout << ", ";
        }
        if (i % 8 == 7)
        {
            cout << endl;
        }
    }
    if (i % 8 != 0)
    {
        cout << endl;
    }
    cout << "}\n";
}

void fibonacci(int x, int y, vector<int> &v, int n)
{
    if (n < 1)
    {
        error("there must be at least one number in the series");
    }
    v.push_back(x);
    if (n == 1) return;
    v.push_back(y);
    if (n == 2) return;
    for (int i = 2; i < n; ++i)
    {
        v.push_back(v[i - 2] + v[i - 1]);
    }
}

int main()
{
    try
    {
        int x = 0;
        int y = 0;
        vector<int> v;
        int n = 0;

        cout << "Enter first number in Fibonacci sequence: ";
        cin >> x;
        cout << "Enter second number in Fibonacci sequence: ";
        cin >> y;
        cout << "Enter number of elements in sequence: ";
        cin >> n;

        fibonacci(x, y, v, n);

        string s = "Your Fibonacci sequence";
        print(s, v);
    }
    catch (exception &e)
    {
        cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "Oops: unknown exception!\n";
        return 2;
    }
}
