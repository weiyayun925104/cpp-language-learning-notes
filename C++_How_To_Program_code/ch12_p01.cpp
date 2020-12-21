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

class abstr_emp
{
private:
    std::string fname;
    std::string lname;
    std::string job;
public:
    enum classkind { Employee, Manager, Fink, Highfink };
    abstr_emp();
    abstr_emp(const std::string &fn, const std::string   &ln, const std::string   &j);
    virtual void ShowAll() const;
    virtual void SetAll();
    friend std::ostream &operator <<(std::ostream &os, const abstr_emp &e);
    virtual ~abstr_emp() = 0;
    virtual void writeall(std::ofstream &ofs) const;
    virtual void getall(std::ifstream &ofs);
};

class employee : public abstr_emp
{
public:
    employee();
    employee(const std::string &fn, const std::string &ln, const std::string &j);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream &ofs) const;
    virtual void getall(std::ifstream &ofs);
};

class manager : virtual public abstr_emp
{
private:
    int inchargeof;
protected:
    int InChargeOf() const
    {
        return inchargeof;
    }
    int &InChargeOf()
    {
        return inchargeof;
    }
public:
    manager();
    manager(const std::string &fn, const std::string &ln, const std::string &j, int ico = 0);
    manager(const abstr_emp &e, int ico);
    manager(const manager &m);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream &ofs) const;
    virtual void getall(std::ifstream &ofs);
};

class fink : virtual public abstr_emp
{
private:
    std::string reportsto;
protected:
    const std::string &ReportsTo() const
    {
        return reportsto;
    }
    std::string &ReportsTo()
    {
        return reportsto;
    }
public:
    fink();
    fink(const std::string &fn, const std::string &ln, const std::string &j, const std::string &rpo);
    fink(const abstr_emp &e, const std::string &rpo);
    fink(const fink &e);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream &ofs) const;
    virtual void getall(std::ifstream &ofs);
};

class highfink : public manager, public fink
{
public:
    highfink();
    highfink(const std::string &fn, const std::string &ln, const std::string &j, const std::string &rpo, int ico);
    highfink(const abstr_emp &e, const std::string &rpo, int ico);
    highfink(const fink &f, int ico);
    highfink(const manager &m, const std::string &rpo);
    highfink(const highfink &h);
    virtual void ShowAll() const;
    virtual void SetAll();
    virtual void writeall(std::ofstream &ofs) const;
    virtual void getall(std::ifstream &ofs);
};


abstr_emp::abstr_emp()
{
    fname = "";
    lname = "";
    job = "";
}

abstr_emp::abstr_emp(const std::string &fn, const std::string   &ln, const std::string   &j) : fname(fn), lname(ln), job(j)
{

}

void abstr_emp::ShowAll() const
{
    std::cout << "First name: " << fname << std::endl;
    std::cout << "Last name: " << lname << std::endl;
    std::cout << "Job: " << job << std::endl;
}

void abstr_emp::SetAll()
{
    std::cout << "Enter first name: ";
    std::cin >> fname;

    while (std::cin.get() != '\n')
    {
        continue;
    }

    std::cout << "Enter last name: ";
    std::cin >> lname;

    while (std::cin.get() != '\n')
    {
        continue;
    }

    std::cout << "Enter the job: ";
    std::getline(std::cin, job, '\n');
}

std::ostream &operator<<(std::ostream &os, const abstr_emp &e)
{
    os << e.lname << ", " << e.fname << " : " << e.job;
    return os;
}

abstr_emp::~abstr_emp()
{

}

void abstr_emp::writeall(std::ofstream &ofs) const
{
    ofs << "First name: " << fname << std::endl;
    ofs << "Last name: " << lname << std::endl;
    ofs << "Job: " << job << std::endl;
}
void abstr_emp::getall(std::ifstream &ifs)
{
    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    std::getline(ifs, fname, '\n');
    std::cout << "First name is " << fname << std::endl;

    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    std::getline(ifs, lname, '\n');
    std::cout << "Last name is " << lname << std::endl;

    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    std::getline(ifs, job, '\n');
    std::cout << "Job is " << job << std::endl;
}

employee::employee() : abstr_emp()
{

}

employee::employee(const std::string &fn, const std::string   &ln, const std::string   &j) : abstr_emp(fn, ln, j)
{

}

void employee::ShowAll() const
{
    std::cout << "Status: Employee" << std::endl;
    abstr_emp::ShowAll();
}

