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

class element
{
public:
    element(int k, int new_height) : key(k), next(new_height + 1) { }
    int key;
    vector<element *> next;
};

class skip_list
{
public:
    skip_list();
    element *find(int x);
    void insert(int x);
    void remove(int x);
    void print();
    void debug_print();
    int get_height()
    {
        return height;
    }
private:
    const int max_height = 128;
    const int infty = numeric_limits<int>::max();
    element head;
    element tail;
    int height;
    mt19937 engine;
};

skip_list::skip_list()
    : head(infty, max_height), tail(infty, max_height), height(0), engine( unsigned ( std::chrono::system_clock::now().time_since_epoch().count() ) )
{
    for (int i = 0; i < head.next.size(); ++i)
    {
        head.next[i] = &tail;
    }
}

element *skip_list::find(int x)
{
    element *p = &head;

    for (int i = height; i >= 0; --i)
    {
        while (p->next[i]->key < x)
        {
            p = p->next[i];
        }
    }

    p = p->next[0];
    if (p->key == x) { return p; }
    else { return nullptr; }
}

void skip_list::insert(int x)
{
    vector<element *> update(max_height + 1);
    element *p = &head;

    for (int i = height; i >= 0; --i)
    {
        while (p->next[i]->key < x)
        {
            p = p->next[i];
        }
        update[i] = p;
    }
    p = p->next[0];

    if (p->key == x) { return; }

    int new_height = nrand_two(0, max_height + 1, engine);
    if (new_height > height)
    {
        for (int i = height + 1; i <= new_height; ++i)
        {
            update[i] = &head;
        }
        height = new_height;
    }

    p = new element(x, new_height);

    for (int i = 0; i <= new_height; ++i)
    {
        p->next[i] = update[i]->next[i];
        update[i]->next[i] = p;
    }
}

void skip_list::remove(int x)
{
    vector<element *> update(max_height + 1);
    element *p = &head;
    for (int i = height; i >= 0; --i)
    {
        while (p->next[i]->key < x)
        {
            p = p->next[i];
        }
        update[i] = p;
    }
    p = p->next[0];

    if (p->key == x)
    {
        for (int i = 0; i < p->next.size(); ++i)
        {
            update[i]->next[i] = p->next[i];
        }
        while (height >= 1 && head.next[height] == &tail)
        {
            --height;
        }
        delete p;
    }
}

void skip_list::print()
{
    element *p = head.next[0];
    while (p != &tail)
    {
        cout << setw(5) << p->key;
        p = p->next[0];
    }
    cout << endl;
}

void skip_list::debug_print()
{
    for (int i = 0; i <= height; ++i)
    {
        element *p = head.next[i];
        cout << setw(3) << i << ": ";
        while (p != &tail)
        {
            cout << setw(3) << p->key << " ";
            p = p->next[i];
        }
        cout << endl;
    }
}

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 engine(seed);
    try
    {
            skip_list sl;
            for (int i = 0; i < 30; ++i)
            {
                sl.insert(nrand_two(0, 100, engine));
            }
            sl.debug_print();
            cout << "Enter value to remove: ";
            int x;
            cin >> x;
            element *p = sl.find(x);
            if (p != nullptr)
            {
                cout << "p->key = " << p->key << endl;
                sl.remove(x);
                sl.debug_print();
            }
            else
            {
                cout << x << " is not found\n";
            }
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
