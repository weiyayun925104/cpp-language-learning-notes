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

class DefaultDeleter
{
public:
    template <typename T>
    void operator()(T *p) const
    {
        delete p;
    }
};

class DefaultDeleterArray
{
public:
    template <typename T>
    void operator()(T *p) const
    {
        delete []p;
    }
};

template <typename T, typename D = DefaultDeleter> class my_unique_ptr;

template <typename T>
void my_swap(my_unique_ptr<T> &, my_unique_ptr<T> &);

template <typename T, typename D>
class my_unique_ptr
{
    friend void my_swap<T>(my_unique_ptr<T> &, my_unique_ptr<T> &);
public:
    my_unique_ptr() : p(nullptr), del(D()) {}
    template <typename U>
    explicit my_unique_ptr(U *t) : p(t), del(D()) {}
    my_unique_ptr(const D &d) : p(nullptr), del(d) {}
    my_unique_ptr(const my_unique_ptr &) = delete;
    my_unique_ptr(my_unique_ptr &&up) noexcept;
    my_unique_ptr &operator=(const my_unique_ptr &) = delete;
    my_unique_ptr &operator=(my_unique_ptr &&) noexcept;
    template <typename U, typename DU>
    my_unique_ptr(my_unique_ptr<U, DU> &&up) noexcept;
    template <typename U, typename DU>
    my_unique_ptr &operator=(my_unique_ptr<U, DU> &&up) noexcept;
    my_unique_ptr &operator=(std::nullptr_t);
    ~my_unique_ptr();
    T &operator*() const;
    T *operator->() const;
    explicit operator bool() const
    {
        return p;
    }
    T *get() const
    {
        return p;
    }
    void swap(my_unique_ptr &);
    T *release();
    void reset();
    void reset(T *);
    void reset(std::nullptr_t);
private:
    void free() const;
    T *p;
    D del;
};

template <typename T, typename D>
inline void my_unique_ptr<T, D>::free() const
{
    if(p)
    {
        del(p);
    }
}

template <typename T, typename D>
my_unique_ptr<T, D>::my_unique_ptr(my_unique_ptr &&up) noexcept
{
    p = up.p;
    del = up.del;
    up.p = nullptr;
}

template <typename T, typename D>
my_unique_ptr<T, D> &my_unique_ptr<T, D>::operator=(my_unique_ptr &&rhs) noexcept
{
    if (this != &rhs)
    {
        p = rhs.p;
        del = rhs.del;
        rhs.p = nullptr;
    }
    return *this;
}

template <typename T, typename D>
template <typename U, typename DU>
my_unique_ptr<T, D>::my_unique_ptr(my_unique_ptr<U, DU> &&up) noexcept
{
    p = up.p;
    del = up.del;
    up.p = nullptr;
}

template <typename T, typename D>
template <typename U, typename DU>
my_unique_ptr<T, D> &my_unique_ptr<T, D>::operator=(my_unique_ptr<U, DU> &&rhs) noexcept
{
    if (this != &rhs)
    {
        p = rhs.p;
        del = rhs.del;
        rhs.p = nullptr;
    }
    return *this;
}

template <typename T, typename D>
my_unique_ptr<T, D> &my_unique_ptr<T, D>::operator=(std::nullptr_t)
{
    free();
    p = nullptr;
    return *this;
}

template <typename T, typename D>
my_unique_ptr<T, D>::~my_unique_ptr()
{
    free();
    p = nullptr;
}

template <typename T, typename D>
inline T &my_unique_ptr<T, D>::operator*() const
{
    if(!p)
        throw std::runtime_error("dereference null pointer");
    return *p;
}

template <typename T, typename D>
inline T *my_unique_ptr<T, D>::operator->() const
{
    return &(this->operator*());
}

template <typename T>
void my_swap(my_unique_ptr<T> &lhs, my_unique_ptr<T> &rhs)
{
    lhs.swap(rhs);
}

template <typename T, typename D>
inline void my_unique_ptr<T, D>::swap(my_unique_ptr &rhs)
{
    using std::swap;
    swap(this->p, rhs.p);
    swap(this->del, rhs.del);
}

template <typename T, typename D>
T *my_unique_ptr<T, D>::release()
{
    auto ret = p;
    p = nullptr;
    return ret;
}

template <typename T, typename D>
void my_unique_ptr<T, D>::reset()
{
    free();
    p = nullptr;
}

template <typename T, typename D>
void my_unique_ptr<T, D>::reset(T *t)
{
    free();
    p = t;
}

template <typename T, typename D>
void my_unique_ptr<T, D>::reset(std::nullptr_t)
{
    free();
    p = nullptr;
}

template <typename T, typename D> class my_unique_ptr<T[], D>;

template <typename T>
void my_swap(my_unique_ptr<T[]> &, my_unique_ptr<T[]> &);

