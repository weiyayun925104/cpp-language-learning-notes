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
using std::setw;
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

void print(const string &label, const vector<string> &v)
{
    cout << label << " (" << v.size() << "): {\n";
    int i;
    for (i = 0; i < v.size(); ++i)
    {
        cout << setw(11) << v[i];
        if (i < v.size() - 1)
        {
            cout << " ";
        }
        if (i % 3 == 2)
        {
            cout << endl;
        }
    }
    if (i % 3 != 0)
    {
        cout << endl;
    }
    cout << "}\n";
}

vector<string> reverse1(const vector<string> &v)
{
    vector<string> v_rev(v.size());
    for (int i = 0; i < v.size(); ++i)
    {
        v_rev[i] = v[v.size() - 1 - i];
    }
    return v_rev;
}

void reverse2(vector<string> &v)
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
        vector<string> v1;
        vector<string> v2;
        v1.push_back("one");
        v1.push_back("three");
        v1.push_back("five");
        v1.push_back("seven");
        v1.push_back("nine");
        v2.push_back("two");
        v2.push_back("four");
        v2.push_back("six");
        v2.push_back("eight");
        print("v1_pre", v1);
        vector<string> v1_rev = reverse1(v1);
        print("v1_post_val", v1);
        print("v1_rev", v1_rev);
        reverse2(v1);
        print("v1_post_ref", v1);
        print("v2_pre", v2);
        vector<string> v2_rev = reverse1(v2);
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
