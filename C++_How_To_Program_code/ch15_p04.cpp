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

namespace Chrono
{
    class Date
    {
    public:
        enum Month
        {
            jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
        };

        Date(int y, Month m, int d);
        Date();

        int day() const
        {
            return d;
        }
        Month month() const
        {
            return m;
        }
        int year() const
        {
            return y;
        }

        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
    private:
        int y;
        Month m;
        int d;
    };

    bool is_date(int y, Date::Month m, int d);
    bool leapyear(int y);

    int day_in_year(const Date &d);
    void split_date(int day_of_year, int year, int *month, int *day);
    int n_leapyears(int y);
    long int days_linear(const Date &d);

    enum Day
    {
        sunday, monday, tuesday, wednesday, thursday, friday, saturday
    };
    Day day_of_week(const Date &d);
    ostream &operator<<(ostream &os, Day d);

    bool operator==(const Date &a, const Date &b);
    bool operator!=(const Date &a, const Date &b);

    ostream &operator<<(ostream &os, const Date &d);
    istream &operator>>(istream &is, Date &dd);
}

namespace Chrono
{
    Date::Date(int yy, Month mm, int dd) : y(yy), m(mm), d(dd)
    {
        if (!is_date(yy, mm, dd))
        {
            error("invalid date");
        }
    }

    const Date &default_date()
    {
        static const Date dd(2001, Date::jan, 1);
        return dd;
    }

    Date::Date() : y(default_date().year()), m(default_date().month()), d(default_date().day()) { }

    int nmonth(Date::Month m)
    {
        switch (m)
        {
        case Date::jan:
            return 0;
        case Date::feb:
            return 31;
        case Date::mar:
            return 31 + 28;
        case Date::apr:
            return 31 + 28 + 31;
        case Date::may:
            return 31 + 28 + 31 + 30;
        case Date::jun:
            return 31 + 28 + 31 + 30 + 31;
        case Date::jul:
            return 31 + 28 + 31 + 30 + 31 + 30;
        case Date::aug:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31;
        case Date::sep:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31;
        case Date::oct:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30;
        case Date::nov:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
        case Date::dec:
            return 31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
        }
    }

    void Date::add_day(int n)
    {
        int doy = nmonth(dec);
        doy += 31;
        if (leapyear(y - 1))
        {
            ++doy;
        }
        int diy = nmonth(dec);
        diy += 31;
        if (leapyear(y))
        {
            ++diy;
        }
        int day_of_year = day_in_year(*this);
        day_of_year += n;
        if (day_of_year >= 1 && day_of_year <= diy)
        {
            int res_month, res_day;
            split_date(day_of_year, y, &res_month, &res_day);
            m = Month(res_month);
            d = res_day;
        }
        else if (day_of_year > diy && day_of_year <= (diy + 365))
        {
            day_of_year -= diy;
            int res_month, res_day;
            split_date(day_of_year, y + 1, &res_month, &res_day);
            y++;
            m = Month(res_month);
            d = res_day;
        }
        else if (day_of_year < 1 && (day_of_year + doy) >= 1)
        {
            day_of_year += doy;
            int res_month, res_day;
            split_date(day_of_year, y - 1, &res_month, &res_day);
            y--;
            m = Month(res_month);
            d = res_day;
        }
    }

