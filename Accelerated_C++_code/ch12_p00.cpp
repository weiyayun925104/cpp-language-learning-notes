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

int main()
{
    Str s("hello1");
    cout << s << endl;
    Str t = "hello2";
    cout << t << endl;
    s = "hello3";
    cout << s << endl;
    Str s1 = "test";
    Str s2 = "ing";
    cout << s1 << endl;
    cout << s2 << endl;

    cout << "Enter a string: ";
    cin >> s;
    cout << s << endl;
    cout << s[3] << endl;
    cout << s1 + s2 << endl;

    Str name = "Geert";
    Str greeting = "Hello, " + name + "!";
    cout << name << endl;
    cout << greeting << endl;

    Str temp1("Hello, ");
    Str temp2 = temp1 + name;
    Str temp3("!");
    greeting = temp2 + temp3;
    cout << temp1 << endl;
    cout << temp2 << endl;
    cout << temp3 << endl;
    cout << greeting << endl;

    return 0;
}
