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

class Sales
{
public:
    enum { MONTHS = 12 };
    class bad_index : public std::logic_error
    {
    private:
        int bi;
    public:
        explicit bad_index(int ix, const std::string &s = "Index error in Sales object\n");
        int bi_val() const
        {
            return bi;
        }
        virtual ~bad_index() {}
    };
    explicit Sales(int yy = 0);
    Sales(int yy, const double *gr, int n);
    virtual ~Sales() { }
    int Year() const
    {
        return year;
    }
    virtual double operator[](int i) const;
    virtual double &operator[](int i);
private:
    double gross[MONTHS];
    int year;
};

class LabeledSales : public Sales
{
public:
    class nbad_index : public Sales::bad_index
    {
    private:
        std::string lbl;
    public:
        nbad_index(const std::string &lb, int ix, const std::string &s = "Index error in LabeledSales object\n");
        const std::string &label_val() const
        {
            return lbl;
        }
        virtual ~nbad_index() {}
    };
    explicit LabeledSales(const std::string &lb = "none", int yy = 0);
    LabeledSales(const std::string &lb, int yy, const double *gr, int n);
    virtual ~LabeledSales() { }
    const std::string &Label() const
    {
        return label;
    }
    virtual double operator[](int i) const;
    virtual double &operator[](int i);
private:
    std::string label;
};


Sales::bad_index::bad_index(int ix, const string &s) : std::logic_error(s), bi(ix)
{
}
Sales::Sales(int yy)
{
    year = yy;
    for (int i = 0; i < MONTHS; ++i)
    {
        gross[i] = 0;
    }
}

Sales::Sales(int yy, const double *gr, int n)
{
    year = yy;
    int lim = (n < MONTHS) ? n : MONTHS;
    int i;
    for (i = 0; i < lim; ++i)
    {
        gross[i] = gr[i];
    }
    for (; i < MONTHS; ++i)
    {
        gross[i] = 0;
    }
}
double Sales::operator[](int i) const
{
    if (i < 0 || i >= MONTHS)
    {
        throw bad_index(i);
    }
    return gross[i];
}

double &Sales::operator[](int i)
{
    if (i < 0 || i >= MONTHS)
    {
        throw bad_index(i);
    }
    return gross[i];
}

LabeledSales::nbad_index::nbad_index(const string &lb, int ix, const string &s) : Sales::bad_index(ix, s)
{
    lbl = lb;
}
LabeledSales::LabeledSales(const string &lb, int yy) : Sales(yy)
{
    label = lb;
}
LabeledSales::LabeledSales(const string &lb, int yy, const double *gr, int n) : Sales(yy, gr, n)
{
    label = lb;
}
double LabeledSales::operator[](int i) const
{
    if (i < 0 || i >= MONTHS)
    {
        throw nbad_index(Label(), i);
    }
    return Sales::operator[](i);
}
double &LabeledSales::operator[](int i)
{
    if (i < 0 || i >= MONTHS)
    {
        throw nbad_index(Label(), i);
    }
    return Sales::operator[](i);
}

int main(int argc, const char *argv[])
{
    try
    {

        double vals1[12] =
        {
            1220, 1100, 1122, 2212, 1232, 2334,
            2884, 2393, 3302, 2922, 3002, 3544
        };

        double vals2[12] =
        {
            12, 11, 22, 21, 32, 34,
            28, 29, 33, 29, 32, 35
        };

        Sales sales1(2011, vals1, 12);
        LabeledSales sales2("Blogstar", 2012, vals2, 12);

        cout << "First try block:\n";
        try
        {
            int i;
            cout << "Year = " << sales1.Year() << endl;
            for (i = 0; i < 12; ++i)
            {

                cout << sales1[i] << ' ';
                if (i % 6 == 5)
                {
                    cout << endl;
                }
            }
            cout << "Year = " << sales2.Year() << endl;
            cout << "Label = " << sales2.Label() << endl;
            for (i = 0; i <= 12; ++i)
            {

                cout << sales2[i] << ' ';
                if (i % 6 == 5)
                {
                    cout << endl;
                }
            }
            cout << "End of try block 1.\n";
        }
        catch (LabeledSales::nbad_index &bad)
        {
            cout << bad.what();
            cout << "Company: " << bad.label_val() << endl;
            cout << "bad index: " << bad.bi_val() << endl;
        }
        catch (Sales::bad_index &bad)
        {
            cout << bad.what();
            cout << "bad index: " << bad.bi_val() << endl;
        }
        cout << "\nNext try block:\n";
        try
        {
            sales2[2] = 37.5;
            sales1[20] = 23345;
            cout << "End of try block 2.\n";
        }
        catch (LabeledSales::nbad_index &bad)
        {
            cout << bad.what();
            cout << "Company: " << bad.label_val() << endl;
            cout << "bad index: " << bad.bi_val() << endl;
        }
        catch (Sales::bad_index &bad)
        {
            cout << bad.what();
            cout << "bad index: " << bad.bi_val() << endl;
        }
        cout << "Done.\n";

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