    void Date::add_month(int n)
    {
        int month = m + n;
        bool day_large = false;
        if (d > 28)
        {
            day_large = true;
            add_day(-3);
        }
        if (month >= jan && month <= dec)
        {
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
        else if (month > dec && month <= dec + 12)
        {
            month -= dec;
            y++;
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
        else if(month < jan && month + 12 >= 1)
        {
            month += 12;
            y--;
            m = Month(month);
            if (day_large == true)
            {
                add_day(3);
            }
        }
    }

    void Date::add_year(int n)
    {
        if (m == feb && d == 29 && !leapyear(y + n))
        {
            m = mar;
            d = 1;
        }
        y += n;
    }

    bool is_date(int y, Date::Month m, int d)
    {
        if (d <= 0)
        {
            return false;
        }

        int days_in_month = 31;

        switch (m)
        {
        case Date::feb:
            days_in_month = (leapyear(y)) ? 29 : 28;
            break;
        case Date::apr:
        case Date::jun:
        case Date::sep:
        case Date::nov:
            days_in_month = 30;
            break;
        }

        if (days_in_month < d)
        {
            return false;
        }

        return true;
    }

    bool leapyear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
    }

    bool operator==(const Date &a, const Date &b)
    {
        return a.year() == b.year() && a.month() == b.month() && a.day() == b.day();
    }

    bool operator!=(const Date &a, const Date &b)
    {
        return !(a == b);
    }

    ostream &operator<<(ostream &os, const Date &d)
    {
        return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
    }

    istream &operator>>(istream &is, Date &dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is)
        {
            return is;
        }
        if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')')
        {
            is.clear(std::ios_base::failbit);
            return is;
        }
        dd = Date(y, Date::Month(m), d);
        return is;
    }

    ostream &operator<<(ostream &os, Day d)
    {
        switch (d)
        {
        case sunday:
            os << "Sunday";
            break;
        case monday:
            os << "Monday";
            break;
        case tuesday:
            os << "Tuesday";
            break;
        case wednesday:
            os << "Wednesday";
            break;
        case thursday:
            os << "Thursday";
            break;
        case friday:
            os << "Friday";
            break;
        case saturday:
            os << "Saturday";
            break;
        }
        return os;
    }

    const Date first_date = Date(1970, Date::jan, 1);
    const Day first_day = thursday;

    Day day_of_week(const Date &d)
    {
        if (d.year() < first_date.year())
        {
            error("day_of_week: works only for 1970 and later");
        }
        int dlin = days_linear(d);
        return Day((first_day + dlin) % 7);
    }

    Date next_Sunday(const Date &d)
    {
        Date nsd = d;
        Day day = day_of_week(d);
        nsd.add_day(7 - day);
        return nsd;
    }

    int day_in_year(const Date &d)
    {
        int diy = nmonth(d.month());
        diy += d.day();
        if (leapyear(d.year()) && d.month() > Date::feb)
        {
            ++diy;
        }
        return diy;
    }

    void split_date(int day_of_year, int year, int *month, int *day)
    {
        int i;
        bool found = false;

        for (i = 1; i <= 12 && !found; i++)
        {
            switch(i)
            {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day_of_year <= 31)
                {
                    found = true;
                }
                else
                {
                    day_of_year -= 31;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day_of_year <= 30)
                {
                    found = true;
                }
                else
                {
                    day_of_year -= 30;
                }
                break;
            case 2:
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                {
                    if (day_of_year <= 29)
                    {
                        found = true;
                    }
                    else
                    {
                        day_of_year -= 29;
                    }
                }
                else
                {
                    if (day_of_year <= 28)
                    {
                        found = true;
                    }
                    else
                    {
                        day_of_year -= 28;
                    }
                }
                break;
            default :
                break;
            }
        }
        *month = i - 1;
        *day = day_of_year;
    }

    int n_leapyears(int y)
    {
        int nl = 0;
        for (int i = 1970; i < y; ++i)
        {
            if (leapyear(i))
            {
                ++nl;
            }
        }
        return nl;
    }

    long int days_linear(const Date &d)
    {
        if (d.year() < first_date.year())
        {
            error("days_linear: year must be 1970 or later");
        }
        int y = d.year() - first_date.year();
        return y * 365 + n_leapyears(d.year()) + day_in_year(d) - 1;
    }

    Date next_workday(const Date &d)
    {
        Date nwd = d;
        Day day = day_of_week(d);
        switch (day)
        {
        case sunday:
        case monday:
        case tuesday:
        case wednesday:
        case thursday:
            nwd.add_day(1);
            break;
        case saturday:
            nwd.add_day(2);
            break;
        case friday:
            nwd.add_day(3);
            break;
        }
        return nwd;
    }
}

namespace Liber
{
    class ISBN
    {
    public:
        int n1;
        int n2;
        int n3;
        int n4;
        char x;

        ISBN(int n1_val, int n2_val, int n3_val, int n4_val, char x_val);
        ISBN();
    };

    bool is_isbn(int, int, int, int, char);

    bool operator==(const ISBN &i1, const ISBN &i2);

    class Book
    {
    public:
        enum Genre
        {
            fiction = 0, nonfiction, periodical, biography, children
        };

        Book(const ISBN &isbn_num, const string &title, const string &author, int c_date, Genre gen, bool checked_out);
        Book();

        const ISBN &isbn() const
        {
            return in;
        }
        const string &title() const
        {
            return t;
        }
        const string &author() const
        {
            return a;
        }
        int c_date() const
        {
            return cd;
        }
        Genre genre() const
        {
            return g;
        }
        bool checked_out() const
        {
            return ch_out;
        }

        void check_out();
        void check_in();

    private:
        ISBN in;
        string t;
        string a;
        int cd;
        Genre g;
        bool ch_out;
    };

