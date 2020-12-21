#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
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
#include <cstdlib>
#include <cstring>
#include <cctype>
#include<climits>
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
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::vector;
using std::list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
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
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::numeric_limits;
using std::common_type;
using std::reverse;

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

template <typename T>
class Handle
{
public:
    Handle() : p(nullptr) { }
    Handle(T *t) : p(t) { }
    Handle(const Handle<T> &s) : p(nullptr)
    {
        if (s.p != nullptr)
        {
            p = s.p->clone();
        }
    }

    Handle<T> &operator=(const Handle<T> &);
    ~Handle()
    {
        delete p;
    }

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const;
    T *operator->() const;

private:
    T *p;
};

template<typename T>
Handle<T> &Handle<T>::operator=(const Handle<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    delete p;
    p = rhs.p != nullptr ? rhs.p->clone() : nullptr;
    return *this;
}

template <typename T>
T &Handle<T>::operator*() const
{
    if (p != nullptr)
    {
        return *p;
    }
    throw runtime_error("unbound Handle");
}

template <typename T>
T *Handle<T>::operator->() const
{
    if (p != nullptr)
    {
        return p;
    }
    throw runtime_error("unbound Handle");
}

template <typename T>
class Ref_handle
{
public:
    Ref_handle() : refptr(new size_t(1)), p(nullptr) { }
    Ref_handle(T *t) : refptr(new size_t(1)), p(t) { }

    Ref_handle(const Ref_handle<T> &h) : refptr(h.refptr), p(h.p)
    {
        ++*refptr;
    }

    Ref_handle<T> &operator=(const Ref_handle<T> &);

    ~Ref_handle();

    operator bool() const
    {
        return p != nullptr;
    }
    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ref_handle");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ref_handle");
    }

private:
    T *p;
    size_t *refptr;
};

template<typename T>
Ref_handle<T> &Ref_handle<T>::operator=(const Ref_handle<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.refptr;

    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }

    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template<typename T>
Ref_handle<T>::~Ref_handle()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

class Ref_counter
{
public:
    Ref_counter() : counter(new size_t(1)) { };
    Ref_counter(size_t s) : counter(new size_t(s)) { };
    Ref_counter(const Ref_counter &r) : counter(r.counter) { };

    Ref_counter &operator=(const Ref_counter &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        if (*counter <= 0)
        {
            delete counter;
        }
        counter = rhs.counter;
        return *this;
    };

    Ref_counter &operator++()
    {
        (*counter)++;
        return *this;
    };

    Ref_counter &operator--()
    {
        (*counter)--;
        return *this;
    };

    Ref_counter operator++(int)
    {
        Ref_counter ret(*(this->counter));
        (*counter)++;
        return ret;
    };

    Ref_counter operator--(int)
    {
        Ref_counter ret(*(this->counter));
        (*counter)--;
        return ret;
    };

    ~Ref_counter()
    {
        if (*counter <= 0)
        {
            delete counter;
        }
    };

    size_t count()
    {
        return *counter;
    };

private:
    size_t *counter;
};


template<typename T>
T *clone(const T *tp)
{
    return tp->clone();
}

template<typename T>
class Ptr
{
public:
    Ptr() : refptr(new size_t(1)), p(nullptr) { }
    Ptr(T *t) : refptr(new size_t(1)), p(t) { }
    Ptr(const Ptr<T> &h) : refptr(h.refptr), p(h.p)
    {
        ++*refptr;
    }

    Ptr<T> &operator=(const Ptr<T> &);
    ~Ptr();

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ptr");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ptr");
    }

    void make_unique()
    {
        if (*refptr > 1)
        {
            --*refptr;
            refptr = new size_t(1);
            p = p != nullptr ? clone(p) : nullptr;
        }
    }

private:
    T *p;
    size_t *refptr;
};

template<typename T>
Ptr<T> &Ptr<T>::operator=(const Ptr<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    ++*rhs.refptr;
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template<typename T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0)
    {
        delete refptr;
        delete p;
    }
}

template<typename T>
class Ptr_r
{
public:
    Ptr_r() : p(nullptr) { }
    Ptr_r(T *t) : p(t) { }
    Ptr_r(const Ptr_r<T> &h) : ref_c(h.ref_c), p(h.p)
    {
        ++ref_c;
    }

    Ptr_r<T> &operator=(const Ptr_r<T> &);
    ~Ptr_r();

    operator bool() const
    {
        return p != nullptr;
    }

    T &operator*() const
    {
        if (p != nullptr)
        {
            return *p;
        }
        throw runtime_error("unbound Ptr_r");
    }

