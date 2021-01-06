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

const char print = ';';
const char number = '8';

class Token
{
public:
    char kind;
    double value;
    string name;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, double val) : kind(ch), value(val) { }
    Token(char ch, const string &n) : kind(ch), value(0), name(n) { }
};

class Token_stream
{
public:
    Token_stream();
    Token_stream(istream &is);
    Token_stream(istream &is, ostream &os);
    Token get();
    void putback(Token t);
    void ignore(char c);
    istream &get_istream();
    void set_istream(istream &is);
    ostream &get_ostream();
    void set_ostream(ostream &os);
private:
    bool full;
    Token buffer;
    istream *is_ptr;
    ostream *os_ptr;
};

Token_stream::Token_stream() : full(false), buffer(0), is_ptr(&cin), os_ptr(&cout) { }
Token_stream::Token_stream(istream &is) : full(false), buffer(0), is_ptr(&is), os_ptr(&cout) { }
Token_stream::Token_stream(istream &is, ostream &os) : full(false), buffer(0), is_ptr(&is), os_ptr(&os) { }
istream   &Token_stream::get_istream()
{
    return (*is_ptr);
}
void   Token_stream::set_istream(istream &is)
{
    is_ptr = &is;
}
ostream   &Token_stream::get_ostream()
{
    return (*os_ptr);
}
void   Token_stream::set_ostream(ostream &os)
{
    os_ptr = &os;
}
void Token_stream::putback(Token t)
{
    if (full)
    {
        error("putback() into a full buffer");
    }
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    (*is_ptr).get(ch);
    while (isspace(ch))
    {
        if (ch == '\n')
        {
            return Token(print);
        }
        (*is_ptr).get(ch);
    }

    switch (ch)
    {
    case print:
    case '{':
    case '}':
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
        return Token(ch);
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        (*is_ptr).putback(ch);
        double val;
        (*is_ptr) >> val;
        return Token(number, val);
    }
    default:
        error("Bad token");
    }
}

void Token_stream::ignore(char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while ((*is_ptr) >> ch)
    {
        if (ch == c)
        {
            return;
        }
    }
}

double expression(Token_stream &ts);

double primary(Token_stream &ts)
{
    Token t = ts.get();
    double d = 0;
    switch (t.kind)
    {
    case '(':
        d = expression(ts);
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' expected");
        }
        break;
    case '{':
        d = expression(ts);
        t = ts.get();
        if (t.kind != '}')
        {
            error("'}' expected");
        }
        break;
    case number:
        d = t.value;
        break;
    case '-':
        d = -primary(ts);
        break;
    case '+':
        d = primary(ts);
        break;
    default:
        error("primary expected");
    }

    return d;
}

double term(Token_stream &ts)
{
    double left = primary(ts);
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary(ts);
            t = ts.get();
            break;
        case '/':
        {
            double d = primary(ts);
            if (d == 0)
            {
                error("divide by zero");
            }
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary(ts);
            int i1 = int(left);
            if (i1 != left)
            {
                error("left-hand operand of % not int");
            }
            int i2 = int(d);
            if (i2 != d)
            {
                error("right-hand operand of % not int");
            }
            if (i2 == 0)
            {
                error("%: divide by zero");
            }
            left = i1 % i2;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression(Token_stream &ts)
{
    double left = term(ts);
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term(ts);
            t = ts.get();
            break;
        case '-':
            left -= term(ts);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double statement(Token_stream &ts)
{
    return expression(ts);
}

void clean_up_mess(Token_stream &ts)
{
    ts.ignore(print);
}

void calculate(Token_stream &ts)
{
    if (ts.get_istream())
    {
        try
        {
            Token t = ts.get();
            while (t.kind == print)
            {
                t = ts.get();
            }
            ts.putback(t);
            ostream &file_out = ts.get_ostream();
            file_out << statement(ts);
        }
        catch(exception &e)
        {
            cerr << e.what() << endl;
            clean_up_mess(ts);
        }
    }
}

string calculateStr(const string &s)
{
    cout << '(' << s << ')' << endl;
    istringstream iss(s + print);
    ostringstream oss;
    Token_stream ts(iss, oss);
    calculate(ts);
    return oss.str();
}

string evalParenthesesExpression(const string &expression)
{
    std::stack<char> stk;
    for (const auto &c : expression)
    {
        if (c == ')')
        {
            string str;
            while (!stk.empty() && stk.top() != '(')
            {
                str += stk.top();
                stk.pop();
            }
            if (stk.empty())
            {
                std::cerr << "Error: parentheses not match in expression: "
                          << expression << std::endl;
                return "";
            }
            stk.pop();
            str = calculateStr(string(str.rbegin(), str.rend()));
            for (const auto &e : str)
                stk.push(e);
        }
        else
        {
            stk.push(c);
        }
    }
    string str;
    while (!stk.empty())
    {
        if (stk.top() == '(')
        {
            std::cerr << "Error: parentheses not match in expression: "
                      << expression << std::endl;
            return "";
        }
        str += stk.top();
        stk.pop();
    }
    str = calculateStr(string(str.rbegin(), str.rend()));
    return str;
}

int main(int argc, const char *argv[])
{
    try
    {
        std::cout << evalParenthesesExpression("12+34-56-((78-9)+10)") << std::endl;
        std::cout << evalParenthesesExpression("(12+34)-(56-((78-9)+10))") << std::endl;
        std::cout << evalParenthesesExpression("3+2*(8/4)+(15/(3+(4/(234+23)+8)/2))") << std::endl;

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
