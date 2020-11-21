#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <cctype>

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
using std::map;
using std::string;
using std::getline;
using std::domain_error;
using std::transform;
using std::back_inserter;
using std::sort;
using std::copy;
using std::accumulate;
using std::find;
using std::find_if;
using std::max;
using std::streamsize;
using std::setprecision;
using std::chrono::steady_clock;
using std::end;


class String_list
{
private:
    string *l;
    string::size_type size;
    string::size_type max;

    void resize();
public:
    typedef string *iterator;

    String_list() : l(new string[1]), size(0), max(1) {};
    String_list(const String_list &src);
    ~String_list();

    String_list &operator = (const String_list &str_list);
    void push_back(string);
    string *begin()
    {
        return l;
    }
    string *end()
    {
        return l + size;
    };
};

String_list::String_list(const String_list &src)
{
    size = src.size;
    max = src.max;
    l = new string[max];

    for (string::size_type i = 0; i < size; i++)
    {
        l[i] = src.l[i];
    }
}

String_list::~String_list()
{
    delete[] l;
}

String_list &String_list::operator = (const String_list &str_list)
{
    if (this == &str_list)
    {
        return *this;
    }

    delete[] l;
    size = str_list.size;
    max = str_list.max;
    l = new string[max];

    for (string::size_type i = 0; i < size; i++)
    {
        l[i] = str_list.l[i];
    }

    return *this;
}

void String_list::resize()
{
    max *= 2;

    string *copy = new string[max];

    for (string::size_type i = 0; i < size; i++)
    {
        copy[i] = l[i];
    }

    delete[] l;

    l = copy;
}

void String_list::push_back(string str)
{
    if (size == max)
    {
        resize();
    }

    l[size++] = str;
}

bool space(char c)
{
    return isspace(c) != 0;
}

bool not_space(char c)
{
    return !isspace(c);
}

String_list split(const string &str)
{
    typedef string::const_iterator iter;
    String_list ret;

    iter i = str.begin();
    while (i != str.end())
    {
        i = find_if(i, str.end(), not_space);

        iter j = find_if(i, str.end(), space);

        if (i != j)
        {
            ret.push_back(string(i, j));
            i = j;
        }
    }
    return ret;
}

int main()
{
    string str = "Please split this amazing string!";
    String_list str_l = split(str);
    String_list::iterator iter = str_l.begin();

    while (iter != str_l.end())
    {
        cout << *iter++ << endl;
    }

    return 0;
}
