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

class List;

class Link
{
public:
    string value;

    Link(const string &v = "", Link *s = nullptr) : value(v), succ(s) { }

    Link *insert(List &l, Link *n);
    Link *add(List &l, Link *n);
    Link *erase(List &l);
    Link *find(const List &l, const string &s);
    const Link *find(const List &l, const string &s) const;

    Link *advance(int n);

    Link *next() const
    {
        return succ;
    }
private:
    Link *succ;
};

class List
{
public:
    List() : first_link(nullptr) { }
    List(Link *l) : first_link(l) { }
    Link *first_link;
};

Link *Link::insert(List &l, Link *n)
{
    if (n == nullptr)
    {
        return n;
    }
    n->succ = this;
    if (l.first_link == this)
    {
        l.first_link = n;
        return n;
    }
    Link *p = l.first_link;
    while (p->succ != this)
    {
        p = p->succ;
    }
    p->succ = n;
    return n;
}

Link *Link::add(List &l, Link *n)
{
    if (n == nullptr)
    {
        return n;
    }
    n->succ = succ;
    succ = n;
    return n;
}

Link *Link::erase(List &l)
{
    if (l.first_link == this)
    {
        l.first_link = succ;
    }
    else
    {
        Link *p = l.first_link;
        while (p->succ != this)
        {
            p = p->succ;
        }
        p->succ = succ;
    }
    Link *ret = succ;
    succ = nullptr;
    return ret;
}

Link *Link::find(const List &l, const string &s)
{
    Link *p = l.first_link;
    while (p != nullptr)
    {
        if (p->value == s)
        {
            return p;
        }
        p = p->succ;
    }
    return nullptr;
}

const Link *Link::find(const List &l, const string &s) const
{
    const Link *p = l.first_link;
    while (p != nullptr)
    {
        if (p->value == s)
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
    if (0 <= n)
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
    else
    {
        error("must advance by a number >= 0");
    }
    return p;
}

void print_all(const List &l)
{
    cout << "{ ";
    Link *p = l.first_link;
    while (p != nullptr)
    {
        cout << p->value;
        p = p->next();
        if (p != nullptr)
        {
            cout << ", ";
        }
    }
    cout << " }";
}

void delete_all(List &l)
{
    Link *p = l.first_link;
    while (p != nullptr)
    {
        Link *temp = p->next();
        delete p;
        p = temp;
    }
    l.first_link = nullptr;
}

int main()
{
    try
    {
        Link *norse_gods = new Link("Thor");
        List n_gods(norse_gods);
        norse_gods = norse_gods->insert(n_gods, new Link("Odin"));
        norse_gods = norse_gods->insert(n_gods, new Link("Zeus"));
        norse_gods = norse_gods->insert(n_gods, new Link("Freia"));

        Link *greek_gods = new Link("Hera");
        List g_gods(greek_gods);
        greek_gods = greek_gods->insert(g_gods, new Link("Athena"));
        greek_gods = greek_gods->insert(g_gods, new Link("Mars"));
        greek_gods = greek_gods->insert(g_gods, new Link("Poseidon"));

        print_all(n_gods);
        cout << "\n";

        print_all(g_gods);
        cout << "\n";

        Link *p = greek_gods->find(g_gods, "Mars");
        if (p != nullptr)
        {
            p->value = "Ares";
        }

        Link *p2 = norse_gods->find(n_gods, "Zeus");
        if (p2 != nullptr)
        {
            if (p2 == norse_gods)
            {
                norse_gods = p2->next();
            }
            p2->erase(n_gods);
            greek_gods->add(g_gods, p2);
            greek_gods = g_gods.first_link;
        }

        print_all(n_gods);
        cout << "\n";

        print_all(g_gods);
        cout << "\n";

        delete_all(n_gods);
        delete_all(g_gods);
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