    T *operator->() const
    {
        if (p != nullptr)
        {
            return p;
        }
        throw runtime_error("unbound Ptr_r");
    }

    void make_unique()
    {
        if (ref_c.count() > 1)
        {
            --ref_c;
            ref_c = Ref_counter();
            p = p != nullptr ? clone(p) : nullptr;
        }
    }

private:
    T *p;
    Ref_counter ref_c;
};

template<typename T>
Ptr_r<T> &Ptr_r<T>::operator=(const Ptr_r<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    if ((--ref_c).count() == 0)
    {
        delete p;
    }
    ref_c = rhs.ref_c;
    p = rhs.p;
    ++ref_c;
    return *this;
}

template<typename T>
Ptr_r<T>::~Ptr_r()
{
    if ((--ref_c).count() == 0)
    {
        delete p;
    }
}

template <typename T>
class Vec
{
public:
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef size_t size_type;
    typedef T value_type;

    Vec()
    {
        create();
    }
    explicit Vec(size_type n, const T &val = T())
    {
        create(n, val);
    }
    Vec(const Vec<T> &v)
    {
        create(v.begin(), v.end());
    }
    template<typename In>
    Vec(In b, In e)
    {
        create(b, e);
    }

    Vec &operator=(const Vec<T> &);
    ~Vec()
    {
        uncreate();
    }
    T &operator[](size_type i)
    {
        return data[i];
    }
    const T &operator[](size_type i) const
    {
        return data[i];
    }

    void push_back(const T &val, bool double_grow = true)
    {
        if (avail == limit)
        {
            grow(double_grow);
        }
        unchecked_append(val);
    }

    size_type size() const
    {
        return avail - data;
    }
    iterator begin()
    {
        return data;
    }
    const_iterator begin() const
    {
        return data;
    }
    iterator end()
    {
        return avail;
    }
    const_iterator end() const
    {
        return avail;
    }

    ostream &print_vec(ostream &);
    void clear()
    {
        destroy();
    };
    iterator erase(iterator it)
    {
        return destroy(it);
    };
    iterator erase(iterator b, iterator e)
    {
        return destroy(b, e);
    };

    template <typename In>
    void insert(iterator position, In first, In last)
    {
        insert_elements(position, first, last);
    };

    template <typename In>
    void assign(In first, In last)
    {
        assign_elements(first, last);
    };

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T &);
    void create(const_iterator, const_iterator);
    template<typename In>
    void create(In, In);

    void uncreate();

    void grow(bool);

    void unchecked_append(const T &);

    void destroy();
    iterator destroy(iterator);
    iterator destroy(iterator, iterator);

    template <typename In>
    void insert_elements(iterator, In, In);

    template <typename In>
    void assign_elements(In, In);
};

template <typename T>
void Vec<T>::create()
{
    data = avail = limit = nullptr;
}

template <typename T>
void Vec<T>::create(size_type n, const T &val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <typename T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template<typename T>
template<typename In>
void Vec<T>::create(In b, In e)
{
    data = alloc.allocate(e - b);
    limit = avail = std::uninitialized_copy(b, e, data);
}

template <typename T>
void Vec<T>::uncreate()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = nullptr;
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    uncreate();
    create(rhs.begin(), rhs.end());
    return *this;
}

template <typename T>
void Vec<T>::grow(bool double_grow)
{
    size_type new_size;

    if (double_grow)
    {
        new_size = max(2 * (limit - data), ptrdiff_t(1));
    }
    else
    {
        new_size = (limit - data) + 1;
    }

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <typename T>
void Vec<T>::unchecked_append(const T &val)
{
    alloc.construct(avail++, val);
}

template<typename T>
std::ostream &Vec<T>::print_vec(std::ostream &os)
{
    if (avail - data > 0)
    {
        iterator iter = data;

        os << *iter++;

        while (iter != avail)
        {
            os << ", " << *iter++;
        }

        os << std::endl;
    }
    return os;
}

template <typename T>
void Vec<T>::destroy()
{
    if (data != nullptr)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
    }
    avail = data;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator pos)
{
    if (data != nullptr && pos != avail)
    {
        alloc.destroy(pos);
        iterator it = pos + 1;

        while (it != avail)
        {
            alloc.construct(pos++, *it);
            alloc.destroy(it++);
        }
        avail = pos;
    }
    return avail;
}

template<typename T>
typename Vec<T>::iterator Vec<T>::destroy(iterator b, iterator e)
{
    if (data != nullptr && b != avail && b != e)
    {
        iterator it = b;
        while (it != e)
        {
            alloc.destroy(it++);
        }

        while (e != avail)
        {
            alloc.construct(b++, *e);
            alloc.destroy(e++);
        }

        avail = b;
    }
    return avail;
}

