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

int get_mode(vector<int> v)
{
    if (v.size() == 0)
    {
        throw domain_error("call get_mode for empty vector");
    }

    sort(v.begin(),v.end());
    int mode_cdt = v[0];
    int mode_cdt_ctr = 1;
    int mode = v[0];
    int mode_ctr = 1;
    for (int i = 1; i<v.size(); ++i)
    {
        if (v[i]==mode_cdt)
        {
            ++mode_cdt_ctr;
            if (mode_cdt_ctr>mode_ctr)
            {
                mode = mode_cdt;
                mode_ctr = mode_cdt_ctr;
            }
        }
        else
        {
            mode_cdt = v[i];
            mode_cdt_ctr = 1;
        }
    }
    cout << mode << " appears " << mode_ctr << " times.\n";
    return mode;
}

int main()
{
    int n = 0;
    int smallest = 0;
    int largest = 0;
    int mode = 0;
    vector<int> vals;
    bool is_first = true;

    cout << "Enter sequence of integers:\n";

    while (cin >> n)
    {
        if (n < smallest || is_first)
        {
            smallest = n;
        }
        if (n > largest || is_first)
        {
            largest = n;
        }
        vals.push_back(n);
        is_first = false;
    }

    mode = get_mode(vals);
    cout << "smallest value: " << smallest << endl;
    cout << "largest value: " << largest << endl;
    cout << "mode: " << mode << endl;

    cout << "values:" << endl;
    for (int i = 0; i<vals.size(); ++i)
    {
        cout << vals[i] << endl;
    }
    return 0;
}
