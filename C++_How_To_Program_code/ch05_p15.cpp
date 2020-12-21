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

class SalaryCalculator
{
private:
    const double COMMISSION_BASE = 250.0;
    const double COMMISSION_RATE = 5.7 / 100.0;
    const double BASE_HOURS = 40.0;
    const double HOURLY_OVERTIME = 1.5;
    const double PIECE_RATE = 10.0;

    double managerRate;
    double hourlyRate;
    double weeklySales;
    double hoursWorked;

    int employeeCode;
    int piecesProduced;
public:
    SalaryCalculator() { }

    void setEmployeeCode()
    {
        int val = 0;

        std::cout << "Enter an employee code (1-4). -1 to quit: ";
        std::cin >> val;
        if (val >= 1 && val <= 4)
        {
            employeeCode = val;
        }
        else
        {
            employeeCode = 0;
        }
    }

    void setPiecesProduced()
    {
        int val = 0;

        std::cout << "Enter pieces produced: ";
        std::cin >> val;
        if (val > 0)
        {
            piecesProduced = val;
        }
        else
        {
            piecesProduced = 0;
        }
    }

    void setWeeklySales()
    {
        double sales = 0.0;

        std::cout << "Enter weekly sales: ";
        std::cin >> sales;
        if (sales > 0)
        {
            weeklySales = sales;
        }
        else
        {
            weeklySales = 0.0;
        }
    }

    void setHoursWorked()
    {
        double hours = 0.0;

        std::cout << "Enter hours worked: ";
        std::cin >> hours;
        if (hours > 0)
        {
            hoursWorked = hours;
        }
        else
        {
            hoursWorked = 0.0;
        }
    }

    void setHourlyRate()
    {
        double rate = 0.0;

        std::cout << "Enter hourly rate: ";
        std::cin >> rate;
        if (rate > 0)
        {
            hourlyRate = rate;
        }
        else
        {
            hourlyRate = 0.0;
        }
    }

    void setManagerRate()
    {
        double rate = 0.0;

        std::cout << "Enter manager weekly salary: ";
        std::cin >> rate;
        if (rate > 0)
        {
            managerRate = rate;
        }
        else
        {
            managerRate = 0.0;
        }
    }

    double getManagerRate() const
    {
        return managerRate;
    }
    double getHourlyRate() const
    {
        return hourlyRate;
    }
    double getWeeklySales() const
    {
        return weeklySales;
    }
    double getHoursWorked() const
    {
        return hoursWorked;
    }
    int getEmployeeCode() const
    {
        return employeeCode;
    }
    int getPiecesProduced() const
    {
        return piecesProduced;
    }

    double getSalary()
    {
        double dValue = 0.0;

        switch (getEmployeeCode())
        {
        case 1:
            setManagerRate();
            dValue = getManagerRate();
            break;
        case 2:
            setHourlyRate();
            setHoursWorked();
            dValue = getHourlyRate();
            if (getHoursWorked() > BASE_HOURS)
            {
                dValue *= BASE_HOURS;
                dValue += ((getHoursWorked() - BASE_HOURS) * (getHourlyRate() * HOURLY_OVERTIME));
            }
            else
            {
                dValue *= getHoursWorked();
            }
            break;
        case 3:
            setWeeklySales();
            dValue = (COMMISSION_BASE + (getWeeklySales() * COMMISSION_RATE));
            break;
        case 4:
            setPiecesProduced();
            dValue = (getPiecesProduced() * PIECE_RATE);
            break;
        default:
            break;
        }
        return dValue;
    }

    bool run()
    {
        reset();
        double dValue = 0.0;
        setEmployeeCode();
        if ((dValue = getSalary()) > 0.0)
        {
            switch (getEmployeeCode())
            {
            case 1:
                cout << "Manager Salary: $" << dValue << endl;
                break;
            case 2:
                cout << "Hourly Worker Salary: $" << dValue << endl;
                break;
            case 3:
                cout << "Commission Worker Salary: $" << dValue << endl;
                break;
            case 4:
                cout << "Piece Worker Salary: $" << dValue << endl;
                break;
            default:
                break;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    void reset()
    {
        managerRate = 0.0;
        hourlyRate = 0.0;
        weeklySales = 0.0;
        hoursWorked = 0.0;
        employeeCode = 0;
        piecesProduced = 0;
    }
};

int main(int argc, const char *argv[])
{
    try
    {
        cout << fixed << setprecision(2);
        SalaryCalculator sc;

        while (sc.run())
            ;

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
