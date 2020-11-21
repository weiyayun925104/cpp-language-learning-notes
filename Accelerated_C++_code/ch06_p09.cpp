#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::accumulate;

string concat(const vector<string> &v)
{
    string s;
    return accumulate(v.begin(), v.end(), s);
}

int main()
{
    vector<string> v = { "one direction", "mama mia", "mamo testo", "lake district mall" };
    cout << concat(v) << endl;

    return 0;
}
