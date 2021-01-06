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

class Book;
ostream &operator<<(ostream &, const Book &);
istream &operator>>(istream &, Book &);
bool operator==(const Book &, const Book &);
bool operator!=(const Book &, const Book &);

class Book
{
    friend ostream &operator<<(ostream &, const Book &);
    friend istream &operator>>(istream &, Book &);
    friend bool operator==(const Book &, const Book &);
    friend bool operator!=(const Book &, const Book &);
public:
    Book() = default;
    Book(const string & na, const string & au, const string & no) :
        book_name(na), book_author(au), book_no(no) {}
    Book(const Book &) = default;
    Book(Book &&b) noexcept :
        book_name(std::move(b.book_name)),
        book_author(std::move(b.book_author)),
        book_no(std::move(book_no)) {}
    Book &operator=(const Book &) = default;
    Book &operator=(Book &&) noexcept;
    Book &operator=(const string &);
    ~Book() = default;
    explicit operator bool() const
    {
        return (!book_name.empty()) &&
               (!book_author.empty()) && (!book_no.empty());
    }
private:
    string book_name;
    string book_author;
    string book_no;
};
Book &Book::operator=(Book &&rhs) noexcept
{
    if(this != &rhs)
    {
        book_name = std::move(rhs.book_name);
        book_author = std::move(rhs.book_author);
        book_no = std::move(rhs.book_no);
    }
    return *this;
}
Book &Book::operator=(const string &isbn)
{
    book_no = isbn;
    return *this;
}
ostream &operator<<(ostream &os, const Book &b)
{
    os << b.book_name << " " << b.book_author << " " << b.book_no;
    return os;
}
istream &operator>>(istream &is, Book &b)
{
    is >> b.book_name >> b.book_author >> b.book_no;
    if(!is)
        b = Book();
    return is;
}
bool operator==(const Book &lhs, const Book &rhs)
{
    return lhs.book_name == rhs.book_name &&
           lhs.book_author == rhs.book_name &&
           lhs.book_no == rhs.book_no;
}
bool operator!=(const Book &lhs, const Book &rhs)
{
    return !(lhs == rhs);
}

int main(int argc, const char *argv[])
{
    try
    {
        Book book1("Of Human Bondage", "W.Somerset Maugham", "978-0-553-21392-8");
        Book book2;
        if(book1)
            std::cout << "book1 True" << std::endl;
        if(book2)
            std::cout << "book2 True" << std::endl;
        bool bk = static_cast<bool>(book2);
        cout << bk << endl;

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
