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

class StrVec
{
    friend bool operator==(const StrVec &, const StrVec &);
    friend bool operator!=(const StrVec &, const StrVec &);
    friend bool operator<(const StrVec &, const StrVec &);
    friend bool operator<=(const StrVec &, const StrVec &);
    friend bool operator>(const StrVec &, const StrVec &);
    friend bool operator>=(const StrVec &, const StrVec &);
public:
    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept;
    StrVec &operator=(const StrVec &);
    StrVec &operator=(StrVec &&) noexcept;
    StrVec(const std::initializer_list<std::string> &);
    StrVec &operator=(const std::initializer_list<std::string> &);
    ~StrVec();
    void push_back(const std::string &);
    void push_back(string &&);
    std::size_t size() const
    {
        return first_free - elements;
    }
    std::size_t capacity() const
    {
        return cap - elements;
    }
    std::string *begin() const
    {
        return elements;
    }
    std::string *end() const
    {
        return first_free;
    }
    void reserve(std::size_t);
    void resize(std::size_t);
    void resize(std::size_t, const std::string &);

    string &operator[](size_t n)
    {
        return elements[n];
    }
    string &operator[](size_t n) const
    {
        return elements[n];
    }
private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc()
    {
        if(size() == capacity()) reallocate();
    }
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void free();
    void reallocate();
    void add_rem(std::size_t n, const std::string &s = "");
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

std::allocator<std::string> StrVec::alloc;

bool operator==(const StrVec &lhs, const StrVec &rhs)
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

bool operator!=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs)
{
    auto shorter = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    auto p = lhs.begin(), q = rhs.begin();
    for(size_t i = 0; p + i != lhs.end(); ++i)
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

bool operator<=(const StrVec &lhs, const StrVec &rhs)
{
    return lhs < rhs || lhs == rhs;
}

bool operator>(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
bool operator>=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs < rhs);
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}
void StrVec::push_back(string &&s)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}
void StrVec::free()
{
    if (elements)
    {
        for_each(begin(), end(), [](const std::string & s)
        {
            alloc.destroy(&s);
        } );
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap =  newdata.second;
}

StrVec::StrVec(StrVec &&s) noexcept : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::StrVec(const std::initializer_list<std::string> &il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
StrVec::~StrVec()
{
    free();
}
StrVec &StrVec::operator=(const StrVec &rhs)
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

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
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
StrVec &StrVec::operator=(const std::initializer_list<std::string> &il)
{
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
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
void StrVec::reserve(std::size_t n)
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
void StrVec::resize(std::size_t n)
{
    add_rem(n);
}
void StrVec::resize(std::size_t n, const std::string &s)
{
    add_rem(n, s);
}
void StrVec::add_rem(std::size_t n, const std::string &s)
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

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;

    friend bool operator==(const StrBlob &, const StrBlob &);
    friend bool operator!=(const StrBlob &, const StrBlob &);
    friend bool operator<(const StrBlob &, const StrBlob &);
    friend bool operator<=(const StrBlob &, const StrBlob &);
    friend bool operator>(const StrBlob &, const StrBlob &);
    friend bool operator>=(const StrBlob &, const StrBlob &);
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    StrBlob(const StrBlob &rhs) : data(std::make_shared<std::vector<std::string>>(*(rhs.data))) {}
    StrBlob &operator=(const StrBlob &);
    size_type size() const
    {
        return data->size();
    }
    bool empty() const
    {
        return data->empty();
    }
    void push_back(const std::string &t)
    {
        data->push_back(t);
    }
    void push_back(string &&t)
    {
        data->push_back(std::move(t));
    }
    void pop_back();
    std::string &front();
    std::string &back();
    const std::string &front() const;
    const std::string &back() const;
    size_type use_count() const
    {
        return data.use_count();
    }
    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr begin() const;
    ConstStrBlobPtr end() const;
    std::string &at(size_type);
    const string &at(size_type) const;
    string &operator[](size_t n)
    {
        return (*data)[n];
    }
    const string &operator[](size_t n) const
    {
        return (*data)[n];
    }
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }

StrBlob::StrBlob(std::initializer_list<std::string> il) :
    data(std::make_shared<std::vector<std::string>>(il)) { };

void StrBlob::check(size_type i, const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

StrBlob &StrBlob::operator=(const StrBlob &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    data = std::make_shared<std::vector<std::string>>(*(rhs.data));
    return *this;
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
const std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
const std::string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}
std::string &StrBlob::at(size_type n)
{
    check(n, "index out of range");
    return data->at(n);
}
const string &StrBlob::at(size_type n) const
{
    check(n, "index out of range");
    return data->at(n);
}
bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
    return *lhs.data == *rhs.data;
}
bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const StrBlob &lhs, const StrBlob &rhs)
{
    return *lhs.data < *rhs.data;
}
bool operator<=(const StrBlob &lhs, const StrBlob &rhs)
{
    return (lhs < rhs || lhs == rhs);
}
bool operator>(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
bool operator>=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs < rhs);
}

class StrBlobPtr
{
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator<=(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator>=(const StrBlobPtr &, const StrBlobPtr &);
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &deref() const;
    StrBlobPtr &incr();
    string &operator[](size_t n);
    const string &operator[](size_t n) const;
private:
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string &) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string &StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
StrBlobPtr &StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}
string &StrBlobPtr::operator[](size_t n)
{
    auto p = check(curr + n, "deference past end");
    return (*p)[curr + n];
}
const string &StrBlobPtr::operator[](size_t n) const
{
    auto p = check(curr + n, "deference past end");
    return (*p)[curr + n];
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return lhs.curr == rhs.curr;
}
bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return lhs.curr < rhs.curr;
}
bool operator<=(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return (lhs < rhs || lhs == rhs);
}
bool operator>(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
bool operator>=(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return !(lhs < rhs);
}

class ConstStrBlobPtr
{
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    const std::string &deref() const;
    ConstStrBlobPtr &incr();
    const string &operator[](size_t n) const;
private:
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string &) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr;
};

std::shared_ptr<std::vector<std::string>> ConstStrBlobPtr::check(size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

const std::string &ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}
ConstStrBlobPtr &ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}
const string &ConstStrBlobPtr::operator[](size_t n) const
{
    auto p = check(curr + n, "deference past end");
    return (*p)[curr + n];
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.wptr.lock() == rhs.wptr.lock() && lhs.curr == rhs.curr;
}
bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr < rhs.curr;
}
bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr <= rhs.curr;
}
bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr > rhs.curr;
}
bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr >= rhs.curr;
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}
ConstStrBlobPtr StrBlob::begin() const
{
    return ConstStrBlobPtr(*this);
}
ConstStrBlobPtr StrBlob::end() const
{
    return ConstStrBlobPtr(*this, data->size());
}

int main(int argc, const char *argv[])
{
    try
    {
        String str1("Hello"), str2("Hello");
        if(str1 < str2)
            cout << "str1 < str2" << endl;
        else if(str1 == str2)
            cout << "str1 == str2" << endl;
        else
            cout << "str1 > str2" << endl;
        StrVec v1{"This", "is", "a", "new", "day"}, v2{"This", "is", "new", "day"};
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
