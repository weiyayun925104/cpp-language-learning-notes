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
#include<climits>
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

template<typename T>
ostream &print_vector(const vector<T> &v, ostream &os)
{
    if (v.size() > 0)
    {
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << endl;
    }

    return os;
}

vector<int> string_lengths(const vector<string> &v)
{
    if (v.size() == 0)
    {
        error("string_lengths: argument is empty vector");
    }
    vector<int> lengths;
    for (int i = 0; i < v.size(); ++i)
    {
        lengths.push_back(v[i].size());
    }
    return lengths;
}

string longest_string(const vector<string> &v)
{
    if (v.size() == 0)
    {
        error("longest_string: argument is empty vector");
    }
    string ls;
    int maxl = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i].size() > maxl)
        {
            maxl = v[i].size();
            ls = v[i];
        }
    }
    return ls;
}

string shortest_string(const vector<string> &v)
{
    if (v.size() == 0)
    {
        error("shortest_string: argument is empty vector");
    }
    string ss = v[0];
    int minl = v[0].size();
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i].size() < minl)
        {
            minl = v[i].size();
            ss = v[i];
        }
    }
    return ss;
}

string alpha_first_string(const vector<string> &v)
{
    if (v.size() == 0)
    {
        error("alpha_first_string: argument is empty vector");
    }
    vector<string> v_cp = v;
    sort(v_cp.begin(), v_cp.end());
    return v_cp[0];
}

string alpha_last_string(const vector<string> &v)
{
    if (v.size() == 0)
    {
        error("alpha_last_string: argument is empty vector");
    }
    vector<string> v_cp = v;
    sort(v_cp.begin(), v_cp.end());
    return v_cp[v_cp.size() - 1];
}

int main()
{
    try
    {
        vector<string> string_v;
        string_v.push_back("first");
        string_v.push_back("second");
        string_v.push_back("third");
        string_v.push_back("fourth");
        string_v.push_back("fifth");
        string_v.push_back("sixth");
        string_v.push_back("seventh");
        cout << "Vector of strings:\n";
        print_vector(string_v, cout);
        vector<int> lengths = string_lengths(string_v);
        cout << "Vector of lengths:\n";
        print_vector(lengths, cout);
        cout << "Longest string: " << longest_string(string_v) << endl;
        cout << "Shortest string: " << shortest_string(string_v) << endl;
        cout << "Lexicographically first string: " << alpha_first_string(string_v) << endl;
        cout << "Lexicographically last string: " << alpha_last_string(string_v) << endl;
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
