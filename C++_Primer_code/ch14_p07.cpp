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
    typedef vector<string>::difference_type difference_type;
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

    friend StrBlob::difference_type operator-(const StrBlobPtr &, const StrBlobPtr &);
    friend StrBlobPtr operator+(const StrBlobPtr &, StrBlob::difference_type);
    friend StrBlobPtr operator+(StrBlob::difference_type, const StrBlobPtr &);

public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &deref() const;
    StrBlobPtr &incr();
    string &operator[](size_t n);
    const string &operator[](size_t n) const;

    StrBlobPtr &operator++();
    StrBlobPtr &operator--();
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);

    StrBlobPtr &operator+=(StrBlob::difference_type n);
    StrBlobPtr &operator-=(StrBlob::difference_type n);

    string &operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    string *operator->() const
    {
        return &(this->operator*());
    }
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

StrBlobPtr &StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobStr");
    ++curr;
    return *this;
}
StrBlobPtr &StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}
StrBlobPtr StrBlobPtr::operator++(int)
{
    auto ret = *this;
    ++*this;
    return ret;
}
StrBlobPtr StrBlobPtr::operator--(int)
{
    auto ret = *this;
    --*this;
    return ret;
}
StrBlobPtr &StrBlobPtr::operator+=(StrBlob::difference_type n)
{
    curr += n;
    check(curr, "pointer addition past end of StrBlobPtr");
    return *this;
}
StrBlobPtr &StrBlobPtr::operator-=(StrBlob::difference_type n)
{
    curr -= n;
    check(curr, "pointer subtraction past begin of StrBlobPtr");
    return *this;
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
StrBlob::difference_type operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    return StrBlob::difference_type(lhs.curr - rhs.curr);
}
StrBlobPtr operator+(const StrBlobPtr &sp, StrBlob::difference_type n)
{
    StrBlobPtr sum = sp;
    sum += n;
    return sum;
}
StrBlobPtr operator+(StrBlob::difference_type n, const StrBlobPtr &sp)
{
    StrBlobPtr sum = sp;
    sum += n;
    return sum;
}

class ConstStrBlobPtr
{
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator<=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator>=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);

    friend StrBlob::difference_type operator-(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend ConstStrBlobPtr operator+(const ConstStrBlobPtr &, StrBlob::difference_type);
    friend ConstStrBlobPtr operator+(StrBlob::difference_type, const ConstStrBlobPtr &);
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    const std::string &deref() const;
    ConstStrBlobPtr &incr();
    const string &operator[](size_t n) const;

    ConstStrBlobPtr &operator++();
    ConstStrBlobPtr &operator--();
    ConstStrBlobPtr operator++(int);
    ConstStrBlobPtr operator--(int);

    ConstStrBlobPtr &operator+=(StrBlob::difference_type n);
    ConstStrBlobPtr &operator-=(StrBlob::difference_type n);

    const string &operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }
    const string *operator->() const
    {
        return &(this->operator*());
    }
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
ConstStrBlobPtr &ConstStrBlobPtr::operator++()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}
ConstStrBlobPtr &ConstStrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin of ConstStrBlobPtr");
    return *this;
}
ConstStrBlobPtr ConstStrBlobPtr::operator++(int)
{
    auto ret = *this;
    ++*this;
    return ret;
}
ConstStrBlobPtr ConstStrBlobPtr::operator--(int)
{
    auto ret = *this;
    --*this;
    return ret;
}
ConstStrBlobPtr &ConstStrBlobPtr::operator+=(StrBlob::difference_type n)
{
    curr += n;
    check(curr, "pointer addition past end of ConstStrBlobPtr");
    return *this;
}
ConstStrBlobPtr &ConstStrBlobPtr::operator-=(StrBlob::difference_type n)
{
    curr -= n;
    check(curr, "pointer subtraction past begin of ConstStrBlobPtr");
    return *this;
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
StrBlob::difference_type operator-(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return StrBlob::difference_type(lhs.curr - rhs.curr);
}
ConstStrBlobPtr operator+(const ConstStrBlobPtr &sp, StrBlob::difference_type n)
{
    ConstStrBlobPtr sum = sp;
    sum += n;
    return sum;
}
ConstStrBlobPtr operator+(StrBlob::difference_type n, const ConstStrBlobPtr &sp)
{
    ConstStrBlobPtr sum = sp;
    sum += n;
    return sum;
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

class HasStrBlobPtr
{
public:
    HasStrBlobPtr() : p(nullptr) {}
    HasStrBlobPtr(StrBlobPtr &a) : p(&a) {}
    StrBlobPtr &operator*() const
    {
        return *p;
    }
    StrBlobPtr *operator->() const
    {
        return &(this->operator*());
    }
private:
    StrBlobPtr *p;
};

int main(int argc, const char *argv[])
{
    try
    {
        StrBlob v = {"Like", "a", "thunderbolt", "he", "falls"};
        StrBlobPtr p1(v);
        HasStrBlobPtr hp(p1);
        std::cout << hp->deref() << std::endl;
        std::cout << hp->operator[](2) << std::endl;

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
