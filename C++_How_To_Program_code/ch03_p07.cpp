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


class Date
{
private:
    int month;
    int day;
    int year;
public:
    Date(int m = 1, int d = 1, int y = 1970) : month(m), day(d), year(y)
    {
        if (m < 1 || m > 12)
        {
            month = 1;
        }
        if (!(is_date(y, m, d)))
        {
            day = 1;
        }
    }

    bool leapyear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    }

    bool is_date(int y, int m, int d)
    {
        if (d <= 0)
        {
            return false;
        }

        int days_in_month = 31;

        switch (m)
        {
        case 2:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month = 30;
            break;
        }

        if (days_in_month < d)
        {
            return false;
        }

        return true;
    }

    void setMonth(int m)
    {
        if (m >= 1 && m <= 12 && is_date(year, m, day))
        {
            month = m;
        }
    }
    void setDay(int d)
    {
        if (is_date(year, month, d))
        {
            day = d;
        }
    }
    void setYear(int y)
    {
        year = y;
    }

    int getMonth() const
    {
        return month;
    }
    int getDay() const
    {
        return day;
    }
    int getYear() const
    {
        return year;
    }

    void displayDate() const
    {
        std::cout << getMonth() << "/" << getDay() << "/" << getYear() << std::endl;
    }
};

class HealthProfile
{
private:
    std::string firstName;
    std::string lastName;
    std::string gender;
    Date birthYMD;
    int ageInYears;
    double height;
    double weight;
public:
    HealthProfile(const std::string &fName, const std::string &lName,
                  const std::string &g, int m, int d, int y, double h, double w)
        : firstName (fName), lastName(lName), gender(g), birthYMD(m, d, y), height(h), weight(w)
    {
        if (fName.size() <= 0)
        {
            firstName = "FirstName";
        }
        if (lName.size() <= 0)
        {
            lastName = "LastName";
        }
        if (g != "Male" && g != "Female")
        {
            gender = "Undefined";
        }

        setAge();
    }

    void setFirstName(const std::string &fName)
    {
        if (fName.size() > 0)
        {
            firstName = fName;
        }
    }
    void setLastName(const std::string &lName)
    {
        if (lName.size() > 0)
        {
            lastName = lName;
        }
    }
    void setGender(const std::string &g)
    {
        if (g == "Male" || g == "Female")
        {
            gender = g;
        }
    }
    void setYMD(int m, int d, int y)
    {
        birthYMD = Date(m, d, y);
        setAge();
    }
    void setAge()
    {
        int cDay, cMonth, cYear;

        std::cout << "Enter the current date(mm dd yyyy): ";
        std::cin >> cMonth >> cDay >> cYear;

        if (cMonth < birthYMD.getMonth())
        {
            ageInYears = ((cYear - birthYMD.getYear()) - 1);
        }
        else if (cMonth > birthYMD.getMonth())
        {
            ageInYears = (cYear - birthYMD.getYear());
        }
        else
        {
            ageInYears =  ((cDay < birthYMD.getDay()) ? ((cYear - birthYMD.getYear()) - 1) : (cYear - birthYMD.getYear()));
        }
    }
    void setHeight(int h)
    {
        height = h;
    }
    void setWeight(int w)
    {
        weight = w;
    }

    const std::string &getFirstName() const
    {
        return firstName;
    }
    const std::string &getLastName() const
    {
        return lastName;
    }
    const std::string &getGender() const
    {
        return gender;
    }
    const Date &getYMD() const
    {
        return birthYMD;
    }
    int getAge() const
    {
        return ageInYears;
    }
    double getHeight() const
    {
        return height;
    }
    double getWeight() const
    {
        return weight;
    }

    double getBMI() const
    {
        return ((getWeight() * 703) / (getHeight() * getHeight()));
    }

    int getMaximumHeartRate() const
    {
        return 220 - getAge();
    }
    void displayTargetHeartRate() const
    {
        std::cout << "Your Target Heart Rate: "
                  << 0.5 * getMaximumHeartRate() << " - "
                  << 0.85 * getMaximumHeartRate() << std::endl;
    }
    void printBMIInfo() const
    {
        std::cout << "\nBMI VALUES" << std::endl;
        std::cout << "Underweight: less than 18.5" << std::endl;
        std::cout << "Normal:      between 18.5 and 24.9" << std::endl;
        std::cout << "Overweight:  between 25 and 29.9" << std::endl;
        std::cout << "Obese:       30 or greater\n" << std::endl;
    }

    void showHealthProfile() const
    {
        std::cout << "Name: " << getFirstName() << " " << getLastName() << std::endl;
        std::cout << "Gender: " << getGender() << std::endl;
        std::cout << "BirthDate ";
        birthYMD.displayDate();
        std::cout << "Age: " << getAge() << std::endl;
        std::cout << "Maximum Heart Rate: " << getMaximumHeartRate() << std::endl;
        displayTargetHeartRate();
        std::cout << "BMI: " << getBMI() << std::endl;
        printBMIInfo();
    }
};

int main(int argc, const char *argv[])
{
    try
    {
        std::string fName, lName, gender;
        int month, day, year;
        double weight, height;

        std::cout << "Enter your first and last name: ";
        std::cin >> fName >> lName;
        std::cout << "Enter your gender (Male/Female): ";
        std::cin >> gender;
        std::cout << "Enter your date of birth (mm dd yyyy): ";
        std::cin >> month >> day >> year;
        std::cout << "Enter your weight in pounds: ";
        std::cin >> weight;
        std::cout << "Enter your height in inches: ";
        std::cin >> height;

        HealthProfile hp(fName, lName, gender, month, day, year, height, weight);
        hp.showHealthProfile();

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
