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
using std::numeric_limits;
using std::common_type;

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

typedef vector<char> Line;

class Text_iterator;

class Document
{
public:
    list<Line> line;

    Document();

    Text_iterator begin();
    Text_iterator end();

    Text_iterator erase(Text_iterator pos);
    Text_iterator insert(Text_iterator pos, char ch);
    void concat(Text_iterator &pos);
    void break_ln(Text_iterator pos);
    void find_replace(const string &find_str, const string &repl_str);
};

class Text_iterator
{
private:
    Document &doc;
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    Text_iterator(Document &d, list<Line>::iterator l, Line::iterator p) : doc(d), ln(l), pos(p) { }
    Text_iterator(const Text_iterator &other) : doc(other.doc), ln(other.ln), pos(other.pos) { }
    Text_iterator &operator=(const Text_iterator &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        doc = rhs.doc;
        ln = rhs.ln;
        pos = rhs.pos;
        return *this;
    }

    list<Line>::iterator get_line()
    {
        return ln;
    }
    Line::iterator get_pos()
    {
        return pos;
    }

    char &operator*()
    {
        return *pos;
    }
    Text_iterator &operator++();

    bool operator==(const Text_iterator &other) const
    {
        return ln == other.ln && pos == other.pos;
    }
    bool operator!=(const Text_iterator &other) const
    {
        return !(*this == other);
    }
};

Text_iterator &Text_iterator::operator++()
{
    if (ln == doc.line.end())
    {
        return *this;
    }
    list<Line>::iterator last = doc.line.end();
    --last;
    if (ln == last && pos == (*ln).begin())
    {
        return *this;
    }
    if (pos != (*ln).end())
    {
        ++pos;
    }
    if (pos == (*ln).end())
    {
        if (ln != last)
        {
            ++ln;
            pos = (*ln).begin();
        }
    }
    return *this;
}

template<typename Iter>
bool my_match(Iter first, Iter last, const string &s)
{
    if (first == last)
    {
        return false;
    }
    if (s.size() == 0)
    {
        return false;
    }
    string::const_iterator s_itr = s.begin();
    while (first != last && s_itr != s.end())
    {
        if (*first != *s_itr)
        {
            return false;
        }
        ++first;
        ++s_itr;
    }
    if (first == last && s_itr != s.end())
    {
        return false;
    }
    return true;
}

template<typename Iter, typename T>
Iter my_find(Iter first, Iter last, const T &val)
{
    Iter p = first;
    while (p != last)
    {
        if (*p == val)
        {
            return p;
        }
        ++p;
    }
    return p;
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string &s)
{
    if (first == last)
    {
        return last;
    }
    if (s.size() == 0)
    {
        return last;
    }
    char first_char = s[0];
    while (true)
    {
        Text_iterator p = my_find<Text_iterator, char>(first, last, first_char);
        if (p == last)
        {
            return last;
        }
        if (my_match<Text_iterator>(p, last, s))
        {
            return p;
        }
        first = ++p;
    }
}

Document::Document()
{
    line.push_back(Line());
}
Text_iterator Document::begin()
{
    return Text_iterator(*this, line.begin(), (* ( line.begin() ) ).begin());
}
Text_iterator Document::end()
{
    list<Line>::iterator last = line.end();
    --last;
    return Text_iterator(*this, last, (*last).begin());
}

Text_iterator Document::erase(Text_iterator pos)
{
    list<Line>::iterator list_it = pos.get_line();
    Line::iterator line_it = pos.get_pos();
    line_it = (*list_it).erase(line_it);
    return Text_iterator(*this, list_it, line_it);
}

Text_iterator Document::insert(Text_iterator pos, char ch)
{
    list<Line>::iterator list_it = pos.get_line();
    Line::iterator line_it = pos.get_pos();
    line_it = (*list_it).insert(line_it, ch);
    return Text_iterator(*this, list_it, line_it);
}

void Document::concat(Text_iterator &pos)
{
    list<Line>::iterator cur_line = pos.get_line();
    Line::iterator line_pos = pos.get_pos();
    Line::size_type index = line_pos - (*cur_line).begin();
    list<Line>::iterator nxt_line = cur_line;
    ++nxt_line;
    list<Line>::iterator last = line.end();
    --last;
    if (nxt_line != last && (*nxt_line).begin() != (*nxt_line).end())
    {
        (*cur_line).insert((*cur_line).end(), (*nxt_line).begin(), (*nxt_line).end());
        pos = Text_iterator(*this, cur_line, (*cur_line).begin() + index);
        line.erase(nxt_line);
    }
}

void Document::break_ln(Text_iterator pos)
{
    list<Line>::iterator cur_line = pos.get_line();
    list<Line>::iterator nxt_line = cur_line;
    ++nxt_line;
    list<Line>::iterator last = line.end();
    --last;
    if (pos.get_pos() + 1 != (*cur_line).end())
    {
        if (nxt_line == last)
        {
            line.push_back(Line());
        }
        (*nxt_line).insert((*nxt_line).begin(), pos.get_pos() + 1, (*cur_line).end());
        (*cur_line).erase(pos.get_pos() + 1, (*cur_line).end());
    }
}

