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


inline int square(int x)
{
    return x * x;
}

void print_square(int v)
{
    cout << v << '\t' << v *v << '\n';
}

void write_sorry()
{
    cout << "Sorry\n";
}

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

int main()
{
    {
        int i = 0;
        while (i < 10)
        {
            cout << i << '\t' << square(i) << '\n';
            ++i ;
        }
    }

    {
        vector<int> v(6);

        v[0] = 5;
        v[1] = 7;
        v[2] = 9;
        v[3] = 4;
        v[4] = 6;
        v[5] = 8;

        copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        vector<string> philosopher(4);

        philosopher [0] = "Kant";
        philosopher [1] = "Plato";
        philosopher [2] = "Hume";
        philosopher [3] = "Kierkegaard";

        copy(philosopher.begin(), philosopher.end(), ostream_iterator<string>(cout, " "));
        cout << endl;

        vector<double> vd(10, -1.2);

        copy(vd.begin(), vd.end(), ostream_iterator<double>(cout, " "));
        cout << endl;
    }

    {
        vector<double> v;

        v.push_back(2.7);
        v.push_back(5.6);
        v.push_back(7.9);

        for(int i = 0; i < v.size(); ++i)
        {
            cout << "v[" << i << "] = " << v[i] << '\n';
        }
    }

    {
        vector<double> temps;
        double temp;
        while (cin >> temp)
        {
            temps.push_back(temp);
        }
        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
        cout << "Average temperature: " << accumulate(temps.begin(), temps.end(), 0.0) / temps.size() << endl;
        try
        {
            cout << "Median temperature: " << median(temps) << endl;
        }
        catch (domain_error &e1)
        {
            cout << e1.what() << endl;
        }
    }

    {
        vector<string> words;
        string temp;
        while (cin >> temp)
        {
            words.push_back(temp);
        }

        cout << "Number of words: " << words.size() << endl;

        sort(words.begin(), words.end());

        for (int i = 0; i < words.size(); ++i)
        {
            if (i == 0 || words[i - 1] != words[i])
            {
                cout << words[i] << "\n";
            }
        }
    }

}