template <typename T>
template <typename In>
void Vec<T>::insert_elements(iterator pos, In first, In last)
{
    Vec<T> tail(pos, avail);

    destroy(pos, avail);

    In iter1 = first;

    while (iter1 != last)
    {
        push_back(*iter1++);
    }

    iterator iter2 = tail.begin();

    while (iter2 != tail.end())
    {
        push_back(*iter2++);
    }
}

template <typename T>
template <typename In>
void Vec<T>::assign_elements(In first, In last)
{
    uncreate();
    create(first, last);
}

template<>
inline Vec<char> *clone< Vec<char> >(const Vec<char> *vp)
{
    return new Vec<char>(*vp);
}

class Str
{
public:
    typedef Vec<char>::size_type size_type;
    typedef Vec<char>::iterator iterator;
    typedef Vec<char>::const_iterator const_iterator;

    Str() : data(new Vec<char>) { }
    Str(size_type n, char c) : data(new Vec<char>(n, c)) { }
    Str(const char *cp) : data(new Vec<char>)
    {
        copy(cp, cp + strlen(cp), back_inserter(*data));
    }
    template<class In>
    Str(In b, In e) : data(new Vec<char>(b, e)) { }

    size_type size() const
    {
        return data->size();
    }

    char &operator[](size_type i)
    {
        data.make_unique();
        return (*data)[i];
    }

    const char &operator[](size_type i) const
    {
        return (*data)[i];
    }

    Str &operator+=(const Str &s)
    {
        data.make_unique();
        copy(s.data->begin(), s.data->end(), back_inserter(*data));
        return *this;
    }

    iterator begin()
    {
        return data->begin();
    };
    const_iterator begin() const
    {
        return data->begin();
    };
    iterator end()
    {
        return data->end();
    };
    const_iterator end() const
    {
        return data->end();
    };

    friend istream &operator >> (istream &is, Str &s)
    {
        s.data->clear();
        char c;
        while (is.get(c) && isspace(c))
            ;
        if (is)
        {
            do
            {
                s.data->push_back(c);
            }
            while (is.get(c) && !isspace(c));
            if (is)
            {
                is.unget();
            }
        }
        return is;
    }

    friend ostream &operator<< (ostream &os, const Str &s)
    {
        for (Str::size_type i = 0; i != s.size(); ++i)
        {
            os << s[i];
        }
        return os;
    }

    friend Str operator+(const Str &l, const Str &r)
    {
        Str ret = l;
        ret += r;
        return ret;
    }

private:
    Ptr< Vec<char> > data;
};

class Str_c
{
public:
    typedef size_t size_type;
    typedef char *iterator;
    typedef const char *const_iterator;

    Str_c()
    {
        create();
    }
    Str_c(size_t n, char c)
    {
        create(n, c);
    }
    Str_c(const Str_c &s)
    {
        create(s.begin(), s.end());
    }
    Str_c(const char *cp)
    {
        create(cp, cp + strlen(cp));
    }
    template<typename In>
    Str_c(In b, In e)
    {
        create(b, e);
    }

    ~Str_c()
    {
        uncreate();
    }

    Str_c &operator=(const Str_c &);

    size_t size() const
    {
        return length - 1;
    }

    char &operator[](size_t i)
    {
        return d[i];
    }
    const char &operator[](size_t i) const
    {
        return d[i];
    }

    Str_c &operator+=(const char ch)
    {
        append(ch);
        return *this;
    }

    Str_c &operator+=(const char *cp)
    {
        append(cp, strlen(cp));
        return *this;
    }

    Str_c &operator+=(const Str_c &s)
    {
        append(s);
        return *this;
    }

    operator void *() const
    {
        return is_not_empty();
    };
    const char *c_str() const
    {
        return d;
    }
    const char *data() const
    {
        return d;
    }

    size_t copy(char *p, size_t n) const
    {
        return copy_characters(p, n);
    }

    iterator begin()
    {
        return d;
    };
    const_iterator begin() const
    {
        return d;
    };
    iterator end()
    {
        return d + size();
    };
    const_iterator end() const
    {
        return d + size();
    };

    friend istream &operator >> (istream &, Str_c &);
    friend ostream &operator<<(ostream &, const Str_c &);
    friend istream &getline(istream &, Str_c &);
    friend Str_c operator+(const Str_c &, const Str_c &);
    friend Str_c operator+(const Str_c &, const char *);
    friend Str_c operator+(const char *, const Str_c &);

