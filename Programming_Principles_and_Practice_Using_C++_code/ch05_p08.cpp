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

int main()
{
    try
    {
        vector<int> vals;
        int val = 0;
        int n = 0;

        cout << "Please enter the number of values you want to sum:\n";
        cin >> n;
        if (n < 1)
        {
            error("You have to sum at least one value!");
        }
        cout << "Please enter some integers (press end to stop)\n";
        while (cin >> val)
        {
            vals.push_back(val);
        }

        if (vals.size() < n)
        {
            error("You wanted to sum more values than you entered");
        }

        int sum = 0;
        cout << "The sum of the first ";
        if (n > 1)
        {
            cout << n << " numbers";
        }
        else
        {
            cout << "number";
        }
        cout << " ( ";
        for (int i = 0; i < n; ++i)
        {
            sum += vals[i];
            cout << vals[i] << ' ';
        }
        cout << ") is " << sum << ".\n";

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