void employee::SetAll()
{
    abstr_emp::SetAll();
}

void employee::writeall(std::ofstream &ofs) const
{
    ofs << abstr_emp::Employee << std::endl;
    abstr_emp::writeall(ofs);
}

void employee::getall(std::ifstream &ifs)
{
    abstr_emp::getall(ifs);
}

manager::manager() : abstr_emp()
{
    inchargeof = 0;
}

manager::manager(const std::string &fn, const std::string &ln,
                 const std::string &j, int ico) : abstr_emp(fn, ln, j)
{
    inchargeof = ico;

    if (inchargeof < 0)
    {
        std::cout << "Error, cannot be in charge of negative people." << std::endl;
        std::cout << "Setting inchargeof to 0" << std::endl;
        inchargeof = 0;
    }
}

manager::manager(const abstr_emp &e, int ico) : abstr_emp(e)
{
    inchargeof = ico;

    if (inchargeof < 0)
    {
        std::cout << "Error, cannot be in charge of negative people." << std::endl;
        std::cout << "Setting inchargeof to 0" << std::endl;
        inchargeof = 0;
    }
}

manager::manager(const manager &m) : abstr_emp(m)
{
    inchargeof = m.inchargeof;
}

void manager::ShowAll() const
{
    std::cout << "Status: Manager" << std::endl;
    abstr_emp::ShowAll();
    std::cout << "In charge of " << inchargeof << " people" << std::endl;
}

void manager::SetAll()
{
    abstr_emp::SetAll();
    std::cout << "Enter the number of people the manager is in charge of: ";
    std::cin >> inchargeof;
    while (std::cin.get() != '\n')
    {
        continue;
    }
    if (inchargeof < 0)
    {
        std::cout << "Error, cannot be in charge of negative people." << std::endl;
        std::cout << "Setting inchargeof to 0" << std::endl;
        inchargeof = 0;
    }
}

void manager::writeall(std::ofstream &ofs) const
{
    ofs << abstr_emp::Manager << std::endl;
    abstr_emp::writeall(ofs);
    ofs << "Number of people managed: " << inchargeof << std::endl;
}

void manager::getall(std::ifstream &ifs)
{
    abstr_emp::getall(ifs);
    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    ifs >> inchargeof;
    ifs.get();
}

fink::fink() : abstr_emp(), reportsto("")
{

}

fink::fink(const std::string &fn, const std::string &ln,
           const std::string &j, const std::string &rpo) : abstr_emp(fn, ln, j), reportsto(rpo)
{

}

fink::fink(const abstr_emp &e, const std::string &rpo) : abstr_emp(e), reportsto(rpo)
{

}

fink::fink(const fink &e) : abstr_emp(e)
{
    reportsto = e.reportsto;
}

void fink::ShowAll() const
{
    std::cout << "Status: fink" << std::endl;
    abstr_emp::ShowAll();
    std::cout << "Reports to " << reportsto << std::endl;
}

void fink::SetAll()
{
    abstr_emp::SetAll();
    std::cout << "Enter whomever is reported to: ";
    std::getline(std::cin, reportsto, '\n');
}

void fink::writeall(std::ofstream &ofs) const
{
    ofs << abstr_emp::Fink << std::endl;
    abstr_emp::writeall(ofs);
    ofs << "Reports to: " << reportsto << std::endl;
}

void fink::getall(std::ifstream &ifs)
{
    abstr_emp::getall(ifs);
    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    std::getline(ifs, reportsto, '\n');
}
highfink::highfink() : abstr_emp(), manager(), fink()
{

}
highfink::highfink(const std::string &fn, const std::string &ln,
                   const std::string &j, const std::string &rpo, int ico) : abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo)
{

}
highfink::highfink(const abstr_emp &e, const std::string &rpo, int ico) : abstr_emp(e), manager(e, ico), fink(e, rpo)
{

}

highfink::highfink(const fink &f, int ico) : abstr_emp(f), manager(f, ico), fink(f)
{

}

highfink::highfink(const manager &m, const std::string &rpo) : abstr_emp(m), manager(m), fink(m, rpo)
{

}

highfink::highfink(const highfink &h) : abstr_emp(h), manager(h), fink(h)
{

}

void highfink::ShowAll() const
{
    std::cout << "Status: Highfink" << std::endl;
    abstr_emp::ShowAll();
    std::cout << "In charge of " << InChargeOf() << " people" << std::endl;
    std::cout << "Reports to " << ReportsTo() << std::endl;
}