    friend bool operator== (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) == 0;
    }

    friend  bool operator!= (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) != 0;
    }

    friend  bool operator< (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }

    friend  bool operator<= (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
    }

    friend  bool operator> (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) > 0;
    }

    friend  bool operator>= (const Str_c &lhs, const Str_c &rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
    }

private:
    char *d;
    size_t length;
    size_t max_length;

    void create();
    void create(size_t, char);
    void create(const_iterator i, const_iterator j)
    {
        length = j - i + 1;
        max_length =  j - i + 1;
        d = new char[length];
        std::copy(i, j, d);
        d[length - 1] = '\0';
    }

    void uncreate()
    {
        if (length != 0)
        {
            delete[] d;
        }
        length = 0;
        max_length = 0;
    }

    template<class In>
    void create(In i, In j)
    {
        length = j - i + 1;
        max_length = j - i + 1;
        d = new char[length];
        std::copy(i, j, d);
        d[length - 1] = '\0';
    }

    void append(const Str_c &);
    void append(const char *, const size_t);
    void prepend(const char *, const size_t);
    void append(const char);

    size_t copy_characters (char *, size_t) const;

    void *is_not_empty() const
    {
        if (size() > 0)
        {
            return d;
        }
        else
        {
            return nullptr;
        }
    }
};

void Str_c::create()
{
    d = new char[1];
    length = 1;
    max_length = 1;
    d[0] = '\0';
}

void Str_c::create(size_t s, char c)
{
    if (s <= 0)
    {
        create();
    }
    else
    {
        d = new char[s + 1];
        length = s + 1;
        max_length = s + 1;
        memset(d, c, s);
        d[s] = '\0';
    }
}

Str_c &Str_c::operator=(const Str_c &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    uncreate();
    create(rhs.begin(), rhs.end());
    return *this;
}

void Str_c::append(const Str_c &s)
{
    append(s.data(), s.size());
}

void Str_c::append(const char *str, const size_t count)
{
    size_t old_length = size();
    if (max_length >= old_length + count + 1)
    {
        length = old_length + count + 1;
        memcpy(&d[old_length], str, count);
        d[length - 1] = '\0';
    }
    else
    {
        size_type new_size = max_length;
        while (new_size < old_length + count + 1)
        {
            new_size *= 2;
        }
        char *copy = new char[old_length];
        memcpy(copy, d, old_length);
        uncreate();
        length = old_length + count + 1;
        max_length = new_size;
        d = new char[max_length];
        memcpy(d, copy, old_length);
        memcpy(&d[old_length], str, count);
        d[length - 1] = '\0';

        delete[] copy;
    }
}

void Str_c::prepend(const char *str, const size_t count)
{
    size_t old_length = size();
    size_type new_size = max_length;
    while (new_size < old_length + count + 1)
    {
        new_size *= 2;
    }

    char *copy = new char[old_length];
    memcpy(copy, d, old_length);
    uncreate();

    length = old_length + count + 1;
    max_length = new_size;
    d = new char[max_length];
    memcpy(d, str, count);
    memcpy(&d[count], copy, old_length);
    d[length - 1] = '\0';

    delete[] copy;
}

void Str_c::append(const char c)
{
    append(&c, 1);
}

Str_c operator+(const Str_c &s, const Str_c &t)
{
    Str_c r = s;
    r += t;
    return r;
}

Str_c operator+(const Str_c &s, const char *str)
{
    Str_c r = s;
    r += str;
    return r;
}

Str_c operator+(const char *str, const Str_c &s)
{
    Str_c r = str;
    r += s;
    return r;
}

ostream &operator<<(ostream &os, const Str_c &s)
{
    copy(s.begin(), s.end(), ostream_iterator<char>(os));
    return os;
}

istream &operator>>(istream &is, Str_c &s)
{
    s.uncreate();
    s.create();
    char c;
    while (is.get(c) && isspace(c))
        ;
    if (is)
    {
        do
        {
            s.append(c);
        }
        while (is.get(c) && !isspace(c));
        if (is)
        {
            is.unget();
        }
    }
    return is;
}

size_t Str_c::copy_characters(char *dest, size_t count) const
{
    size_t i;

    for (i = 0; i < count && i < size(); i++)
    {
        dest[i] = d[i];
    }

    return i;
}

istream &getline(istream &is, Str_c &s)
{
    s.uncreate();
    s.create();

    char c;

    if (is)
    {
        while (is.get(c) && c != '\n')
        {
            s.append(c);
        }
    }

    return is;
}

class Picture;

class Pic_base
{
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;
    friend class Picture;
    friend ostream &operator<<(ostream &, const Picture &);

