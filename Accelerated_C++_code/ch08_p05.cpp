#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <utility>
#include <chrono>
#include <random>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::stringstream;
using std::vector;
using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::list;
using std::getline;
using std::find_if;
using std::search;
using std::copy;
using std::sort;
using std::transform;
using std::accumulate;
using std::inserter;
using std::istream_iterator;
using std::ostream_iterator;
using std::back_inserter;
using std::logic_error;
using std::domain_error;
using std::to_string;
using std::distance;
using std::unique;
using std::mt19937;
using std::uniform_int_distribution;

typedef std::vector<std::string> Rule;
typedef std::vector<Rule> Rule_collection;
typedef std::map<std::string, Rule_collection> Grammar;

template<typename T>
T median(vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;
    vec_sz size = v.size();
    if (size == 0)
    {
        throw domain_error("median of empty vector");
    }
    sort(v.begin(), v.end());

    vec_sz mid = size / 2;
    return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

double average(const vector<double> &v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
    {
        throw domain_error("Argument to nrand is out of range");
    }

    const int bucket_size = RAND_MAX / n;
    int r;

    do
    {
        r = rand() / bucket_size;
    }
    while (r >= n);

    return r;
}

int nrand_improved(int n, mt19937 &e)
{
    if (n <= 0)
    {
        throw domain_error("Argument to nrand is out of range");
    }
    uniform_int_distribution<int> d(0, n - 1);
    return d(e);
}

istream &count_words(istream &is, ostream &os)
{
    string s;
    map<string, int> counters;

    while (is >> s)
    {
        ++counters[s];
    }

    for (map<string, int>::const_iterator it = counters.begin(); it != counters.end(); ++it)
    {
        os << it->first << "\t" << it->second << endl;
    }

    return is;
}

pair<int, string> flip_count_pair(const pair<string, int> &p)
{
    return pair<int, string>(p.second, p.first);
}

istream &count_sort_words(istream &is, ostream &os)
{
    string s;
    map<string, int> counters;

    while (is >> s)
    {
        ++counters[s];
    }

    multimap<int, string> counters_r;
    transform(counters.begin(), counters.end(), inserter(counters_r, counters_r.begin()), flip_count_pair);

    for (multimap<int, string>::const_iterator it = counters_r.begin(); it != counters_r.end(); ++it)
    {
        os << it->second << "\t" << it->first << endl;
    }

    return is;
}

bool space(char c)
{
    return isspace(c) != 0;
}

bool not_space(char c)
{
    return !isspace(c);
}

vector<string> split(const string &str)
{
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end())
    {

        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);

        if (i != j)
        {
            ret.push_back(string(i, j));
            i = j;
        }
    }
    return ret;
}

list<string> split_to_list(const string &str)
{
    vector<string> ret = split(str);
    list <string> list;
    copy(ret.begin(), ret.end(), back_inserter(list));

    return list;
}

template <typename T>
void split(const string &str, T os)
{
    typedef string::const_iterator iter;
    iter i = str.begin();
    while (i != str.end())
    {
        i = std::find_if(i, str.end(), not_space);

        iter j = std::find_if(i, str.end(), space);

        if (i != j)
        {
            *os++ = string(i, j);
            i = j;
        }
    }
}

map<string, vector<int> > xref(istream &in, vector<string> find_words(const string &))
{
    string line;
    int line_number = 0;
    map<string, vector<int> > ret;

    while (getline(in, line, '\n'))
    {
        ++line_number;

        vector<string> words = find_words(line);

        for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
        {
            ret[*it].push_back(line_number);
        }
    }

    return ret;
}

map<string, vector<int> > xref_unique(istream &in, vector<string> find_words(const string &))
{
    string line;
    int line_number = 0;
    map<string, vector<int> > ret;

    while (getline(in, line, '\n'))
    {
        ++line_number;

        vector<string> words = find_words(line);

        for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it)
        {
            ret[*it].push_back(line_number);
        }
    }

    for (map<string, vector<int> >::iterator it = ret.begin(); it != ret.end(); ++it)
    {
        it->second.resize( distance(it->second.begin(), unique(it->second.begin(), it->second.end()) ) );
    }

    return ret;
}

