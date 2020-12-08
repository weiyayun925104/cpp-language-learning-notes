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
using std::swap;
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

vector<int> reverse1(const vector<int> &v)
{
    vector<int> v_rev(v.size());
    for (int i = 0; i < v.size(); ++i)
    {
        v_rev[i] = v[v.size() - 1 - i];
    }
    return v_rev;
}

void reverse2(vector<int> &v)
{
    for (int i = 0; i < v.size() / 2; ++i)
    {
        swap(v[i], v[v.size() - 1 - i]);
    }
}

int main()
{
    try
    {
        vector<int> v1;
        vector<int> v2;
        v1.push_back(1);
        v1.push_back(3);
        v1.push_back(5);
        v1.push_back(7);
        v1.push_back(9);
        v2.push_back(2);
        v2.push_back(4);
        v2.push_back(6);
        v2.push_back(8);
        print("v1_pre", v1);
        vector<int> v1_rev = reverse1(v1);
        print("v1_post_val", v1);
        print("v1_rev", v1_rev);
        reverse2(v1);
        print("v1_post_ref", v1);
        print("v2_pre", v2);
        vector<int> v2_rev = reverse1(v2);
        print("v2_post_val", v2);
        print("v2_rev", v2_rev);
        reverse2(v2);
        print("v2_post_ref", v2);
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
