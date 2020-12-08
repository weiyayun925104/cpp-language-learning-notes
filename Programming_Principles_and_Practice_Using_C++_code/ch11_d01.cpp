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

void int_output()
{
    cout << showbase << "Birth year:" << endl
         << 1980 << "\t(decimal)" << endl
         << hex << 1980 << "\t(hexadecimal)" << endl
         << oct << 1980 << "\t(octal)" << endl;

    cout << dec << endl << "Age:" << endl
         << 33 << "\t(decimal)" << endl
         << hex << 33 << "\t(hexadecimal)" << endl
         << oct << 33 << "\t(octal)" << endl;
        cout << dec << endl;
}

void int_input()
{
    int a;
    int b;
    int c;
    int d;
    cin >> a >> hex >> b >> oct >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
}

void float_output()
{
    cout << 1234567.89 << "\t(general)\n"
         << fixed << 1234567.89 << "\t(fixed)\n"
         << scientific << 1234567.89 << "\t(scientific)\n";
}

int main()
{
    try
    {
    	int_output();
    	int_input();
    	float_output();
        cout << setw(10) << "Wuethrich" << " | " << "Benjamin" << " | "
             << setw(16) << "+1345 326 5181" << " | " << setw(29) << "benjamin.wuethrich@gmail.com" << endl
             << setw(10) << "Forrest" << " | " << setw(8) << "Kara" << " | "
             << setw(16) << "+1345 516 1920" << " | " << setw(29) << "kara_forrest@hotmail.com" << endl
             << setw(10) << "Aarnau" << " | " << setw(8) << "Mayra" << " | "
             << "+34 66 696 55 63" << " | " << setw(29) << "mayraaachen@hotmail.com" << endl
             << setw(10) << "Michel" << " | " << setw(8) << "Tanael" << " | "
             << "+41 79 374 48 62" << " | " << setw(29) << "tanael@gmail.com" << endl
             << setw(10) << "Widler" << " | " << setw(8) << "Andrea" << " | "
             << "+41 79 293 29 38" << " | " << setw(29) << "andreawidler@bluewin.ch" << endl
             << "Amanatidou" << " | " << "Elisabet" << " | "
             << "+41 76 701 61 28" << " | " << "elisabet.amanatidou@gmail.com" << endl;
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