template <typename Out>
void xref_uniq(istream &in, Out os, vector<string> find_words(const string &))
{
    const map<string, vector<int> > ret = xref_unique(in, find_words);

    for (map<string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it)
    {
        stringstream ss;
        ss << it->first << " occurs on line(s): ";

        vector<int>::const_iterator line_it = it->second.begin();
        ss << *line_it++;

        while (line_it != it->second.end())
        {
            ss << ", " << *line_it++;
        }

        *os++ = ss.str();
    }

    in.clear();
    in.seekg(0, std::ios::beg);
}

bool bracketed(const string &s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

Grammar read_grammar(istream &in)
{
    Grammar ret;
    string line;

    while (getline(in, line, '\n'))
    {
        vector<string> entry = split(line);

        if (entry.size() > 1)
        {
            ret[entry[0]].push_back( Rule( entry.begin() + 1, entry.end() ) );
        }
    }

    return ret;
}

Grammar read_grammar_list(istream &in)
{
    Grammar ret;
    string line;

    while (getline(in, line, '\n'))
    {
        list<string> entry = split_to_list(line);

        if (entry.size() > 1)
        {
            ret[entry.front()].push_back( Rule( ++entry.begin(), entry.end() ) );
        }
    }

    return ret;
}
void gen_aux(const Grammar &g, const string &word, vector<string> &ret)
{
    if (!bracketed(word))
    {
        ret.push_back(word);
    }
    else
    {
        Grammar::const_iterator it = g.find(word);

        if (it == g.end())
        {
            throw logic_error("empty rule");
        }

        const Rule_collection &c = it->second;

        const Rule &r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
        {
            gen_aux(g, *i, ret);
        }
    }
}

void gen_aux(const Grammar &g, const string &word, list<string> &ret)
{
    if (!bracketed(word))
    {
        ret.push_back(word);
    }
    else
    {
        Grammar::const_iterator it = g.find(word);

        if (it == g.end())
        {
            throw logic_error("empty rule");
        }

        const Rule_collection &c = it->second;

        const Rule &r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
        {
            gen_aux(g, *i, ret);
        }
    }
}

template <typename Out>
void gen_aux(const Grammar &g, const string &word, Out os)
{
    if (!bracketed(word))
    {
        *os++ = word;
    }
    else
    {
        Grammar::const_iterator it = g.find(word);

        if (it == g.end())
        {
            throw logic_error("empty rule");
        }

        const Rule_collection &c = it->second;

        const Rule &r = c[nrand(c.size())];

        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
        {
            gen_aux(g, *i, os);
        }
    }
}

vector<string> gen_sentence(const Grammar &g)
{
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);

    return ret;
}

list<string> gen_sentence_list(const Grammar &g)
{
    list<string> ret;
    gen_aux(g, "<sentence>", ret);

    return ret;
}

template <typename Out>
void gen_sentence(const Grammar &g, Out os)
{
    gen_aux(g, "<sentence>", os);
}

int generate_sentence_list_output(string file)
{
    ifstream infile;
    infile.open(file);
    list<string> sentence = gen_sentence_list(read_grammar_list(infile));
    infile.close();
    infile.clear();
    copy(sentence.begin(), sentence.end(), std::ostream_iterator<string, char>(cout, " "));
    cout << endl;

    return 0;
}

vector<string> gen_sentence_vectors(const Grammar &g)
{
    vector<string> ret;
    vector<string> rules;

    rules.push_back("<sentence>");

    while (!rules.empty())
    {
        string segment = rules.back();
        rules.pop_back();

        if (!bracketed(segment))
        {
            ret.push_back(segment);
        }
        else
        {

            Grammar::const_iterator it = g.find(segment);

            if (it == g.end())
            {
                throw logic_error("empty rule");
            }

            const Rule_collection &c = it->second;

            const Rule &r = c[nrand(c.size())];

            for (Rule::const_reverse_iterator i = r.rbegin(); i != r.rend(); ++i)
            {
                rules.push_back(*i);
            }
        }
    }

    return ret;
}

int generate_sentence_vectors_output(string file)
{
    ifstream infile;
    infile.open(file);
    vector<string> sentence = gen_sentence_vectors(read_grammar(infile));
    infile.close();
    infile.clear();
    copy(sentence.begin(), sentence.end(), std::ostream_iterator<string, char>(cout, " "));
    cout << endl;

    return 0;
}

