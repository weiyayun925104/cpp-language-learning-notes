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

template<typename T>
T maxv(const vector<T> &v)
{
    if (v.size() == 0)
    {
        error("maxv: argument vector is empty");
    }
    T v_max = v[0];
    if (v.size() == 1)
    {
        return v_max;
    }
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] > v_max)
        {
            v_max = v[i];
        }
    }
    return v_max;
}

template<typename T>
T minv(const vector<T> &v)
{
    if (v.size() == 0)
    {
        error("minv: argument vector is empty");
    }
    T v_min = v[0];
    if (v.size() == 1)
    {
        return v_min;
    }
    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] < v_min)
        {
            v_min = v[i];
        }
    }
    return v_min;
}

template<typename T>
double meanv(const vector<T> &v)
{
    if (v.size() == 0)
    {
        error("meanv: argument vector is empty");
    }
    T v_sum = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        v_sum += v[i];
    }
    return double(v_sum) / v.size();
}

template<typename T>
double medianv(vector<T> v)
{
    if (v.size() == 0)
    {
        error("medianv: argument vector is empty");
    }
    sort(v.begin(), v.end());
    auto size = v.size();
    auto mid = size / 2;
    return size % 2 == 0 ? double(v[mid] + v[mid - 1]) / 2 : v[mid];
}

template <typename T>
class Vector_properties
{
public:
    Vector_properties() : smallest(0), largest(0), mean(0), median(0) { }
    T smallest;
    T largest;
    double mean;
    double median;
};

template <typename T>
Vector_properties<T> get_props(const vector<T> &v)
{
    Vector_properties<T> vec_props;
    vec_props.largest = maxv<T>(v);
    vec_props.smallest = minv<T>(v);
    vec_props.mean = meanv<T>(v);
    vec_props.median = medianv<T>(v);
    return vec_props;
}

int main()
{
    try
    {
        vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.push_back(5);
        v.push_back(7);
        v.push_back(9);
        v.push_back(8);
        v.push_back(6);
        v.push_back(4);
        v.push_back(2);
        v.push_back(99);
        Vector_properties<int> vec_props = get_props<int>(v);

        cout << "Vector:\n";
        print_vector(v, cout);
        cout << endl;

        cout << "max: " << vec_props.largest << endl;
        cout << "min: " << vec_props.smallest << endl;
        cout << "mean: " << vec_props.mean << endl;
        cout << "median: " << vec_props.median << endl;
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