void Document::find_replace(const string &find_str, const string &repl_str)
{
    if (begin() == end())
    {
        return ;
    }
    if (find_str.size() == 0)
    {
        return ;
    }
    Text_iterator pos = find_txt(begin(), end(), find_str);
    while (pos != end())
    {
        string::const_iterator find_it = find_str.begin();
        string::const_iterator repl_it = repl_str.begin();
        while (find_it != find_str.end() && repl_it != repl_str.end())
        {
            if (*find_it != *repl_it)
            {
                *pos = *repl_it;
                if (*find_it == '\n')
                {
                    concat(pos);
                }
                if (*repl_it == '\n')
                {
                    break_ln(pos);
                }
            }
            ++pos;
            ++find_it;
            ++repl_it;
        }

        while (find_it != find_str.end())
        {
            list<Line>::iterator cur_line = pos.get_line();
            if (*pos == '\n')
            {
                concat(pos);
            }
            else if (*pos != '\n' && (*cur_line).size() == 1)
            {
                concat(pos);
            }
            pos = erase(pos);
            cur_line = pos.get_line();
            if ((*cur_line).size() == 0)
            {
                line.erase(cur_line);
                pos = end();
                break;
            }
            ++find_it;
        }

        while (repl_it != repl_str.end())
        {
            list<Line>::iterator cur_line = pos.get_line();
            list<Line>::iterator last = line.end();
            --last;
            if (cur_line == last)
            {
                line.push_back(Line());
            }
            pos = insert(pos, *repl_it);
            if (*repl_it == '\n')
            {
                break_ln(pos);
            }
            ++pos;
            ++repl_it;
        }

        pos = find_txt(pos, end(), find_str);
    }
}

istream &operator>>(istream &is, Document &d)
{
    char ch;
    while (is.get(ch))
    {
        d.line.back().push_back(ch);
        if (ch == '\n')
        {
            d.line.push_back(Line());
        }
    }
    if (d.line.back().size() > 0)
    {
        d.line.push_back(Line());
    }
    return is;
}

void print(Document &d, Text_iterator p)
{
    for ( ; p != d.end(); ++p)
    {
        cout << *p;
    }
    cout << "\n";
}

int char_count(Document &d)
{
    Text_iterator iter = d.begin();
    int ctr = 0;
    while (iter != d.end())
    {
        ++iter;
        ++ctr;
    }
    return ctr;
}

int file_word_count(const string &fname)
{
    ifstream ifs(fname.c_str());
    if (!ifs)
    {
        error("can't open file " + fname);
    }
    string s;
    int ctr = 0;
    while (ifs >> s)
    {
        ++ctr;
    }
    return ctr;
}

int word_count1(Document &d)
{
    Text_iterator p = d.begin();
    string fname = "ch20_p06_tmp1.txt";
    ofstream ofs(fname.c_str());
    if (!ofs)
    {
        error("can't open file " + fname);
    }
    while (p != d.end())
    {
        ofs << *p;
        ++p;
    }
    ofs.close();

    int ctr = file_word_count(fname);
    return ctr;
}

int word_count2(Document &d)
{
    Text_iterator p = d.begin();
    string fname = "ch20_p06_tmp2.txt";
    ofstream ofs(fname.c_str());
    if (!ofs)
    {
        error("can't open file " + fname);
    }
    while (p != d.end())
    {
        if (isalpha(*p))
        {
            ofs << *p;
        }
        else
        {
            ofs << ' ';
        }
        ++p;
    }
    ofs.close();

    int ctr = file_word_count(fname);
    return ctr;
}

bool is_whitespace(char c, const string &white)
{
    for (int i = 0; i < white.size(); ++i)
    {
        if (white[i] == c)
        {
            return true;
        }
    }
    return false;
}

int word_count3(Document &d, const string &white)
{
    Text_iterator p = d.begin();
    string fname = "ch20_p06_tmp3.txt";
    ofstream ofs(fname.c_str());
    if (!ofs)
    {
        error("can't open file " + fname);
    }
    while (p != d.end())
    {
        if (is_whitespace(*p, white))
        {
            ofs << ' ';
        }
        else
        {
            ofs << *p;
        }
        ++p;
    }
    ofs.close();

    int ctr = file_word_count(fname);
    return ctr;
}

int main()
{
    try
    {
        string ifname = "ch20_p06_in.txt";
        ifstream ifs(ifname.c_str());
        if (!ifs)
        {
            error("can't open file " + ifname);
        }
        Document my_doc;
        ifs >> my_doc;
        print(my_doc, my_doc.begin());

        cout << "\nSearching for string 'wrong':\n";
        string f_str = "wrong";
        Text_iterator p = find_txt(my_doc.begin(), my_doc.end(), f_str);
        if (p == my_doc.end())
        {
            cout << "not found";
        }
        else
        {
            print(my_doc, p);
        }

        cout << "\nReplace 'wrong' with 'HelloWorld':\n";
        f_str = "wrong";
        string r_str = "HelloWorld";
        my_doc.find_replace(f_str, r_str);
        print(my_doc, my_doc.begin());


        cout << "\nNumber of characters in this document: "
             << char_count(my_doc) << "\n";

        cout << "Number of words (whitespace-separated) in this document: "
             << word_count1(my_doc) << "\n";

        cout << "Number of words (sequences of alphabetic characters) in this "
             << "document: " << word_count2(my_doc) << "\n";

        cout << "Number of words separated by whitespace or \".!'\" in this "
             << "document: " << word_count3(my_doc, ".!'") << "\n";
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
