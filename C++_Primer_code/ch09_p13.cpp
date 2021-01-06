#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
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
#include <initializer_list>
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
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
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
using std::begin;
using std::end;
using std::initializer_list;
using std::invalid_argument;

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

static const vector<string> MONALL { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
    "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

class Date
{
public:
    Date() = default;
    Date(const string &);
    Date &print_date();
private:
    bool isleap(unsigned);
    unsigned year = 1900;
    unsigned month = 1;
    unsigned day = 1;
};

Date::Date(const string &date) : Date()
{
    unsigned year_temp = 0, month_temp = 0, day_temp = 0;
    if(date.empty())
        throw invalid_argument("Argument shouldn't be empty");
    vector<string> split;
    string str;
    for(const auto &c : date)
    {
        if(!(isspace(c) || c == ',' || c == '-' || c == '/' || c == '.'))
        {
            str.push_back(c);
        }
        else
        {
            if(!str.empty())
            {
                split.push_back(str);
                str.clear();
            }
        }
    }
    if(!str.empty())
    {
        split.push_back(str);
        str.clear();
    }
    if(split.size() != 3)
        throw invalid_argument("Not a valid date.");
    if(isalpha(split[0][0]))
    {
        for(auto &c : split[0])
        {
            c = toupper(c);
        }
        for(decltype(MONALL.size()) m = 0; m < MONALL.size(); ++m)
        {
            if(MONALL[m].find(split[0]) == 0)
            {
                if(split[0].size() >= 3 && split[0].size() <= MONALL[m].size())
                {
                    month_temp = m + 1;
                    break;
                }
                else
                    throw invalid_argument("Not a valid month.");
            }
            if(m == (MONALL.size() - 1))
                throw invalid_argument("Not a valid month.");
        }
    }
    else if(isdigit(split[0][0]))
    {
        month_temp = stoi(split[0]);
        if(month_temp < 1 || month_temp > 12)
            throw invalid_argument("Not a valid month.");
    }
    else
        throw invalid_argument("Input is not a month.");
    day_temp = stoi(split[1]);
    year_temp = stoi(split[2]);
    switch(month_temp)
    {
    case 2:
        if(isleap(year_temp))
        {
            if(day_temp > 29)
                throw invalid_argument("Date is invalid for leap year.");
        }
        else
        {
            if(day_temp > 28)
                throw invalid_argument("Date is invalid for non-leap year.");
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if(day_temp > 31)
            throw invalid_argument("Date is invalid.");
        break;
    case 4:
    case 6:
    case 9:
    case 11:
    default:
        if(day_temp > 30)
            throw invalid_argument("Date is out of range.");
        break;
    }
    year = year_temp;
    month = month_temp;
    day = day_temp;
}
Date &Date::print_date()
{
    cout << year << "-" << month << "-" << day << endl;
    return *this;
}
inline bool Date::isleap(unsigned y)
{
    return ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0));
}

int main(int argc, const char *argv[])
{
    try
    {
        string d;
        while(getline(cin, d))
        {
            try
            {
                Date date(d);
                date.print_date();
            }
            catch(invalid_argument &inv_arg)
            {
                cerr << inv_arg.what()
                     << "\nTry again? Enter y or n" << endl;
                char c;
                cin >> c;
                if(!cin || c == 'n')
                    break;
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
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
