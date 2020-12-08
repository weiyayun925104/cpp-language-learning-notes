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
using std::numeric_limits;
using std::common_type;

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

template<typename T>
class Link
{
private:
    Link<T> *prev;
    Link<T> *succ;
public:
    T value;
    Link(const T &v = T(), Link<T> *p = nullptr, Link<T> *s = nullptr) : value(v), prev(p), succ(s) { }

    Link<T> *insert(Link<T> *n);
    Link<T> *add(Link<T> *n);
    Link<T> *add_ordered(Link<T> *n);
    Link<T> *erase();
    Link<T> *find(const T &v);

    Link<T> *advance(int n);

    Link<T> *next() const
    {
        return succ;
    }
    Link<T> *previous() const
    {
        return prev;
    }
    void print_all();
};

template<typename T>
Link<T> *Link<T>::insert(Link<T> *n)
{
    if (n == nullptr)
    {
        return n;
    }
    n->succ = this;
    if (prev != nullptr)
    {
        prev->succ = n;
    }
    n->prev = prev;
    prev = n;
    return n;
}

template<typename T>
Link<T> *Link<T>::add(Link<T> *n)
{
    if (n == nullptr)
    {
        return n;
    }
    n->prev = this;
    if (succ != nullptr)
    {
        succ->prev = n;
    }
    n->succ = succ;
    succ = n;
    return n;
}

template<typename T>
Link<T> *Link<T>::add_ordered(Link<T> *n)
{
    if (n == nullptr)
    {
        return n;
    }
    if (n->value < value)
    {
        Link<T> *p = insert(n);
        return p;
    }
    Link<T> *p = this;
    while (n->value >= p->value)
    {
        if (p->succ == nullptr)
        {
            p->add(n);
            return this;
        }
        p = p->succ;
    }
    p->insert(n);
    return this;
}

template<typename T>
Link<T> *Link<T>::erase()
{
    if (succ != nullptr)
    {
        succ->prev = prev;
    }
    if (prev != nullptr)
    {
        prev->succ = succ;
    }
    Link<T> *ret = succ;
    succ = nullptr;
    prev = nullptr;
    return ret;
}

template<typename T>
Link<T> *Link<T>::find(const T &v)
{
    Link<T> *p = this;
    while (p != nullptr)
    {
        if (p->value == v)
        {
            return p;
        }
        p = p->succ;
    }
    return nullptr;
}

template<typename T>
Link<T> *Link<T>::advance(int n)
{
    Link<T> *p = this;
    if (0 < n)
    {
        while (n--)
        {
            if (p->succ == nullptr)
            {
                return nullptr;
            }
            p = p->succ;
        }
    }
    else if (n < 0)
    {
        while (n++)
        {
            if (p->prev == nullptr)
            {
                return nullptr;
            }
            p = p->prev;
        }
    }
    return p;
}

template<typename T>
void Link<T>::print_all()
{
    Link<T> *p = this;
    while (p != nullptr)
    {
        cout << p->value << "\n";
        p = p->succ;
    }
}

template<typename T>
void delete_all(Link<T> *p)
{
    while (p != nullptr)
    {
        Link<T> *temp = p->next();
        delete p;
        p = temp;
    }
}

template<typename T>
Link<T> *extract(Link<T> **l, const T &v)
{
    if ( (*l) == nullptr )
    {
        return nullptr;
    }
    Link<T> *p = (*l)->find(v);
    if (p != nullptr)
    {
        if (p == (*l))
        {
            (*l) = p->next();
        }
        p->erase();
        return p;
    }
    return nullptr;
}

template<typename T>
void move(Link<T> *&from, Link<T> *&to, const T &v)
{
    Link<T> *temp = extract<T>(&from, v);
    if (temp != nullptr)
    {
        to = to->add_ordered(temp);
    }
}

template<typename T>
class my_list
{
private:
    Link<T> *first;
    Link<T> *last;
public:
    my_list() : first(new Link<T>()), last(first) { }
    ~my_list()
    {
        delete_all(first);
    }

    void print()
    {
        Link<T> *p = first;
        while (p != last)
        {
            cout << p->value << "\n";
            p = p->next();
        }
    }

    class iterator
    {
    private:
        Link<T> *curr;
    public:
        friend class my_list<T>;
        iterator(Link<T> *p) : curr(p) { }

        iterator &operator++()
        {
            curr = curr->next();
            return *this;
        }
        iterator &operator--()
        {
            curr = curr->previous();
            return *this;
        }
        T &operator*()
        {
            return curr->value;
        }

        bool operator==(const iterator &b) const
        {
            return curr == b.curr;
        }
        bool operator!=(const iterator &b) const
        {
            return curr != b.curr;
        }
    };

    iterator begin();
    iterator end();

    iterator insert(iterator p, const T &v);
    iterator erase(iterator p);

    void push_front(const T &v);
    void push_back(const T &v);
    void pop_front();
    void pop_back();

    T &front();
    T &back();
};

template<typename T>
typename my_list<T>::iterator my_list<T>::begin()
{
    return iterator(first);
}

template<typename T>
typename my_list<T>::iterator my_list<T>::end()
{
    return iterator(last);
}

template<typename T>
typename my_list<T>::iterator my_list<T>::insert(iterator p, const T &v)
{
    Link<T> *n = new Link<T>(v);
    Link<T> *p_link = p.curr;
    Link<T> *p_ret = p_link->insert(n);
    if (first == p_link)
    {
        first = p_ret;
    }
    return iterator(p_ret);
}

template<typename T>
typename my_list<T>::iterator my_list<T>::erase(iterator p)
{
    Link<T> *p_link = p.curr;
    Link<T> *p_ret = p_link->erase();
    if (first == p_link)
    {
        first = p_ret;
    }
    delete p_link;
    return iterator(p_ret);
}

template<typename T>
void my_list<T>::push_front(const T &v)
{
    Link<T> *n = new Link<T>(v);
    Link<T> *p_link = first;
    Link<T> *p_ret = p_link->insert(n);
    first = p_ret;
}

template<typename T>
void my_list<T>::push_back(const T &v)
{
    Link<T> *n = new Link<T>(v);
    Link<T> *p_link = last;
    Link<T> *p_ret = p_link->insert(n);
    if (first == p_link)
    {
        first = p_ret;
    }
}

template<typename T>
void my_list<T>::pop_front()
{
    Link<T> *p_link = first;
    Link<T> *p_ret = p_link->erase();
    first = p_ret;
    delete p_link;
}

template<typename T>
void my_list<T>::pop_back()
{
    Link<T> *p_link = last->previous();
    Link<T> *p_ret = p_link->erase();
    if (first == p_link)
    {
        first = p_ret;
    }
    delete p_link;
}

template<typename T>
T &my_list<T>::front()
{
    Link<T> *p_link = first;
    return p_link->value;
}

template<typename T>
T &my_list<T>::back()
{
    Link<T> *p_link = last->previous();
    return p_link->value;
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
{
    Iterator high = first;
    for (Iterator p = first; p != last; ++p)
    {
        if (*high < *p)
        {
            high = p;
        }
    }
    return high;
}

int main()
{
    try
    {
        my_list<int> lst;
        int x;
        while (cin >> x)
        {
            lst.push_front(x);
        }
        lst.print();
        my_list<int>::iterator p = high(lst.begin(), lst.end());
        cout << "The highest value was " << *p << "\n";
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
