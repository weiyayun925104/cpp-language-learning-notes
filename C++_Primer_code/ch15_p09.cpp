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

class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
    const std::string & isbn() const
    {
        return bookNo;
    }
    virtual double net_price(std::size_t n) const
    {
        return n * price;
    }
    virtual void debug() const;
    Quote(const Quote &q) : bookNo(q.bookNo), price(q.price) {}
    Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {}
    Quote &operator=(const Quote &);
    Quote &operator=(Quote &&) noexcept;
    virtual ~Quote() = default;
    virtual Quote *clone() const &
    {
        return new Quote(*this);
    }
    virtual Quote *clone() && { return new Quote(std::move(*this)); }
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

inline void Quote::debug() const
{
    std::cout << "std::string bookNo\n"
              << "double price\n"
              << std::endl;
}

inline Quote &Quote::operator=(const Quote &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    bookNo = rhs.bookNo;
    price = rhs.price;
    return *this;
}
inline Quote &Quote::operator=(Quote &&rhs) noexcept
{
    if(this != &rhs)
    {
        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
    }
    return *this;
}

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc):
        Quote(book, price), quantity(qty), discount(disc) {}
    double net_price(std::size_t) const = 0;
    Disc_quote(const Disc_quote &dq) : Quote(dq), quantity(dq.quantity), discount(dq.discount) {}
    Disc_quote(Disc_quote &&dq) noexcept : Quote(std::move(dq)), quantity(std::move(dq.quantity)), discount(std::move(dq.discount)) {}
    Disc_quote &operator=(const Disc_quote &);
    Disc_quote &operator=(Disc_quote &&) noexcept;
    ~Disc_quote() = default;
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

inline Disc_quote &Disc_quote::operator=(const Disc_quote &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    return *this;
}

inline Disc_quote &Disc_quote::operator=(Disc_quote &&rhs) noexcept
{
    if(this != &rhs)
    {
        Quote::operator=(std::move(rhs));
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
    }
    return *this;
}

class Bulk_quote : public Disc_quote
{
public:
    using Disc_quote::Disc_quote;
    Bulk_quote() = default;
    double net_price(std::size_t) const override;
    void debug() const override;
    Bulk_quote(const Bulk_quote &bq) : Disc_quote(bq) {}
    Bulk_quote(Bulk_quote &&bq) noexcept : Disc_quote(std::move(bq)) {}
    Bulk_quote &operator=(const Bulk_quote &);
    Bulk_quote &operator=(Bulk_quote &&) noexcept;
    ~Bulk_quote() = default;
    virtual Bulk_quote *clone() const &
    {
        return new Bulk_quote(*this);
    }
    virtual Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }
};

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

inline void Bulk_quote::debug() const
{
    std::cout << "std::string bookNo\n"
              << "double price\n"
              << "std::size_t min_qty\n"
              << "double discount\n"
              << std::endl;
}

inline Bulk_quote &Bulk_quote::operator=(const Bulk_quote &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    Disc_quote::operator=(rhs);
    return *this;
}
inline Bulk_quote &Bulk_quote::operator=(Bulk_quote &&rhs) noexcept
{
    if(this != &rhs)
    {
        Disc_quote::operator=(std::move(rhs));
    }
    return *this;
}

class Basket
{
public:
    void add_item(const Quote &sale)
    {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void add_item(Quote &&sale)
    {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }
    double total_receipt(std::ostream &) const;
private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

double Basket::total_receipt(std::ostream &os) const
{
    double sum = 0;
    for (auto iter = items.cbegin();
            iter != items.cend();
            iter = items.upper_bound(*iter))
    {
        cout << sum << ", ";
        sum += print_total(os, *(*iter), items.count(*iter));
        cout << sum << endl;
    }
    os << "Total Sale: " << sum << std::endl;
    return sum;
}

int main(int argc, const char *argv[])
{
    try
    {
        Basket basket;
        for(std::size_t i = 0; i != 10; ++i)
            basket.add_item(Bulk_quote("978-7-121-20038-0", 128.0, 6, 0.05));
        for(std::size_t i = 0; i != 10; ++i)
            basket.add_item(Bulk_quote("7-115-13771-4", 59.0, 10, 0.15));
        for(std::size_t i = 0; i != 10; ++i)
            basket.add_item(Bulk_quote("978-7-111-40701-0", 128.0, 10, 0.2));
        for(std::size_t i = 0; i != 10; ++i)
            basket.add_item(Bulk_quote("978-0-87779-855-2", 56.0, 5, 0.1));
        basket.total_receipt(cout);

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