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
using std::fstream;
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
using std::accumulate;
using std::find;
using std::find_if;
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

class Roman_int
{
public:
    Roman_int();
    Roman_int(int n);
    int as_int() const;
    void set_val(int v);
private:
    int val;
};

// N = 0 I = 1 V = 5 X= 10 L= 50 C = 100 D = 500 M = 1000
const char N = 'N';
const char I = 'I';
const char V = 'V';
const char X = 'X';
const char L = 'L';
const char C = 'C';
const char D = 'D';
const char M = 'M';

bool is_valid_char(char ch);
int get_value(char ch);
bool counter_illegal(int counter, char ch);
int roman_int_to_int(const string &s);


Roman_int::Roman_int() : val(0) { }

Roman_int::Roman_int(int n) : val(n) { }

int Roman_int::as_int() const
{
    return val;
}

void Roman_int::set_val(int v)
{
    val = v;
}

Roman_int operator+(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() + r2.as_int());
}

Roman_int operator-(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() - r2.as_int());
}

Roman_int operator-(const Roman_int &r)
{
    return Roman_int(-r.as_int());
}

Roman_int operator*(const Roman_int &r1, const Roman_int &r2)
{
    return Roman_int(r1.as_int() * r2.as_int());
}

Roman_int operator/(const Roman_int &r1, const Roman_int &r2)
{
    if (r2.as_int() == 0)
    {
        error("division / by zero");
    }
    return Roman_int(r1.as_int() / r2.as_int());
}

Roman_int operator%(const Roman_int &r1, const Roman_int &r2)
{
    if (r2.as_int() == 0)
    {
        error("division % by zero");
    }
    return Roman_int(r1.as_int() % r2.as_int());
}

bool operator==(const Roman_int &r1, const Roman_int &r2)
{
    return r1.as_int() == r2.as_int();
}

bool operator!=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r1 == r2);
}

bool operator<(const Roman_int &r1, const Roman_int &r2)
{
    return r1.as_int() < r2.as_int();
}

bool operator>(const Roman_int &r1, const Roman_int &r2)
{
    return r2 < r1;
}

bool operator<=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r2 < r1);
}

bool operator>=(const Roman_int &r1, const Roman_int &r2)
{
    return !(r1 < r2);
}

bool is_valid_char(char ch)
{
    return ch == N || ch == I || ch == V || ch == X || ch == L || ch == C || ch == D || ch == M;
}

ostream &operator<<(ostream &os, const Roman_int &r)
{
    int val = r.as_int();
    if (val == 0)
    {
        return os << N;
    }
    if (val < 0)
    {
        os << '-';
        val = -val;
    }

    while (val >= 1000)
    {
        os << M;
        val -= 1000;
    }
    if (val >= 900)
    {
        os << C << M;
        val -= 900;
    }
    else if (val >= 500)
    {
        os << D;
        val -= 500;
    }
    else if (val >= 400)
    {
        os << C << D;
        val -= 400;
    }
    while (val >= 100)
    {
        os << C;
        val -= 100;
    }
    if (val >= 90)
    {
        os << X << C;
        val -= 90;
    }
    else if (val >= 50)
    {
        os << L;
        val -= 50;
    }
    else if (val >= 40)
    {
        os << X << L;
        val -= 40;
    }
    while (val >= 10)
    {
        os << X;
        val -= 10;
    }
    if (val == 9)
    {
        os << I << X;
        val -= 9;
    }
    else if (val >= 5)
    {
        os << V;
        val -= 5;
    }
    else if (val == 4)
    {
        os << I << V;
        val -= 4;
    }
    while (val >= 1)
    {
        os << I;
        --val;
    }
    return os;
}

int get_value(char ch)
{
    switch (ch)
    {
    case N:
        return 0;
    case I:
        return 1;
    case V:
        return 5;
    case X:
        return 10;
    case L:
        return 50;
    case C:
        return 100;
    case D:
        return 500;
    case M:
        return 1000;
    default:
        error("illegal letter used: " + string(1, ch));
    }
}

bool counter_illegal(int counter, char ch)
{
    switch (ch)
    {
    case N:
    case V:
    case L:
    case D:
        return counter > 1;
    case I:
    case X:
    case C:
    case M:
        return counter > 3;
    default:
        error("counter_illegal: invalid character " + string(1, ch));
    }
}

int roman_int_to_int(const string &s)
{
    if (s.size() == 0)
    {
        error("roman_to_int: empty string");
    }
    if (s.size() == 1)
    {
        return get_value(s[0]);
    }

    int counter = 1;
    int val = get_value(s[s.size() - 1]);

    for (int i = s.size() - 2; i >= 0; --i)
    {
        if (s[i] == s[i + 1])
        {
            ++counter;
            if (counter_illegal(counter, s[i]))
            {
                error("illegal repetition of letter: " + string(1, s[i]));
            }
        }
        else
        {
            counter = 1;
        }

        if (get_value(s[i]) < get_value(s[i + 1]))
        {
            if ((s[i] == I || s[i] == X || s[i] == C) && get_value(s[i + 1]) <= 10 * get_value(s[i]))
            {
                val -= get_value(s[i]);
            }
            else
            {
                error("illegal use of " + string(1, s[i]));
            }
        }
        else
        {
            val += get_value(s[i]);
        }
    }
    return val;
}

istream &operator>>(istream &is, Roman_int &r)
{
    is.exceptions(is.exceptions() | std::ios_base::badbit);

    string s;
    char ch;

    while (is.get(ch))
    {
        if (is_valid_char(ch))
        {
            s += ch;
        }
        else
        {
            is.putback(ch);
            break;
        }
    }

    int val = roman_int_to_int(s);
    r.set_val(val);
    return is;
}

