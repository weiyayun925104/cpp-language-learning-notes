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

template <typename T> class my_shared_ptr;

template <typename T>
void my_swap(my_shared_ptr<T> &, my_shared_ptr<T> &);

template <typename T>
class my_shared_ptr
{
    friend void my_swap<T>(my_shared_ptr<T> &, my_shared_ptr<T> &);
public:
    typedef typename std::function<void(T *)> Deleter;

    my_shared_ptr() : p(nullptr), ref(nullptr), del(nullptr) {}
    template <typename U>
    explicit my_shared_ptr(U *q) : p(q), ref(new std::size_t(1)), del(nullptr) {}
    template <typename U>
    my_shared_ptr(U *q, const Deleter &d) : p(q), ref(new std::size_t(1)), del(d) {}
    template <typename U>
    my_shared_ptr(const my_shared_ptr<U> &sp, const Deleter &d) : p(sp.p), ref(sp.ref), del(d)
    {
        ++*ref;
    }
    my_shared_ptr(const my_shared_ptr &sp) : p(sp.p), ref(sp.ref), del(sp.del)
    {
        ++*ref;
    }
    my_shared_ptr(my_shared_ptr &&sp) noexcept : p(std::move(sp.p)), ref(std::move(sp.ref)), del(std::move(sp.del))
    {
        sp.p = nullptr;
        sp.ref = nullptr;
        sp.del = nullptr;
    }
    my_shared_ptr &operator=(const my_shared_ptr &);
    my_shared_ptr &operator=(my_shared_ptr &&) noexcept;
    template <typename U>
    my_shared_ptr(const my_shared_ptr<U> &sp) : p(sp.p), ref(sp.ref), del(sp.del)
    {
        ++*ref;
    }
    template <typename U>
    my_shared_ptr(my_shared_ptr<U> &&sp) noexcept : p(std::move(sp.p)), ref(std::move(sp.ref)), del(std::move(sp.del))
    {
        sp.p = nullptr;
        sp.ref = nullptr;
        sp.del = nullptr;
    }
    template <typename U>
    my_shared_ptr &operator=(const my_shared_ptr<U> &);
    template <typename U>
    my_shared_ptr &operator=(my_shared_ptr<U> &&) noexcept;
    ~my_shared_ptr();
    T &operator*() const;
    T *operator->() const;
    explicit operator bool() const
    {
        return p;
    }
    std::size_t use_count() const
    {
        if (ref == nullptr)
        {
            return 0;
        }
        else
        {
            return *ref;
        }
    };
    bool unique() const
    {
        if (ref == nullptr)
        {
            return false;
        }
        else
        {
            return (*ref == 1);
        }
    }
    T *get() const
    {
        return p;
    }
    void swap(my_shared_ptr &);
    void reset();
    void reset(T *);
    void reset(T *, const Deleter &);
private:
    void free() const;
    T *p;
    std::size_t *ref;
    Deleter del;
};

template <typename T>
inline void my_shared_ptr<T>::free() const
{
    if ((ref != nullptr) && (--*ref == 0))
    {
        del ? del(p) : delete p;
        delete ref;
    }
}

template <typename T>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(const my_shared_ptr &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.ref;
    free();
    p = rhs.p;
    ref = rhs.ref;
    del = rhs.del;
    return *this;
}

template <typename T>
template <typename U>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(const my_shared_ptr<U> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.ref;
    free();
    p = rhs.p;
    ref = rhs.ref;
    del = rhs.del;
    return *this;
}

template <typename T>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(my_shared_ptr &&rhs) noexcept
{
    if(this != &rhs)
    {
        p = std::move(rhs.p);
        ref = std::move(rhs.ref);
        del = std::move(rhs.del);
        rhs.p = nullptr;
        rhs.ref = nullptr;
        rhs.del = nullptr;
    }
    return *this;
}

template <typename T>
template <typename U>
my_shared_ptr<T> &my_shared_ptr<T>::operator=(my_shared_ptr<U> &&rhs) noexcept
{
    if(this != &rhs)
    {
        p = std::move(rhs.p);
        ref = std::move(rhs.ref);
        del = std::move(rhs.del);
        rhs.p = nullptr;
        rhs.ref = nullptr;
        rhs.del = nullptr;
    }
    return *this;
}

template <typename T>
my_shared_ptr<T>::~my_shared_ptr()
{
    free();
}

