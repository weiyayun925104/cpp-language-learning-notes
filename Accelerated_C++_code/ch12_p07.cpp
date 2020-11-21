#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <cstring>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

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
            alloc.construct(pos++, *it++);
            alloc.destroy(pos);
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

class Str
{
public:
    typedef Vec<char>::size_type size_type;
    typedef Vec<char>::iterator iterator;
    typedef Vec<char>::const_iterator const_iterator;

    Str() { }
    Str(size_type n, char c) : data(n, c) { }
    Str(const char *cp)
    {
        copy(cp, cp + strlen(cp), back_inserter(data));
    }

    template<typename In>
    Str(In b, In e) : data(b, e) { }

    size_type size() const
    {
        return data.size();
    }

    char &operator[](size_type i)
    {
        return data[i];
    }
    const char &operator[](size_type i) const
    {
        return data[i];
    }

    Str &operator+=(const Str &s)
    {
        copy(s.data.begin(), s.data.end(), back_inserter(data));
        return *this;
    }

    template <typename In>
    void insert(iterator position, In first, In last)
    {
        data.insert(position, first, last);
    };

    iterator begin()
    {
        return data.begin();
    };
    const_iterator begin() const
    {
        return data.begin();
    };
    iterator end()
    {
        return data.end();
    };
    const_iterator end() const
    {
        return data.end();
    };

    friend istream &operator >> (istream &is, Str &s)
    {
        s.data.clear();
        char c;
        while (is.get(c) && isspace(c))
            ;
        if (is)
        {
            do
            {
                s.data.push_back(c);
            }
            while (is.get(c) && !isspace(c));
            if (is)
            {
                is.unget();
            }
        }
        return is;
    }
    friend ostream &operator<<(ostream &os, const Str &s)
    {
        for (size_type i = 0; i != s.size(); ++i)
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
    Vec<char> data;
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
    Str_c r = s;
    r.prepend(str, strlen(str));
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

int main()
{
    Str_c greeting = "Hello buddy!";
    Str_c::const_iterator iter = greeting.begin();

    while (iter != greeting.end())
    {
        cout << *iter++;
    }
    cout << endl;

    return 0;
}
