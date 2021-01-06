#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <valarray>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
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
#include <initializer_list>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
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
using std::fstream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::array;
using std::valarray;
using std::vector;
using std::deque;
using std::list;
using std::forward_list;
using std::set;
using std::multiset;
using std::map;
using std::multimap;
using std::unordered_set;
using std::unordered_multiset;
using std::unordered_map;
using std::unordered_multimap;
using std::pair;
using std::stack;
using std::queue;
using std::priority_queue;
using std::string;
using std::getline;
using std::to_string;
using std::domain_error;
using std::runtime_error;
using std::exception;
using std::transform;
using std::back_inserter;
using std::istream_iterator;
using std::ostream_iterator;
using std::search;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::replace_if;
using std::max;
using std::min;
using std::swap;
using std::stable_partition;
using std::streamsize;
using std::streampos;
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
using std::ios;
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
using std::right;
using std::flush;
using std::numeric_limits;
using std::common_type;
using std::reverse;
using std::begin;
using std::end;
using std::initializer_list;
using std::function;
using std::bind;
using std::out_of_range;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::uninitialized_copy_n;
using std::uninitialized_fill_n;
using std::make_shared;
using std::make_unique;

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

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(const int &min, const int &max)
{
    return std::uniform_int_distribution<int> {min, max}(gen);
}


std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
{
    return (ctr > 1) ? word + ending : word;
}

class QueryResult;
std::ostream &print(std::ostream &, const QueryResult &);

class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::multiset<line_no>>> wm;
};

class QueryResult
{
    friend std::ostream &print(std::ostream &, const QueryResult &);
    friend std::ostream &print(std::ostream &, const QueryResult &, TextQuery::line_no, TextQuery::line_no);
public:
    QueryResult(const std::string &s,
                std::shared_ptr<std::multiset<TextQuery::line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) :
        sought(s), lines(p), file(f) { }

    std::multiset<TextQuery::line_no>::iterator begin() const
    {
        return lines->begin();
    }
    std::multiset<TextQuery::line_no>::iterator end() const
    {
        return lines->end();
    }
    std::shared_ptr<std::vector<std::string>> get_file() const
    {
        return file;
    }
private:
    std::string sought;
    std::shared_ptr<std::multiset<TextQuery::line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while(getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new std::multiset<line_no>);
            lines->insert(n);
        }
    }
}
QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::multiset<line_no>> nodata(new std::multiset<line_no>);
    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}
std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << std::endl;
    std::set<TextQuery::line_no> uniq_lines;
    for(auto num : * (qr.lines))
    {
        uniq_lines.insert(num);
    }
    for(auto num : uniq_lines)
        os << "(line " << num + 1 << "):" << std::endl
           << *((qr.file)->begin() + num) << std::endl;
    return os;
}
std::ostream &print(std::ostream &os, const QueryResult &qr, TextQuery::line_no min, TextQuery::line_no max)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << make_plural(qr.lines->size(), "time", "s") << std::endl;
    std::set<TextQuery::line_no> uniq_lines;
    for(auto num : * (qr.lines))
    {
        uniq_lines.insert(num);
    }
    for(auto num : uniq_lines)
    {
        if((num + 1) >= min && (num + 1) <= max)
        {
            os << "(line " << num + 1 << "):" << std::endl
               << *((qr.file)->begin() + num) << std::endl;
        }
        else if((num + 1) > max)
        {
            break;
        }
    }
    return os;
}

#define NDEBUG

class Query_base
{
    friend class Query;
protected:
    Query_base()
    {
#ifndef NDEBUG
        std::cerr << "Query_base::Query_base()" << std::endl;
#endif
    }
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual std::string rep() const = 0;
};

class Query
{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
public:
    Query(const std::string &);
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }
    std::string rep() const
    {
#ifndef NDEBUG
        std::cerr << "Query::rep()" << std::endl;
#endif
        return q->rep();
    }
private:
    Query(std::shared_ptr<Query_base> query) : q(query)
    {
#ifndef NDEBUG
        std::cerr << "Query::Query(shared_ptr<Query_base>)" << std::endl;
#endif
    }
    std::shared_ptr<Query_base> q;
};

std::ostream &operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}