template <typename T, typename D = DefaultDeleterArray>
class my_unique_ptr<T[], D>
{
    friend void my_swap<T>(my_unique_ptr<T[]> &, my_unique_ptr<T[]> &);
public:
    my_unique_ptr() : p(nullptr), del(D()) {}
    explicit my_unique_ptr(T *t) : p(t), del(D()) {}
    my_unique_ptr(const D &d) : p(nullptr), del(d) {}
    my_unique_ptr(const my_unique_ptr &) = delete;
    my_unique_ptr(my_unique_ptr &&up) noexcept;
    my_unique_ptr &operator=(const my_unique_ptr &) = delete;
    my_unique_ptr &operator=(my_unique_ptr &&) noexcept;
    my_unique_ptr &operator=(std::nullptr_t);
    ~my_unique_ptr();
    T &operator[](std::size_t n) const
    {
        return p[n];
    }
    explicit operator bool() const
    {
        return p;
    }
    T *get() const
    {
        return p;
    }
    void swap(my_unique_ptr &);
    void release();
    void reset();
    void reset(T *);
    void reset(std::nullptr_t);
private:
    void free() const;
    T *p;
    D del;
};

template <typename T, typename D>
inline void my_unique_ptr<T[], D>::free() const
{
    if(p)
    {
        del(p);
    }
}


template <typename T, typename D>
my_unique_ptr<T[], D>::my_unique_ptr(my_unique_ptr &&up) noexcept
{
    p = up.p;
    del = up.del;
    up.p = nullptr;
}

template <typename T, typename D>
my_unique_ptr<T[], D> &my_unique_ptr<T[], D>::operator=(my_unique_ptr &&rhs) noexcept
{
    if (this != &rhs)
    {
        p = rhs.p;
        del = rhs.del;
        rhs.p = nullptr;
    }
    return *this;
}

template <typename T, typename D>
my_unique_ptr<T[], D> &my_unique_ptr<T[], D>::operator=(std::nullptr_t)
{
    free();
    p = nullptr;
    return *this;
}

template <typename T, typename D>
my_unique_ptr<T[], D>::~my_unique_ptr()
{
    free();
}

template <typename T>
void my_swap(my_unique_ptr<T[]> &lhs, my_unique_ptr<T> &rhs)
{
    lhs.swap(rhs);
}

template <typename T, typename D>
inline void my_unique_ptr<T[], D>::swap(my_unique_ptr &rhs)
{
    using std::swap;
    swap(this->p, rhs.p);
    swap(this->del, rhs.del);
}

template <typename T, typename D>
void my_unique_ptr<T[], D>::release()
{
    free();
    p = nullptr;
}

template <typename T, typename D>
void my_unique_ptr<T[], D>::reset()
{
    free();
    p = nullptr;
}
template <typename T, typename D>
void my_unique_ptr<T[], D>::reset(T *t)
{
    free();
    p = t;
}
template <typename T, typename D>
void my_unique_ptr<T[], D>::reset(std::nullptr_t)
{
    free();
    p = nullptr;
}

class Base
{
public:
    virtual void print() const
    {
        std::cout << "This is the base class." << std::endl;
    }
    virtual ~Base() = default;
};
class Derived : public Base
{
public:
    void print() const
    {
        std::cout << "This is a derived class." << std::endl;
    }
    ~Derived() = default;
};
struct DebugDelete
{
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}
    template <typename T>
    void operator()(T *p) const
    {
        os << "deleting my_unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};

int main(int argc, const char *argv[])
{
    try
    {
        my_unique_ptr<int> q;
        my_unique_ptr<int, DefaultDeleter> q2;
        q2.reset(new int(2));
        if(!q2)
            cout << "q2 is null!" << endl;
        cout << *q2 << endl;
        int *p = new int(2);
        q2 = nullptr;
        q = my_unique_ptr<int>(p);
        cout << *q << endl;
        q = std::move(my_unique_ptr<int>(new int(9)));
        cout << *q << endl;
        q2.reset();
        try
        {
            cout << *q2 << endl;
        }
        catch(runtime_error &err)
        {
            cout << err.what() << endl;
        }
        {
            my_unique_ptr<vector<string>, DebugDelete> q3(new vector<string>({ "str1", "str2" }));
            cout << *q3 << endl;
            cout << "q3->size(): " << q3->size() << endl;
        }
        my_unique_ptr<string, DebugDelete> q4;
        my_unique_ptr<string> q5;
        my_unique_ptr<string> q6;
        q4.reset(new string("q4"));
        q5.reset(new string("q5"));
        q6.reset(new string("q6"));
        cout << *q4 << endl;
        cout << *q5 << endl;
        cout << *q6 << endl;
        q5.swap(q6);
        cout << *q5 << endl;
        cout << *q6 << endl;
        auto sp = q4.release();
        if(!q4)
            cout << "q4 is null!" << endl;
        delete sp;

        my_unique_ptr<int[]> up(new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        for(size_t i = 0; i != 10; ++i)
            cout << up[i] << " ";
        cout << endl;
        up.release();
        const my_unique_ptr<int> up2(new int(1));
        cout << *up2 << endl;
        my_unique_ptr<Base> upb(new Derived());
        upb->print();

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
