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
using std::stable_partition;
using std::streamsize;
using std::setprecision;
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

class Name_value
{
public:
    string name;
    int value;
    Name_value(string str, int val) : name(str), value(val) { }
};

void list_score(string s, const vector<Name_value> &vec)
{
    int i = 0;
    while (i < vec.size())
    {
        if (vec[i].name == s)
        {
            cout << '(' << s << ',' << vec[i].value << ")\n";
            return;
        }
        ++i;
    }
    cout << "Name not found\n";
}

void list_names(int n, const vector<Name_value> &vec)
{
    bool exists = false;
    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i].value == n)
        {
            cout << '(' << vec[i].name << ',' << n << ")\n";
            exists = true;
        }
    }
    if (!exists)
    {
        cout << "Score not found\n";
    }
}

int main()
{
    try
    {
        cout << "Enter name-and-value pairs such as 'Joe 17':\n";
        string name = "";
        int value = -1;
        vector<Name_value> nv_vec;
        while (cin >> name && cin >> value)
        {
            for (int i = 0; i < nv_vec.size(); ++i)
            {
                if (name == nv_vec[i].name)
                {
                    error("name occurs twice: " + name);
                }
            }
            nv_vec.push_back(Name_value(name, value));
        }

        for (int i = 0; i < nv_vec.size(); ++i)
        {
            cout << "(" << nv_vec[i].name << ',' << nv_vec[i].value << ")\n";
        }

        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
        int sc = 0;
        cout << "Enter name or score ('NoName' to exit):\n";
        while (true)
        {
            if (cin >> sc)
            {
                list_names(sc, nv_vec);
            }
            else
            {
                cin.clear();
                string na;
                cin >> na;
                if (na == "NoName")
                {
                    return 0;
                }
                list_score(na, nv_vec);
            }
            cout << "Enter name or score ('NoName' to exit):\n";
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
