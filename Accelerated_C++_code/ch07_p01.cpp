#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include <utility>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::vector;
using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::getline;
using std::find_if;
using std::search;
using std::copy;
using std::transform;
using std::inserter;
using std::logic_error;
using std::domain_error;

typedef std::vector<std::string> Rule;
typedef std::vector<Rule> Rule_collection;
typedef std::map<std::string, Rule_collection> Grammar;

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

pair<int, string> flip_count_pair(pair<string, int> p) 
{
  return pair<int, string>(p.second, p.first);
}

istream& count_sort_words(istream& is, ostream& os)
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

vector<string> gen_sentence(const Grammar &g)
{
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);

    return ret;
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

int test_xref()
{
    string file = "grammar_ch07.txt";
    ifstream infile;
    infile.open(file);
    map<string, vector<int> > ret = xref(infile, split);
    infile.close();
    infile.clear();

    for (map<string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it)
    {
        cout << it->first << " occurs on line(s): ";
        const vector<int> &v = it->second;
        copy(v.begin(), v.end(), std::ostream_iterator<int, char>(cout, " "));
        cout << endl;
    }

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

int main()
{
    test_xref();
    cout << endl;
    test_generate_sentence();
    cout << endl;
    test_count_words();
    return 0;
}