    typedef vector<string>::size_type ht_sz;
    typedef string::size_type wd_sz;

    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(ostream &, ht_sz, bool) const = 0;
    virtual void reframe(const char, const char, const char) = 0;

protected:
    static void pad(ostream &os, wd_sz beg, wd_sz end);
};

class Frame_Pic : public Pic_base
{
    friend Picture frame(const Picture &);
    friend Picture frame(const Picture &, const char, const char, const char);

    Ptr<Pic_base> p;
    char corner;
    char top_bottom;
    char side;

    Frame_Pic(const Ptr<Pic_base> &pic, const char corner_val = '+',
              const char top_bottom_val = '-', const char side_val = '|')
        : p(pic), corner(corner_val), top_bottom(top_bottom_val), side(side_val) { }

    wd_sz width() const
    {
        return p->width() + 4;
    }
    ht_sz height() const
    {
        return p->height() + 4;
    }

    void display(ostream &, ht_sz, bool) const;
    void reframe(const char, const char, const char);
};

class VCat_Pic : public Pic_base
{
    friend Picture vcat(const Picture &, const Picture &);

    Ptr<Pic_base> top, bottom;

    VCat_Pic(const Ptr<Pic_base> &t, const Ptr<Pic_base> &b) : top(t), bottom(b) { }

    wd_sz width() const
    {
        return max(top->width(), bottom->width());
    }

    ht_sz height() const
    {
        return top->height() + bottom->height();
    }

    void display(ostream &, ht_sz, bool) const;
    void reframe(const char, const char, const char);
};

class HCat_Pic : public Pic_base
{
    friend Picture hcat(const Picture &, const Picture &);

    Ptr<Pic_base> left, right;

    HCat_Pic(const Ptr<Pic_base> &l, const Ptr<Pic_base> &r) : left(l), right(r) { }

    wd_sz width() const
    {
        return left->width() + right->width();
    }

    ht_sz height() const
    {
        return max(left->height(), right->height());
    }

    void display(ostream &, ht_sz, bool) const;
    void reframe(const char, const char, const char);
};

class String_Pic : public Pic_base
{
    friend class Picture;

    vector<string> data;
    String_Pic(const vector<string> &v) : data(v) { }

    wd_sz width() const;
    ht_sz height() const
    {
        return data.size();
    };
    void display(ostream &, ht_sz, bool) const;
    void reframe(const char, const char, const char) {}
};

class Picture
{
    friend Picture frame(const Picture &);
    friend Picture frame(const Picture &, const char, const char, const char);
    friend Picture hcat(const Picture &, const Picture &);
    friend Picture vcat(const Picture &, const Picture &);
    friend ostream &operator<<(ostream &, const Picture &);

public:
    Picture(const vector<string> & = vector<string>());
    void reframe(const char corner, const char top_bottom, const char side);

private:
    Ptr<Pic_base> p;

    Picture(Pic_base *ptr) : p(ptr) { }
};

Picture frame(const Picture &pic)
{
    return new Frame_Pic(pic.p);
}

Picture frame(const Picture &pic, const char corner_val, const char top_bottom_val, const char side_val)
{
    return new Frame_Pic(pic.p, corner_val, top_bottom_val, side_val);
}

Picture hcat(const Picture &l, const Picture &r)
{
    return new HCat_Pic(l.p, r.p);
}

Picture vcat(const Picture &t, const Picture &b)
{
    return new VCat_Pic(t.p, b.p);
}

Picture::Picture(const vector<string> &v) : p(new String_Pic(v)) { }

ostream &operator<<(ostream &os, const Picture &picture)
{
    const Pic_base::ht_sz ht = picture.p->height();
    for (Pic_base::ht_sz i = 0; i != ht; ++i)
    {
        picture.p->display(os, i, false);
        os << endl;
    }
    return os;
};

Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;
    for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
    {
        n = max(n, data[i].size());
    }
    return n;
}

void String_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;
    if (row < height())
    {
        os << data[row];
        start = data[row].size();
    }
    if (do_pad)
    {
        pad(os, start, width());
    }
}

void VCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height())
    {
        top->display(os, row, do_pad);
        w = top->width();
    }
    else if (row < height())
    {
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad)
    {
        pad(os, w, width());
    }
}

void HCat_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    ht_sz left_row = row;
    ht_sz right_row = row;

    if (left->height() > right->height())
    {
        ht_sz index = ((left->height() - right->height()) / 2);

        if (row >= index)
        {
            right_row = row - index;
        }
        else
        {
            right_row = right->height();
        }
    }
    else
    {
        ht_sz index = ((right->height() - left->height()) / 2);

        if (row >= index)
        {
            left_row = row - index;
        }
        else
        {
            left_row = left->height();
        }
    }

    left->display(os, left_row, do_pad || right_row < right->height());
    right->display(os, right_row, do_pad);
}