const char let = 'L';
const char con = 'C';
const char quit = 'q';
const char help = 'h';
const char print = ';';
const char number = '8';
const char name = 'a';
const string declkey = "let";
const string conkey = "const";
const string quitkey = "quit";
const string helpkey = "help";
const string prompt = "> ";
const string result = "= ";

class Token
{
public:
    char kind;
    Roman_int value;
    string name;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, const Roman_int &val) : kind(ch), value(val) { }
    Token(char ch, const string &n) : kind(ch), value(0), name(n) { }
};

class Token_stream
{
public:
    Token_stream();
    Token_stream(istream &is);
    Token get();
    void putback(const Token &t);
    void ignore(char c);
    istream &get_istream();
private:
    bool full;
    Token buffer;
    istream *is_ptr;
};

Token_stream::Token_stream() : full(false), buffer(0), is_ptr(&cin) { }
Token_stream::Token_stream(istream &is) : full(false), buffer(0), is_ptr(&is) { }
istream   &Token_stream::get_istream()
{
    return (*is_ptr);
}

void Token_stream::putback(const Token &t)
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
    case '=':
        return Token(ch);
    case N:
    case I:
    case V:
    case X:
    case L:
    case C:
    case D:
    case M:
    {
        (*is_ptr).putback(ch);
        Roman_int val;
        (*is_ptr) >> val;
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while ((*is_ptr).get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
            {
                s += ch;
            }
            (*is_ptr).putback(ch);
            if (s == declkey)
            {
                return Token(let);
            }
            if (s == conkey)
            {
                return Token(con);
            }
            if (s == helpkey)
            {
                return Token(help);
            }
            if (s == quitkey)
            {
                return Token(quit);
            }
            return Token(name, s);
        }
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

class Variable
{
public:
    string name;
    Roman_int value;
    bool is_const;
    Variable(const string &n, const Roman_int &v, bool b) : name(n), value(v), is_const(b) { }
};

class Symbol_table
{
public:
    Roman_int get(const string &s);
    void set(const string &s, const Roman_int &d);
    bool is_declared(const string &var);
    Roman_int declare(const string &var, const Roman_int &val, bool b);
private:
    vector<Variable> var_table;
};

Roman_int Symbol_table::get(const string &s)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            return var_table[i].value;
        }
    }
    error("get: undefined variable " + s);
}

void Symbol_table::set(const string &s, const Roman_int &d)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            if (var_table[i].is_const)
            {
                error(s + " is a constant");
            }
            var_table[i].value = d;
            return;
        }
    }
    error("set: undefined variable " + s);
}

bool Symbol_table::is_declared(const string &var)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == var)
        {
            return true;
        }
    }
    return false;
}

Roman_int Symbol_table::declare(const string &var, const Roman_int &val, bool b)
{
    if (is_declared(var))
    {
        error(var + " declared twice");
    }
    var_table.push_back(Variable(var, val, b));
    return Roman_int(val);
}

Token_stream ts;
Symbol_table st;
Roman_int expression();

Roman_int primary()
{
    Token t = ts.get();
    Roman_int d(0);
    switch (t.kind)
    {
    case '(':
        d = expression();
        t = ts.get();
        if (t.kind != ')')
        {
            error("')' expected");
        }
        break;
    case '{':
        d = expression();
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
        d = -primary();
        break;
    case '+':
        d = primary();
        break;
    case name:
    {
        Token t2 = ts.get();
        if (t2.kind == '=')
        {
            d = expression();
            st.set(t.name, d);
        }
        else
        {
            ts.putback(t2);
            d = st.get(t.name);
        }
    }
    break;
    default:
        error("primary expected");
    }

    return d;
}

Roman_int term()
{
    Roman_int left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left = left * primary();
            t = ts.get();
            break;
        case '/':
        {
            Roman_int d = primary();
            if (d == Roman_int(0))
            {
                error("divide by zero");
            }
            left = left / d;
            t = ts.get();
            break;
        }
        case '%':
        {
            Roman_int d = primary();
            if (d == Roman_int(0))
            {
                error("%: divide by zero");
            }
            left = left % d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

Roman_int expression()
{
    Roman_int left = term();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left = left + term();
            t = ts.get();
            break;
        case '-':
            left = left - term();
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

Roman_int declaration(bool b)
{
    Token t = ts.get();
    if (t.kind != name)
    {
        error ("name expected in declaration");
    }
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=')
    {
        error("= missing in declaration of " + var_name);
    }

    Roman_int d = expression();
    st.declare(var_name, d, b);
    return d;
}

Roman_int statement()
{
    Token t = ts.get();
    switch(t.kind)
    {
    case let:
        return declaration(false);
    case con:
        return declaration(true);
    default:
        ts.putback(t);
        return expression();
    }
}

void clean_up_mess()
{
    ts.ignore(print);
}

void print_help()
{
    cout << "Instructions: enter expressions, you can declare variables using\n";
    cout << "the 'let' keyword and constants with the 'const' keyword.\n";
}

void calculate()
{
    while (ts.get_istream())
    {
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
            {
                t = ts.get();
            }
            if (t.kind == help)
            {
                print_help();
            }
            else if (t.kind == quit)
            {
                return;
            }
            else
            {
                ts.putback(t);
                cout << result << statement() << endl;
            }
        }
        catch(exception &e)
        {
            cerr << e.what() << endl;
            clean_up_mess();
        }
    }
}

int main(int argc, const char *argv[])
{
    try
    {
        cout << "Welcome to our simple calculator.\n";
        cout << "Enter '" << helpkey << "' to get the help info; enter '" << quitkey << "' to quit.\n";

        calculate();

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
