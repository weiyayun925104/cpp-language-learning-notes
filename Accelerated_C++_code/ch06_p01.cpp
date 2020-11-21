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
    typedef vector<string>::const_iterator iter;
    iter it = v.begin();

    while (it != v.end())
    {
        maxlen = max(maxlen, it->size());
        it++;
    }

    return maxlen;
}

vector<string> frame(const vector<string> &v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    ret.push_back(border);

    vector<string>::const_iterator iter = v.begin();
    while (iter != v.end())
    {
        ret.push_back("* " + *iter + string(maxlen - iter->size(), ' ') + " *");
        iter++;
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

    typedef vector<string>::const_iterator iter;
    iter iter_l = left.begin();
    iter iter_r = right.begin();
    while (iter_l != left.end() || iter_r != right.end())
    {
        string s;

        if (iter_l != left.end())
        {
            s = *iter_l++;
        }

        s += string(width1 - s.size(), ' ');

        if (iter_r != right.end())
        {
            s += *iter_r++;
        }

        ret.push_back(s);
    }

    return ret;
}

int test_frame()
{
    vector<string> v1 = { "one test", "two test", "aye caramba" };
    vector<string> v2 = { "one direction", "mama mia", "mamo testo", "lake district mall" };

    vector<string> vert = vcat(frame(v1), frame(v2));

    vector<string>::const_iterator iter = vert.begin();

    while (iter != vert.end())
    {
        cout << *(iter++) << endl;
    }

    vector<string> horz = hcat(frame(v1), frame(v2));

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
