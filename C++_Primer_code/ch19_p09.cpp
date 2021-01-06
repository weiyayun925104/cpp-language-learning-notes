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
#include <tuple>
#include <bitset>
#include <regex>
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
using std::tuple;
using std::make_tuple;
using std::tuple_size;
using std::tuple_element;
using std::bitset;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::regex_replace;
using std::smatch;
using std::ssub_match;
using std::sregex_iterator;

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

class isbn_mismatch: public std::logic_error
{
public:
    explicit isbn_mismatch(const std::string &s): std::logic_error(s) {}
    isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs):
        std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};

class Sales_data;
std::ostream &operator<<(std::ostream &, const Sales_data &);
std::istream &operator>>(std::istream &, Sales_data &);
Sales_data operator+(const Sales_data &, const Sales_data &);
bool operator==(const Sales_data &, const Sales_data &);
bool operator!=(const Sales_data &, const Sales_data &);

class Sales_data
{
    friend std::ostream &operator<<(std::ostream &, const Sales_data &);
    friend std::istream &operator>>(std::istream &, Sales_data &);
    friend Sales_data operator+(const Sales_data &, const Sales_data &);
    friend bool operator==(const Sales_data &, const Sales_data &);
    friend bool operator!=(const Sales_data &, const Sales_data &);

    friend class std::hash<Sales_data>;

    friend void debug_test(const Sales_data &);
    friend auto count_price(const std::vector<Sales_data> &vec, double) -> decltype(vec.begin());
public:
    using Avg = double (Sales_data::*)() const;

    Sales_data() : Sales_data("", 0, 0)
    {

    }
    explicit Sales_data(const std::string &s) : Sales_data(s, 0, 0)
    {

    }
    Sales_data(const std::string &s, unsigned n, double p) :
        bookNo(s), units_sold(n), revenue(p * n)
    {

    }
    explicit Sales_data(std::istream &is) : Sales_data()
    {

        is >> *this;
    }

    const std::string &isbn() const
    {
        return bookNo;
    }

    Sales_data &operator+=(const Sales_data &);
    Sales_data &operator=(const std::string &);

    explicit operator std::string() const
    {
        return bookNo;
    }
    operator double() const
    {
        return revenue;
    }

    static const std::string Sales_data::*data()
    {
        return &Sales_data::bookNo;
    }
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    double avg_price() const;
};

Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    if (isbn() != rhs.isbn())
        throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
Sales_data &Sales_data::operator=(const std::string &isbn)
{
    bookNo = isbn;
    return *this;
}

inline double Sales_data::avg_price() const
{
    if(units_sold != 0)
        return revenue / units_sold;
    else
        return revenue;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
    os << item.bookNo << " "
       << item.units_sold << " "
       << item.revenue << " "
       << item.avg_price();
    return os;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    if(is)
        item.revenue = item.units_sold * price;
    else
        item = Sales_data();
    return is;
}
bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.bookNo == rhs.bookNo &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}
bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

namespace std
{
    template <> struct hash<Sales_data>
    {
        size_t operator()(const Sales_data &s) const noexcept
        {
            return std::hash<string>()(s.bookNo) ^
                   std::hash<unsigned>()(s.units_sold) ^
                   std::hash<double>()(s.revenue);
        }
    };
}

void debug_test(const Sales_data &item)
{
    Sales_data::Avg price = &Sales_data::avg_price;
    cout << (item.*price)() << endl;
}

auto count_price(const std::vector<Sales_data> &vec, double price) -> decltype(vec.begin())
{
    auto f = bind(&Sales_data::avg_price, std::placeholders::_1);
    return find_if(vec.begin(), vec.end(), [&](const Sales_data & s)
    {
        return price < f(s);
    });
}

class Token
{
    friend std::ostream &operator<<(std::ostream &, const Token &);
public:
    Token() : tok(INT), ival{0} {}
    Token(const Token &t) : tok(t.tok)
    {
        copyUnion(t);
    }
    Token(Token &&t) noexcept : tok(std::move(t.tok))
    {
        moveUnion(std::move(t));
    }
    Token &operator=(const Token &);
    Token &operator=(Token &&) noexcept;
    ~Token()
    {
        freeUnion();
    }
    Token &operator=(const std::string &);
    Token &operator=(char);
    Token &operator=(int);
    Token &operator=(double);
    Token &operator=(const Sales_data &);
private:
    enum { INT, CHAR, DBL, STR, SALE } tok;
    union
    {
        char cval;
        int ival;
        double dval;
        std::string sval;
        Sales_data sdata;
    };
    void copyUnion(const Token &);
    void moveUnion(Token &&t);
    void freeUnion();
};

