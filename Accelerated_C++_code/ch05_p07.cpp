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

int test_frame()
{
    vector<string> v;
    vector<string> v_framed = frame(v);

    vector<string>::const_iterator iter = v_framed.begin();

    while (iter != v_framed.end())
    {
        cout << *iter++ << endl;
    }

    return 0;
}

int main()
{
    test_frame();

    return 0;
}
