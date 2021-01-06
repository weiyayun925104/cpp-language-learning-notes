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

inline void *operator new(std::size_t size)
{
    std::cout << "You are using self-defined version of new!" << std::endl;
    if(void *mem = std::malloc(size))
        return mem;
    else
        throw std::bad_alloc();
}
inline void operator delete(void *mem) noexcept
{
    std::cout << "You are using self-defined version of delete!" << std::endl;
    free(mem);
}

template <typename T> class Vec;
template <typename T> bool operator==(const Vec<T> &, const Vec<T> &);
template <typename T> bool operator!=(const Vec<T> &, const Vec<T> &);
template <typename T> bool operator<(const Vec<T> &, const Vec<T> &);
template <typename T> bool operator<=(const Vec<T> &, const Vec<T> &);
template <typename T> bool operator>(const Vec<T> &, const Vec<T> &);
template <typename T> bool operator>=(const Vec<T> &, const Vec<T> &);
template <typename T>
class Vec
{
    friend bool operator== <T>(const Vec<T> &, const Vec<T> &);
    friend bool operator!= <T>(const Vec<T> &, const Vec<T> &);
    friend bool operator< <T>(const Vec<T> &, const Vec<T> &);
    friend bool operator<= <T>(const Vec<T> &, const Vec<T> &);
    friend bool operator> <T>(const Vec<T> &, const Vec<T> &);
    friend bool operator>= <T>(const Vec<T> &, const Vec<T> &);
public:
    Vec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(const Vec &);
    Vec(Vec &&) noexcept;
    Vec &operator=(const Vec &);
    Vec &operator=(Vec &&) noexcept;
    Vec &operator=(const std::initializer_list<T> &);
    Vec(const std::initializer_list<T> &);
    T &operator[](std::size_t n)
    {
        return elements[n];
    }
    const T &operator[](std::size_t n) const
    {
        return elements[n];
    }
    ~Vec();
    void push_back(const T &);
    void push_back(T &&);
    std::size_t size() const
    {
        return first_free - elements;
    }
    std::size_t capacity() const
    {
        return cap - elements;
    }
    T *begin() const
    {
        return elements;
    }
    T *end() const
    {
        return first_free;
    }
    void reserve(std::size_t);
    void resize(std::size_t);
    void resize(std::size_t, const T &);
    template <typename ... Args> void emplace_back(Args &&...);
private:
    static std::allocator<T> alloc;
    void chk_n_alloc()
    {
        if(size() == capacity()) reallocate();
    }
    std::pair<T *, T *> alloc_n_copy(const T *, const T *);
    void free();
    void reallocate();
    void add_rem(std::size_t n, const T &s = T());
    T *elements;
    T *first_free;
    T *cap;
};

template <typename T>
std::allocator<T> Vec<T>::alloc;

template <typename T>
bool operator==(const Vec<T> &lhs, const Vec<T> &rhs)
{
    if(lhs.size() != rhs.size())
    {
        return false;
    }
    else
    {
        for(auto p = lhs.elements, q = rhs.elements; p != lhs.first_free; ++p, ++q)
        {
            if(*p != *q)
            {
                return false;
            }
        }
        return true;
    }
}

template <typename T>
bool operator!=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Vec<T> &lhs, const Vec<T> &rhs)
{
    auto shorter = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    auto p = lhs.begin(), q = rhs.begin();
    for(std::size_t i = 0; i < shorter; ++i)
    {
        if(*(p + i) == *(q + i))
            continue;
        else if(*(p + i) < * (q + i))
            return true;
        else
            return false;
    }
    return lhs.size() < rhs.size();
}

template <typename T>
bool operator<=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return (lhs < rhs || lhs == rhs);
}
template <typename T>
bool operator>(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
template <typename T>
bool operator>=(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return !(lhs < rhs);
}

template <typename T>
void Vec<T>::push_back(const T &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

template <typename T>
void Vec<T>::push_back(T &&s)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

template <typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e)
{
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
void Vec<T>::free()
{
    if (elements)
    {
        for(auto p = first_free; p != elements; /*empty*/ )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

template <typename T>
Vec<T>::Vec(const Vec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap =  newdata.second;
}

template <typename T>
Vec<T>::Vec(Vec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

template <typename T>
Vec<T>::Vec(const std::initializer_list<T> &il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T>
Vec<T>::~Vec()
{
    free();
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
template <typename T>
Vec<T> &Vec<T>::operator=(Vec &&rhs) noexcept
{
    if(this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const std::initializer_list<T> &il)
{
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T>
void Vec<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++,  std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

template <typename T>
void Vec<T>::reserve(std::size_t n)
{
    if(n > capacity())
    {
        auto newdata = alloc.allocate(n);
        auto dest = newdata;
        auto elem = elements;
        for(std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        cap = elements + n;
    }
}
template <typename T>
void Vec<T>::resize(std::size_t n)
{
    add_rem(n);
}
template <typename T>
void Vec<T>::resize(std::size_t n, const T &s)
{
    add_rem(n, s);
}
template <typename T>
void Vec<T>::add_rem(std::size_t n, const T &s)
{
    if(n <= size())
    {
        auto p = first_free;
        while(p != elements + n)
            alloc.destroy(--p);
        first_free = p;
    }
    else
    {
        auto new_elem_count = n - size();
        for(std::size_t i = 0; i != new_elem_count; ++i)
            push_back(s);
    }
}

template <typename T>
template <typename ... Args>
void Vec<T>::emplace_back(Args &&... args)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args) ...);
}

int main(int argc, const char *argv[])
{
    try
    {
        Vec<string> v1{"This", "is", "a", "new", "day"}, v2{"This", "is", "new", "day"};
        if(v1 < v2)
            cout << "v1 < v2" << endl;
        else if(v1 == v2)
            cout << "v1 == v2" << endl;
        else
            cout << "v1 > v2" << endl;

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
