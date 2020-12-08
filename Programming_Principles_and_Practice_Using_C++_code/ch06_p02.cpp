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

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";

class Token
{
public:
    char kind;
    double value;
    Token(char ch) : kind(ch), value(0) { }
    Token(char ch, double val) : kind(ch), value(val) { }
};

class Token_stream
{
public:
    Token_stream();
    Token get();
    void putback(Token t);
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
    cin >> ch;

    switch (ch)
    {
    case print:
    case quit:
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
        error("Bad token");
    }
}

Token_stream ts;

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
    else if (p > 12)
    {
        error("factorial too large");
    }
    else if (p == 0)
    {
        return 1;
    }
    else
    {
        int res = p;
        for (int i = p - 1; i > 0; --i)
        {
            res *= i;
        }
        return res;
    }
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
        default:
            ts.putback(t);
            return left;
        }
    }
}

void calculate()
{
    while (cin)
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)
        {
            t = ts.get();
        }
        if (t.kind == quit)
        {
            return;
        }
        ts.putback(t);
        cout << result << expression() << endl;
    }
}

int main()
{
    try
    {
        cout << "Welcome to our simple calculator.\n";
        cout << "Please enter expressions using floating-point numbers.\n";
        cout << "Operators available: +, -, *, /, %, !, (), {}.\n";
        cout << "Enter '" << print << "' to print the result; enter '" << quit << "' to quit.\n";
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
