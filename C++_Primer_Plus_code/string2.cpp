#include <cstring>
#include <cctype>
#include "string2.h"

using std::cin;
using std::cout;

int String::num_strings = 0;

int String::HowMany()
{
    return num_strings;
}

String::String(const char *s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}

String::String()
{
    len = 0;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
}

String::String(const String &st)
{
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    num_strings++;
}
String::~String()
{
    --num_strings;
    delete[] str;
}
void String::stringup()
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}
void String::stringlow()
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}
int String::has(char ch)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == ch)
        {
            count++;
        }
    }
    return count;
}
String &String::operator= (const String &st)
{
    if (this == &st)
    {
        return *this;
    }
    delete[] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}
String &String::operator=(const char *s)
{
    delete[] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}
char &String::operator [] (int i)
{
    return str[i];
}
const char &String::operator [] (int i) const
{
    return str[i];
}
bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}
bool operator>(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) > 0);
}
bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

String operator + (const String &st1, const String &st2)
{
    String temp;
    delete [] temp.str;

    temp.len = strlen(st1.str) + strlen(st2.str);
    temp.str = new char[temp.len + 1];
    strcat(strcpy(temp.str, st1.str), st2.str);

    return temp;
}
String operator+(const char *s, const String &st)
{
    String temp;
    delete[] temp.str;

    temp.len = strlen(s) + st.len;
    temp.str = new char[temp.len + 1];
    strcat(strcpy(temp.str, s), st.str);

    return temp;
}
String operator+(const String &st, const char *s)
{
    String temp;
    delete[] temp.str;

    temp.len = strlen(s) + st.len;
    temp.str = new char[temp.len + 1];
    strcat(strcpy(temp.str, st.str), s);

    return temp;
}
ostream &operator<<(ostream &os, const String &st)
{
    os << st.str;
    return os;
}
istream &operator>>(istream &is, String &st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
    {
        st = temp;
    }
    while (is && is.get() != '\n')
    {
        continue;
    }
    return is;
}
