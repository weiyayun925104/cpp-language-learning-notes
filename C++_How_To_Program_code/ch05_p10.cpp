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


class GradeBook
{
private:
    std::string courseName;
    int aCount;
    int bCount;
    int cCount;
    int dCount;
    int fCount;
public:
    explicit GradeBook(const std::string &name) : courseName(name)
    {
        aCount = 0;
        bCount = 0;
        cCount = 0;
        dCount = 0;
        fCount = 0;
    }
    void setCourseName(const std::string &name)
    {
        if (name.size() <= 25)
        {
            courseName = name;
        }
        else
        {
            courseName = name.substr(0, 25);

            std::cout << "Name \"" << name << "\" exceeds maximum length (25).\n";
            std::cout << "Limiting courseName to first 25 characters.\n";
        }
    }
    const std::string &getCourseName()
    {
        return courseName;
    }
    void displayMessage()
    {
        std::cout << "Welcome to the grade book for\n"
                  << getCourseName() << "!" << std::endl;
    }
    void inputGrades()
    {
        char grade;
        char c;
        std::cout << "Enter the letter grades: " << std::endl;
        while (std::cin >> grade && (c = tolower(grade)) >= 'a' && c <= 'f')
        {
            switch (c)
            {
            case 'a':
                ++aCount;
                break;
            case 'b':
                ++bCount;
                break;
            case 'c':
                ++cCount;
                break;
            case 'd':
                ++dCount;
                break;
            case 'f':
                ++fCount;
                break;
            default:
                break;
            }
        }
    }
    void displayGradeReport() const
    {
        std::cout << "Number of students who received each letter grade: " << std::endl
                  << "A: " << aCount << "\nB: " << bCount << "\nC: " << cCount << std::endl
                  << "D: " << dCount << "\nF: " << fCount << std::endl;

        cout << "Grade Point Average: " <<
             (aCount * 4 + bCount * 3 + cCount * 2 + dCount * 1 + fCount * 0) /
             (aCount + bCount + cCount + dCount + fCount) << endl;
    }
};

int main(int argc, const char *argv[])
{
    try
    {
        GradeBook myGradeBook("Data Structures in C++");

        myGradeBook.displayMessage();
        myGradeBook.inputGrades();
        myGradeBook.displayGradeReport();

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
