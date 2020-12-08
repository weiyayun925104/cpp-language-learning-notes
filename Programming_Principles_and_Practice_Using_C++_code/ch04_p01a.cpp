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
    const double dollars_per_yen = 0.01;
    const double dollars_per_euro = 1.35;
    const double dollars_per_pound = 1.61;
    const double dollars_per_yuan = 0.16;
    const double dollars_per_kroner = 0.18;
    double amount = 0;
    char currency = ' ';
    cout << "Please enter an amount followed by a currency (Y, U, p, y or k):\n";
    cin >> amount >> currency;

    switch (currency)
    {
    case 'Y':
        cout << amount << " yen is " << dollars_per_yen *amount << " dollars\n";
        break;
    case 'U':
        cout << amount << " euro is " << dollars_per_euro *amount << " dollars\n";
        break;
    case 'p':
        cout << amount << " pound is " << dollars_per_pound *amount << " dollars\n";
        break;
    case 'y':
        cout << amount << " yuan is " << dollars_per_yuan *amount << " dollars\n";
        break;
    case 'k':
        cout << amount << " kroner is " << dollars_per_kroner *amount << " dollars\n";
        break;
    default:
        cout << "Sorry, I don't know the currency '" << currency << "'\n";
        break;
    }
    return 0;
}
