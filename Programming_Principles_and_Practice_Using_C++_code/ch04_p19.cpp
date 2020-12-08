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
using std::string;
using std::getline;
using std::to_string;
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

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

vector<string> names;
vector<int> scores;

void list_score(string s)
{
    int i = 0;
    while (i < names.size())
    {
        if (names[i] == s)
        {
            cout << '(' << s << ',' << scores[i] << ")\n";
            return;
        }
        ++i;
    }
    cout << "Name not found\n";
}

void list_names(int n)
{
    bool exists = false;
    for (int i = 0; i < scores.size(); ++i)
    {
        if (scores[i] == n)
        {
            cout << '(' << names[i] << ',' << n << ")\n";
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
    string name = " ";
    int score = 0;
    cout << "Enter name-and-value pairs such as 'Joe 17':\n";
    while (cin >> name && cin >> score)
    {
        names.push_back(name);
        scores.push_back(score);
    }

    for (int i = 0; i < names.size(); ++i)
    {
        for (int j = i + 1; j < names.size(); ++j)
        {
            if (names[i] == names[j])
            {
                error("Name appears twice!");
            }
        }
    }

    for (int i = 0; i < names.size(); ++i)
    {
        cout << '(' << names[i] << ',' << scores[i] << ")\n";
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
            list_names(sc);
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
            list_score(na);
        }
        cout << "Enter name or score ('NoName' to exit):\n";
    }
}
