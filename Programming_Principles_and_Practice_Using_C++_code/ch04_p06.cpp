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


int main()
{
    vector<string> s_digits;
    s_digits.push_back("zero");
    s_digits.push_back("one");
    s_digits.push_back("two");
    s_digits.push_back("three");
    s_digits.push_back("four");
    s_digits.push_back("five");
    s_digits.push_back("six");
    s_digits.push_back("seven");
    s_digits.push_back("eight");
    s_digits.push_back("nine");
    vector<string> i_digits;
    i_digits.push_back("0");
    i_digits.push_back("1");
    i_digits.push_back("2");
    i_digits.push_back("3");
    i_digits.push_back("4");
    i_digits.push_back("5");
    i_digits.push_back("6");
    i_digits.push_back("7");
    i_digits.push_back("8");
    i_digits.push_back("9");
    string inp = "";
    while (cin >> inp)
    {
        bool was_found = false;
        for (int i = 0; i < s_digits.size(); ++i)
        {
            if (s_digits[i] == inp)
            {
                cout << i << endl;
                was_found = true;
            }
            if (i_digits[i] == inp)
            {
                cout << s_digits[i] << endl;
                was_found = true;
            }
        }
        if (!was_found)
        {
            cout << "Input must be zero, one, ..., nine or 0-9\n";
        }
    }
}
