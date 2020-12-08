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

string bin_file = "ch11_p08.bin";

void to_binary(const string &s)
{
    ifstream ifs(s.c_str());
    if (!ifs) { error("can't open input file " + s); }
    ofstream ofs(bin_file.c_str(), std::ios_base::binary);
    if (!ofs) { error("can't open output file " + bin_file); }

    char ch;
    while (ifs.get(ch))
    {
        ofs.write(&ch, sizeof(char));
    }
}

void from_binary(const string &s)
{
    ifstream ifs(bin_file.c_str(), std::ios_base::binary);
    if (!ifs) { error("can't open input file " + bin_file); }
    ofstream ofs(s.c_str());
    if (!ofs) { error("can't open output file " + s); }

    char ch;
    while (ifs.read(&ch, sizeof(char)))
    {
        ofs << ch;
    }
}

int main()
{
    try
    {
        cout << "Enter input file name: ";
        string iname;
        cin >> iname;
        to_binary(iname);

        cout << "Enter output file name: ";
        string oname;
        cin >> oname;
        from_binary(oname);

        cout << "Done!\n";
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
