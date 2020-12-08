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
#include <utility>
#include <random>
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
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
    try
    {
        char ch;
        Str_c s;
        while (cin.get(ch) && ch != '!')
        {
            s += ch;
        }

        cout << s << "\n";
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
