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
using std::fstream;
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

class Day
{
public:
    explicit Day(int d) : val(d) { }
    int val;
};

ostream &operator<<(ostream &os, const Day &d)
{
    os << d.val;
    return os;
}

class Month
{
public:
    explicit Month(int m) : val(m) { }
    int val;
};

ostream &operator<<(ostream &os, const Month &m)
{
    os << m.val;
    return os;
}

class Year
{
public:
    explicit Year(int y) : val(y) { }
    int val;
};

ostream &operator<<(ostream &os, const Year &y)
{
    os << y.val;
    return os;
}

class Date
{
private:
    Day d;
    Month m;
    Year y;
public:
    Date() : d(1), m(1), y(1970) { }
    Date(const Day &day, const Month &month, const Year &year) : d(day), m(month), y(year) { }
    Date(const Date &r) : d(r.d), m(r.m), y(r.y) { }
    const Day &day() const
    {
        return d;
    }
    const Month &month() const
    {
        return m;
    }
    const Year &year() const
    {
        return y;
    }
};

ostream &operator<<(ostream &os, const Date &date)
{
    os << date.day() << '.' << date.month() << '.' << date.year();
    return os;
}

istream &operator>>(istream &is, Date &date)
{
    int d;
    int m;
    int y;
    char ch1;
    char ch2;
    is >> d;
    if (!is)
    {
        return is;
    }
    is >> ch1;
    if (!is)
    {
        return is;
    }
    is >> m;
    if (!is)
    {
        return is;
    }
    is >> ch2;
    if (!is)
    {
        return is;
    }
    is >> y;
    if (!is)
    {
        return is;
    }
    if (ch1 != '.' || ch2 != '.')
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    date = Date(Day(d), Month(m), Year(y));
    return is;
}

class Purchase
{
private:
    string n;
    double up;
    int c;
public:
    Purchase() : n(""), up(0.0), c(0) { }
    Purchase(const string &name, double unit_price, int count) : n(name), up(unit_price), c(count) { }
    const string &name() const
    {
        return n;
    }
    double unit_price() const
    {
        return up;
    }
    int count() const
    {
        return c;
    }
};

ostream &operator<<(ostream &os, const Purchase &p)
{
    os << p.name() << " | " << p.unit_price() << " | " << p.count();
    return os;
}

istream &operator>>(istream &is, Purchase &p)
{
    string name;
    getline(is, name, '|');
    if (!is)
    {
        return is;
    }
    if (name.size() == 0)
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    name.pop_back();
    double unit_price;
    char ch2;
    int count;
    is >> unit_price;
    if (!is)
    {
        return is;
    }
    is >> ch2;
    if (!is)
    {
        return is;
    }
    is >> count;
    if (!is)
    {
        return is;
    }
    if (ch2 != '|')
    {
        is.clear(std::ios_base::failbit);
        return is;
    }
    p = Purchase(name, unit_price, count);
    return is;
}

class Order
{
private:
    string n;
    string addr;
    Date d;
    vector<Purchase> vp;
public:
    Order() : n(), addr(), d(), vp() { }
    Order(const string &name, const string &address, const Date &date, const vector<Purchase> &vpurchases)
        : n(name), addr(address), d(date), vp(vpurchases) { }
    const string &name() const
    {
        return n;
    }
    const string &address() const
    {
        return addr;
    }
    const Date &date() const
    {
        return d;
    }
    int n_purchases() const
    {
        return vp.size();
    }
    const Purchase &purchase(int i) const
    {
        return vp[i];
    }
};

ostream &operator<<(ostream &os, const Order &o)
{
    os << o.name() << '\n' << o.address() << '\n' << o.date() << '\n';
    for (int i = 0; i < o.n_purchases(); ++i)
    {
        os << o.purchase(i) << '\n';
    }
    return os;
}

istream &operator>>(istream &is, Order &o)
{
    char ch;
    is >> ch;
    if (!is)
    {
        return is;
    }
    is.unget();
    string name;
    getline(is, name, '\n');
    if (!is)
    {
        return is;
    }
    string address;
    getline(is, address, '\n');
    if (!is)
    {
        return is;
    }
    Date date;
    is >> date;
    if (!is)
    {
        return is;
    }
    is.ignore();
    string line;
    vector<Purchase> purchases;
    while (getline(is, line, '\n') && line != "")
    {
        Purchase purchase;
        istringstream iss(line);
        iss >> purchase;
        purchases.push_back(purchase);
    }
    is.clear();
    o = Order(name, address, date, purchases);
    return is;
}

template<typename T>
class Sort_by_name
{
public:
    bool operator()(const T &a, const T &b) const
    {
        return a.name() < b.name();
    }
};

template<typename T>
class Sort_by_address
{
public:
    bool operator()(const T &a, const T &b) const
    {
        return a.address() < b.address();
    }
};

template<typename Cont>
void read_orders_from_file(Cont &c, const string &fname)
{
    ifstream ifs(fname.c_str());
    if (!ifs)
    {
        error("can't open file " + fname);
    }
    Order o;
    while (ifs >> o)
    {
        c.push_back(o);
    }
}

template<typename Iter>
void write_orders_to_file(Iter first, Iter last, const string &fname)
{
    ofstream ofs(fname.c_str());
    if (!ofs)
    {
        error("can't open file " + fname);
    }
    while (first != last)
    {
        ofs << *first << '\n';
        ++first;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        const string ifname1 = "ch15_p05_in1.txt";
        vector<Order> vo;
        read_orders_from_file(vo, ifname1);

        sort(vo.begin(), vo.end(), Sort_by_name<Order>());
        for (int i = 0; i < vo.size(); ++i)
        {
            cout << vo[i] << '\n';
        }

        const string ofname1 = "ch15_p05_out1.txt";
        write_orders_to_file(vo.begin(), vo.end(), ofname1);

        const string ifname2 = "ch15_p05_in2.txt";
        list<Order> lo;
        read_orders_from_file(lo, ifname2);

        cout << "\n";
        lo.sort(Sort_by_address<Order>());
        typedef list<Order>::iterator Liter;
        for (Liter it = lo.begin(); it != lo.end(); ++it)
        {
            cout << *it << '\n';
        }

        const string ofname2 = "ch15_p05_out2.txt";
        write_orders_to_file(lo.begin(), lo.end(), ofname2);

        lo.sort(Sort_by_name<Order>());
        vector<Order> vo_merge(vo.size() + lo.size());
        merge(vo.begin(), vo.end(), lo.begin(), lo.end(), vo_merge.begin(), Sort_by_name<Order>());
        const string ofname3 = "ch15_p05_out3.txt";
        write_orders_to_file(vo_merge.begin(), vo_merge.end(), ofname3);

        set<Order, Sort_by_name<Order>> so;
        typedef vector<Order>::iterator Viter;
        for (Viter it = vo_merge.begin(); it != vo_merge.end(); ++it)
        {
            so.insert(*it);
        }

        cout << "\n";
        double val_t = 0;
        double val_s;
        for (set<Order>::iterator it = so.begin(); it != so.end(); ++it)
        {
            cout << *it << '\n';
            val_s = 0;
            for (int i = 0; i < (*it).n_purchases(); ++i)
            {
                val_s += (*it).purchase(i).count() * (*it).purchase(i).unit_price();
                val_t += (*it).purchase(i).count() * (*it).purchase(i).unit_price();
            }
            cout << "Total of the order: " << val_s << "\n";
            cout << "Running total so far: " << val_t << "\n\n";
        }

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
