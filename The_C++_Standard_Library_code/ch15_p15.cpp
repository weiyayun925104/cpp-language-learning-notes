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
#include <streambuf>
#include <locale>
#include <cstdio>
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

template <typename T>
inline void PRINT_MAPPED_ELEMENTS (const T &coll, const std::string &optstr = "")
{
    std::cout << optstr;
    for (const auto &elem : coll)
    {
        std::cout << '[' << elem.first << ',' << elem.second << "] ";
    }
    std::cout << std::endl;
}

template <typename T>
inline void INSERT_ELEMENTS (T &coll, int first, int last)
{
    for (int i = first; i <= last; ++i)
    {
        coll.insert(coll.end(), i);
    }
}

template <typename T>
inline void hash_combine (std::size_t &seed, const T &val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val (std::size_t &seed, const T &val)
{
    hash_combine(seed, val);
}

template <typename T, typename... Types>
inline void hash_val (std::size_t &seed,
                      const T &val, const Types &... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
template <typename... Types>
inline std::size_t hash_val (const Types &... args)
{
    std::size_t seed = 0;
    hash_val (seed, args...);
    return seed;
}

template <typename T1, typename T2>
std::ostream &operator << (std::ostream &strm, const std::pair<T1, T2> &p)
{
    return strm << "[" << p.first << "," << p.second << "]";
}

template <typename charT,
          typename traits = std::char_traits<charT> >
class basic_outbuf : public std::basic_streambuf<charT, traits>
{
protected:
    // central output function
    // - print characters in uppercase mode
    virtual typename traits::int_type
    overflow (typename traits::int_type c)
    {
        if (!traits::eq_int_type(c, traits::eof()))
        {
            char cc;
            // convert lowercase to uppercase
            try
            {
                // convert the character into a char (default: '?')
                cc = std::use_facet<std::ctype<charT>>(std::locale("en_US.utf8")).narrow(c, '?');
                cc = std::toupper(cc, std::locale("en_US.utf8"));

                // and write the character to the standard output
                if (std::putchar(cc) == EOF)
                {
                    return traits::eof();
                }
            }
            catch(std::bad_cast &e)
            {
                cout << e.what() << endl;
            }
        }
        return traits::not_eof(c);
    }
};

typedef basic_outbuf<char, std::char_traits<char>>    outbuf;
typedef basic_outbuf<wchar_t, std::char_traits<wchar_t>> woutbuf;

int main(int argc, const char *argv[])
{
    try
    {
        std::locale loc = std::locale("en_US.utf8"); // user's preferred locale
        std::cout << loc.name() << std::endl;
        std::cout << "std::use_facet<std::ctype<char>>(loc).toupper('3') = "
                  << std::use_facet<std::ctype<char>>(loc).toupper('3') << '\n';
        std::cout << "std::use_facet<std::ctype<char>>(loc).narrow(51, '?') = " 
        	     << std::use_facet<std::ctype<char>>(loc).narrow(51, '?') << '\n';

        outbuf ob;                // create special output buffer
        std::ostream out(&ob);    // initialize output stream with that output buffer

        out << "31 hexadecimal: " << std::hex << 31 << std::endl;

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
