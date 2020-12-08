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

void print_until_s(const vector<string> &v, const string &quit)
{
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] == quit)
        {
            return;
        }
        cout << v[i] << endl;
    }
}

void print_until_ss(const vector<string> &v, const string &quit)
{
    int counter = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] == quit)
        {
            if (counter == 1)
            {
                return;
            }
            else
            {
                ++counter;
            }
        }
        cout << v[i] << endl;
    }
}

int main()
{
    try
    {
        vector<string> v;
        v.push_back("one");
        v.push_back("word");
        v.push_back("and");
        v.push_back("then");
        v.push_back("another");
        v.push_back("word");
        cout << "print_until_s:\n";
        print_until_s(v, "word");
        cout << "print_until_ss:\n";
        print_until_ss(v, "word");
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
