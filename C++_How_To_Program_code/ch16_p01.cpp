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

class Item
{
public:
    string name;
    int iid;
    double value;
    Item() : name(), iid(0), value(0) { }
    Item(const string &n, int i, double v) : name(n), iid(i), value(v) { }
};

istream &operator>>(istream &is, Item &it)
{
    string name;
    int iid;
    double value;
    is >> name;
    if (!is)
    {
        return is;
    }
    is >> iid;
    if (!is)
    {
        return is;
    }
    is >> value;
    if (!is)
    {
        return is;
    }
    it = Item(name, iid, value);
    return is;
}

ostream &operator<<(ostream &os, const Item &it)
{
    return os << it.name << '\t' << it.iid << '\t' << it.value;
}

class  Comp_by_name
{
public:
    bool operator()(const Item &a, const Item &b) const
    {
        return a.name < b.name;
    }
};

class Comp_by_iid
{
public:
    bool operator()(const Item &a, const Item &b) const
    {
        return a.iid < b.iid;
    }
};

bool comp_by_value(const Item &a, const Item &b)
{
    return a.value < b.value;
}

class Find_by_name
{
private:
    string name;
public:
    Find_by_name(const string &s) : name(s) { }
    bool operator()(const Item &it) const
    {
        return it.name == name;
    }
};

class Find_by_iid
{
private:
    int iid;
public:
    Find_by_iid(int i) : iid(i) { }
    bool operator()(const Item &it) const
    {
        return it.iid == iid;
    }
};

template<typename iter>
void print(iter first, iter last)
{
    while (first != last)
    {
        cout << *first << '\n';
        ++first;
    }
}

void f1()
{
    cout << "First round: vector\n";
    vector<Item> vi;
    const string ifname = "ch16_p01_in1.txt";

    cout << "fill with ten items from file\n";
    ifstream ifs(ifname.c_str());
    if (!ifs)
    {
        error("can't open " + ifname);
    }
    Item i;
    while (ifs >> i)
    {
        vi.insert(vi.end(), i);
    }
    print(vi.begin(), vi.end());

    cout << "\nsort by name\n";
    sort(vi.begin(), vi.end(), Comp_by_name());
    print(vi.begin(), vi.end());

    cout << "\nsort by iid\n";
    sort(vi.begin(), vi.end(), Comp_by_iid());
    print(vi.begin(), vi.end());

    cout << "\nsort by value, print in decreasing order\n";
    sort(vi.begin(), vi.end(), comp_by_value);
    reverse(vi.begin(), vi.end());
    print(vi.begin(), vi.end());

    cout << "\ninsert two items, sort by value, print in decreasing order\n";
    vi.insert(vi.end(), Item("Horsesh", 99, 12.34));
    vi.insert(vi.end(), Item("C S400", 9988, 499.95));
    sort(vi.begin(), vi.end(), comp_by_value);
    reverse(vi.begin(), vi.end());
    print(vi.begin(), vi.end());

    cout << "\nremove two items identified by name\n";
    vector<Item>::iterator vi_it = find_if(vi.begin(), vi.end(), Find_by_name("GoPro"));
    vi.erase(vi_it);
    vi_it = find_if(vi.begin(), vi.end(), Find_by_name("Xbox"));
    vi.erase(vi_it);
    print(vi.begin(), vi.end());

    cout << "\nremove two tems identified by iid\n";
    vi_it = find_if(vi.begin(), vi.end(), Find_by_iid(14910));
    vi.erase(vi_it);
    vi_it = find_if(vi.begin(), vi.end(), Find_by_iid(754));
    vi.erase(vi_it);
    print(vi.begin(), vi.end());
}

void f2()
{
    cout << "\nSecond round: list\n";
    list<Item> li;
    const string ifname = "ch16_p01_in1.txt";

    cout << "fill with ten items from file\n";
    ifstream ifs(ifname.c_str());
    if (!ifs)
    {
        error("can't open " + ifname);
    }
    Item i;
    while (ifs >> i)
    {
        li.insert(li.end(), i);
    }
    print(li.begin(), li.end());

    cout << "\nsort by name\n";
    li.sort(Comp_by_name());
    print(li.begin(), li.end());

    cout << "\nsort by iid\n";
    li.sort(Comp_by_iid());
    print(li.begin(), li.end());

    cout << "\nsort by value, print in decreasing order\n";
    li.sort(comp_by_value);
    reverse(li.begin(), li.end());
    print(li.begin(), li.end());

    cout << "\ninsert two items, sort by value, print in decreasing order\n";
    li.insert(li.end(), Item("Horsesh", 99, 12.34));
    li.insert(li.end(), Item("C S400", 9988, 499.95));
    li.sort(comp_by_value);
    reverse(li.begin(), li.end());
    print(li.begin(), li.end());

    cout << "\nremove two items identified by name\n";
    list<Item>::iterator li_it = find_if(li.begin(), li.end(), Find_by_name("GoPro"));
    li.erase(li_it);
    li_it = find_if(li.begin(), li.end(), Find_by_name("Xbox"));
    li.erase(li_it);
    print(li.begin(), li.end());

    cout << "\nremove two tems identified by iid\n";
    li_it = find_if(li.begin(), li.end(), Find_by_iid(14910));
    li.erase(li_it);
    li_it = find_if(li.begin(), li.end(), Find_by_iid(754));
    li.erase(li_it);
    print(li.begin(), li.end());
}

