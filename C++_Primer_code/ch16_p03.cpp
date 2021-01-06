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

template <typename T> class BlobPtr;
template <typename T> class Blob;

template <typename T> bool operator==(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator!=(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator<(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator<=(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator>(const Blob<T> &, const Blob<T> &);
template <typename T> bool operator>=(const Blob<T> &, const Blob<T> &);

template <typename T> class Blob
{
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T> &, const Blob<T> &);
    friend bool operator!=<T>(const Blob<T> &, const Blob<T> &);
    friend bool operator< <T>(const Blob<T> &, const Blob<T> &);
    friend bool operator<=<T>(const Blob<T> &, const Blob<T> &);
    friend bool operator><T>(const Blob<T> &, const Blob<T> &);
    friend bool operator>=<T>(const Blob<T> &, const Blob<T> &);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    typedef typename std::vector<T>::difference_type difference_type;

    Blob();
    Blob(std::initializer_list<T> il);
    size_type size() const
    {
        return data->size();
    }
    bool empty() const
    {
        return data->empty();
    }
    void push_back(const T &t)
    {
        data->push_back(t);
    }
    void push_back(T &&t)
    {
        data->push_back(std::move(t));
    }
    void pop_back();
    T &front();
    T &back();
    const T &front() const;
    const T &back() const;
    T &operator[] (size_type);
    const T &operator[] (size_type) const;
    T &at(size_type);
    const T &at(size_type) const;
    size_type use_count() const
    {
        return data->use_count();
    }
private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type, const std::string &) const;
};
template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il): data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

template <typename T>
T &Blob<T>::front()
{
    check(0, "front on empty Blob");
    return data->front();
}
template <typename T>
T &Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
const T &Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}

template <typename T>
const T &Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "index out of range");
    return (*data)[i];
}

template <typename T>
const T &Blob<T>::operator[](size_type i) const
{
    check(i, "index out of range");
    return (*data)[i];
}

template <typename T>
T &Blob<T>::at(size_type i)
{
    check(i, "index out of range");
    return data->at(i);
}

template <typename T>
const T &Blob<T>::at(size_type i) const
{
    check(i, "index out of range");
    return data->at(i);
}

