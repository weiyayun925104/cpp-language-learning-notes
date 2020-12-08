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

class God
{
public:
    God(const string &n = "", const string &m = "", const string &v = "", const string &w = "")
        : name(n), mythology(m), vehicle(v), weapon(w) { }
    string name;
    string mythology;
    string vehicle;
    string weapon;
};

ostream &operator<<(ostream &os, const God &g)
{
    os << g.name << ": " << g.mythology << ", "
       << g.vehicle << ", " << g.weapon;
    return os;
}

bool operator==(const God &g1, const God &g2)
{
    return (g1.name == g2.name && g1.mythology == g2.mythology
            && g1.vehicle == g2.vehicle && g1.weapon == g2.weapon);
}

bool operator!=(const God &g1, const God &g2)
{
    return !(g1 == g2);
}

bool operator<(const God &g1, const God &g2)
{
    return g1.name < g2.name;
}

bool operator>(const God &g1, const God &g2)
{
    return g2 < g1;
}

bool operator<=(const God &g1, const God &g2)
{
    return !(g1 > g2);
}

bool operator>=(const God &g1, const God &g2)
{
    return !(g1 < g2);
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
void move(Link<T>*&from, Link<T>*&to, const T &v)
{
    Link<T> *temp = extract<T>(&from, v);
    if (temp != nullptr)
    {
        to = to->add_ordered(temp);
    }
}

int main()
{
    try
    {
        Link<God> *all_gods = new Link<God>(God("Thor", "Norse", "Pinzgauer", "Hammer"));
        all_gods = all_gods->insert(new Link<God>(God("Odin", "Norse", "Eight-legged horse", "")));
        all_gods = all_gods->insert(new Link<God>(God("Zeus", "Greek", "", "Lightning")));
        all_gods = all_gods->insert(new Link<God>(God("Freia", "Norse", "F-transport", "F-weapon")));
        all_gods = all_gods->insert(new Link<God>(God("Hera", "Greek", "H-transport", "Spear")));
        all_gods = all_gods->insert(new Link<God>(God("Athena", "Greek", "A-transport", "A-weapon")));
        all_gods = all_gods->insert(new Link<God>(God("Mars", "Roman", "M-transport", "M-weapon")));
        all_gods = all_gods->insert(new Link<God>(God("Poseidon", "Greek", "Seahorse", "Trident")));
        all_gods = all_gods->insert(new Link<God>(God("Ares", "Greek", "A-transport", "A-weapon")));
        all_gods = all_gods->insert(new Link<God>(God("Vesuvius", "Roman", "V-transport", "Volcano")));
        all_gods = all_gods->insert(new Link<God>(God("Bacchus", "Roman", "Stretcher", "Wine goblet")));

        all_gods->print_all();

        Link<God> *norse_gods = extract<God>(&all_gods, God("Odin", "Norse", "Eight-legged horse", ""));
        move<God>(all_gods, norse_gods, God("Thor", "Norse", "Pinzgauer", "Hammer"));
        move<God>(all_gods, norse_gods, God("Freia", "Norse", "F-transport", "F-weapon"));

        Link<God> *greek_gods = extract<God>(&all_gods, God("Hera", "Greek", "H-transport", "Spear"));
        move<God>(all_gods, greek_gods, God("Athena", "Greek", "A-transport", "A-weapon"));
        move<God>(all_gods, greek_gods, God("Poseidon", "Greek", "Seahorse", "Trident"));
        move<God>(all_gods, greek_gods, God("Zeus", "Greek", "", "Lightning"));
        move<God>(all_gods, greek_gods, God("Ares", "Greek", "A-transport", "A-weapon"));

        Link<God> *roman_gods = extract<God>(&all_gods, God("Mars", "Roman", "M-transport", "M-weapon"));
        move<God>(all_gods, roman_gods, God("Vesuvius", "Roman", "V-transport", "Volcano"));
        move<God>(all_gods, roman_gods, God("Bacchus", "Roman", "Stretcher", "Wine goblet"));

        cout << "\nNorse gods:\n";
        norse_gods->print_all();
        cout << "\nGreek gods:\n";
        greek_gods->print_all();
        cout << "\nRoman gods:\n";
        roman_gods->print_all();

        delete_all<God>(norse_gods);
        delete_all<God>(greek_gods);
        delete_all<God>(roman_gods);
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
