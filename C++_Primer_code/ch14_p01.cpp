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

class String
{
public:
    typedef size_t size_type;
    typedef char *iterator;
    typedef const char *const_iterator;

    String();
    String(size_t, const char &);
    String(const char *);
    String(const String &);
    String(String &&) noexcept;
    String &operator=(const String &);
    String &operator=(String &&) noexcept;
    ~String();
    void push_back(const char &);
    void push_back(char &&);
    std::size_t size() const
    {
        return first_free - elements;
    }
    std::size_t capacity() const
    {
        return cap - elements;
    }
    char *begin() const
    {
        return elements;
    }
    char *end() const
    {
        return first_free;
    }
    bool empty() const
    {
        return elements == first_free;
    }
    void reserve(std::size_t);
    void clear();

    char &operator[](size_t i)
    {
        return elements[i];
    }
    const char &operator[](size_t i) const
    {
        return elements[i];
    }
    String &operator+=(const char &ch)
    {
        append(&ch, 1);
        return *this;
    }

    String &operator+=(const char *cp)
    {
        append(cp, strlen(cp));
        return *this;
    }

    String &operator+=(const String &s)
    {
        append(s.elements, s.size());
        return *this;
    }

    operator void *() const
    {
        if (size() > 0)
        {
            return elements;
        }
        else
        {
            return nullptr;
        }
    };
    const char *c_str() const
    {
        return elements;
    }

    friend istream &operator >> (istream &, String &);
    friend ostream &operator<<(ostream &, const String &);
    friend istream &getline(istream &, String &);
    friend String operator+(const String &, const String &);
    friend String operator+(const String &, const char *);
    friend String operator+(const char *, const String &);

    friend bool operator== (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }

    friend  bool operator!= (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) != 0;
    }

    friend  bool operator< (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }

    friend  bool operator<= (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
    }

    friend  bool operator> (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }

    friend  bool operator>= (const String &lhs, const String &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
    }

private:
    void chk_n_alloc()
    {
        if( (size() + 1) >= capacity() ) reallocate();
    }
    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    void free();
    void reallocate();
    void append(const char *, const size_t);
private:
    static std::allocator<char> alloc;
    static std::size_t ini_size;
    char *elements;
    char *first_free;
    char *cap;
};

std::allocator<char> String::alloc;
std::size_t String::ini_size = 15;

void String::push_back(const char &c)
{
    chk_n_alloc();
    alloc.construct(first_free++, c);
    alloc.construct(first_free, '\0');
}
void String::push_back(char &&c)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(c));
    alloc.construct(first_free, '\0');
}

void String::clear()
{
    if (elements)
    {
        for(auto p = first_free + 1; p != elements; /* empty */)
            alloc.destroy(--p);
        first_free = elements;
        alloc.construct(first_free, '\0');
    }
}

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    auto newcapacity = (e - b > ini_size) ? (e - b) : ini_size;
    ++newcapacity;
    auto newdata = alloc.allocate(newcapacity);
    auto newfree = std::uninitialized_copy(b, e, newdata);
    alloc.construct(newfree, '\0');
    return {newdata, newfree};
}

void String::free()
{
    if (elements)
    {
        for(auto p = first_free + 1; p != elements; /* empty */)
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

void String::reallocate()
{
    auto newcapacity = (capacity() * 2);
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    for(std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    alloc.construct(first_free, '\0');
    cap = elements + newcapacity;
}

void String::reserve(std::size_t n)
{
    if(n > capacity())
    {
        auto newcapacity = capacity();
        while (newcapacity < n)
        {
            newcapacity *= 2;
        }
        auto newdata = alloc.allocate(newcapacity);
        auto dest = newdata;
        auto elem = elements;
        for(std::size_t i = 0; i != size(); ++i)
            alloc.construct(dest++, std::move(*elem++));
        free();
        elements = newdata;
        first_free = dest;
        alloc.construct(first_free, '\0');
        cap = elements + newcapacity;
    }
}

void String::append(const char *str, const size_t count)
{
    size_t old_length = size();
    reserve(old_length + count + 1);
    first_free = std::uninitialized_copy(str, str + count, first_free);
    alloc.construct(first_free, '\0');
}

String::String(): elements(nullptr), first_free(nullptr), cap(nullptr)
{
    auto newcapacity = ini_size;
    ++newcapacity;
    elements = alloc.allocate(newcapacity);
    first_free = elements;
    cap = elements + newcapacity;
}

String::String(size_t n, const char &c)
{
    auto newcapacity = ini_size;
    ++newcapacity;
    while (newcapacity < (n + 1))
    {
        newcapacity *= 2;
    }
    elements = alloc.allocate(newcapacity);
    first_free = elements + n;
    cap = elements + newcapacity;
    std::uninitialized_fill(elements, first_free, c);
    alloc.construct(first_free, '\0');
}

String::String(const char *s)
{
    auto newdata = alloc_n_copy(s, s + strlen(s));
    elements = newdata.first;
    first_free = newdata.second;
    cap = (strlen(s) > ini_size) ? (first_free + 1) : (elements + ini_size + 1);
}

String::String(const String &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = newdata.second;
    cap = (s.size() > ini_size) ? (first_free + 1) : (elements + ini_size + 1);
}

String::String(String &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

String &String::operator=(const String &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = newdata.second;
    cap = (rhs.size() > ini_size) ? (first_free + 1) : (elements + ini_size + 1);
    return *this;
}

String &String::operator=(String &&rhs) noexcept
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

String::~String()
{
    free();
}

String operator+(const String &s, const String &t)
{
    String r = s;
    r += t;
    return r;
}

String operator+(const String &s, const char *str)
{
    String r = s;
    r += str;
    return r;
}

String operator+(const char *str, const String &s)
{
    String r = str;
    r += s;
    return r;
}

ostream &operator<<(ostream &os, const String &s)
{
    copy(s.begin(), s.end(), ostream_iterator<char>(os));
    return os;
}

istream &operator>>(istream &is, String &s)
{
    s.clear();
    char c;
    while (is.get(c) && isspace(c))
        ;
    if (is)
    {
        do
        {
            s.push_back(c);
        }
        while (is.get(c) && !isspace(c));
        if (is)
        {
            is.unget();
        }
    }
    return is;
}

istream &getline(istream &is, String &s)
{
    s.clear();
    char c;

    if (is)
    {
        while (is.get(c) && c != '\n')
        {
            s.push_back(c);
        }
    }

    return is;
}

int main(int argc, const char *argv[])
{
    try
    {
        String s1 = "This is a whole sentence.";
        String s2 = s1;
        std::cout << s1 << std::endl;
        std::cout << s2 << std::endl;

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
