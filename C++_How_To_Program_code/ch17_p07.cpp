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

class Customer
{
private:
    long arrive;
    int processtime;
public:
    Customer()
    {
        arrive = processtime = 0;
    }
    void set(long when);
    long when() const
    {
        return arrive;
    }
    int ptime() const
    {
        return processtime;
    }
};

typedef Customer Item;

class Queue
{
private:
    struct Node
    {
        Item item;
        struct Node *next;
    };
    enum { Q_SIZE = 10 };
    Node *front;
    Node *rear;
    int items;
    const int qsize;

    Queue(const Queue &q) : qsize(0) { }
    Queue &operator=(const Queue &q)
    {
        return *this;
    }
public:
    Queue(int qs = Q_SIZE);
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item &item);
    bool dequeue(Item &item);
};

Queue::Queue(int qs) : qsize(qs)
{
    front = rear = nullptr;
    items = 0;
}

Queue::~Queue()
{
    Node *next;
    while (front != nullptr)
    {
        next = front->next;
        delete front;
        front = next;
    }
}

bool Queue::isempty() const
{
    return items == 0;
}

bool Queue::isfull() const
{
    return items == qsize;
}

int Queue::queuecount() const
{
    return items;
}
bool Queue::enqueue(const Item &item)
{
    if (isfull())
    {
        return false;
    }
    Node *add = new Node;

    add->item = item;
    add->next = nullptr;
    if (items == 0)
    {
        front = add;
        rear = add;
    }
    else
    {
        rear->next = add;
        rear = add;
    }
    items++;
    return true;
}
bool Queue::dequeue(Item &item)
{
    if (isempty())
    {
        return false;
    }
    item = front->item;
    items--;
    Node *next = front->next;
    delete front;
    front = next;
    if (items == 0)
    {
        front = nullptr;
        rear = nullptr;
    }
    return true;
}
void Customer::set(long when)
{
    processtime = std::rand() % 3 + 1;
    arrive = when;
}

const int MIN_PER_HR = 60;

bool newcustomer(double x)
{
    return ( (std::rand() * x) / RAND_MAX < 1);
}

int main(int argc, const char *argv[])
{
    try
    {
        std::srand(std::time(nullptr));

        cout << "Case Study: Bank of Heather Automatic Teller\n";
        cout << "Enter maximum size of queue: ";
        int qs;
        cin >> qs;

        cout << "Enter the number of simulation hours: ";
        int hours;
        cin >> hours;
        long cyclelimit = MIN_PER_HR * hours;

        double perhour;
        double min_per_cust;

        Item temp;
        long turnaways = 0;
        long customers = 0;
        long served = 0;
        long sum_line = 0;
        int wait_time = 0;
        long line_wait = 0;

        int i = hours;

        do
        {
            perhour = i--;
            min_per_cust = MIN_PER_HR / perhour;
            Queue line(qs);
            turnaways = 0;
            customers = 0;
            served = 0;
            sum_line = 0;
            wait_time = 0;
            line_wait = 0;

            for (long cycle = 0; cycle < cyclelimit; cycle++)
            {
                if (newcustomer(min_per_cust))
                {
                    if (line.isfull())
                    {
                        turnaways++;
                    }
                    else
                    {
                        customers++;
                        temp.set(cycle);
                        line.enqueue(temp);
                    }
                }
                if (wait_time <= 0 && !line.isempty())
                {
                    line.dequeue(temp);
                    wait_time = temp.ptime();
                    line_wait += cycle - temp.when();
                    served++;
                }
                if (wait_time > 0)
                {
                    wait_time--;
                }
                sum_line += line.queuecount();
            }
        }
        while ((double)line_wait / served > 1.0);
        i++;

        if (customers > 0)
        {
            std::cout << "customers per hours: " << i << std::endl;
            cout << "customers accepted: " << customers << endl;
            cout << "customers served: " << served << endl;
            cout << "customers turnaways: " << turnaways << endl;
            cout.precision(2);
            cout.setf(ios_base::fixed, ios_base::floatfield);
            cout.setf(ios_base::showpoint);
            cout << "average queue size: " << (double)sum_line / cyclelimit << endl;
            cout << "average wait time: " << (double)line_wait / served << " minutes\n";
        }
        else
        {
            cout << "No customers!\n";
        }
        cout << "Done.\n";

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
