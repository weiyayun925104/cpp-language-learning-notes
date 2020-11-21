#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;
using std::string;
using std::sort;
using std::greater;

ostream &write_lower_upper(ostream &os, const vector<string> &v)
{
    vector<string> v_copy = v;
    sort(v_copy.begin(), v_copy.end(), greater<string>());

    for (vector<string>::size_type i = 0; i < v_copy.size(); i++)
    {
        os << v_copy[i] << endl;
    }

    return os;
}

int main()
{
    vector<string> words = { "TEST", "test", "mountain", "BIKE", "six", "seven", "EIGHT", "NINE", "ten" };
    write_lower_upper(cout, words);

    return 0;
}