template <typename T>
inline T &my_shared_ptr<T>::operator*() const
{
    if(!p)
        throw std::runtime_error("deference null pointer");
    return *p;
}
template <typename T>
inline T *my_shared_ptr<T>::operator->() const
{
    return &(this->operator*());
}

template <typename T>
inline void my_swap(my_shared_ptr<T> &lhs, my_shared_ptr<T> &rhs)
{
    lhs.swap(rhs);
}

template <typename T>
inline void my_shared_ptr<T>::swap(my_shared_ptr &rhs)
{
    using std::swap;
    swap(this->p, rhs.p);
    swap(this->ref, rhs.ref);
    swap(this->del, rhs.del);
}

template <typename T>
void my_shared_ptr<T>::reset()
{
    free();
    p = nullptr;
    ref = nullptr;
    del = nullptr;
}
template <typename T>
void my_shared_ptr<T>::reset(T *tp)
{
    free();
    p = tp;
    ref = new std::size_t(1);
    del = nullptr;
}
template <typename T>
void my_shared_ptr<T>::reset(T *tp, const Deleter &d)
{
    free();
    p = tp;
    ref = new std::size_t(1);
    del = d;
}

template <typename T>
inline my_shared_ptr<T> make_my_shared(const T &t)
{
    return my_shared_ptr<T>(new T(t));
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
void del_int(int *p)
{
    delete p;
    cout << "delete int pointer p" << endl;
}
int del_str(string *p)
{
    delete p;
    cout << "delete string pointer p" << endl;
    return 0;
}

int main(int argc, const char *argv[])
{
    try
    {
        my_shared_ptr<int> sp(new int(2));
        my_shared_ptr<int> sp2 = sp;
        my_shared_ptr<int> sp3;
        cout << "Is sp unique? " << sp.unique() << endl;
        cout << "sp.use_count(): " << sp.use_count() << endl;
        cout << "sp2.use_count(): " << sp2.use_count() << endl;
        cout << "sp3.use_count(): " << sp3.use_count() << endl;
        my_shared_ptr<int> sp4(sp2, del_int);
        cout << "sp4.use_count(): " << sp4.use_count() << endl;
        cout << "sp4 = " << *sp4 << endl;
        {
            my_shared_ptr<string> sp5;
            cout << "sp5.use_count(): " << sp5.use_count() << endl;
            sp5.reset(new string("this"), del_str);
            cout << "sp5.use_count(): " << sp5.use_count() << endl;
        }
        cout << "sp6: ";
        auto sp6 = make_my_shared<vector<int>>(vector<int> {1, 2, 3, 4, 5});
        for(auto p = sp6->begin(); p != sp6->end(); ++p)
            cout << *p << " ";
        cout << endl;
        my_shared_ptr<double> sp7;
        if(sp7)
            cout << "sp7 != nullptr" << endl;
        else
            cout << "sp7 == nullptr" << endl;
        my_shared_ptr<vector<char>> sp9(new vector<char> {1, 2, 3});
        auto sp10 = sp9;
        cout << "sp9.use_count(): " << sp9.use_count() << endl;
        sp9.reset();
        cout << "sp9.use_count(): " << sp9.use_count() << endl;
        cout << "sp10.use_count(): " << sp10.use_count() << endl;
        my_shared_ptr<int> sp11;
        cout << "sp11.use_count(): " << sp11.use_count() << endl;
        my_shared_ptr<vector<string>> sp12(new vector<string>(), [](vector<string> *q)
        {
            cout << "delete vector" << endl;
            delete q;
        });
        my_swap(sp, sp11);
        cout << "sp.use_count(): " << sp.use_count() << endl;
        cout << "sp11.use_count(): " << sp11.use_count() << endl;
        sp.swap(sp11);
        cout << "sp.use_count(): " << sp.use_count() << endl;
        cout << "sp11.use_count(): " << sp11.use_count() << endl;
        try
        {
            cout << *sp << " " << *sp11 << endl;
        }
        catch(runtime_error &err)
        {
            cerr << err.what() << endl;
        }
        std::initializer_list<int> il = {1, 2, 3};
        auto sp13 = make_my_shared<vector<int>>(il);
        cout << "sp13.use_count(): " << sp13.use_count() << endl;
        my_swap(sp, sp11);
        auto pi = sp11.get();
        cout << *pi << endl;
        my_shared_ptr<int> sp14;
        my_shared_ptr<Base> sp15(new Derived());
        sp15->print();

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
