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
#include <codecvt>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <future>
#include <thread>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cwctype>
#include <climits>
#include <ctime>
#include <cmath>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
using std::streambuf;
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
using std::locale;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

template <typename T>
class MyAlloc
{
public:
    // type definitions
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T *               pointer;
    typedef const T *     const_pointer;
    typedef T &             reference;
    typedef const T &    const_reference;
    typedef T                 value_type;

    // constructors and destructor
    // - nothing to do because the allocator has no state
    MyAlloc() throw()
    {
    }
    MyAlloc(const MyAlloc &) throw()
    {
    }
    template <typename U>
    MyAlloc (const MyAlloc<U> &) throw()
    {
    }
    ~MyAlloc() throw()
    {
    }

    // allocate but don't initialize num elements of type T
    T *allocate (std::size_t num, const void *hint = 0)
    {
        // allocate memory with global new
        return static_cast<T *>(::operator new(num * sizeof(T)));
    }

    // deallocate storage p of deleted elements
    void deallocate (T *p, std::size_t num)
    {
        // deallocate memory with global delete
        ::operator delete(p);
    }

    // return address of values
    T *address (T &value) const
    {
        return &value;
    }
    const T *address (const T &value) const
    {
        return &value;
    }

    // return maximum number of elements that can be allocated
    std::size_t max_size () const throw()
    {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // initialize elements of allocated storage p with value value
    void construct (T *p, const T &value)
    {
        // initialize memory with placement new
        ::new((void *)p)T(value);
    }

    // destroy elements of initialized storage p
    void destroy (T *p)
    {
        // destroy objects by calling their destructor
        p->~T();
    }

    // rebind allocator to type U
    template <typename U>
    struct rebind
    {
        typedef MyAlloc<U> other;
    };
};

// return that all specializations of this allocator are interchangeable
template <typename T1, typename T2>
bool operator== (const MyAlloc<T1> &,
                 const MyAlloc<T2> &) throw()
{
    return true;
}
template <typename T1, typename T2>
bool operator!= (const MyAlloc<T1> &,
                 const MyAlloc<T2> &) throw()
{
    return false;
}

int main(int argc, const char *argv[])
{
    try
    {
        // a vector with special allocator
        std::vector<int, MyAlloc<int> > v;

        // an int/float map with special allocator
        std::map<int, float, std::less<int>,
            MyAlloc<std::pair<const int, float> > > m;

        // a string with special allocator
        std::basic_string<char, std::char_traits<char>, MyAlloc<char> > s;


        // special string type that uses special allocator
        typedef std::basic_string<char, std::char_traits<char>,
                MyAlloc<char> > MyString;

        // special string/string map type that uses special allocator
        typedef std::map<MyString, MyString, std::less<MyString>,
                MyAlloc<std::pair<const MyString, MyString> > > MyMap;
        // create object of this type
        MyMap mymap;
        //...

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