    bool operator==(const Book &b1, const Book &b2);
    bool operator!=(const Book &b1, const Book &b2);
    ostream &operator<<(ostream &os, const Book &b);


    class Patron
    {
    public:
        Patron(const string &name, int card_number, double fees);
        Patron();

        const string &get_name() const
        {
            return name;
        }
        int get_number() const
        {
            return card_number;
        }
        double get_fees() const
        {
            return fees;
        }

        void set_fee(double f);
    private:
        string name;
        int card_number;
        double fees;
    };

    bool owes_fee(const Patron &p);

    bool operator==(const Patron &p1, const Patron &p2);
    bool operator!=(const Patron &p1, const Patron &p2);

    class Library
    {
    public:
        class Transaction
        {
        public:
            Book b;
            Patron p;
            Chrono::Date d;

            Transaction(const Book &bb, const Patron &pp, const Chrono::Date &dd);
            Transaction();
        };

        Library(const vector<Book> &books, const vector<Patron> &patrons, const vector<Transaction> &transactions);
        Library();

        void add_book(const Book &b);
        void add_patron(const Patron &p);
        void check_out(const Book &b, const Patron &p, const Chrono::Date &d);
        void set_fee(const Patron &p, double f);

        const vector<Book> &get_books() const
        {
            return books;
        }
        const vector<Patron> &get_patrons() const
        {
            return patrons;
        }
        const vector<Transaction> &get_transactions() const
        {
            return transactions;
        }
        vector<Patron> get_debtors() const;

    private:
        vector<Book> books;
        vector<Patron> patrons;
        vector<Transaction> transactions;
    };

}

namespace Liber
{
    ISBN::ISBN(int n1_val, int n2_val, int n3_val, int n4_val, char x_val)
        : n1(n1_val), n2(n2_val), n3(n3_val), n4(n4_val), x(x_val)
    {
        if (!is_isbn(n1, n2, n3, n4, x))
        {
            error("is_isbn(): invalid number");
        }
    }

    const ISBN &default_isbn()
    {
        static const ISBN in(0, 0, 0, 0, '0');
        return in;
    }

    ISBN::ISBN()
        : n1(default_isbn().n1),
          n2(default_isbn().n2),
          n3(default_isbn().n3),
          n4(default_isbn().n4),
          x(default_isbn().x)
    {
    }

    bool is_isbn(int, int, int, int, char x)
    {
        return (isalpha(x) || isdigit(x));
    }

    bool operator==(const ISBN &i1, const ISBN &i2)
    {
        return (i1.n1 == i2.n1 && i1.n2 == i2.n2 && i1.n3 == i2.n3 && i1.n4 == i2.n4 && i1.x == i2.x);
    }

    Book::Book(const ISBN &isbn_num, const string &title, const string &author, int c_date, Genre gen, bool checked_out)
        : in(isbn_num), t(title), a(author), cd(c_date), g(gen), ch_out(checked_out)
    {
    }

    const Book &default_book()
    {
        static const Book b(ISBN(), "", "", 0, Book::fiction, false);
        return b;
    }

    Book::Book()
        : in(default_book().isbn()),
          t(default_book().title()),
          a(default_book().author()),
          cd(default_book().c_date()),
          g(default_book().genre()),
          ch_out(default_book().checked_out())
    {
    }

    void Book::check_out()
    {
        if (checked_out())
        {
            error("already checked out");
        }
        ch_out = true;
    }

    void Book::check_in()
    {
        if (!checked_out())
        {
            error("already checked in");
        }
        ch_out = false;
    }

    bool operator==(const Book &b1, const Book &b2)
    {
        return (b1.isbn() == b2.isbn());
    }

    bool operator!=(const Book &b1, const Book &b2)
    {
        return !(b1 == b2);
    }

    ostream &operator<<(ostream &os, const Book &b)
    {
        return os << b.title() << endl
               << b.author() << endl
               << b.isbn().n1 << '-'
               << b.isbn().n2 << '-'
               << b.isbn().n3 << '-'
               << b.isbn().n4 << '-'
               << b.isbn().x << endl;
    }

    Patron::Patron(const string &n, int cn, double f)
        : name(n), card_number(cn), fees(f)
    {
    }

    const Patron &default_patron()
    {
        static const Patron p("", 0, 0);
        return p;
    }

    Patron::Patron()
        : name(default_patron().get_name()),
          card_number(default_patron().get_number()),
          fees(default_patron().get_fees())
    {
    }

    void Patron::set_fee(double f)
    {
        if (f < 0)
        {
            error("set_fee(): fee cannot be smaller than zero");
        }
        fees = f;
    }

