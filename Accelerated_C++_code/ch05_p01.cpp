#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::max;
using std::transform;
using std::sort;

vector<string> split(const string &s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size())
    {
        while (i != s.size() && isspace(s[i]))
        {
            ++i;
        }

        string_size j = i;

        while (j != s.size() && !isspace(s[j]))
        {
            ++j;
        }

        if (i != j)
        {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

string::size_type width(const vector<string> &v)
{
    string::size_type maxlen = 0;

    for (vector<string>::size_type i = 0; i != v.size(); ++i)
    {
        maxlen = max(maxlen, v[i].size());
    }

    return maxlen;
}

vector<string> frame(const vector<string> &v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    ret.push_back(border);

    for (vector<string>::size_type i = 0; i != v.size(); ++i)
    {
        ret.push_back("* " + v[i] + string(maxlen - v[i].size(), ' ')  + " *");
    }

    ret.push_back(border);

    return ret;
}

vector<string> vcat(const vector<string> &top, const vector<string> &bottom)
{
    vector<string> ret = top;

    ret.insert(ret.end(), bottom.begin(), bottom.end());

    return ret;
}

vector<string> hcat(const vector<string> &left, const vector<string> &right)
{
    vector<string> ret;

    string::size_type width1 = width(left) + 1;

    vector<string>::size_type i = 0, j = 0;

    while (i != left.size() || j != right.size())
    {
        string s;

        if (i != left.size())
        {
            s = left[i++];
        }

        s += string(width1 - s.size(), ' ');

        if (j != right.size())
        {
            s += right[j++];
        }

        ret.push_back(s);
    }

    return ret;
}

bool compare_ignore_case(string s1, string s2)
{
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    return s1 < s2;
}

vector<string> rotate(const string &s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size())
    {
        while (i != s.size() && isspace(s[i]))
        {
            ++i;
        }

        string_size j = i;

        while (j != s.size() && !isspace(s[j]))
        {
            ++j;
        }

        if (i != j)
        {
            string line = s.substr(i, s.size() - i);
            line += '\t';
            if (i > 0)
            {
                line += s.substr(0, i);
            }
            ret.push_back(line);
            i = j;
        }
    }
    return ret;
}

void unrotate(vector<string> &v)
{
    vector<string> v1, v2;
    vector<string>::iterator iter = v.begin();

    typedef string::size_type s_size;

    while (iter != v.end())
    {
        s_size seperator = iter->find('\t');
        if(seperator >= iter->size() - 1)
        {
            v1.push_back(string(2, ' '));
        }
        else
        {
            v1.push_back( iter->substr( seperator + 1, iter->size() - 1 - seperator ) );
        }
        v2.push_back( iter->substr(0, seperator) );
        ++iter;
    }

    iter = v.begin();
    vector<string>::iterator iter_v1 = v1.begin();
    vector<string>::iterator iter_v2 = v2.begin();
    s_size maxlen = width(v1);

    while (iter != v.end())
    {
        *iter = string(maxlen - iter_v1->size(), ' ') + *iter_v1 + '\t' + *iter_v2;
        ++iter;
        ++iter_v1;
        ++iter_v2;
    }
}

vector<string> permuted_index(const vector<string> &v)
{
    vector<string>::const_iterator iter = v.begin();
    vector<string> permuted_v;

    while (iter != v.end())
    {
        vector<string> rotated_v = rotate(*iter++);
        permuted_v.insert(permuted_v.end(), rotated_v.begin(), rotated_v.end());
    }

    sort(permuted_v.begin(), permuted_v.end(), compare_ignore_case);

    unrotate(permuted_v);

    return permuted_v;
}

int main()
{
    vector<string> v = { "The quick brown fox", "jumped over the fence" };
    vector<string> permuted_v = permuted_index(v);

    vector<string>::const_iterator iter = permuted_v.begin();

    while (iter != permuted_v.end())
    {
        cout << *iter++ << endl;
    }

    return 0;
}
