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

struct Reading
{
    int hour;
    double temperature;
    Reading() : hour(0), temperature(0) { }
    Reading(int h, double t) : hour(h), temperature(t) { }
};

bool operator<(const Reading &r1, const Reading &r2)
{
    return r1.temperature < r2.temperature;
}

ostream &operator<<(ostream &os, const Reading &r)
{
    return os << '(' << r.hour << ',' << r.temperature << ')';
}

istream &operator>>(istream &is, Reading &r)
{
    int hour;
    char c1, c2, c3;
    double temperature;
    is >> c1 >> hour >> c2 >> temperature >> c3;
    if (!is)
    {
        return is;
    }
    if (c1 != '(' || c2 != ',' || c3 != ')')
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    r = Reading(hour, temperature);
    return is;
}

const int max_temp = 108;
const int min_temp = -44;

void fill_from_file(vector<Reading> &readings, const string &name)
{
    ifstream ist(name.c_str());
    if (!ist)
    {
        error("can't open input file " + name);
    }
    Reading r;
    while (ist >> r)
    {
        if (r.hour < 0 || r.hour > 23)
        {
            error("hour out of range");
        }
        if (r.temperature < min_temp || r.temperature > max_temp)
        {
            error("temperature out of range");
        }
        readings.push_back(r);
    }
}

void print_vector(const vector<Reading> &r)
{
    for (int i = 0; i < r.size(); ++i)
    {
        cout << r[i] << endl;
    }
}

int main()
{
    try
    {
        vector<Reading> readings;
        fill_from_file(readings, "ch10_p02.txt");

        sort(readings.begin(), readings.end());
        print_vector(readings);
        auto size = readings.size();
        auto mid = size / 2;
        double median;
        if (size % 2 == 0)
        {
            median = (readings[mid].temperature + readings[mid - 1].temperature) / 2;
        }
        else
        {
            median = readings[mid].temperature;
        }
        double sum = 0;
        for (int i = 0; i < readings.size(); ++i)
        {
            sum += readings[i].temperature;
        }
        double avg = sum / readings.size();

        cout << "median temperature: " << median << " F" << endl;
        cout << "average temperature: " << avg << " F" << endl;
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
