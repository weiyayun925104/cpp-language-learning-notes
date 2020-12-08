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
    os << g.name << ", " << g.mythology << ", ";
    os << g.vehicle << ", " << g.weapon;
    return os;
}

class Link
{
public:
    God value;

    Link(const string &n = "", const string &m = "", const string &v = "",
         const string &w = "", Link *p = nullptr, Link *s = nullptr)
        : value(n, m, v, w), prev(p), succ(s) { }

    Link *insert(Link *n);
    Link *add(Link *n);
    Link *add_ordered(Link *n);
    Link *erase();
    Link *find(const string &s);
    const Link *find(const string &s) const;

    Link *advance(int n);

    Link *next() const
    {
        return succ;
    }
    Link *previous() const
    {
        return prev;
    }
private:
    Link *prev;
    Link *succ;
};

Link *Link::insert(Link *n)
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

Link *Link::add(Link *n)
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

Link *Link::add_ordered(Link *n)
{
    if (n == nullptr)
    {
        return n;
    }
    if (n->value.name < value.name)
    {
        Link *p = insert(n);
        return p;
    }
    Link *p = this;
    while (n->value.name >= p->value.name)
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

Link *Link::erase()
{
    if (succ != nullptr)
    {
        succ->prev = prev;
    }
    if (prev != nullptr)
    {
        prev->succ = succ;
    }
    Link *ret = succ;
    succ = nullptr;
    prev = nullptr;
    return ret;
}

Link *Link::find(const string &s)
{
    Link *p = this;
    while (p != nullptr)
    {
        if (p->value.name == s)
        {
            return p;
        }
        p = p->succ;
    }
    return nullptr;
}

const Link *Link::find(const string &s) const
{
    const Link *p = this;
    while (p != nullptr)
    {
        if (p->value.name == s)
        {
            return p;
        }
        p = p->succ;
    }
    return nullptr;
}

Link *Link::advance(int n)
{
    Link *p = this;
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

void print_all(Link *p)
{
    while (p != nullptr)
    {
        cout << p->value << endl;
        p = p->next();
    }
}

void delete_all(Link *p)
{
    while (p != nullptr)
    {
        Link *temp = p->next();
        delete p;
        p = temp;
    }
}

Link *extract(Link **l, const string &s)
{
    if ( (*l) == nullptr )
    {
        return nullptr;
    }
    Link *p = (*l)->find(s);
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

int main()
{
    try
    {
        Link *all_gods = new Link("Thor", "Norse", "Pinzgauer", "Hammer");
        all_gods = all_gods->insert(new Link("Odin", "Norse", "Eight-legged horse", ""));
        all_gods = all_gods->insert(new Link("Zeus", "Greek", "", "Lightning"));
        all_gods = all_gods->insert(new Link("Freia", "Norse", "F-transport", "F-weapon"));
        all_gods = all_gods->insert(new Link("Hera", "Greek", "H-transport", "Spear"));
        all_gods = all_gods->insert(new Link("Athena", "Greek", "A-transport", "A-weapon"));
        all_gods = all_gods->insert(new Link("Mars", "Roman", "M-transport", "M-weapon"));
        all_gods = all_gods->insert(new Link("Poseidon", "Greek", "Seahorse", "Trident"));
        all_gods = all_gods->insert(new Link("Ares", "Greek", "A-transport", "A-weapon"));
        all_gods = all_gods->insert(new Link("Vesuvius", "Roman", "V-transport", "Volcano"));
        all_gods = all_gods->insert(new Link("Bacchus", "Roman", "Stretcher", "Wine goblet"));

        print_all(all_gods);
        cout << endl;

        Link *norse_gods = extract(&all_gods, "Odin");
        norse_gods = norse_gods->add_ordered(extract(&all_gods, "Thor"));
        norse_gods = norse_gods->add_ordered(extract(&all_gods, "Freia"));
        cout << "Norse gods:\n";
        print_all(norse_gods);
        cout << endl;

        Link *greek_gods = extract(&all_gods, "Hera");
        greek_gods = greek_gods->add_ordered(extract(&all_gods, "Athena"));
        greek_gods = greek_gods->add_ordered(extract(&all_gods, "Poseidon"));
        greek_gods = greek_gods->add_ordered(extract(&all_gods, "Zeus"));
        greek_gods = greek_gods->add_ordered(extract(&all_gods, "Ares"));
        cout << "Greek gods:\n";
        print_all(greek_gods);
        cout << endl;

        Link *roman_gods = extract(&all_gods, "Mars");
        roman_gods = roman_gods->add_ordered(extract(&all_gods, "Vesuvius"));
        roman_gods = roman_gods->add_ordered(extract(&all_gods, "Bacchus"));
        cout << "Roman gods:\n";
        print_all(roman_gods);
        cout << endl;

        delete_all(norse_gods);
        delete_all(greek_gods);
        delete_all(roman_gods);
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
