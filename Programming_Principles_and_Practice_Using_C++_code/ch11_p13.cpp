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
using std::istringstream;
using std::ostringstream;
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
using std::ios_base;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

inline std::ios_base &general(std::ios_base &b)
{
    b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
    return b;
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
        cout << "Enter input file name: ";
        string iname;
        cin >> iname;
        ifstream ifs(iname.c_str());
        if (!ifs) { error("can't open input file " + iname); }

        char ch;
        int space = 0;
        int alpha = 0;
        int digit = 0;
        int xdigit = 0;
        int upper = 0;
        int lower = 0;
        int alnum = 0;
        int cntrl = 0;
        int punct = 0;
        int print = 0;
        int graph = 0;

        while (ifs.get(ch))
        {
            if (isspace(ch)) ++space;
            if (isalpha(ch)) ++alpha;
            if (isdigit(ch)) ++digit;
            if (isxdigit(ch)) ++xdigit;
            if (isupper(ch)) ++upper;
            if (islower(ch)) ++lower;
            if (isalnum(ch)) ++alnum;
            if (iscntrl(ch)) ++cntrl;
            if (ispunct(ch)) ++punct;
            if (isprint(ch)) ++print;
            if (isgraph(ch)) ++graph;
        }

        cout << "Analysis:\n";
        cout << "isspace:\t" << space << endl;
        cout << "isalpha:\t" << alpha << endl;
        cout << "isdigit:\t" << digit << endl;
        cout << "isxdigit:\t" << xdigit << endl;
        cout << "isupper:\t" << upper << endl;
        cout << "islower:\t" << lower << endl;
        cout << "isalnum:\t" << alnum << endl;
        cout << "iscntrl:\t" << cntrl << endl;
        cout << "ispunct:\t" << punct << endl;
        cout << "isprint:\t" << print << endl;
        cout << "isgraph:\t" << graph << endl;
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
