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
#include <initializer_list>
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
using std::begin;
using std::end;
using std::initializer_list;

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

class Book
{
    friend istream &operator >> (istream &, Book &);
    friend ostream &operator<<(ostream &, const Book &);
public:
    Book() = default;
    Book(string na, string au = "", string no = "") :
        book_name(na), book_author(au), book_no(no) {}
    Book(const Book &) = default;
    Book(Book &&b) noexcept :
        book_name(std::move(b.book_name)),
        book_author(std::move(b.book_author)),
        book_no(std::move(book_no)) {}
    Book &operator=(const Book &) = default;
    Book &operator=(Book &&) noexcept;
    ~Book() = default;
private:
    string book_name;
    string book_author;
    string book_no;
};
Book &Book::operator=(Book &&rhs) noexcept
{
    if (this == &rhs)
    {
        return *this;
    }

    book_name = std::move(rhs.book_name);
    book_author = std::move(rhs.book_author);
    book_no = std::move(rhs.book_no);

    return *this;
}

istream &operator>>(istream &is, Book &b)
{
    cout << "Enter the name of book: " << endl;
    getline(is, b.book_name);
    if (!is)
    {
        return is;
    }
    cout << "Enter the author of book: " << endl;
    getline(is, b.book_author);
    if (!is)
    {
        return is;
    }
    cout << "Enter the no of book: " << endl;
    getline(is, b.book_no);
    return is;
}

ostream &operator<<(ostream &os, const Book &b)
{
    os << b.book_name << " "
       << b.book_author << " "
       << b.book_no;
    return os;
}

int main(int argc, const char *argv[])
{
    try
    {
        Book my_book1("Harry Potter and the Order of the Phoenix", "Rowling, J.K.", "9780-4393-5807-0-1");
        Book my_book2("Lone Survivor", "Luttrell, Marcus", "9780-3160-6760-0-7");

        cout << my_book1 << endl;
        cout << my_book2 << endl;

        my_book1 = Book("Einstein: His Life and Universe", "Isaacson, Walter", "9781-4165-3932-0-2");
        cout << my_book1 << endl;

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
