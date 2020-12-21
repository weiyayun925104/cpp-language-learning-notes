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

class CreditLimits
{
private:
    int accountNumber;
    double beginningBalance;
    double totalMonthCharges;
    double totalMonthCredit;
    double creditLimit;
public:
    CreditLimits() : accountNumber(0), beginningBalance(0.0), totalMonthCharges(0.0),
        totalMonthCredit(0.0), creditLimit(0.0) { }

    void setAccountNumber()
    {
        int accNo = 0;
        std::cout << "Enter account number (or -1 to quit): ";
        std::cin >> accNo;
        if (accNo > 0)
        {
            accountNumber = accNo;
        }
        else
        {
            accountNumber = 0;
        }
    }
    void setBeginningBalance()
    {
        double startBalance = 0.0;

        std::cout << "Enter beginning balance: ";
        std::cin >> startBalance;
        if (startBalance > 0)
        {
            beginningBalance = startBalance;
        }
        else
        {
            beginningBalance = 0.0;
        }
    }
    void setTotalMonthCharges()
    {
        double totalCharges = 0.0;

        std::cout << "Enter total charges: ";
        std::cin >> totalCharges;
        if (totalCharges > 0)
        {
            totalMonthCharges = totalCharges;
        }
        else
        {
            totalMonthCharges = 0.0;
        }
    }
    void setTotalMonthCredit()
    {
        double totalCredit = 0.0;

        std::cout << "Enter total credits: ";
        std::cin >> totalCredit;
        if (totalCredit > 0)
        {
            totalMonthCredit = totalCredit;
        }
        else
        {
            totalMonthCredit = 0.0;
        }
    }
    void setCreditLimit()
    {
        double limit = 0.0;

        std::cout << "Enter credit limit: ";
        std::cin >> limit;
        if (limit > 0)
        {
            creditLimit = limit;
        }
        else
        {
            creditLimit = 0.0;
        }
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    double getBeginningBalance() const
    {
        return beginningBalance;
    }

    double getTotalMonthCharges() const
    {
        return totalMonthCharges;
    }

    double getTotalMonthCredit() const
    {
        return totalMonthCredit;
    }

    double getCreditLimit() const
    {
        return creditLimit;
    }

    double getNewBalance() const
    {
        return ( (getBeginningBalance() + getTotalMonthCharges()) - getTotalMonthCredit() );
    }

    bool isCreditLimitExceeded() const
    {
        return (getCreditLimit() - getNewBalance() < 0) ? true : false;
    }
    void printInfo() const
    {
        std::cout << "Account: " << getAccountNumber() << std::endl;
        std::cout << "Credit limit: " << getCreditLimit() << std::endl;
        std::cout << "Balance: " << getNewBalance() << std::endl;

        if (isCreditLimitExceeded())
        {
            std::cout << "Credit Limit Exceeded." << std::endl;
        }
    }
    bool run()
    {
        setAccountNumber();
        if (getAccountNumber() > 0.0)
        {
            setBeginningBalance();
            setTotalMonthCharges();
            setTotalMonthCredit();
            setCreditLimit();

            printInfo();

            return true;
        }
        else
        {
            return false;
        }
    }
};

int main(int argc, const char *argv[])
{
    try
    {
        CreditLimits cl;

        while (cl.run())
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