int test_generate_sentence(string file)
{
    ifstream infile;
    infile.open(file);
    Grammar g = read_grammar(infile);

    vector<string> sentence_vector;
    list<string> sentence_list;

    gen_sentence(g, back_inserter(sentence_vector));
    gen_sentence(g, back_inserter(sentence_list));
    gen_sentence(g, ostream_iterator<string>(cout, " "));

    cout << endl;

    vector<string>::const_iterator itv = sentence_vector.begin();
    if (!sentence_vector.empty())
    {
        cout << *itv++;
    }
    while (itv != sentence_vector.end())
    {
        cout << " " << *itv++;
    }
    cout << endl;

    list<string>::const_iterator itl = sentence_list.begin();
    if (!sentence_list.empty())
    {
        cout << *itl++;
    }
    while (itl != sentence_list.end())
    {
        cout << " " << *itl++;
    }
    cout << endl;

    return 0;
}

bool not_url_char(char c)
{
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";

    return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
    static const string sep = "://";

    typedef string::const_iterator iter;

    iter i = b;

    while ( ( i = search(i, e, sep.begin(), sep.end()) ) != e )
    {

        if (i != b && i + sep.size() != e)
        {

            iter beg = i;
            while (beg != b && isalpha(beg[-1]))
            {
                --beg;
            }

            if (beg != i && !not_url_char( i[sep.size()] ))
            {
                return beg;
            }
        }

        i += sep.size();
    }

    return e;
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

vector<string> find_urls(const string &s)
{
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    while (b != e)
    {

        b = url_beg(b, e);

        if (b != e)
        {
            iter after = url_end(b, e);

            ret.push_back(string(b, after));

            b = after;
        }
    }

    return ret;
}

int print_formatted_xref(string file, size_t line_length)
{
    ifstream infile;
    infile.open(file);
    map<string, vector<int> > ret_uniq = xref_unique(infile, split);
    infile.close();
    infile.clear();

    for (map<string, vector<int> >::const_iterator it = ret_uniq.begin(); it != ret_uniq.end(); ++it)
    {
        string s = it->first + " occurs on line(s): ";
        string s_spaces(s.size(), ' ');

        vector<int>::const_iterator line_it = it->second.begin();

        while (line_it != it->second.end())
        {
            string nr = to_string(*line_it);

            if (line_it != it->second.end() - 1)
            {
                nr += ", ";
            }

            if (s.size() + nr.size() > line_length)
            {
                cout << s << endl;
                s = s_spaces + nr;
            }
            else
            {
                s += nr;
            }

            ++line_it;
        }

        if (s.size() > s_spaces.size())
        {
            cout << s << endl;
        }
    }

    return 0;
}

int print_formatted_line_xref(string file, size_t line_length)
{
    ifstream infile;
    infile.open(file);
    map<string, vector<int> > ret_uniq = xref_unique(infile, split);
    infile.close();
    infile.clear();

    for (map<string, vector<int> >::const_iterator it = ret_uniq.begin(); it != ret_uniq.end(); ++it)
    {
        string line = it->second.size() > 1 ? "lines" : "line";
        string s = it->first + " occurs on " + line + ": ";
        string s_spaces(s.size(), ' ');

        vector<int>::const_iterator line_it = it->second.begin();

        while (line_it != it->second.end())
        {
            string nr = to_string(*line_it);

            if (line_it != it->second.end() - 1)
            {
                nr += ", ";
            }

            if (s.size() + nr.size() > line_length)
            {
                cout << s << endl;
                s = s_spaces + nr;
            }
            else
            {
                s += nr;
            }

            ++line_it;
        }

        if (s.size() > s_spaces.size())
        {
            cout << s << endl;
        }
    }

    return 0;
}

int print_xref_urls(string file, size_t line_length)
{
    ifstream infile;
    infile.open(file);
    map<string, vector<int> > ret_uniq = xref_unique(infile, find_urls);
    infile.close();
    infile.clear();
    for (map<string, vector<int> >::const_iterator it = ret_uniq.begin(); it != ret_uniq.end(); ++it)
    {
        string line = it->second.size() > 1 ? "lines" : "line";
        string s = it->first + " occurs on " + line + ": ";
        string s_spaces(s.size(), ' ');

        vector<int>::const_iterator line_it = it->second.begin();

        while (line_it != it->second.end())
        {
            string nr = to_string(*line_it);

            if (line_it != it->second.end() - 1)
            {
                nr += ", ";
            }

            if (s.size() + nr.size() > line_length)
            {
                cout << s << endl;
                s = s_spaces + nr;
            }
            else
            {
                s += nr;
            }

            ++line_it;
        }

        if (s.size() > s_spaces.size())
        {
            cout << s << endl;
        }
    }

    return 0;
}

int test_xref()
{
    string file = "grammar_ch07.txt";
    ifstream infile;
    infile.open(file);
    map<string, vector<int> > ret = xref(infile, split);
    infile.close();
    infile.clear();
    infile.open(file);
    map<string, vector<int> > ret_uniq = xref_unique(infile, split);
    infile.close();
    infile.clear();

    for (map<string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it)
    {
        cout << it->first << " occurs on line(s): ";
        const vector<int> &v = it->second;
        copy(v.begin(), v.end(), std::ostream_iterator<int, char>(cout, " "));
        cout << endl;
    }
    cout << endl;
    for (map<string, vector<int> >::const_iterator it = ret_uniq.begin(); it != ret_uniq.end(); ++it)
    {
        cout << it->first << " occurs on line(s): ";
        const vector<int> &v = it->second;
        copy(v.begin(), v.end(), std::ostream_iterator<int, char>(cout, " "));
        cout << endl;
    }
    return 0;
}

int test_xref(string file)
{
    ifstream infile;
    infile.open(file);

    vector<string> xref_vector;
    list<string> xref_list;

    xref_uniq(infile, back_inserter(xref_vector), split);
    xref_uniq(infile, back_inserter(xref_list), split);
    xref_uniq(infile, ostream_iterator<string>(cout, "\n"), split);

    cout << endl;

    vector<string>::const_iterator itv = xref_vector.begin();
    if (!xref_vector.empty())
    {
        cout << *itv++ << endl;
    }
    while (itv != xref_vector.end())
    {
        cout << *itv++ << endl;
    }
    cout << endl;

    list<string>::const_iterator itl = xref_list.begin();
    if (!xref_list.empty())
    {
        cout << *itl++ << endl;
    }
    while (itl != xref_list.end())
    {
        cout << *itl++ << endl;
    }
    cout << endl;

    return 0;
}

int test_generate_sentence()
{
    string file = "grammar_ch07.txt";
    ifstream infile;
    infile.open(file);
    vector<string> sentence = gen_sentence(read_grammar(infile));
    infile.close();
    infile.clear();
    copy(sentence.begin(), sentence.end(), std::ostream_iterator<string, char>(cout, " "));
    cout << endl;
    return 0;
}

int test_count_words()
{
    string file = "grammar_ch07.txt";
    ifstream infile;
    infile.open(file);
    count_sort_words(infile, cout);
    infile.close();
    infile.clear();
    return 0;
}

int test_split()
{
    cout << "Enter lines to split: " << endl;
    string s;
    while (getline(cin, s, '\n') && s != "quit")
    {
        split(s, ostream_iterator<string, char>(cout, "\n"));
    }
    return 0;
}

void test_stream_iterators()
{
    cout << "Enter a few integers: ";

    vector<int> v;
    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));
    cout << endl;

    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test_median()
{
    vector<double> v_double = { 12.5, 16.3, 25.7 };
    cout << median(v_double) << endl;

    vector<int> v_int = { 12, 25, 16, 30 };
    cout << median(v_int) << endl;
}

int main()
{
    std::srand(std::time(nullptr));
    test_xref();
    cout << endl;
    test_generate_sentence();
    cout << endl;
    generate_sentence_list_output("grammar_ch07.txt");
    cout << endl;
    generate_sentence_vectors_output("grammar_ch07.txt");
    cout << endl;
    test_count_words();
    cout << endl;
    print_formatted_line_xref("grammar_ch07.txt", 60);
    cout << endl;
    print_xref_urls("urls_ch07.txt", 60);
    cout << endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 engine(seed);
    for (int i = 0; i < 10; i++)
    {
        cout << nrand_improved(100, engine) << endl;
    }
    cout << endl;
    test_median();
    test_stream_iterators();
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
    test_split();
    cout << endl;
    test_generate_sentence("grammar_ch07.txt");
    cout << endl;
    test_xref("grammar_ch07.txt");
    return 0;
}