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

vector<string> center(const vector<string> &v)
{
    vector<string> v_out;
    vector<string>::size_type maxlen = width(v);
    vector<string>::const_iterator iter = v.begin();

    while (iter != v.end())
    {
        int spaces_l = (maxlen - iter->size()) / 2;
        int spaces_r = maxlen - iter->size() - spaces_l;
        v_out.push_back(string(spaces_l, '*') + *iter++ + string(spaces_r, '*'));
    }

    return v_out;
}

int main()
{
    vector<string> v = { "This is really great", "really", "super awesome", "awesomesauce" };
    vector<string> centered_v = center(v);

    vector<string>::const_iterator iter = centered_v.begin();

    while (iter != centered_v.end())
    {
        cout << *iter++ << endl;
    }

    return 0;
}
