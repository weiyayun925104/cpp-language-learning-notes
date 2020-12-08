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

vector<string> num_words;

void init()
{
    num_words.push_back("thousand");
    num_words.push_back("hundred");
    num_words.push_back("ten");
    num_words.push_back("one");
}

int char_to_int(vector<int> v)
{
    if (v.size() == 0)
    {
        error("empty vector handed to char_to_int()");
    }
    if (v.size() > 4)
    {
        error("char_to_int can handle only up to four digits");
    }
    int num = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        num = 10 * num + v[i];
    }
    return num;
}

void plural_s(int n)
{
    if (n == 0 || n > 1)
    {
        cout << 's';
    }
    if (n == 1)
    {
        return;
    }
    if (n < 0)
    {
        error("plural_s can handle only non-negative numbers");
    }
}

void print_number(const vector<int> &v, int num)
{
    if (num > 9999 || v.size() > 4)
    {
        error("print_number can only handle numbers with four digits");
    }
    if (v.size() == 0)
    {
        error("print_number was handed an empty vector");
    }
    cout << num << " is ";
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << ' ' << num_words[i + 4 - v.size()];
        plural_s(v[i]);
        if (i < v.size() - 1)
        {
            cout << " and ";
        }
    }
    cout << endl;
}

int main()
{
    try
    {
        init();

        cout << "Enter number with up to four digits, followed by a ';' and a newline.\n";
        cout << "Enter 'q' to quit.\n";
        while (true)
        {
            vector<int> ch_vec;
            char ch;
            while (cin >> ch)
            {
                if (ch == 'q')
                {
                    return 0;
                }
                if (ch < '0' || ch > '9')
                {
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                    break;
                }
                ch_vec.push_back(ch - '0');
            }

            int as_int = char_to_int(ch_vec);

            print_number(ch_vec, as_int);

            cout << "Enter number with up to four digits, followed by a ';' and a newline.\n";
            cout << "Enter 'q' to quit.\n";
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