void Frame_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    if (row >= height())
    {
        if (do_pad)
        {
            pad(os, 0, width());
        }
    }
    else
    {
        if (row == 0 || row == height() - 1)
        {
            os << corner << string(width() - 2, top_bottom) << corner;
        }
        else if (row == 1 || row == height() - 2)
        {
            os << side;
            pad(os, 1, width() - 1);
            os << side;
        }
        else
        {
            os << side << ' ';
            p->display(os, row - 2, true);
            os << ' ' << side;
        }
    }
}

void Pic_base::pad(ostream &os, wd_sz beg, wd_sz end)
{
    while (beg != end)
    {
        os << " ";
        ++beg;
    }
}

class Picture_v;

class Pic_base_v
{
    friend class Frame_Pic_v;
    friend class HCat_Pic_v;
    friend class VCat_Pic_v;
    friend class String_Pic_v;
    friend class Picture_v;
    friend ostream &operator<<(ostream &, const Picture_v &);

    typedef Vec<Str>::size_type ht_sz;
    typedef Str::size_type wd_sz;

    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(ostream &, ht_sz, bool) const = 0;

protected:
    static void pad(ostream &os, wd_sz beg, wd_sz end);
};

class Frame_Pic_v : public Pic_base_v
{
    friend Picture_v frame(const Picture_v &);

    Ptr<Pic_base_v> p;

    Frame_Pic_v(const Ptr<Pic_base_v> &pic) : p(pic) { }

    wd_sz width() const
    {
        return p->width() + 4;
    }
    ht_sz height() const
    {
        return p->height() + 4;
    }

    void display(ostream &, ht_sz, bool) const;
};

class VCat_Pic_v : public Pic_base_v
{
    friend Picture_v vcat(const Picture_v &, const Picture_v &);

    Ptr<Pic_base_v> top, bottom;

    VCat_Pic_v(const Ptr<Pic_base_v> &t, const Ptr<Pic_base_v> &b) : top(t), bottom(b) { }

    wd_sz width() const
    {
        return max(top->width(), bottom->width());
    }

    ht_sz height() const
    {
        return top->height() + bottom->height();
    }

    void display(ostream &, ht_sz, bool) const;
};

class HCat_Pic_v : public Pic_base_v
{
    friend Picture_v hcat(const Picture_v &, const Picture_v &);

    Ptr<Pic_base_v> left, right;

    HCat_Pic_v(const Ptr<Pic_base_v> &l, const Ptr<Pic_base_v> &r) : left(l), right(r) { }

    wd_sz width() const
    {
        return left->width() + right->width();
    }

    ht_sz height() const
    {
        return max(left->height(), right->height());
    }

    void display(ostream &, ht_sz, bool) const;
};

class String_Pic_v : public Pic_base_v
{
    friend class Picture_v;

    Vec<Str> data;
    String_Pic_v(const Vec<Str> &v) : data(v) { }

    wd_sz width() const;
    ht_sz height() const
    {
        return data.size();
    };
    void display(ostream &, ht_sz, bool) const;
};

class Picture_v
{
    friend Picture_v frame(const Picture_v &);
    friend Picture_v hcat(const Picture_v &, const Picture_v &);
    friend Picture_v vcat(const Picture_v &, const Picture_v &);
    friend ostream &operator<<(ostream &, const Picture_v &);

public:
    Picture_v(const Vec<Str> & = Vec<Str>());

private:
    Ptr<Pic_base_v> p;
    Picture_v(Pic_base_v *ptr) : p(ptr) { }
};

Picture_v frame(const Picture_v &pic)
{
    return new Frame_Pic_v(pic.p);
}

Picture_v hcat(const Picture_v &l, const Picture_v &r)
{
    return new HCat_Pic_v(l.p, r.p);
}

Picture_v vcat(const Picture_v &t, const Picture_v &b)
{
    return new VCat_Pic_v(t.p, b.p);
}

Picture_v::Picture_v(const Vec<Str> &v) : p(new String_Pic_v(v)) { }

ostream &operator<<(ostream &os, const Picture_v &picture_v)
{
    const Pic_base_v::ht_sz ht = picture_v.p->height();
    for (Pic_base_v::ht_sz i = 0; i != ht; ++i)
    {
        picture_v.p->display(os, i, false);
        os << endl;
    }
    return os;
};

Pic_base_v::wd_sz String_Pic_v::width() const
{
    Pic_base_v::wd_sz n = 0;
    for (Pic_base_v::ht_sz i = 0; i != data.size(); ++i)
    {
        n = max(n, data[i].size());
    }
    return n;
}

