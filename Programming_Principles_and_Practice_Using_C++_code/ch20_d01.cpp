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

template<typename T, int N>
class array
{
public:
    typedef T value_type;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;

    T elems[N];

    iterator begin()
    {
        return elems;
    }
    const_iterator begin() const
    {
        return elems;
    }
    iterator end()
    {
        return elems + N;
    }
    const_iterator end() const
    {
        return elems + N;
    }

    size_type size() const
    {
        return N;
    }

    T &operator[](int n)
    {
        return elems[n];
    }
    const T &operator[](int n) const
    {
        return elems[n];
    }

    T *data()
    {
        return elems;
    }
    const T *data() const
    {
        return elems;
    }
};

template<typename Iter>
void my_print(Iter f, Iter e, const string &s)
{
    if (f != e)
    {
        cout << s << ": { ";
        cout << *f++;
        while (f != e)
        {
            cout << ", " << *f++;
        }
        cout << " }\n";
    }
}

template<typename Iter1, typename Iter2>
Iter2 my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
    while (f1 != e1)
    {
        *f2++ = *f1++;
    }
    return f2;
}

int main()
{
    try
    {
        const int arr_sz = 10;
        array<int, arr_sz> arr_int;
        for (int i = 0; i < arr_int.size(); ++i)
        {
            arr_int[i] = i;
        }
        my_print(arr_int.begin(), arr_int.end(), "arr_int");

        vector<int> vec_int;
        for (int i = 0; i < arr_sz; ++i)
        {
            vec_int.push_back(i);
        }
        my_print(vec_int.begin(), vec_int.end(), "vec_int");

        list<int> lst_int;
        for (int i = 0; i < arr_sz; ++i)
        {
            lst_int.push_back(i);
        }
        my_print(lst_int.begin(), lst_int.end(), "lst_int");

        array<int, arr_sz> arr_cp = arr_int;
        my_print(arr_cp.begin(), arr_cp.end(), "arr_cp");
        vector<int> vec_cp = vec_int;
        my_print(vec_cp.begin(), vec_cp.end(), "vec_cp");
        list<int> lst_cp = lst_int;
        my_print(lst_cp.begin(), lst_cp.end(), "lst_cp");

        for (array<int, arr_sz>::iterator p = arr_int.begin(); p != arr_int.end(); ++p)
        {
            *p += 2;
        }
        my_print(arr_int.begin(), arr_int.end(), "arr_int+=2");

        for (vector<int>::iterator p = vec_int.begin(); p != vec_int.end(); ++p)
        {
            *p += 3;
        }
        my_print(vec_int.begin(), vec_int.end(), "vec_int+=3");

        for (list<int>::iterator p = lst_int.begin(); p != lst_int.end(); ++p)
        {
            *p += 5;
        }
        my_print(lst_int.begin(), lst_int.end(), "lst_int+=5");

        vector<int>::iterator vec_iter = my_copy(arr_int.begin(), arr_int.end(), vec_int.begin());
        array<int, arr_sz>::iterator arr_iter = my_copy(lst_int.begin(), lst_int.end(), arr_int.begin());

        if (vec_iter != vec_int.begin() && arr_iter != arr_int.begin())
        {
            my_print(arr_int.begin(), arr_int.end(), "arr_int copied from lst_int");
            my_print(vec_int.begin(), vec_int.end(), "vec_int copied from arr_int");
            my_print(lst_int.begin(), lst_int.end(), "lst_int");
        }

        vec_iter = find(vec_int.begin(), vec_int.end(), 3);
        if (vec_iter != vec_int.end())
        {
            cout << "In vec_int, 3 has index " << vec_iter - vec_int.begin() << ".\n";
        }

        list<int>::iterator lst_iter = find(lst_int.begin(), lst_int.end(), 27);

        if (lst_iter != lst_int.end())
        {
            int idx = distance(lst_int.begin(), lst_iter);
            cout << "In lst_int, 27 has index " << idx << ".\n";
        }
        else
        {
            cout << "27 is not in lst_int.\n";
        }
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