void read_pair(map<string, int> &msi)
{
    string s;
    int i;
    cin >> s;
    if (!cin)
    {
        error("Problem reading from cin");
    }
    cin >> i;
    if (!cin)
    {
        error("Problem reading from cin");
    }
    msi[s] = i;
}

template<typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p)
{
    os << setw(12) << left << p.first << '\t' << p.second;
    return os;
}

template<typename T>
class Map_add
{
public:
    T operator()(const T &v, const pair<string, T> &p)
    {
        return v + p.second;
    }
};

void f3()
{
    map<string, int> msi;

    msi["lecture"] = 21;
    msi["university"] = 35;
    msi["education"] = 15;
    msi["school"] = 99;
    msi["kindergarten"] = 105;
    msi["river"] = 5;
    msi["city"] = 10;
    msi["capital"] = 70;
    msi["software"] = 88;
    msi["hardware"] = 43;

    print(msi.begin(), msi.end());

    typedef map<string, int>::const_iterator MI;
    MI p = msi.begin();
    while (p != msi.end())
    {
        p = msi.erase(p);
    }
    cout << "Size of map after deleting: " << msi.size() << '\n';

    cout << "Enter 10 (string,int) pairs, separated by space:\n";
    for (int i = 0; i < 10; ++i)
    {
        read_pair(msi);
    }

    cout << '\n';
    print(msi.begin(), msi.end());

    int msi_sum = 0;
    msi_sum = accumulate(msi.begin(), msi.end(), msi_sum, Map_add<int>());
    cout << "\nSum of all ints in msi: " << msi_sum << '\n';

    map<int, string> mis;

    for (p = msi.begin(); p != msi.end(); ++p)
    {
        mis[p->second] = p->first;
    }

    cout << "\nContents of mis:\n";
    print(mis.begin(), mis.end());
}

template<typename T>
class Less_than
{
private:
    T v;
public:
    Less_than(const T &val) : v(val) { }
    bool operator()(const T &x) const
    {
        return x < v;
    }
};

void f4()
{
    const string fname = "ch16_p01_in2.txt";
    ifstream ifs(fname.c_str());
    if (!ifs)
    {
        error("can't open " + fname);
    }
    vector<double> vd;
    double d;
    while (ifs >> d)
    {
        vd.push_back(d);
    }

    cout << "vd:\n";
    print(vd.begin(), vd.end());

    vector<int> vi(vd.size());
    copy(vd.begin(), vd.end(), vi.begin());

    cout << "\n(vd,vi) pairs:\n";
    for (int i = 0; i < vd.size(); ++i)
    {
        cout << '(' << vd[i] << ',' << vi[i] << ")\n";
    }

    double sum_vd = 0;
    sum_vd = accumulate(vd.begin(), vd.end(), sum_vd);
    cout << "\nSum of the elements of vd: " << sum_vd << '\n';

    int sum_vi = 0;
    sum_vi = accumulate(vi.begin(), vi.end(), sum_vi);
    cout << "Difference of sum_vd and sum_vi: " << sum_vd - sum_vi << '\n';

    reverse(vd.begin(), vd.end());
    cout << "\nvd after reverse:\n";
    print(vd.begin(), vd.end());

    double vd_mean = sum_vd / vd.size();
    cout << "\nMean value of elements in vd: " << vd_mean << '\n';

    vector<double> vd2(count_if(vd.begin(), vd.end(), Less_than<double>(vd_mean)));
    copy_if(vd.begin(), vd.end(), vd2.begin(), Less_than<double>(vd_mean));
    cout << "\nvd2:\n";
    print(vd2.begin(), vd2.end());

    sort(vd.begin(), vd.end());
    cout << "\nAfter sort, vd:\n";
    print(vd.begin(), vd.end());
}

int main(int argc, const char *argv[])
{
    try
    {
        f1();
        f2();
        f3();
        f4();

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