template <typename T>
inline bool operator==(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return *lhs.data == *rhs.data;
}
template <typename T>
inline bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs == rhs);
}
template <typename T>
inline bool operator<(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return *lhs.data < *rhs.data;
}
template <typename T>
inline bool operator<=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return (lhs < rhs || lhs == rhs);
}
template <typename T>
inline bool operator>(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
template <typename T>
inline bool operator>=(const Blob<T> &lhs, const Blob<T> &rhs)
{
    return !(lhs < rhs);
}

template <typename T> bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator!=(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator<(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator<=(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator>(const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T> bool operator>=(const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T> BlobPtr<T> operator+(const BlobPtr<T> &, typename Blob<T>::difference_type);
template <typename T> BlobPtr<T> operator-(const BlobPtr<T> &, typename Blob<T>::difference_type);
template <typename T> typename Blob<T>::difference_type operator-(const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T>
class BlobPtr
{
    friend bool operator==<T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator!=<T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator< <T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator<=<T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator><T>(const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator>=<T>(const BlobPtr<T> &, const BlobPtr<T> &);

    friend BlobPtr<T> operator+<T>(const BlobPtr<T> &, typename Blob<T>::difference_type);
    friend BlobPtr<T> operator-<T>(const BlobPtr<T> &, typename Blob<T>::difference_type);
    friend typename Blob<T>::difference_type operator-<T>(const BlobPtr<T> &, const BlobPtr<T> &);
public:
    typedef typename std::vector<T>::size_type size_type;
    BlobPtr();
    BlobPtr(Blob<T> &a, size_type sz = 0): wptr(a.data), curr(sz) {}
    T &operator*() const;
    T &operator[](size_type);
    const T &operator[](size_type) const;

    BlobPtr &operator++();
    BlobPtr &operator--();
    BlobPtr operator++(int);
    BlobPtr operator--(int);

    BlobPtr &operator+=(typename Blob<T>::difference_type);
    BlobPtr &operator-=(typename Blob<T>::difference_type);
private:
    std::shared_ptr<std::vector<T>> check(size_type, const std::string &) const;
    std::weak_ptr<std::vector<T>> wptr;
    size_type curr;
};

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(size_type i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("unbound BlobPtr");
    if(i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

template <typename T>
BlobPtr<T>::BlobPtr(): curr(0) {}

template <typename T>
T &BlobPtr<T>::operator*() const
{
    auto p = check(curr, "deference past end");
    return (*p)[curr];
}

template <typename T>
T &BlobPtr<T>::operator[](size_type n)
{
    auto p = check(curr + n, "subscript past end");
    return (*p)[curr + n];
}

template <typename T>
const T &BlobPtr<T>::operator[](size_type n) const
{
    auto p = check(curr + n, "subscript past end");
    return (*p)[curr + n];
}

template <typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return lhs.curr == rhs.curr;
}

template <typename T>
bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return lhs.curr < rhs.curr;
}

template <typename T>
bool operator<=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return (lhs < rhs || lhs == rhs);
}

template <typename T>
bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs < rhs || lhs == rhs);
}
template <typename T>
bool operator>=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs < rhs);
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
    auto p = check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--()
{
    --curr;
    auto p = check(curr, "decrement past begin of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    auto ret = *this;
    ++*this;
    return ret;
}
template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    auto ret = *this;
    --*this;
    return ret;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator+=(typename Blob<T>::difference_type n)
{
    curr += n;
    check(curr, "pointer addition past end of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator-=(typename Blob<T>::difference_type n)
{
    curr -= n;
    check(curr, "pointer subtraction past begin of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> operator+(const BlobPtr<T> &sp, typename Blob<T>::difference_type n)
{
    auto sum = sp;
    sum += n;
    return sum;
}

template <typename T>
BlobPtr<T> operator-(const BlobPtr<T> &sp, typename Blob<T>::difference_type n)
{
    auto sum = sp;
    sum -= n;
    return sum;
}

template <typename T>
typename Blob<T>::difference_type operator-(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return typename Blob<T>::difference_type(lhs.curr - rhs.curr);
}

int main(int argc, const char *argv[])
{
    try
    {
        Blob<int> blob1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        Blob<int> blob2 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        BlobPtr<int> ps(blob1), ps2(blob1, blob1.size());
        cout << "blob1.size(): " << blob1.size() << endl;
        blob1.push_back(12);
        cout << "blob1.size(): " << blob1.size() << endl;
        blob1.pop_back();
        blob1.pop_back();
        cout << "blob1.front(): " << blob1.front() << endl;
        cout << "blob1.back(): " << blob1.back() << endl;
        blob1.front() = 20;
        cout << "blob1.front(): " << blob1.front() << endl;
        blob1[2] = 23;
        cout << "blob1[2] = " << blob1[2] << endl;
        cout << "blob1.at(8) = " << blob1[8] << endl;
        cout << "blob1 == blob2 ? " << (blob1 == blob2) << endl;
        cout << "blob1 != blob2 ? " << (blob1 != blob2) << endl;
        cout << "blob1 < blob2 ? " << (blob1 < blob2) << endl;
        cout << "blob1 <= blob2 ? " << (blob1 <= blob2) << endl;
        cout << "blob1 > blob2 ? " << (blob1 > blob2) << endl;
        cout << "blob1 >= blob2 ? " << (blob1 >= blob2) << endl;
        cout << "*ps = " << *ps << endl;
        cout << "ps[5] = " << ps[5] << endl;
        cout << "*++ps = " << *++ps << endl;
        cout << "*ps++ = " << *ps++ << endl;
        cout << "*--ps = " << *--ps << endl;
        cout << "*ps-- = " << *ps-- << endl;
        ps += 4;
        cout << "ps += 4 = " << *ps << endl;

        try
        {
            ps -= 20;
            cout << "ps -= 20 = " << *ps << endl;
        }
        catch(out_of_range &err)
        {
            std::cerr << err.what() << endl;
        }

        ps = ps + 22;
        cout << "(ps = ps + 22) = " << *ps << endl;
        ps = ps - 1;
        cout << "(ps = ps - 1) = " << *ps << endl;
        cout << "ps2 - ps = " << ps2 - ps << endl;

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
