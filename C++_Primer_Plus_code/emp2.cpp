#include "emp2.h"

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
