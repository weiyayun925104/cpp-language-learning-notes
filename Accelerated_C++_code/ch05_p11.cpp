#include <iostream>
#include <vector>
#include <list>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::list;
using std::string;

bool has_asc_desc(const string &s)
{
    string::const_iterator iter = s.begin();
    string asc_desc = "bdfhkltgjpqy";

    while (iter != s.end())
    {
        std::size_t found = asc_desc.find(tolower(*iter++));
        if (found != std::string::npos)
        {
            return true;
        }
    }

    return false;
}

list<string> extract_asc_desc(list<string> &l)
{
    list<string> l_ad;
    list<string>::const_iterator iter = l.begin();

    while (iter != l.end())
    {
        if (has_asc_desc(*iter))
        {
            l_ad.push_back(*iter);
            iter = l.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    return l_ad;
}

string longest_not_asc_desc(list<string> l)
{
    extract_asc_desc(l);
    string longest;

    for (list<string>::const_iterator iter = l.begin(); iter != l.end(); iter++)
    {
        if (iter->length() > longest.length())
        {
            longest = *iter;
        }
    }

    return longest;
}

int main()
{
    list<string> words = { "TEST", "teet", "racecar", "BIKE", "six", "madam", "EIGHT", "reDder", "ten", "multilangual" };
    cout << longest_not_asc_desc(words) << endl;

    return 0;
}
