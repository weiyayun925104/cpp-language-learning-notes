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

class Time
{
private:
    int hour;
    int minute;
    int second;
public:
    Time();
    Time(int, int, int);

    void setTime(int, int, int);
    void setHour(int);
    void setMinute(int);
    void setSecond(int);

    int getHour();
    int getMinute();
    int getSecond();

    void printUniversal();
    void printStandard();
};

Time::Time()
{
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);

    localTime = localtime(&currentTime);

    hour = localTime->tm_hour;
    minute = localTime->tm_min;
    second = localTime->tm_sec;
}

Time::Time(int hour, int minute, int second)
{
    setTime(hour, minute, second);
}

void Time::setTime(int h, int m, int s)
{
    setHour(h);
    setMinute(m);
    setSecond(s);
}

void Time::setHour(int h)
{
    if (h >= 0 && h <= 23)
    {
        hour = h;
    }
    else
    {
        throw std::invalid_argument("hour must be 0-23");
    }
}
void Time::setMinute(int m)
{
    if (m >= 0 && m <= 59)
    {
        minute = m;
    }
    else
    {
        throw std::invalid_argument("minute must be 0-59");
    }
}
void Time::setSecond(int s)
{
    if (s >= 0 && s <= 59)
    {
        second = s;
    }
    else
    {
        throw std::invalid_argument("second must be 0-59");
    }
}
int Time::getHour()
{
    return hour;
}
int Time::getMinute()
{
    return minute;
}
int Time::getSecond()
{
    return second;
}
void Time::printUniversal()
{
    std::cout << std::setfill('0') << std::setw(2) << getHour() << ":"
              << std::setw(2) << getMinute() << ":" << std::setw(2) << getSecond();
}
void Time::printStandard()
{
    std::cout << ((getHour() == 0 || getHour() == 12) ? 12 : getHour() % 12)
              << ":" << std::setfill('0') << std::setw(2) << getMinute() << ":"
              << std::setw(2) << getSecond() << (hour < 12 ? " AM" : " PM");
}

int main(int argc, const char *argv[])
{
    try
    {
        Time time1;
        Time time2(12, 12, 12);

        std::cout << "time1: ";
        time1.printUniversal();
        std::cout << std::endl;
        time1.printStandard();
        std::cout << std::endl;

        std::cout << "time2: ";
        time2.printUniversal();
        std::cout << std::endl;
        time2.printStandard();
        std::cout << std::endl;

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
