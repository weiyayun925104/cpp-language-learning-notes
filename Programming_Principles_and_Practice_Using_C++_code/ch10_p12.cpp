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


int main()
{
    try
    {
        string ifname;
        cout << "Enter input file name: ";
        cin >> ifname;
        ifstream ifs(ifname.c_str());
        if (!ifs) { error("can't open input file " + ifname); }
        string word;
        cout << "Enter word to look for: ";
        cin >> word;

        int counter = 0;
        string current_line;
        while (getline(ifs, current_line, '\n'))
        {
            ++counter;
            for (int i = 0; i < current_line.size(); ++i)
            {
                if (current_line[i] == word[0] && current_line.size() > i + word.size() - 1)
                {
                    bool identical = true;
                    for (int j = 1; j < word.size(); ++j)
                    {
                        if (word[j] != current_line[i + j])
                        {
                            identical = false;
                        }
                    }
                    if (identical)
                    {
                        cout << counter << ": " << current_line << endl;
                        break;
                    }
                }
            }
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
