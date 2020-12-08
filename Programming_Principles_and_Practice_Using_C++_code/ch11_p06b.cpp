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

void to_lowercase(string &s)
{
    if (s.size() == 0) { return; }
    for (int i = 0; i < s.size(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

void remove_punct(string &s)
{
    if (s.size() == 0) { return; }
    for (int i = 0; i < s.size(); ++i)
    {
        if (ispunct(s[i]) && s[i] != '\'' && s[i] != '-') { s[i] = ' '; }
    }
}

void remove_hyphen(string &s)
{
    if (s.size() == 0) { return; }
    if (s.size() >= 2 && s[0] == '-' && s[1] == ' ') { s[0] = ' '; }
    if (s.size() >= 2 && s[s.size() - 1] == '-' && s[s.size() - 2] == ' ') { s[s.size() - 1] = ' '; }
    for (int i = 1; i < s.size() - 1; ++i)
    {
        if (s[i] == '-' && s[i - 1] == ' ' && s[i + 1] == ' ') { s[i] = ' '; }
        if (s[i] == '-' && s[i + 1] == '-')
        {
            s[i] = ' ';
            s[i + 1] = ' ';
            ++i;
        }
    }
}

void expand_aux(string &s)
{
    if (s.size() == 0) { return; }
    istringstream is(s);
    string word;
    string s_exp;
    ostringstream os(s_exp);
    while (is >> word)
    {
        if (word.size() >= 5
                 && word[word.size() - 3] == 'n'
                 && word[word.size() - 2] == '\''
                 && word[word.size() - 1] == 't')
        {
            for (int i = 0; i < word.size() - 3; ++i)
            {
                os << word[i];
            }
            os << " not";
        }
        else { os << word; }
        os << ' ';
    }
    s = os.str();
}

void convert_file(const string &iname, const string &oname)
{
    ifstream ifs(iname.c_str());
    if (!ifs) { error("can't open input file " + iname); }
    ofstream ofs(oname.c_str());
    if (!ofs) { error("can't open output file " + oname); }

    string s;
    while (getline(ifs, s, '\n'))
    {
        to_lowercase(s);
        remove_punct(s);
        remove_hyphen(s);
        expand_aux(s);
        ofs << s << endl;
    }
}

void build_dict(const string &iname, const string &oname)
{
    ifstream ifs(iname.c_str());
    if (!ifs) { error("can't open input file " + iname); }
    ofstream ofs(oname.c_str());
    if (!ofs) { error("can't open output file " + oname); }

    vector<string> vs;
    string word;
    while (ifs >> word)
    {
        vs.push_back(word);
    }

    sort(vs.begin(), vs.end());
    for (int i = 0; i < vs.size(); ++i)
    {
        if (i == 0 || vs[i] != vs[i - 1]) { ofs << vs[i] << endl; }
    }
}

int main()
{
    try
    {
        cout << "Enter input file name: ";
        string iname;
        cin >> iname;
        cout << "Enter output file name: ";
        string oname;
        cin >> oname;
        convert_file(iname, oname);
        cout << "Enter name for dictionary file: ";
        string dname;
        cin >> dname;
        build_dict(oname, dname);
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
