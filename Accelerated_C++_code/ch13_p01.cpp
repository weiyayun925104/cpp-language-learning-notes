#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <memory>
#include <cstring>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::runtime_error;
using std::transform;
using std::back_inserter;
using std::ostream_iterator;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::min;
using std::stable_partition;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

double median(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double> &hw)
{
    if (hw.size() == 0)
    {
        throw domain_error("Student has done no homework");
    }
    return grade(midterm, final, median(hw));
}

istream &read_hw(istream &is, vector<double> &hw)
{
    if (is)
    {
        double x;
        while (is >> x)
        {
            hw.push_back(x);
        }

        is.clear();
        while (is.get() != '\n')
        {
            continue;
        }
    }

    return is;
}

class Core
{
public:
    friend class Student_info;
    friend class Audit;
    Core() : midterm(0), final(0)
    {
        cerr << "constructor Core()" << endl;
    }
    Core(istream &is)
    {
        cerr << "constructor Core(istream &is)" << endl;
        read(is);
    }

    virtual ~Core()
    {
        cerr << "destructor ~Core()" << endl;
    }

    const string &name() const
    {
        return _name;
    }
    virtual double grade() const
    {
        return ::grade(midterm, final, homework);
    }
    string letter_grade() const;
    virtual istream &read(istream &);

    bool valid() const
    {
        return !homework.empty();
    }
    virtual bool requirements_met() const
    {
        return find(homework.begin(), homework.end(), 0.0) == homework.end();
    }

protected:
    virtual Core *clone() const
    {
        return new Core(*this);
    }
    istream &read_common(istream &in)
    {
        in >> _name >> midterm >> final;
        return in;
    }
    double midterm, final;
    vector<double> homework;

private:
    string _name;
};

istream &Core::read(istream &in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

string Core::letter_grade() const
{
    static const double numbers[] =
    {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    static const char *const letters[] =
    {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

    double result = grade();

    for (size_t i = 0; i < ngrades; ++i)
    {
        if (result >= numbers[i])
        {
            return letters[i];
        }
    }
    return "?\?\?";
}

inline bool compare(const Core &c1, const Core &c2)
{
    return c1.name() < c2.name();
}

inline bool compare_Core_ptrs(const Core *cp1, const Core *cp2)
{
    return compare(*cp1, *cp2);
}

class Grad : public Core
{
public:
    Grad() : thesis(0.0)
    {
        cerr << "constructor Grad()" << endl;
    }
    Grad(istream &is)
    {
        cerr << "constructor Grad(istream &is)" << endl;
        read(is);
    }

    double grade() const;
    istream &read(istream &);

    bool requirements_met() const
    {
        return Core::requirements_met() && thesis != 0.0;
    }

protected:
    Grad *clone() const
    {
        return new Grad(*this);
    }

private:
    double thesis;
};

istream &Grad::read(istream &in)
{
    Core::read_common(in);
    in >> Grad::thesis;
    read_hw(in, Core::homework);
    return in;
}

double Grad::grade() const
{
    return min(Core::grade(), Grad::thesis);
}

class Credit : public Core
{
public:
    Credit() {}
    Credit(istream &is) : Core(is) {}

    double grade() const;
    bool passed() const
    {
        return grade() >= 60;
    }

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }

protected:
    Credit *clone() const
    {
        return new Credit(*this);
    }
};

double Credit::grade() const
{
    if (Core::homework.empty())
    {
        return (midterm + final) / 2.0;
    }
    else
    {
        return Core::grade();
    }
}

class Audit : public Core
{
public:
    Audit() {}
    Audit(istream &is)
    {
        read(is);
    }

    istream &read(istream &in)
    {
        in >> _name;
        return in;
    }

    double grade() const
    {
        return 0.0;
    };

    bool valid() const
    {
        return true;
    }
    bool requirements_met() const
    {
        return true;
    }

protected:
    Audit *clone() const
    {
        return new Audit(*this);
    }
};

class Student_info
{
public:
    Student_info() : cp(nullptr) { }
    Student_info(istream &is) : cp(nullptr)
    {
        read(is);
    }
    Student_info(const Student_info &);
    Student_info &operator=(const Student_info &);
    ~Student_info()
    {
        delete cp;
    }

    istream &read(istream &);

    const string &name() const
    {
        if (cp != nullptr)
        {
            return cp->name();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

    double grade() const
    {
        if (cp != nullptr)
        {
            return cp->grade();
        }
        else
        {
            throw runtime_error("uninitialized Student");
        }
    }

private:
    Core *cp;
};


istream &Student_info::read(istream &is)
{
    char ch;
    cout << "Enter U for new Core, C for new Credit, A for new Audit, G for new Grad" << endl;
    if (is >> ch)
    {
        delete cp;
        if (ch == 'U')
        {
            cout << "new Core" << endl;
            cp = new Core(is);
        }
        else if (ch == 'C')
        {
            cout << "new Credit" << endl;
            cp = new Credit(is);
        }
        else if (ch == 'A')
        {
            cout << "new Audit" << endl;
            cp = new Audit(is);
        }
        else
        {
            cout << "new Grad" << endl;
            cp = new Grad(is);
        }
    }
    return is;
}

Student_info::Student_info(const Student_info &s) : cp(nullptr)
{
    if (s.cp != nullptr)
    {
        cp = s.cp->clone();
    }
}

Student_info &Student_info::operator=(const Student_info &s)
{
    if (this == &s)
    {
        return *this;
    }
    delete cp;
    if (s.cp != nullptr)
    {
        cp = s.cp->clone();
    }
    else
    {
        cp = nullptr;
    }
    return *this;
}

inline bool compare_info(const Student_info &s1, const Student_info &s2)
{
    return s1.name() < s2.name();
}

int main()
{
    Core core1;
    Grad grad1;

    cout << "Enter Core student info:" << endl;
    Core core2(cin);

    cout << "Enter Grad student info:" << endl;
    Grad grad2(cin);

    cout << core2.name() << ", " << core2.grade() << endl;
    cout << grad2.name() << ", " << grad2.grade() << endl;

    return 0;
}
