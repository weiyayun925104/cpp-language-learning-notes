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

vector<int> mondays;
vector<int> tuesdays;
vector<int> wednesdays;
vector<int> thursdays;
vector<int> fridays;
vector<int> saturdays;
vector<int> sundays;
int rejected = 0;

int handle_input(string day, int val)
{
    int cont = 0;
    if (day == "Monday" || day == "monday" || day == "Mon" || day == "mon")
    {
        mondays.push_back(val);
    }
    else if (day == "Tuesday" || day == "tuesday" || day == "Tue" || day == "tue")
    {
        tuesdays.push_back(val);
    }
    else if (day == "Wednesday" || day == "wednesday" || day == "Wed" || day == "wed")
    {
        wednesdays.push_back(val);
    }
    else if (day == "Thursday" || day == "thursday" || day == "Thu" || day == "thu")
    {
        thursdays.push_back(val);
    }
    else if (day == "Friday" || day == "friday" || day == "Fri" || day == "fri")
    {
        fridays.push_back(val);
    }
    else if (day == "Saturday" || day == "saturday" || day == "Sat" || day == "sat")
    {
        saturdays.push_back(val);
    }
    else if (day == "Sunday" || day == "sunday" || day == "Sun" || day == "sun")
    {
        sundays.push_back(val);
    }
    else if (day == "q" && val == 0)
    {
        cont = -1;
    }
    else
    {
        ++rejected;
    }
    return cont;
}

int get_sum(const vector<int> &v)
{
    int sum = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        sum += v[i];
    }
    return sum;
}

void print_day(string day, const vector<int> &v)
{
    cout << day << " (sum: " << get_sum(v) << ")\n";
    cout << "Values:";
    for (int i = 0; i < v.size(); ++i)
    {
        cout << ' ' << v[i];
    }
    cout << endl;
}

void print_results()
{
    print_day("Monday", mondays);
    print_day("Tuesday", tuesdays);
    print_day("Wednesday", wednesdays);
    print_day("Thursday", thursdays);
    print_day("Friday", fridays);
    print_day("Saturday", saturdays);
    print_day("Sunday", sundays);
    cout << rejected << " values rejected\n";
}

int main()
{
    try
    {
        string day = " ";
        int val = 0;
        cout << "Enter weekday/value pairs, exit with 'q 0'\n";
        while (cin >> day && cin >> val)
        {
            int cont = handle_input(day, val);
            if (cont == -1)
            {
                print_results();
                return 0;
            }
        }
        error("Invalid input");
    }
    catch (exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception!\n";
        return 2;
    }
}