class WordQuery : public Query_base
{
    friend class Query;
    WordQuery(const std::string &s) : query_word(s)
    {
#ifndef NDEBUG
        std::cerr << "WordQuery::WordQuery(const string&)" << std::endl;
#endif
    }
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    std::string rep() const
    {
#ifndef NDEBUG
        std::cerr << "WordQuery::rep()" << std::endl;
#endif
        return query_word;
    }
    std::string query_word;
};

inline Query::Query(const std::string &s) : q(new WordQuery(s))
{
#ifndef NDEBUG
    std::cerr << "Query::Query(const string&)" << std::endl;
#endif
}

class NotQuery : public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q)
    {
#ifndef NDEBUG
        std::cerr << "NotQuery::NotQuery(const Query)" << std::endl;
#endif
    }
    QueryResult eval(const TextQuery &) const;
    std::string rep() const
    {
#ifndef NDEBUG
        std::cerr << "NotQuery::rep()" << std::endl;
#endif
        return "~(" + query.rep() + ")";
    }
    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::multiset<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for(std::size_t n = 0; n != sz; ++n)
    {
        if (beg == end || *beg != n)
            ret_lines->insert(n);
        else
            ++beg;
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query &l, const Query &r, const std::string &s) :
        lhs(l), rhs(r), opSym(s)
    {
#ifndef NDEBUG
        std::cerr << "BinaryQuery::BinaryQuery(const Query&, const Query&, string)" << std::endl;
#endif
    }
    std::string rep() const
    {
#ifndef NDEBUG
        std::cerr << "BinaryQuery::rep()" << std::endl;
#endif
        return "(" + lhs.rep() + " "
               + opSym + " "
               + rhs.rep() + ")";
    }
    Query lhs, rhs;
    std::string opSym;
};

class AndQuery : public BinaryQuery
{
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "&")
    {
#ifndef NDEBUG
        std::cerr << "AndQuery::AndQuery(const Query&, const Query&)" << std::endl;
#endif
    }
    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::multiset<line_no>>();
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

class OrQuery : public BinaryQuery
{
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right) :
        BinaryQuery(left, right, "|")
    {
#ifndef NDEBUG
        std::cerr << "OrQuery::OrQuery(const Query&, const Query&)" << std::endl;
#endif
    }
    QueryResult eval(const TextQuery &) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::multiset<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}

inline bool is_cmd(const string &s)
{
    bool cmd = false;
    if(s.size() > 1 && s[0] == '$')
    {
        auto illegal_pos = s.substr(1).find_first_not_of("0123456789");
        cmd = (illegal_pos == string::npos);
    }
    return cmd;
}

Query get_query(vector<Query>::const_reverse_iterator beg, vector<Query>::const_reverse_iterator end, const string &s)
{
    if(is_cmd(s))
    {
        auto index = stoul(s.substr(1)) - 1;
        if(index < (end - beg))
            return *(beg + index);
        else
            throw out_of_range("index out of range!");
    }
    else
    {
        return Query(s);
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        if(argc != 2)
            return -1;
        ifstream is(argv[1]);
        TextQuery tq(is);
        cout << "Input 3 words or input q to quit:" << endl;
        string opt;
        vector<Query> his;
        while(getline(cin, opt) && opt != "q")
        {
            string sought1, sought2, sought3;
            istringstream istr(opt);
            istr >> sought1 >> sought2 >> sought3;
            try
            {
                Query q = get_query(his.crbegin(), his.crend(), sought1) &
                          get_query(his.crbegin(), his.crend(), sought2) |
                          get_query(his.crbegin(), his.crend(), sought3);
                his.push_back(q);
                QueryResult qr = q.eval(tq);
                TextQuery::line_no min, max;
                cout << "Input two numbers of range between 1 and " << qr.get_file()->size() << "\n";
                while(cin >> min >> max)
                {
                    cout << "Executing Query for: " << q << "\n";
                    print(cout, qr, min, max);
                    cout << "Input two numbers of range between 1 and " << qr.get_file()->size() << "\n";
                }
            }
            catch(out_of_range &err)
            {
                err.what();
            }
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
            cout << "Input 3 words or $ followed by a number representing the query history, or input q to quit:\n";
        }

        return 0;
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
