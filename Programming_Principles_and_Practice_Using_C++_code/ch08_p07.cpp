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

vector<string> name;
vector<double> age;

void enter_values()
{
    string s;
    cout << "Enter list of names, 'done' when done:\n";
    while (cin >> s && s != "done")
    {
        for (int i = 0; i < name.size(); ++i)
        {
            if (s == name[i]) { error("Duplicate name " + s); }
        }
        name.push_back(s);
    }

    for (int i = 0; i < name.size(); ++i)
    {
        cout << "Age of " << name[i] << ": ";
        double a;
        cin >> a;
        age.push_back(a);
    }
}

void print(const vector<string> &name, const vector<double> &age)
{
    if (name.size() != age.size()) { error("print: vectors must be same size"); }
    for (int i = 0; i < name.size(); ++i)
    {
        cout << '(' << name[i] << ',' << age[i] << ")\n";
    }
}

int find_index(const vector<string> &vec, const string &s)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == s)
        {
            return i;
        }
    }
    error("name not found");
}

int main()
{
    try
    {
        enter_values();
        cout << "Entered like this:\n";
        print(name, age);

        vector<string> name_orig = name;
        vector<double> age_orig = age;
        sort(name.begin(), name.end());
        for (int i = 0; i < name.size(); ++i)
        {
            age[i] = age_orig[find_index(name_orig, name[i])];
        }

        cout << "\nAfter sorting:\n";
        print(name, age);
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
