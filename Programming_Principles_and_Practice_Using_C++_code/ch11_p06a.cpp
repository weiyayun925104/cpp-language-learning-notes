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


class Punct_stream
{
public:
    Punct_stream(istream &is) : source(is), sensitive(true) { }

    void whitespace(const string &s)
    {
        white = s;
    }
    void add_white(char c)
    {
        white += c;
    }
    bool is_whitespace(char c);
    void case_sensitive(bool b)
    {
        sensitive = b;
    }
    bool is_case_sensitive()
    {
        return sensitive;
    }

    Punct_stream &operator>>(string &s);
    operator bool();
private:
    istream &source;
    istringstream buffer;
    string white;
    bool sensitive;
};

bool Punct_stream::is_whitespace(char c)
{
    for (int i = 0; i < white.size(); ++i)
    {
        if (c == white[i])
        {
            return true;
        }
    }
    return false;
}

Punct_stream::operator bool()
{
    return ( (buffer) || (source) );
}

Punct_stream &Punct_stream::operator>>(string &s)
{
    while (!(buffer >> s))
    {
        string line;

        if ( !( getline(source, line, '\n') ) )
        {
            return *this;
        }
        buffer.clear();

        for (int i = 0; i < line.size(); ++i)
        {
            if (is_whitespace(line[i]))
            {
                line[i] = ' ';
            }
            else if (!sensitive)
            {
                line[i] = tolower(line[i]);
            }
        }
        buffer.str(line);
    }
    return *this;
}

int main()
{
    try
    {
        Punct_stream ps(cin);
        ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
        ps.case_sensitive(false);

        cout << "please enter words\n";
        vector<string> vs;
        string word;
        while (ps >> word)
        {
            vs.push_back(word);
        }

        sort(vs.begin(), vs.end());
        for (int i = 0; i < vs.size(); ++i)
        {
            if (i == 0 || vs[i] != vs[i - 1])
            {
                cout << vs[i] << endl;
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
