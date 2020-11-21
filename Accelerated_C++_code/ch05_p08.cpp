#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::max;

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

vector<string> hcat_alternative(const vector<string> &left, const vector<string> &right)
{
    vector<string> ret;

    string::size_type width1 = width(left) + 1;

    vector<string>::size_type i = 0, j = 0;

    string s;
    while (i != left.size() || j != right.size())
    {
        s = "";
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

int test_frame()
{
    vector<string> v1 = { "one test", "two test", "aye caramba" };
    vector<string> v2 = { "one direction", "mama mia", "mamo testo", "lake district mall" };

    vector<string> vert = hcat(frame(v1), frame(v2));

    vector<string>::const_iterator iter = vert.begin();

    while (iter != vert.end())
    {
        cout << *(iter++) << endl;
    }

   cout << endl;

    vector<string> horz = hcat_alternative(frame(v1), frame(v2));

    iter = horz.begin();

    while (iter != horz.end())
    {
        cout << *(iter++) << endl;
    }

    return 0;
}

int main()
{
    test_frame();

    return 0;
}
