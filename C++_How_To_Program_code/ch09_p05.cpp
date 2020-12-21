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
using std::left;
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

namespace Chrono
{
    class Date
    {
    public:
        enum Month
        {
            jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
        };

        Date(int y, Month m, int d);
        Date();

        int day() const
        {
            return d;
        }
        Month month() const
        {
            return m;
        }
        int year() const
        {
            return y;
        }

        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
    private:
        int y;
        Month m;
        int d;
    };

    bool is_date(int y, Date::Month m, int d);
    bool leapyear(int y);

    int day_in_year(const Date &d);
    void split_date(int day_of_year, int year, int *month, int *day);
    int n_leapyears(int y);
    long int days_linear(const Date &d);

    enum Day
    {
        sunday, monday, tuesday, wednesday, thursday, friday, saturday
    };
    Day day_of_week(const Date &d);
    ostream &operator<<(ostream &os, Day d);

    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);

    ostream &operator<<(ostream &os, const Date &d);
    istream &operator>>(istream &is, Date &dd);
}

namespace Chrono
{
    Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd)
    {
        if (!is_date(yy, mm, dd))
        {
            error("invalid date");
        }
    }

    const Date &default_date()
    {
        static const Date dd(2001, Date::jan, 1);
        return dd;
    }

    Date::Date() : y(default_date().year()), m(default_date().month()), d(default_date().day()) { }

    int nmonth(Date::Month m)
    {
        switch (m)
        {
        case Date::jan:
            return 0;
        case Date::feb:
            return 31;
        case Date::mar:
            return 31 + 28;
        case Date::apr:
            return 31 + 28 + 31;
        case Date::may:
            return 31 + 28 + 31 + 30;
        case Date::jun:
            return 31 + 28 + 31 + 30 + 31;
        case Date::jul:
            return 31 + 28 + 31 + 30 + 31 + 30;
        case Date::aug:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31;
        case Date::sep:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
        case Date::oct:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        case Date::nov:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
        case Date::dec:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
        }
    }

    void Date::add_day(int n)
    {
        int doy = nmonth(dec);
        doy += 31;
        if (leapyear(y - 1))
        {
            ++doy;
        }
        int diy = nmonth(dec);
        diy += 31;
        if (leapyear(y))
        {
            ++diy;
        }
        int day_of_year = day_in_year(*this);
        day_of_year += n;
        if (day_of_year >= 1 && day_of_year <= diy)
        {
            int res_month, res_day;
            split_date(day_of_year, y, &res_month, &res_day);
            m = Month(res_month);
            d = res_day;
        }
        else if (day_of_year > diy && day_of_year <= (diy + 365))
        {
            day_of_year -= diy;
            int res_month, res_day;
            split_date(day_of_year, y + 1, &res_month, &res_day);
            y++;
            m = Month(res_month);
            d = res_day;
        }
        else if (day_of_year < 1 && (day_of_year + doy) >= 1)
        {
            day_of_year += doy;
            int res_month, res_day;
            split_date(day_of_year, y - 1, &res_month, &res_day);
            y--;
            m = Month(res_month);
            d = res_day;
        }
    }

    void Date::add_month(int n)
    {
        int month = m + n;
        bool day_large = false;
        if (d > 28)
        {
            day_large = true;
            add_day(-3);
        }
        if (month >= jan && month <= dec)
        {
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
        else if (month > dec && month <= dec + 12)
        {
            month -= dec;
            y++;
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
        else if(month < jan && month + 12 >= 1)
        {
            month += 12;
            y--;
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
    }

    void Date::add_year(int n)
    {
        if (m == feb && d == 29 && !leapyear(y + n))
        {
            m = mar;
            d = 1;
        }
        y += n;
    }

    bool is_date(int y, Date::Month m, int d)
    {
        if (d <= 0)
        {
            return false;
        }

        int days_in_month = 31;

        switch (m)
        {
        case Date::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Date::apr:
        case Date::jun:
        case Date::sep:
        case Date::nov:
            days_in_month = 30;
            break;
        }

        if (days_in_month < d)
        {
            return false;
        }

        return true;
    }

    bool leapyear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }

    ostream &operator<<(ostream &os, const Date &d)
    {
        return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
    }

    istream &operator>>(istream &is, Date &dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is)
        {
            return is;
        }
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
        {
            is.clear(std::ios_base::failbit);
            return is;
        }
        dd = Date(y, Date::Month(m), d);
        return is;
    }

    ostream &operator<<(ostream &os, Day d)
    {
        switch (d)
        {
        case sunday:
            os << "Sunday";
            break;
        case monday:
            os << "Monday";
            break;
        case tuesday:
            os << "Tuesday";
            break;
        case wednesday:
            os << "Wednesday";
            break;
        case thursday:
            os << "Thursday";
            break;
        case friday:
            os << "Friday";
            break;
        case saturday:
            os << "Saturday";
            break;
        }
        return os;
    }

    const Date first_date = Date(1970, Date::jan, 1);
    const Day first_day = thursday;

    Day day_of_week(const Date &d)
    {
        if (d.year() < first_date.year())
        {
            error("day_of_week: works only for 1970 and later");
        }
        int dlin = days_linear(d);
        return Day((first_day + dlin) % 7);
    }

    Date next_Sunday(const Date &d)
    {
        Date nsd = d;
        Day day = day_of_week(d);
        nsd.add_day(7 - day);
        return nsd;
    }

    int day_in_year(const Date &d)
    {
        int diy = nmonth(d.month());
        diy += d.day();
        if (leapyear(d.year()) && d.month() > Date::feb)
        {
            ++diy;
        }
        return diy;
    }

    void split_date(int day_of_year, int year, int *month, int *day)
    {
        int i;
        bool found = false;

        for (i = 1; i <= 12 && !found; i++)
        {
            switch(i)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day_of_year <= 31)
                {
                    found = true;
                }
                else
                {
                    day_of_year -= 31;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day_of_year <= 30)
                {
                    found = true;
                }
                else
                {
                    day_of_year -= 30;
                }
                break;
            case 2:
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                {
                    if (day_of_year <= 29)
                    {
                        found = true;
                    }
                    else
                    {
                        day_of_year -= 29;
                    }
                }
                else
                {
                    if (day_of_year <= 28)
                    {
                        found = true;
                    }
                    else
                    {
                        day_of_year -= 28;
                    }
                }
                break;
            default :
                break;
            }
        }
        *month = i - 1;
        *day = day_of_year;
    }

    int n_leapyears(int y)
    {
        int nl = 0;
        for (int i = 1970; i < y; ++i)
        {
            if (leapyear(i))
            {
                ++nl;
            }
        }
        return nl;
    }

    long int days_linear(const Date &d)
    {
        if (d.year() < first_date.year())
        {
            error("days_linear: year must be 1970 or later");
        }
        int y = d.year() - first_date.year();
        return y * 365 + n_leapyears(d.year()) + day_in_year(d) - 1;
    }

    Date next_workday(const Date &d)
    {
        Date nwd = d;
        Day day = day_of_week(d);
        switch (day)
        {
        case sunday:
        case monday:
        case tuesday:
        case wednesday:
        case thursday:
            nwd.add_day(1);
            break;
        case saturday:
            nwd.add_day(2);
            break;
        case friday:
            nwd.add_day(3);
            break;
        }
        return nwd;
    }
}

using Chrono::Date;

int main(int argc, const char *argv[])
{
    try
    {
        Date dd(2015, Date::Month(11), 30);

        for (int i = 0; i < 365; ++i)
        {
            dd.add_day(1);

            std::cout << dd << std::endl;
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