inline void Token::freeUnion()
{
    if(tok == STR)
        sval.std::string::~string();
    if(tok == SALE)
        sdata.~Sales_data();
}

std::ostream &operator<<(std::ostream &os, const Token &t)
{
    switch(t.tok)
    {
    case Token::INT:
        os << t.ival;
        break;
    case Token::CHAR:
        os << t.cval;
        break;
    case Token::DBL:
        os << t.dval;
        break;
    case Token::STR:
        os << t.sval;
        break;
    case Token::SALE:
        os << t.sdata;
        break;
    }
    return os;
}

Token &Token::operator=(int i)
{
    freeUnion();
    ival = i;
    tok = INT;
    return *this;
}

Token &Token::operator=(char c)
{
    freeUnion();
    cval = c;
    tok = CHAR;
    return *this;
}

Token &Token::operator=(double d)
{
    freeUnion();
    dval = d;
    tok = DBL;
    return *this;
}

Token &Token::operator=(const std::string &s)
{
    std::string stmp = s;
    freeUnion();
    new (&sval) std::string(std::move(stmp));
    tok = STR;
    return *this;
}
Token &Token::operator=(const Sales_data &item)
{
    Sales_data itmp = item;
    freeUnion();
    new (&sdata) Sales_data(std::move(itmp));
    tok = SALE;
    return *this;
}

void Token::copyUnion(const Token &t)
{
    switch (t.tok)
    {
    case Token::INT:
        ival = t.ival;
        break;
    case Token::CHAR:
        cval = t.cval;
        break;
    case Token::DBL:
        dval = t.dval;
        break;
    case Token::STR:
        new (&sval) std::string(t.sval);
        break;
    case Token::SALE:
        new (&sdata) Sales_data(t.sdata);
        break;
    }
}

void Token::moveUnion(Token &&t)
{
    switch (t.tok)
    {
    case Token::INT:
        ival = std::move(t.ival);
        break;
    case Token::CHAR:
        cval = std::move(t.cval);
        break;
    case Token::DBL:
        dval = std::move(t.dval);
        break;
    case Token::STR:
        new (&sval) std::string(std::move(t.sval));
        break;
    case Token::SALE:
        new (&sdata) Sales_data(std::move(t.sdata));
        break;
    }
}

Token &Token::operator=(const Token &t)
{
    if (this == &t)
    {
        return *this;
    }
    if (tok == STR && t.tok != STR) sval.std::string::~string();
    if (tok == SALE && t.tok != SALE) sdata.~Sales_data();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else if (tok == SALE && t.tok == SALE)
        sdata = t.sdata;
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
}

Token &Token::operator=(Token &&t) noexcept
{
    if(this != &t)
    {
        freeUnion();
        moveUnion(std::move(t));
        tok = std::move(t.tok);
    }
    return *this;
}

int main(int argc, const char *argv[])
{
    try
    {
        string s = "this is a string";
        Sales_data item("978-7-121-20038-0", 12, 128.0);
        int i = 12;
        char c = 'c';
        double d = 1.28;
        Token tkn;
        tkn = i;
        cout << tkn << endl;
        tkn = c;
        cout << tkn << endl;
        tkn = d;
        cout << tkn << endl;
        tkn = s;
        cout << tkn << endl;
        tkn = item;
        cout << tkn << endl;
        Token tkn2 = tkn;
        cout << tkn2 << endl;
        tkn2 = s;
        cout << tkn2 << endl;
        tkn2 = tkn;
        cout << tkn2 << endl;
        tkn2 = c;
        cout << tkn2 << endl;
        tkn = s;
        cout << tkn << endl;
        tkn2 = std::move(tkn);
        cout << tkn2 << endl;
        Token tkn3 = std::move(tkn2);
        cout << tkn3 << endl;
        tkn3 = tkn3;
        cout << tkn3 << endl;
        tkn3 = item;
        cout << tkn3 << endl;
        tkn2 = std::move(tkn3);
        cout << tkn2 << endl;

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