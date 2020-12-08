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

vector<string> s_digits;

void init_vector()
{
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
}

int get_number()
{
    int inp = 0;
    if (cin>>inp)
    {
        return inp;
    }
    cin.clear();
    string inp_s;
    cin >> inp_s;
    for (int i = 0; i<s_digits.size(); ++i)
    {
        if (s_digits[i]==inp_s)
        {
            return i;
        }
    }
    return (-1);
}

int main()
{
    init_vector();
    cout << "Enter two values (number or single digit spelled out) separated by\n"
        << "a character (+, -, * or /). Enter 'q' as operator to exit.\n";
    while (true)
    {
        int val1 = 0;
        int val2 = 0;
        char op = 0;
        val1 = get_number();
        cin >> op;
        val2 = get_number();
        if (val1==-1 || val2==-1)
        {
            cout << "Numbers must be int or, when spelled out, single digit\n";
        }
        else
        {
            switch (op)
            {
            case '+':
                cout << "The sum of " << val1 << " and " << val2 << " is " << val1+val2 << ".\n";
                break;
            case '-':
                cout << "The difference of " << val1 << " and " << val2 << " is " << val1-val2 << ".\n";
                break;
            case '*':
                cout << "The product of " << val1 << " and " << val2 << " is " << val1*val2 << ".\n";
                break;
            case '/':
                if (val2==0)
                {
                    cout << "No division by zero!\n";
                }
                else
                {
                    cout << "The ratio of " << val1 << " and " << val2 << " is " << double(val1)/val2 << ".\n";
                }
                break;
            case 'q':
                return 0;
            default:
                cout << "This is not a valid operation (use +, -, * or /)\n";
                break;
            }
        }
    }
}

