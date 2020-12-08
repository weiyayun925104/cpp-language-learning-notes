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
#include <utility>
#include <random>
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
using std::stringstream;
using std::vector;
using std::list;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
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

class Name_pairs
{
public:
    void read_names();
    void read_ages();
    void print() const;
    void sort();
    const vector<string> &get_name() const
    {
        return name;
    }
    const vector<double> &get_age() const
    {
        return age;
    }
private:
    vector<string> name;
    vector<double> age;
};

void Name_pairs::read_names()
{
    cout << "Enter names, 'NoName' to finish: ";
    string s;
    while (cin >> s && s != "NoName")
    {
        for (int i = 0; i < name.size(); ++i)
        {
            if (name[i] == s)
            {
                error("Name exists already: " + s);
            }
        }
        name.push_back(s);
    }
}

void Name_pairs::read_ages()
{
    age = vector<double>();
    for (int i = 0; i < name.size(); ++i)
    {
        cout << "Age of " << name[i] << ": ";
        double a;
        cin >> a;
        age.push_back(a);
    }
}

void Name_pairs::print() const
{
    if (name.size() != age.size())
    {
        error("print(): name and age must be the same size");
    }
    for (int i = 0; i < name.size(); ++i)
    {
        cout << '(' << name[i] << ',' << age[i] << ')' << endl;
    }
}

void Name_pairs::sort()
{
    if (name.size() != age.size())
    {
        error("sort(): name and age must be the same size");
    }
    vector<string> name_presort = name;
    vector<double> age_cp = age;
    std::sort(name.begin(), name.end());
    for (int i = 0; i < name.size(); ++i)
    {
        for (int j = 0; j < name_presort.size(); ++j)
        {
            if (name[i] == name_presort[j])
            {
                age[i] = age_cp[j];
            }
        }
    }
}

ostream &operator<<(ostream &os, const Name_pairs &np)
{
    if (np.get_name().size() != np.get_age().size())
    {
        error("<<: name and age must be the same size");
    }
    for (int i = 0; i < np.get_name().size(); ++i)
    {
        os << '(' << np.get_name()[i] << ',' << np.get_age()[i] << ')' << endl;
    }
    return os;
}

bool operator==(const Name_pairs &a, const Name_pairs &b)
{
    if (a.get_name().size() != b.get_name().size() || a.get_age().size() != b.get_age().size())
    {
        return false;
    }
    for (int i = 0; i < a.get_name().size(); ++i)
    {
        if (a.get_name()[i] != b.get_name()[i])
        {
            return false;
        }
    }
    for (int i = 0; i < a.get_age().size(); ++i)
    {
        if (a.get_age()[i] != b.get_age()[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Name_pairs &a, const Name_pairs &b)
{
    return !(a == b);
}

int main()
{
    try
    {
        Name_pairs np1;
        np1.read_names();
        np1.read_ages();
        Name_pairs np2;
        np2.read_names();
        np2.read_ages();
        cout << "np1:\n" << np1;
        cout << "np2:\n" << np2;
        if (np1 == np2)
        {
            cout << "Identical!\n";
        }
        else
        {
            cout << "Not identical!\n";
        }
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