    bool owes_fee(const Patron &p)
    {
        return p.get_fees() > 0;
    }

    bool operator==(const Patron &p1, const Patron &p2)
    {
        return p1.get_number() == p2.get_number();
    }

    bool operator!=(const Patron &p1, const Patron &p2)
    {
        return !(p1 == p2);
    }

    Library::Transaction::Transaction(const Book &bb, const Patron &pp, const Chrono::Date &dd)
        : b(bb), p(pp), d(dd)
    {
    }

    const Library::Transaction &default_transaction()
    {
        static const Library::Transaction tt = Library::Transaction(Book(), Patron(), Chrono::Date());
        return tt;
    }

    Library::Transaction::Transaction()
        : b(default_transaction().b),
          p(default_transaction().p),
          d(default_transaction().d)
    {
    }

    Library::Library(const vector<Book> &b, const vector<Patron> &p, const vector<Transaction> &t)
        : books(b), patrons(p), transactions(t)
    {
    }

    const Library &default_library()
    {
        vector<Book> b;
        vector<Patron> p;
        vector<Library::Transaction> t;
        static const Library l(b, p, t);
        return l;
    }

    Library::Library()
        : books(default_library().get_books()),
          patrons(default_library().get_patrons()),
          transactions(default_library().get_transactions())
    {
    }

    void Library::add_book(const Book &b)
    {
        for (int i = 0; i < books.size(); ++i)
        {
            if (books[i] == b)
            {
                error("add_book(): book is already in library");
            }
        }
        books.push_back(b);
    }

    void Library::add_patron(const Patron &p)
    {
        for (int i = 0; i < patrons.size(); ++i)
        {
            if (patrons[i] == p)
            {
                error("add_patron(): patron is already registered");
            }
        }
        patrons.push_back(p);
    }

    void Library::check_out(const Book &b, const Patron &p, const Chrono::Date &d)
    {
        bool b_exists = false;
        int b_idx = 0;
        for (int i = 0; i < books.size(); ++i)
        {
            if (books[i] == b)
            {
                b_exists = true;
                b_idx = i;
                break;
            }
        }
        if (!b_exists)
        {
            error("check_out(): book is not in library");
        }

        if (books[b_idx].checked_out())
        {
            error("check_out(): book is already checked out");
        }

        bool p_exists = false;
        int p_idx = 0;
        for (int i = 0; i < patrons.size(); ++i)
        {
            if (patrons[i] == p)
            {
                p_exists = true;
                p_idx = i;
                break;
            }
        }
        if (!p_exists)
        {
            error("check_out(): patron is not registered");
        }

        if (patrons[p_idx].get_fees() > 0)
        {
            error("check_out(): patron owes library fees");
        }

        transactions.push_back(Transaction(books[b_idx], patrons[p_idx], d));
        books[b_idx].check_out();
    }

    void Library::set_fee(const Patron &p, double f)
    {
        int idx = 0;
        bool exists = false;
        for (int i = 0; i < patrons.size(); ++i)
        {
            if (patrons[i] == p)
            {
                exists = true;
                idx = i;
                break;
            }
        }
        if (!exists)
        {
            error("Library::set_fee(): patron does not exist");
        }
        patrons[idx].set_fee(f);
    }

    vector<Patron> Library::get_debtors() const
    {
        vector<Patron> debtors;
        for (int i = 0; i < patrons.size(); ++i)
        {
            if (patrons[i].get_fees() > 0)
            {
                debtors.push_back(patrons[i]);
            }
        }
        return debtors;
    }

}

using Liber::Library;
using Liber::Book;
using Liber::ISBN;
using Liber::Patron;
using Chrono::Date;
using Chrono::leapyear;
using Chrono::day_in_year;
using Chrono::n_leapyears;
using Chrono::days_linear;
using Chrono::day_of_week;

