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
using std::showbase;
using std::hex;
using std::oct;
using std::dec;
using std::fixed;
using std::scientific;
using std::left;
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

template <typename T>
class QueueTp
{
private:
    struct Node
    {
        T value;
        Node *next = nullptr;
        Node *prev = nullptr;
    };
    using link = Node*;
    link head = nullptr;
    link tail = nullptr;
    void emptyList();
public:
    QueueTp();
    QueueTp(const QueueTp<T> &q);
    ~QueueTp();

    bool enqueue(const T &val);
    bool dequeue(T &val);
    bool isEmpty() const;

    QueueTp<T> &operator = (const QueueTp<T> &q);
};

template <typename T>
QueueTp<T>::QueueTp() : head(nullptr), tail(nullptr)
{

}

template <typename T>
QueueTp<T>::QueueTp(const QueueTp<T> &q)
{
    link tail = q.tail;
    while (tail != nullptr)
    {
        enqueue(tail->value);
        tail = tail->prev;
    }
}
template <typename T>
QueueTp<T>::~QueueTp()
{
    emptyList();
}
template <typename T>
void QueueTp<T>::emptyList()
{
    link t = head;
    link next;
    while (t != nullptr)
    {
        next = t->next;
        delete t;
        t = next;
    }
    head = nullptr;
    tail = nullptr;
}
template <typename T>
bool QueueTp<T>::enqueue(const T &val)
{
    link l = new (std::nothrow) Node;
    if (l == nullptr)
    {
        return false;
    }
    else
    {
        if (isEmpty())
        {
            l->value = val;
            l->next = nullptr;
            l->prev = nullptr;
            head = l;
            tail = l;
        }
        else
        {
            l->value = val;
            l->next = head;
            l->prev = nullptr;
            head->prev = l;
            head = l;
        }
        return true;
    }
}
template <typename T>
bool QueueTp<T>::dequeue(T &val)
{
    if (isEmpty())
    {
        return false;
    }
    else
    {
        if (head == tail)
        {
            val = tail->value;
            delete tail;
            head = tail = nullptr;
        }
        else
        {
            val = tail->value;
            link prev = tail->prev;
            delete tail;
            tail = prev;
            tail->next = nullptr;
        }
        return true;
    }
}
template <typename T>
bool QueueTp<T>::isEmpty() const
{
    if (nullptr == head && nullptr == tail)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template <typename T>
QueueTp<T> &QueueTp<T>::operator = (const QueueTp<T> &q)
{
    if (&q == this)
    {
        return *this;
    }

    emptyList();
    link t = q.tail;
    while (t != nullptr)
    {
        enqueue(t->value);
        t = t->prev;
    }
    return *this;
}

class Worker
{
private:
    std::string fullname;
    long id;
protected:
    virtual void Data() const;
    virtual void Get();
public:
    Worker() : fullname("no one"), id(0L) {}
    Worker(const std::string &s, long n) : fullname(s), id(n) {}
    virtual ~Worker() = 0;
    virtual void Set() = 0;
    virtual void Show() const = 0;
};

class Waiter : virtual public Worker
{
private:
    int panache;
protected:
    void Data() const;
    void Get();
public:
    Waiter() : Worker(), panache(0) {}
    Waiter(const std::string &s, long n, int p = 0) : Worker(s, n), panache(p) {}
    Waiter(const Worker &wk, int p = 0) : Worker(wk), panache(p) {}
    void Set();
    void Show() const;
};

class Singer : virtual public Worker
{
protected:
    enum
    {
        other, alto, contralto, soprano,
        bass, baritone, tenor
    };
    enum { Vtypes = 7 };
    void Data() const;
    void Get();
private:
    static const char *pv[Vtypes];
    int voice;
public:
    Singer() : Worker(), voice(other) {}
    Singer(const std::string &s, long n, int v = other) : Worker(s, n), voice(v) {}
    Singer(const Worker &wk, int v = other) : Worker(wk), voice(v) {}
    void Set();
    void Show() const;
};
class SingingWaiter : public Singer, public Waiter
{
protected:
    void Data() const;
    void Get();
public:
    SingingWaiter() {}
    SingingWaiter(const std::string &s, long n, int p = 0, int v = Singer::other) : Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker &wk, int p = 0, int v = Singer::other) : Worker(wk), Waiter(wk, p), Singer(wk, v) {}
    SingingWaiter(const Waiter &wt, int v = Singer::other) : Worker(wt), Waiter(wt), Singer(wt, v) {}
    SingingWaiter(const Singer &wt, int p = 0) : Worker(wt), Waiter(wt, p), Singer(wt) {}
    void Set();
    void Show() const;
};

