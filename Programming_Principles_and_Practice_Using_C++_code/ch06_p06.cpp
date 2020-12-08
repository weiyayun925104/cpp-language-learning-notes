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

class String_stream
{
public:
    String_stream();
    string get();
    void putback(string s);
private:
    bool full;
    string buffer;
};

String_stream::String_stream() : full(false), buffer("") { }

void String_stream::putback(string s)
{
    if (full)
    {
        error("putback() into a full buffer");
    }
    buffer = s;
    full = true;
}

string String_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    string s = "";
    cin >> s;
    return s;
}

String_stream sstr;

bool conjunction()
{
    string s = sstr.get();
    if (s == "and" || s == "or" || s == "but")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool noun()
{
    string s = sstr.get();
    if (s == "birds" || s == "fish" || s == "C++")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool verb()
{
    string s = sstr.get();
    if (s == "rules" || s == "fly" || s == "swim")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool subject()
{
    string s = sstr.get();
    if (s == "the")
    {
        return noun();
    }
    else
    {
        sstr.putback(s);
        return noun();
    }
}

bool sentence()
{
    return (subject() && verb());
}

int main()
{
    try
    {
        bool is_ok = false;
        while (true)
        {
            is_ok = sentence();
            if (!is_ok)
            {
                cout << "Not OK\n";
                return 0;
            }
            string s = sstr.get();
            if (s == ".")
            {
                cout << "OK\n";
                return 0;
            }
            else
            {
                sstr.putback(s);
                is_ok = conjunction();
                if (!is_ok)
                {
                    cout << "Not OK\n";
                    return 0;
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
