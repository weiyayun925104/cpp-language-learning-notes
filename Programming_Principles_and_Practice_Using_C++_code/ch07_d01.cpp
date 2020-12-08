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

const char let = 'L';
const char con = 'C';
const char quit = 'q';
const char help = 'h';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square_root = 's';
const char power = 'p';
const string declkey = "let";
const string conkey = "const";
const string sqrtkey = "sqrt";
const string powkey = "pow";
const string quitkey = "quit";
const string helpkey = "help";
const string prompt = "> ";
const string result = "= ";

class Token
{
public:
    char kind;
    double value;
    string name;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, double val) : kind(ch), value(val) { }
    Token(char ch, string n) : kind(ch), value(0), name(n) { }
};

class Token_stream
{
public:
    Token_stream();
    Token get();
    void putback(Token t);
    void ignore(char c);
private:
    bool full;
    Token buffer;
};

Token_stream::Token_stream() : full(false), buffer(0) { }

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
    cin.get(ch);
    while (isspace(ch))
    {
        if (ch == '\n')
        {
            return Token(print);
        }
        cin.get(ch);
    }

    switch (ch)
    {
    case print:
    case '!':
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
    case ',':
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
        cin.putback(ch);
        double val;
        cin >> val;
        return Token(number, val);
    }
    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
            {
                s += ch;
            }
            cin.putback(ch);
            if (s == declkey)
            {
                return Token(let);
            }
            if (s == conkey)
            {
                return Token(con);
            }
            if (s == sqrtkey)
            {
                return Token(square_root);
            }
            if (s == powkey)
            {
                return Token(power);
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
    while (cin >> ch)
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
    double value;
    bool is_const;
    Variable(string n, double v, bool b) : name(n), value(v), is_const(b) { }
};

class Symbol_table
{
public:
    double get(string s);
    void set(string s, double d);
    bool is_declared(string var);
    double declare(string var, double val, bool b);
private:
    vector<Variable> var_table;
};

double Symbol_table::get(string s)
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

void Symbol_table::set(string s, double d)
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

bool Symbol_table::is_declared(string var)
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

double Symbol_table::declare(string var, double val, bool b)
{
    if (is_declared(var))
    {
        error(var + " declared twice");
    }
    var_table.push_back(Variable(var, val, b));
    return val;
}

Token_stream ts;
Symbol_table st;
double expression();

double factorial(double d)
{
    int p = d;
    if (double(p) != d)
    {
        error("factorial not defined for non-integers");
    }
    if (p < 0)
    {
        error("factorial not defined for negative values");
    }
    else if (p == 0)
    {
        return 1;
    }
    else
    {
        double res = p;
        for (int i = p - 1; i > 0; --i)
        {
            res *= i;
            if (res > 1.0e+16)
            {
                error("factorial too large");
            }
        }
        return res;
    }
}

double my_pow(double base, int expo)
{
    if (expo < 0)
    {
        error("my_pow not defined for negative expo");
    }
    if (expo == 0)
    {
        if (base == 0)
        {
            return 0;
        }
        return 1;
    }
    double res = base;
    for (int i = 2; i <= expo; ++i)
    {
        res *= base;
    }
    return res;
}

double primary()
{
    Token t = ts.get();
    double d = 0;
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
    case square_root:
    {
        Token t2 = ts.get();
        if (t2.kind != '(')
        {
            error("'(' expected");
        }
        double d2 = expression();
        if (d2 < 0)
        {
            error("Square roots of negative numbers... nope!");
        }
        t2 = ts.get();
        if (t2.kind != ')')
        {
            error("')' expected");
        }
        d = sqrt(d2);
    }
    break;
    case power:
    {
        Token t2 = ts.get();
        if (t2.kind != '(')
        {
            error("'(' expected");
        }
        double d2 = expression();
        t2 = ts.get();
        if (t2.kind != ',')
        {
            error("',' expected");
        }
        t2 = ts.get();
        if (t2.kind != number)
        {
            error("second argument of 'pow' is not a number");
        }
        int i2 = int(t2.value);
        if (i2 != t2.value)
        {
            error("second argument of 'pow' is not an integer");
        }
        t2 = ts.get();
        if (t2.kind != ')')
        {
            error("')' expected");
        }
        d = my_pow(d2, i2);
    }
    break;
    default:
        error("primary expected");
    }

    t = ts.get();
    if (t.kind != '!')
    {
        ts.putback(t);
        return d;
    }
    return factorial(d);
}

double term()
{
    double left = primary();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
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
            double d = primary();
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

double expression()
{
    double left = term();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;
        case '-':
            left -= term();
            t = ts.get();
            break;
        case '=':
            error("use of '=' outside of a declaration");
        default:
            ts.putback(t);
            return left;
        }
    }
}

double declaration(bool b)
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

    double d = expression();
    st.declare(var_name, d, b);
    return d;
}

double statement()
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
    cout << "Instructions: enter expressions, there are\n";
    cout << "a few functions, you can declare variables using\n";
    cout << "the 'let' keyword and constants with the 'const'\n";
    cout << "keyword.\n";
}

void calculate()
{
    while (cin)
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

int main()
{
    try
    {
        cout << "Welcome to our simple calculator.\n";
        cout << "Enter '" << helpkey << "' to get the help info; enter '" << quitkey << "' to quit.\n";
        st.declare("pi", 3.1415926535, true);
        st.declare("e", 2.7182818284, true);
        st.declare("k", 1000, true);

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
