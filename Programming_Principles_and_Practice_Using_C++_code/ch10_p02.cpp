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

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
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

struct Reading
{
    int hour;
    double temperature;
    Reading(int h, double t) : hour(h), temperature(t) { }
};

ostream &operator<<(ostream &os, const Reading &r)
{
    return os << '(' << r.hour << ',' << r.temperature << ')';
}

const int max_temp = 107;
const int min_temp = -43;

Reading create_reading(mt19937 &e)
{
    int h = nrand_two(0, 24, e);
    double t = nrand_two(min_temp, max_temp+1, e) + nrand_two(-10, 11, e) / double(10);
    return Reading(h, t);
}

void write_to_file(const vector<Reading> &r, const string &name)
{
    ofstream ost(name.c_str());
    if (!ost) { error("can't open output file " + name); }
    for (int i = 0; i < r.size(); ++i)
    {
        ost << r[i] << endl;
    }
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 engine(seed);
    try
    {
        vector<Reading> readings;
        for (int i = 0; i < 10; ++i)
        {
            readings.push_back(create_reading(engine));
        }

        write_to_file(readings, "ch10_p02.txt");
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