void String_Pic_v::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;
    if (row < height())
    {
        os << data[row];
        start = data[row].size();
    }
    if (do_pad)
    {
        pad(os, start, width());
    }
}

void VCat_Pic_v::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height())
    {
        top->display(os, row, do_pad);
        w = top->width();
    }
    else if (row < height())
    {
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad)
    {
        pad(os, w, width());
    }
}

void HCat_Pic_v::display(ostream &os, ht_sz row, bool do_pad) const
{
    left->display(os, row, do_pad || row < right->height());
    right->display(os, row, do_pad);
}

void Frame_Pic_v::display(ostream &os, ht_sz row, bool do_pad) const
{
    if (row >= height())
    {
        if (do_pad)
        {
            pad(os, 0, width());
        }
    }
    else
    {
        if (row == 0 || row == height() - 1)
        {
            os << Str(width(), '*');
        }
        else if (row == 1 || row == height() - 2)
        {
            os << '*';
            pad(os, 1, width() - 1);
            os << '*';
        }
        else
        {
            os << "* ";
            p->display(os, row - 2, true);
            os << " *";
        }
    }
}

void Pic_base_v::pad(ostream &os, wd_sz beg, wd_sz end)
{
    while (beg != end)
    {
        os << " ";
        ++beg;
    }
}

void Frame_Pic::reframe(const char corner_val, const char top_bottom_val, const char side_val)
{
    this->corner = corner_val;
    this->top_bottom = top_bottom_val;
    this->side = side_val;

    p->reframe(corner_val, top_bottom_val, side_val);
}

void VCat_Pic::reframe(const char corner_val, const char top_bottom_val, const char side_val)
{
    top->reframe(corner_val, top_bottom_val, side_val);
    bottom->reframe(corner_val, top_bottom_val, side_val);
}

void HCat_Pic::reframe(const char corner_val, const char top_bottom_val, const char side_val)
{
    left->reframe(corner_val, top_bottom_val, side_val);
    right->reframe(corner_val, top_bottom_val, side_val);
}

void Picture::reframe(const char corner_val, const char top_bottom_val, const char side_val)
{
    p->reframe(corner_val, top_bottom_val, side_val);
}

double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
    {
        throw domain_error("Student has done no homework");
    }
    return grade(midterm, final, median(hw));
}

istream &read_hw(istream &is, vector<double> &hw)
{
    if (is)
    {
        double x;
        while (is >> x)
        {
            hw.push_back(x);
        }

        is.clear();
        while (is.get() != '\n')
        {
            continue;
        }
    }

    return is;
}

class Core
{
public:
    friend class Student_info;
    friend class Audit;
    Core() : midterm(0), final(0)
    {
        cerr << "constructor Core()" << endl;
    }
    Core(istream &is)
    {
        cerr << "constructor Core(istream &is)" << endl;
        read(is);
    }

    virtual ~Core()
    {
        cerr << "destructor ~Core()" << endl;
    }

    const string &name() const
    {
        return _name;
    }
    virtual double grade() const
    {
        return ::grade(midterm, final, homework);
    }
    string letter_grade() const;
    virtual istream &read(istream &);

    bool valid() const
    {
        return !homework.empty();
    }
    virtual bool requirements_met() const
    {
        return find(homework.begin(), homework.end(), 0.0) == homework.end();
    }
    virtual Core *clone() const
    {
        return new Core(*this);
    }

protected:
    istream &read_common(istream &in)
    {
        in >> _name >> midterm >> final;
        return in;
    }
    double midterm, final;
    vector<double> homework;

private:
    string _name;
};