Worker::~Worker() { }

void Worker::Data() const
{
    cout << "Name: " << fullname << endl;
    cout << "Employee ID: " << id << endl;
}

void Worker::Get()
{
    std::getline(cin, fullname, '\n');
    cout << "Enter worker's ID: ";
    cin >> id;
    while (cin.get() != '\n')
    {
        continue;
    }
}

void Waiter::Set()
{
    cout << "Enter waiter's name: ";
    Worker::Get();
    Get();
}
void Waiter::Show() const
{
    cout << "Category: waiter\n";
    Worker::Data();
    Data();
}
void Waiter::Data() const
{
    cout << "Panache rating: " << panache << endl;
}
void Waiter::Get()
{
    cout << "Enter waiter's panache rating: ";
    cin >> panache;
    while (cin.get() != '\n')
    {
        continue;
    }
}
const char *Singer::pv[Singer::Vtypes] = { "other", "alto", "contralto", "soprano", "bass", "baritone", "tenor" };

void Singer::Set()
{
    cout << "Enter singer's name: ";
    Worker::Get();
    Get();
}

void Singer::Show() const
{
    cout << "Category: singer\n";
    Worker::Data();
    Data();
}
void Singer::Data() const
{
    cout << "Vocal range: " << pv[voice] << endl;
}
void Singer::Get()
{
    cout << "Enter number for singer's vocal range:\n";
    int i;
    for (i = 0; i < Vtypes; i++)
    {
        cout << i << ": " << pv[i] << "   ";
        if (i % 4 == 3)
        {
            cout << endl;
        }
    }
    if (i % 4 != 0)
    {
        cout << '\n';
    }
    while (cin >> voice && (voice < 0 || voice >= Vtypes))
    {
        cout << "Please enter a value >= 0 and < " << Vtypes << endl;
    }
    cin.clear();
    while (cin.get() != '\n')
    {
        continue;
    }
}
void SingingWaiter::Data() const
{
    Singer::Data();
    Waiter::Data();
}
void SingingWaiter::Get()
{
    Waiter::Get();
    Singer::Get();
}
void SingingWaiter::Set()
{
    cout << "Enter singing waiter's name: ";
    Worker::Get();
    Get();
}
void SingingWaiter::Show() const
{
    cout << "Category: singing waiter\n";
    Worker::Data();
    Data();
}

const int SIZE = 5;

int main(int argc, const char *argv[])
{
    try
    {
        QueueTp<Worker *> q;
        Worker *pw;
        int ct;
        for (ct = 0; ct < SIZE; ct++)
        {
            std::cout << "Enter the employee category:\n";
            std::cout << "w: waiter  s: singer  ";
            std::cout << "t: singing waiter  q: quit\n";

            char choice = 0;
            std::cin >> choice;
            while (std::cin.get() != '\n')
            {
                continue;
            }
            while (std::strchr("wstq", choice) == nullptr)
            {
                std::cout << "Please enter a w, s, t, or q: ";
                std::cin >> choice;
                while (std::cin.get() != '\n')
                {
                    continue;
                }
            }

            if (choice == 'q')
            {
                break;
            }

            switch (choice)
            {
            case 'w':
                pw = new Waiter;
                break;
            case 's':
                pw = new Singer;
                break;
            case 't':
                pw = new SingingWaiter;
                break;
            default:
                pw = new SingingWaiter;
                break;
            }

            pw->Set();
            q.enqueue(pw);
        }

        std::cout << "\nHere is your staff:\n";

        for (int i = 0; i < ct; i++)
        {
            q.dequeue(pw);
            pw->Show();
            delete pw;
            std::cout << std::endl;
        }
        std::cout << "Done.\n";

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
