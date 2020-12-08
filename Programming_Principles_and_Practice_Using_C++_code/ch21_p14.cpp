#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
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
#include <limits>
#include <type_traits>
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
using std::set;
using std::multiset;
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
using std::copy_if;
using std::count_if;
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
using std::left;
using std::numeric_limits;
using std::common_type;
using std::reverse;

inline void error(const string &errormessage)
{
    cerr << errormessage << endl;
    throw runtime_error(errormessage);
}

int nrand_one(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

int nrand_two(int m, int n, mt19937 &e)
{
    if (n <= m)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(m, n - 1);
    return d(e);
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

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    if (v.size() > 0)
    {
        os << "{ ";
        os << v[0];

        for (typename vector<T>::size_type i = 1; i < v.size(); i++)
        {
            os << ", " << v[i];
        }

        os << " }";
    }

    return os;
}

template<typename T>
istream &operator>>(istream &is, vector<T> &d)
{
    char ch1;
    char ch2;
    T temp;
    vector<T> v_temp;
    is >> ch1;
    if (!is)
    {
        return is;
    }
    if (ch1 != '{')
    {
        is.clear(ios_base::failbit);
        return is;
    }
    while (is >> temp && is >> ch2)
    {
        if (ch2 == ',')
        {
            v_temp.push_back(temp);
        }
        else if (ch2 == '}')
        {
            v_temp.push_back(temp);
            d = v_temp;
            return is;
        }
        else
        {
            is.clear(ios_base::failbit);
            return is;
        }
    }

    return is;
}


namespace Text_query
{
    map<string, int> clean_txt(const string &fname);
    int num_of_occurrences(const string &word, const map<string, int> &clean_txt);
    string most_frequent(const map<string, int> &clean_txt);
    string longest(const map<string, int> &clean_txt);
    string shortest(const map<string, int> &clean_txt);

    class First_char
    {
    private:
        char ch;
    public:
        First_char(char c) : ch(c) { }
        bool operator()(const pair<string, int> &p) const
        {
            return p.first[0] == ch;
        }
    };

    vector<string> start_with(char ch, const map<string, int> &clean_txt);

    class Length
    {
    private:
        int n;
    public:
        Length(int nn) : n(nn) { }
        bool operator()(const pair<string, int> &p) const
        {
            return p.first.size() == n;
        }
    };

    vector<string> has_length(int n, const map<string, int> &clean_txt);
}

namespace Text_query
{
    map<string, int> clean_txt(const string &fname)
    {
        ifstream ifs(fname);
        if (!ifs)
        {
            error("Can not open file " + fname);
        }
        ostringstream oss;

        char ch;
        while (ifs.get(ch))
        {
            if (ispunct(ch) && ch != '\'')
            {
                ch = ' ';
            }
            oss << char(tolower(ch));
        }

        map<string, int> words;
        istringstream iss(oss.str());
        string w;
        while (iss >> w)
        {
            if (w == "can't")
            {
                ++words["cannot"];
            }
            else if (w == "shan't")
            {
                ++words["shall"];
                ++words["not"];
            }
            else if (w == "won't")
            {
                ++words["will"];
                ++words["not"];
            }
            else if (w == "let's")
            {
                ++words["let"];
                ++words["us"];
            }
            else if (w == "'" || w.size() == 2 && w[0] == '\'')
            {
                // do nothing, don't add word
            }
            else if (w.size() >= 3 && *(w.end() - 2) == '\'')
            {
                switch (w.back())
                {
                case 'd':
                    ++words["would"];
                    ++words[w.substr(0, w.size() - 2)];
                    break;
                case 'm':
                    ++words["am"];
                    ++words[w.substr(0, w.size() - 2)];
                    break;
                case 's':
                    ++words["is"];
                    ++words[w.substr(0, w.size() - 2)];
                    break;
                case 't':
                    ++words["not"];
                    ++words[w.substr(0, w.size() - 3)];
                    break;
                default:
                    break;
                }
            }
            else if (w.size() >= 4 && *(w.end() - 3) == '\'')
            {
                switch (*(w.end() - 2))
                {
                case 'l':
                    ++words["will"];
                    ++words[w.substr(0, w.size() - 3)];
                    break;
                case 'r':
                    ++words["are"];
                    ++words[w.substr(0, w.size() - 3)];
                    break;
                case 'v':
                    ++words["have"];
                    ++words[w.substr(0, w.size() - 3)];
                    break;
                default:
                    break;
                }
            }
            else
            {
                ++words[w];
            }
        }

        typedef map<string, int>::iterator Iter;
        for (Iter p = words.begin(); p != words.end(); ++p)
        {
            Iter q = p;
            ++q;
            if (q != words.end() && q->first[0] == p->first[0]
                    && q->first.size() == p->first.size() + 1
                    && q->first == p->first + "s")
            {
                q = words.erase(q);
            }
        }

        return words;
    }

    int num_of_occurrences(const string &word, const map<string, int> &clean_txt)
    {
        if (clean_txt.find(word) != clean_txt.end())
        {
            return clean_txt.at(word);
        }
        else
        {
            return 0;
        }
    }

    string most_frequent(const map<string, int> &clean_txt)
    {
        string s;
        int max = 0;
        typedef map<string, int>::const_iterator Iter;
        for (Iter p = clean_txt.begin(); p != clean_txt.end(); ++p)
        {
            if (p->second > max)
            {
                max = p->second;
                s = p->first;
            }
        }
        return s;
    }

    string longest(const map<string, int> &clean_txt)
    {
        string s;
        int l_max = 0;
        typedef map<string, int>::const_iterator Iter;
        for (Iter p = clean_txt.begin(); p != clean_txt.end(); ++p)
        {
            if (p->first.length() > l_max)
            {
                l_max = p->first.length();
                s = p->first;
            }
        }
        return s;
    }

    string shortest(const map<string, int> &clean_txt)
    {
        string s;
        typedef map<string, int>::const_iterator Iter;
        Iter p = clean_txt.begin();
        s = p->first;
        int l_min = p->first.length();
        ++p;
        for (; p != clean_txt.end(); ++p)
        {
            if (p->first.length() < l_min)
            {
                l_min = p->first.length();
                s = p->first;
            }
        }
        return s;
    }

    vector<string> start_with(char ch, const map<string, int> &clean_txt)
    {
        int count = count_if(clean_txt.begin(), clean_txt.end(), First_char(ch));
        vector<pair<string, int>> vp(count);
        copy_if(clean_txt.begin(), clean_txt.end(), vp.begin(), First_char(ch));
        vector<string> vs;
        for (int i = 0; i < vp.size(); ++i)
        {
            vs.push_back(vp[i].first);
        }
        return vs;
    }

    vector<string> has_length(int n, const map<string, int> &clean_txt)
    {
        int count = count_if(clean_txt.begin(), clean_txt.end(), Length(n));
        vector<pair<string, int>> vp(count);
        copy_if(clean_txt.begin(), clean_txt.end(), vp.begin(), Length(n));
        vector<string> vs;
        for (int i = 0; i < vp.size(); ++i)
        {
            vs.push_back(vp[i].first);
        }
        return vs;
    }
}

void print_menu()
{
    cout << "What would you like to do?\n"
         << "1 - Enter input file name\n"
         << "2 - Get number of occurrences of a word\n"
         << "3 - Get most frequent word\n"
         << "4 - Get longest word\n"
         << "5 - Get shortest word\n"
         << "6 - Get words starting with a specific letter\n"
         << "7 - Get words of a specific length\n"
         << "0 - Exit\n";
}

string get_ifname()
{
    cout << "\nEnter input file name: ";
    string s;
    cin >> s;
    cout << '\n';
    return s;
}

bool file_check(const string &fname)
{
    if (fname == "")
    {
        cout << "\nFile name is empty!\n\n";
        return false;
    }

    ifstream ifs(fname.c_str());
    if (!ifs)
    {
        cout << "\nFile " << fname << " doesn't exist!\n\n";
        return false;
    }

    return true;
}

void get_n_occurrences(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    cout << "\nEnter word: ";
    string s;
    cin >> s;
    int n = Text_query::num_of_occurrences(s, clean_txt);
    cout << "\n\'" << s << "\' occurs " << n << " time" << (n == 1 ? "" : "s") << ".\n\n";
}

void get_most_frequent(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    string s = Text_query::most_frequent(clean_txt);
    cout << "\nThe most frequent word is \'" << s << "\'.\n\n";
}

void get_longest(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    string s = Text_query::longest(clean_txt);
    cout << "\nThe longest word is \'" << s << "\'.\n\n";
}

void get_shortest(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    string s = Text_query::shortest(clean_txt);
    cout << "\nThe shortest word is \'" << s << "\'.\n\n";
}

void get_start_with(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    cout << "\nEnter character: ";
    char ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> vs = Text_query::start_with(ch, clean_txt);
    cout << "\nWords starting with '" << ch << "':\n";
    for (int i = 0; i < vs.size(); ++i)
    {
        cout << vs[i] << '\n';
    }
    cout << '\n';
}

void get_has_length(const map<string, int> &clean_txt)
{
    if (clean_txt.size() == 0)
    {
        cout << "\nNo text loaded!\n\n";
        return;
    }
    cout << "\nEnter number of characters: ";
    int n;
    while (!( cin >> n))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPlease enter a number\n";
        cout << "\nEnter number of characters: ";
    }
    vector<string> vs = Text_query::has_length(n, clean_txt);
    cout << "\nWords with " << n << " characters:\n";
    for (int i = 0; i < vs.size(); ++i)
    {
        cout << vs[i] << '\n';
    }
    cout << '\n';
}

int main()
{
    try
    {
        string ifname;
        map<string, int> words;

        bool keep_running = true;
        while (keep_running)
        {
            print_menu();
            int n;
            while (!(cin >> n))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPlease enter a number\n";
                print_menu();
            }
            switch (n)
            {
            case 0:
                keep_running = false;
                break;
            case 1:
                ifname = get_ifname();
                if (file_check(ifname))
                {
                    words = Text_query::clean_txt(ifname);
                }
                break;
            case 2:
                get_n_occurrences(words);
                break;
            case 3:
                get_most_frequent(words);
                break;
            case 4:
                get_longest(words);
                break;
            case 5:
                get_shortest(words);
                break;
            case 6:
                get_start_with(words);
                break;
            case 7:
                get_has_length(words);
                break;
            default:
                cout << "\nEnter a number between 0 and 7\n\n";
                break;
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