void highfink::SetAll()
{
    abstr_emp::SetAll();
    std::cout << "Enter the number of people managed: ";
    std::cin >> InChargeOf();
    while (std::cin.get() != '\n')
    {
        continue;
    }
    if (InChargeOf() < 0)
    {
        std::cout << "Error, cannot be in charge of negative people." << std::endl;
        std::cout << "Setting inchargeof to 0" << std::endl;
        InChargeOf() = 0;
    }

    std::cout << "Enter whomever is reported to: ";
    std::getline(std::cin, ReportsTo(), '\n');
}

void highfink::writeall(std::ofstream &ofs) const
{
    ofs << abstr_emp::Highfink << std::endl;
    abstr_emp::writeall(ofs);
    ofs << "Number of people managed: " << InChargeOf() << std::endl;
    ofs << "Reports to: " << ReportsTo() << std::endl;
}

void highfink::getall(std::ifstream &ifs)
{
    abstr_emp::getall(ifs);
    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    ifs >> InChargeOf();
    ifs.get();
    ifs.ignore(256, ':');
    while (' ' == ifs.peek())
    {
        ifs.get();
    }
    std::getline(ifs, ReportsTo(), '\n');
}

const int MAX = 10;

void displayMenu(void)
{
    std::cout << "Select one of the following:" << std::endl;
    std::cout << std::left;
    std::cout << std::setw(20) << "a. Employee";
    std::cout << std::setw(20) << "b. Manager";
    std::cout << std::endl;
    std::cout << std::setw(20) << "c. Fink";
    std::cout << std::setw(20) << "d. Highfink";
    std::cout << std::endl;
    std::cout << "(q to quit)" << std::endl;
}

void eatline(void)
{
    while (std::cin.get() != '\n')
    {
        continue;
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        abstr_emp *pc[MAX];
        std::cout << "You may enter of to " << MAX << " employees" << std::endl;

        int count = 0;
        char ch;
        std::ifstream fin;
        fin.open("employeeList.dat");

        if (fin.is_open())
        {
            int classtype = 0;
            while ( fin >> classtype && fin.get(ch) )
            {
                switch (classtype)
                {
                case abstr_emp::Employee:
                    std::cout << "Creating an employee object" << std::endl;
                    pc[count] = new employee;
                    pc[count++]->getall(fin);
                    break;
                case abstr_emp::Manager:
                    std::cout << "Creating an manager object" << std::endl;
                    pc[count] = new manager;
                    pc[count++]->getall(fin);
                    break;
                case abstr_emp::Fink:
                    std::cout << "Creating an fink object" << std::endl;
                    pc[count] = new fink;
                    pc[count++]->getall(fin);
                    break;
                case abstr_emp::Highfink:
                    std::cout << "Creating an highfink object" << std::endl;
                    pc[count] = new highfink;
                    pc[count++]->getall(fin);
                    break;
                default:
                    std::cerr << "It looks like an error has occurred" << std::endl;
                    break;
                }
            }
            std::cout << "Here is your current employee list: " << std::endl;
            for (int i = 0; i < count; i++)
            {
                pc[i]->ShowAll();
                std::cout << std::endl;
            }
            fin.close();
        }

        while (count < MAX)
        {
            displayMenu();
            std::cin >> ch;
            eatline();

            switch (ch)
            {
            case 'a':
                pc[count] = new employee;
                pc[count]->SetAll();
                count++;
                break;
            case 'b':
                pc[count] = new manager;
                pc[count]->SetAll();
                count++;
                break;
            case 'c':
                pc[count] = new fink;
                pc[count]->SetAll();
                count++;
                break;
            case 'd':
                pc[count] = new highfink;
                pc[count]->SetAll();
                count++;
                break;
            case 'q':
                break;
            default:
                std::cout << "Error input not recognized" << std::endl;
                continue;
                break;
            }
            if (ch == 'q')
            {
                break;
            }
        }

        std::ofstream fout;
        fout.open("employeeList.dat");

        if (!fout.is_open())
        {
            std::cerr << "Error, cannot open employeeList.dat" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Here's our updated list: " << std::endl;

        for (int i = 0; i < count; i++)
        {
            pc[i]->ShowAll();
            std::cout << std::endl;
            pc[i]->writeall(fout);
        }
        fout.close();
        for (int i = 0; i < count; i++)
        {
            delete pc[i];
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
