#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <bitset>
#include <regex>
#include <stack>
#include <queue>
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
#include <initializer_list>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
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
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::istream_iterator;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::replace_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::streampos;
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
using std::ios;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::right;
using std::flush;
using std::numeric_limits;
using std::common_type;
using std::reverse;
using std::begin;
using std::end;
using std::initializer_list;
using std::function;
using std::bind;
using std::out_of_range;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::uninitialized_copy_n;
using std::uninitialized_fill_n;
using std::make_shared;
using std::make_unique;
using std::tuple;
using std::make_tuple;
using std::tuple_size;
using std::tuple_element;
using std::bitset;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::regex_replace;
using std::smatch;
using std::ssub_match;
using std::sregex_iterator;

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

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(const int &min, const int &max)
{
    return std::uniform_int_distribution<int> {min, max}(gen);
}

template <typename T>
inline void PRINT_ELEMENTS (const T &coll, const std::string &optstr = "")
{
    std::cout << optstr;
    for (const auto  &elem : coll)
    {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

template <typename InputIterator, typename Tp>
inline InputIterator find_before (InputIterator first, InputIterator last, const Tp &val)
{
    if (first == last)
    {
        return first;
    }
    InputIterator next(first);
    ++next;
    while (next != last && !(*next == val))
    {
        ++next;
        ++first;
    }
    return first;
}

template <typename InputIterator, typename Pred>
inline InputIterator find_before_if (InputIterator first, InputIterator last, Pred pred)
{
    if (first == last)
    {
        return first;
    }
    InputIterator next(first);
    ++next;
    while (next != last && !pred(*next))
    {
        ++next;
        ++first;
    }
    return first;
}

namespace MyLib
{
    template <typename Cont>
    inline bool replace_key (Cont &c,
                             const typename Cont::key_type &old_key,
                             const typename Cont::key_type &new_key)
    {
        typename Cont::iterator pos;
        pos = c.find(old_key);
        if (pos != c.end())
        {
            // insert new element with value of old element
            c.insert(typename Cont::value_type(new_key, pos->second));
            // remove old element
            c.erase(pos);
            return true;
        }
        else
        {
            // key not found
            return false;
        }
    }
}

class RuntimeCmp
{
public:
    enum cmp_mode {normal, reverse};
private:
    cmp_mode mode;
public:
    // constructor for sorting criterion
    // - default criterion uses value normal
    RuntimeCmp (cmp_mode m = normal) : mode(m)
    {
    }
    // comparison of elements
    // - member function for any element type
    template <typename T>
    bool operator() (const T &t1, const T &t2) const
    {
        return mode == normal ?  t1 < t2 :  t2 < t1;
    }
    // comparison of sorting criteria
    bool operator== (const RuntimeCmp &rc) const
    {
        return mode == rc.mode;
    }
};

// type of a set that uses this sorting criterion
typedef set<int, RuntimeCmp> IntSet;

int main(int argc, const char *argv[])
{
    try
    {
        // create, fill, and print set with normal element order
        // - uses default sorting criterion
        IntSet coll1 = { 4, 7, 5, 1, 6, 2, 5 };
        PRINT_ELEMENTS (coll1, "coll1: ");

        // create sorting criterion with reverse element order
        RuntimeCmp reverse_order(RuntimeCmp::reverse);

        // create, fill, and print set with reverse element order
        IntSet coll2(reverse_order);
        coll2 = { 4, 7, 5, 1, 6, 2, 5 };
        PRINT_ELEMENTS (coll2, "coll2: ");

        // assign elements AND sorting criterion
        coll1 = coll2;
        coll1.insert(3);
        PRINT_ELEMENTS (coll1, "coll1: ");

        // just to make sure...
        if (coll1.value_comp() == coll2.value_comp())
        {
            cout << "coll1 and coll2 have the same sorting criterion"
                 << endl;
        }
        else
        {
            cout << "coll1 and coll2 have a different sorting criterion"
                 << endl;
        }

        return 0;
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