void test_liber()
{
    Library my_lib;

    Book my_book(ISBN(9780, 4390, 2348, 0, '1'),
                 "Hunger Games, The",
                 "Collins, Suzanne",
                 2008,
                 Book::fiction,
                 false);
    my_lib.add_book(my_book);

    Book my_book2(ISBN(9780, 4393, 5807, 0, '1'),
                  "Harry Potter and the Order of the Phoenix",
                  "Rowling, J.K.",
                  2003,
                  Book::children,
                  false);
    my_lib.add_book(my_book2);

    my_lib.add_book(Book(ISBN(9781, 4165, 3932, 0, '2'),
                         "Einstein: His Life and Universe",
                         "Isaacson, Walter",
                         2007,
                         Book::biography,
                         false));

    my_lib.add_book(Book(ISBN(9780, 3160, 6760, 0, '7'),
                         "Lone Survivor",
                         "Luttrell, Marcus",
                         2008,
                         Book::nonfiction,
                         false));

    my_lib.add_book(Book(ISBN(1234, 5678, 1234, 0, 'x'),
                         "Triathlete Issue 2/14",
                         "Competitor Group",
                         2014,
                         Book::periodical,
                         false));

    cout << "All my books:\n\n";
    const vector<Book> &books = my_lib.get_books();
    for (int i = 0; i < books.size(); ++i)
    {
        cout << books[i] << endl;
    }

    Patron my_patron1 = Patron("Forrest, Kara", 100, 0);
    my_lib.add_patron(my_patron1);
    Patron my_patron2 = Patron("Wuethrich, Benjamin", 101, 0);
    my_lib.add_patron(my_patron2);
    my_lib.add_patron(Patron("Buehler, Catriona", 102, 0));
    my_lib.add_patron(Patron("Schaerli, Tobias", 103, 0));
    my_lib.add_patron(Patron("Bieler, Ueli", 104, 0));

    cout << "List of patrons:\n\n";
    const vector<Patron> &patrons = my_lib.get_patrons();
    for (int i = 0; i < patrons.size(); ++i)
    {
        cout << patrons[i].get_name() << ", " << patrons[i].get_number() << ", " << patrons[i].get_fees() << endl;
    }

    my_lib.set_fee(my_patron1, 10);
    my_lib.set_fee(my_patron2, 15);

    cout << "\nList of debtors:\n\n";
    vector<Patron> debtors = my_lib.get_debtors();
    for (int i = 0; i < debtors.size(); ++i)
    {
        cout << debtors[i].get_name() << ", " << debtors[i].get_number() << ", " << debtors[i].get_fees() << endl;
    }

    my_lib.check_out(my_book, patrons[2], Date(2014, Date::jan, 31));
    my_lib.check_out(my_book2, patrons[3], Date());

    cout << "\nTransactions:\n";
    const vector<Library::Transaction> &transactions = my_lib.get_transactions();
    for (int i = 0; i < transactions.size(); ++i)
    {
        cout << transactions[i].b <<
             transactions[i].d << endl <<
             transactions[i].p.get_name() << endl;
    }
}

void test_leapyear()
{
    if (leapyear(2000))
    {
        cout << "2000 is a leap year\n";
    }
    if (leapyear(2004))
    {
        cout << "2004 is a leap year\n";
    }
    if (leapyear(2005))
    {
        cout << "2005 is a leap year\n";
    }
    if (leapyear(2100))
    {
        cout << "2100 is a leap year\n";
    }
}

void test_lineardate()
{
    cout << "Jan 1, 2000 is day #" <<
         day_in_year(Date(2000, Date::jan, 1)) <<
         " of the year.\n";
    cout << "Feb 29, 2000 is day #" <<
         day_in_year(Date(2000, Date::feb, 29)) <<
         " of the year.\n";
    cout << "Mar 1, 2000 is day #" <<
         day_in_year(Date(2000, Date::mar, 1)) <<
         " of the year.\n";

    cout << "Number of leap years since 1970:\n" <<
         "1971: " << n_leapyears(1971) << endl <<
         "1972: " << n_leapyears(1972) << endl <<
         "1973: " << n_leapyears(1973) << endl <<
         "1974: " << n_leapyears(1974) << endl <<
         "2000: " << n_leapyears(2000) << endl <<
         "2001: " << n_leapyears(2001) << endl <<
         "2101: " << n_leapyears(2101) << endl;

    cout << "Days since Jan 1, 1970:\n" <<
         "Jan 1, 1970: " << days_linear(Date(1970, Date::jan, 1)) << endl <<
         "Mar 1, 2001: " << days_linear(Date(2001, Date::mar, 1)) << endl <<
         "Jan 31, 2014: " << days_linear(Date(2014, Date::jan, 31)) << endl <<
         "Nov 30, 2111: " << days_linear(Date(2111, Date::nov, 30)) << endl;

    cout << "Day of week:\n" <<
         "Jan 1, 1970: " << day_of_week(Date(1970, Date::jan, 1)) << endl <<
         "Sep 11, 2001: " << day_of_week(Date(2001, Date::sep, 11)) << endl <<
         "Jan 31, 2014: " << day_of_week(Date(2014, Date::jan, 31)) << endl;
}

int main(int argc, const char *argv[])
{
    try
    {
        test_liber();
        test_leapyear();
        test_lineardate();

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