istream &Core::read(istream &in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

string Core::letter_grade() const
{
    static const double numbers[] =
    {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    static const char *const letters[] =
    {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

    double result = grade();

    for (size_t i = 0; i < ngrades; ++i)
    {
        if (result >= numbers[i])
        {
            return letters[i];
        }
    }
    return "?\?\?";
}

inline bool compare(const Core &c1, const Core &c2)
{
    return c1.name() < c2.name();
}

inline bool compare_Core_ptrs(const Core *cp1, const Core *cp2)
{
    return compare(*cp1, *cp2);
}

class Grad : public Core
{
public:
    Grad() : thesis(0.0)
    {
        cerr << "constructor Grad()" << endl;
    }
    Grad(istream &is)
    {
        cerr << "constructor Grad(istream &is)" << endl;
        read(is);
    }

    ~Grad()
    {
        cerr << "destructor ~Grad()" << endl;
    }
    double grade() const;
    istream &read(istream &);

    bool requirements_met() const
    {
        return Core::requirements_met() && thesis != 0.0;
    }
    Grad *clone() const
    {
        return new Grad(*this);
    }

protected:

private:
    double thesis;
};

istream &Grad::read(istream &in)
{
    Core::read_common(in);
    in >> Grad::thesis;
    read_hw(in, Core::homework);
    return in;
}

double Grad::grade() const
{
    return min(Core::grade(), Grad::thesis);
}

class Credit : public Core
{
public:
    Credit() {}
    Credit(istream &is) : Core(is) {}

    double grade() const;
    bool passed() const
    {
        return grade() >= 60;
    }

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }
    Credit *clone() const
    {
        return new Credit(*this);
    }

protected:
};

double Credit::grade() const
{
    if (Core::homework.empty())
    {
        return (midterm + final) / 2.0;
    }
    else
    {
        return Core::grade();
    }
}

class Audit : public Core
{
public:
    Audit() {}
    Audit(istream &is)
    {
        read(is);
    }

    istream &read(istream &in)
    {
        in >> _name;
        return in;
    }

    double grade() const
    {
        return 0.0;
    };

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }
    Audit *clone() const
    {
        return new Audit(*this);
    }

protected:
};

class Student_info
{
public:
    Student_info() { }
    Student_info(istream &is)
    {
        read(is);
    }

    istream &read(istream &);

    const string &name() const
    {
        if (cp)
        {
            return cp->name();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

    double grade() const
    {
        if (cp)
        {
            return cp->grade();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

private:
    Handle<Core> cp;
};

istream &Student_info::read(istream &is)
{
    char ch;
    cout << "Enter U for new Core, C for new Credit, A for new Audit, G for new Grad" << endl;
    if (is >> ch)
    {
        if (ch == 'U')
        {
            cout << "new Core" << endl;
            cp = new Core(is);
        }
        else if (ch == 'C')
        {
            cout << "new Credit" << endl;
            cp = new Credit(is);
        }
        else if (ch == 'A')
        {
            cout << "new Audit" << endl;
            cp = new Audit(is);
        }
        else
        {
            cout << "new Grad" << endl;
            cp = new Grad(is);
        }
    }
    return is;
}

inline bool compare_info(const Student_info &s1, const Student_info &s2)
{
    return s1.name() < s2.name();
}

class Student_info_p
{
public:
    Student_info_p() { }
    Student_info_p(istream &is)
    {
        read(is);
    }

    istream &read(istream &);

    const string &name() const
    {
        if (cp)
        {
            return cp->name();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

    double grade() const
    {
        if (cp)
        {
            return cp->grade();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

private:
    Ptr<Core> cp;
};

istream &Student_info_p::read(istream &is)
{
    char ch;
    cout << "Enter U for new Core, C for new Credit, A for new Audit, G for new Grad" << endl;
    if (is >> ch)
    {
        if (ch == 'U')
        {
            cout << "new Core" << endl;
            cp = new Core(is);
        }
        else if (ch == 'C')
        {
            cout << "new Credit" << endl;
            cp = new Credit(is);
        }
        else if (ch == 'A')
        {
            cout << "new Audit" << endl;
            cp = new Audit(is);
        }
        else
        {
            cout << "new Grad" << endl;
            cp = new Grad(is);
        }
    }
    return is;
}

inline bool compare_info_p(const Student_info_p &s1, const Student_info_p &s2)
{
    return s1.name() < s2.name();
}

inline bool compare_Core_handles(const Handle<Core> hc1, const Handle<Core> hc2)
{
    return compare(*hc1, *hc2);
}

inline bool compare_Core_Ptr(const Ptr<Core> hc1, const Ptr<Core> hc2)
{
    return compare(*hc1, *hc2);
}

inline bool compare_Core_Ptr_r(const Ptr_r<Core> hc1, const Ptr_r<Core> hc2)
{
    return compare(*hc1, *hc2);
}

Picture histogram(const vector<Student_info> &students)
{
    Picture names;
    Picture grades;
    for (vector<Student_info>::const_iterator it = students.begin(); it != students.end(); ++it)
    {
        names = vcat(names, vector<string>(1, it->name()));
        grades = vcat(grades, vector<string>(1, " " + string((int)it->grade() / 5, '=')));
    }
    return hcat(names, grades);
}

int main(int argc, const char *argv[])
{
    try
    {
        vector<Student_info> students;
        Student_info record;
        while (record.read(cin))
        {
            students.push_back(record);
        }
        sort(students.begin(), students.end(), compare_info);
        cout << frame(histogram(students)) << endl;

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
