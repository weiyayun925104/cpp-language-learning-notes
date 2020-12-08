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
#include <limits>
#include <type_traits>

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
using std::istringstream;
using std::ostringstream;
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
using std::ios_base;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::numeric_limits;
using std::common_type;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
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

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}


double *get_from_jack(int *count)
{
    string ifname = "ch20_p02_in1.txt";
    ifstream ifs(ifname.c_str());
    if (!ifs)
    {
        error("Can't open input file " + ifname);
    }

    vector<double> v;
    double d;
    while (ifs >> d)
    {
        v.push_back(d);
    }

    *count = v.size();
    double *data = new double[*count];
    for (int i = 0; i < v.size(); ++i)
    {
        data[i] = v[i];
    }

    return data;
}

vector<double> *get_from_jill()
{
    string ifname = "ch20_p02_in2.txt";
    ifstream ifs(ifname.c_str());
    if (!ifs)
    {
        error ("Can't open input file " + ifname);
    }

    vector<double> *v = new vector<double>;
    double d;
    while (ifs >> d)
    {
        (*v).push_back(d);
    }

    return v;
}

double *high_ptr(double *first, double *last)
{
    double h = numeric_limits<double>::min();
    double *high = nullptr;
    for(double *p = first; p != last; ++p)
    {
        if (h < *p)
        {
            high = p;
            h = *p;
        }
    }
    return high;
}

template<typename In>
In high(In first, In last)
{
    if (first == last)
    {
        return In(nullptr);
    }
    In high = first;
    In p = first;
    ++p;
    for (; p != last; ++p)
    {
        if (*high < *p)
        {
            high = p;
        }
    }
    return high;
}

int main()
{
    try
    {
        int jack_count = 0;
        double *jack_data = get_from_jack(&jack_count);
        vector<double> *jill_data = get_from_jill();

        double *jack_high = high(jack_data, jack_data + jack_count);
        vector<double> &v = *jill_data;
        double *jill_high = high(&v[0], &v[0] + v.size());
        cout << "Jill's high " << *jill_high << "; Jack's high " << *jack_high << endl;

        delete[] jack_data;
        delete jill_data;
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
