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

std::random_device rd;
std::mt19937 gen(rd());

int getRandomNumber(const int &min, const int &max)
{
    return std::uniform_int_distribution<int> {min, max}(gen);
}

class Person
{
private:
    std::string firstname;
    std::string lastname;
protected:
    virtual void Data() const;
public:
    Person(const std::string &first = "", const std::string &last = "");
    virtual ~Person() {};
    void setFirstName(const std::string &s)
    {
        firstname = s;
    }
    void setLastName(const std::string &s)
    {
        lastname = s;
    }
    virtual void Show() const;
    virtual void Set();
};
class Gunslinger : virtual public Person
{
private:
    double drawtime;
    int notches;
protected:
    void Data() const;
    virtual void setData();
public:
    Gunslinger(const std::string &first = "", const std::string &last = "", double d = 0, int n = 0);
    ~Gunslinger() {};
    void setDrawTime(double d);
    void setNotches(int n);
    double Draw() const
    {
        return drawtime;
    }
    int Notches() const
    {
        return notches;
    }
    virtual void Show() const;
    virtual void Set()
    {
        Person::Set();
        Gunslinger::setData();
    }
};

class PokerPlayer : virtual public Person
{
public:
    PokerPlayer(std::string first = "", std::string last = "");
    ~PokerPlayer() {}
    int Draw() const
    {
        return getRandomNumber(1, 52);
    }
    virtual void Show() const;
    virtual void Set()
    {
        Person::Set();
    }
};

class BadDude : public Gunslinger, public PokerPlayer
{
private:
public:
    BadDude(std::string first = "", std::string last = "", double d = 0, int n = 0);
    ~BadDude() {}
    double Gdraw() const
    {
        return Gunslinger::Draw();
    }
    int Cdraw() const
    {
        return PokerPlayer::Draw();
    }
    virtual void Show() const;
    void Set();
};


void Person::Data() const
{
    std::cout << "First name: " << firstname << std::endl;
    std::cout << "Last name: " << lastname << std::endl;
}
Person::Person(const std::string &first, const std::string &last)
{
    firstname = first;
    lastname = last;
}
void Person::Show() const
{
    std::cout << "Type Person" << std::endl;
    Data();
}
void Person::Set()
{
    std::cout << "Enter the first name: ";
    std::getline(std::cin, firstname, '\n');
    std::cout << "Enter the last name: ";
    std::getline(std::cin, lastname, '\n');
}
void Gunslinger::Data() const
{
    std::cout << "Draw time: " << drawtime << std::endl;
    std::cout << "Notches: " << notches << std::endl;
}
void Gunslinger::setData()
{
    std::cout << "Enter the draw time: ";
    std::cin >> drawtime;
    while (!std::cin || drawtime < 0)
    {
        std::cin.clear();
        while (std::cin.get() != '\n')
        {
            continue;
        }
        std::cout << "Draw time must be a positive number.\nTry again: ";
        std::cin >> drawtime;
    }

    std::cout << "Enter the number of notches: ";
    std::cin >> notches;
    while (!std::cin || notches < 0)
    {
        std::cin.clear();
        while (std::cin.get() != '\n')
        {
            continue;
        }
        std::cout << "Notches must be a positive integer.\nTry again: ";
        std::cin >> notches;
    }
    while (std::cin.get() != '\n')
    {
        continue;
    }
}

Gunslinger::Gunslinger(const std::string &first, const std::string &last, double d, int n) : Person(first, last)
{
    drawtime = d;
    notches = n;
}

void Gunslinger::setDrawTime(double d)
{
    if (d < 0)
    {
        std::cerr << "Error, draw time cannot be negative. ";
        std::cerr << "Setting draw time to 0." << std::endl;
        drawtime = 0;
    }
    else
    {
        drawtime = d;
    }
}
void Gunslinger::setNotches(int n)
{
    if (n < 0)
    {
        std::cerr << "Error, notches cannot be negative. ";
        std::cerr << "Setting notches to 0." << std::endl;
        notches = 0;
    }
    else
    {
        notches = n;
    }
}

void Gunslinger::Show() const
{
    std::cout << "Type Gunslinger" << std::endl;
    Person::Data();
    Data();
}
PokerPlayer::PokerPlayer(std::string first, std::string last) : Person(first, last)
{

}
void PokerPlayer::Show() const
{
    std::cout << "Type Poker Player" << std::endl;
    Person::Data();
}
BadDude::BadDude(std::string first, std::string last, double d, int n) : Person(first, last), Gunslinger(first, last, d, n), PokerPlayer(first, last)
{

}
void BadDude::Show() const
{
    std::cout << "Type BadDude" << std::endl;
    Person::Data();
    Gunslinger::Data();
}
void BadDude::Set()
{
    Person::Set();
    Gunslinger::setData();
}

const int SIZE = 4;

int main(int argc, const char *argv[])
{
    try
    {
        Person *pp[SIZE];
        int ct;
        for (ct = 0; ct < SIZE; ct++)
        {
            std::cout << "Enter the person category:\n";
            std::cout << "p: person        g: gunslinger" << std::endl;
            std::cout << "k: poker player  b: bad dude" << std::endl;
            std::cout << "q: quit" << std::endl;

            char choice = 0;
            std::cin >> choice;
            while (std::cin.get() != '\n')
            {
                continue;
            }

            while (std::strchr("pgkbq", choice) == nullptr)
            {
                std::cout << "Please enter a p, g, k, b, or q: ";
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
            case 'p':
                pp[ct] = new Person;
                break;
            case 'g':
                pp[ct] = new Gunslinger;
                break;
            case 'k':
                pp[ct] = new PokerPlayer;
                break;
            case 'b':
                pp[ct] = new BadDude;
                break;
            default:
                pp[ct] = new BadDude;
                break;
            }
            pp[ct]->Set();
            pp[ct]->Show();
            std::cout << "ct = " << ct << std::endl;
            std::cout << std::endl;
        }

        std::cout << "Your selection:" << std::endl;
        for (int i = 0; i < ct; i++)
        {
            pp[i]->Show();
            std::cout << std::endl;
            delete *(pp + i);
        }

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
