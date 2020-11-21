#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::ostream;
using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::sort;
using std::copy;

int quartiles(vector<int> &someInts)
{
    sort(someInts.begin(), someInts.end());

    int quarter = someInts.size() / 4;
    int remainder = someInts.size() % 4;

    if (quarter == 0)
    {
        cout << "Vector is smaller than 4 elements." << endl;
        return 1;
    }

    int start = someInts.size();

    for (int i = 0; i < 4; i++, remainder--)
    {
        stringstream result;
        int quarterSize = remainder > 0 ? quarter + 1 : quarter;
        int stop = start - quarterSize;
        vector<int>::const_iterator first = someInts.begin() + stop;
        vector<int>::const_iterator last = someInts.begin() + start;
        copy(first, last, std::ostream_iterator<int, char>(result, " "));
        cout << "Quarter " << i + 1 << ": " << result.str() << endl;
        start -= quarterSize;
    }

    return 0;
}

int main()
{
    vector<int> someInts = { 10, 12, 5, 8, 13, 25, 1, 121, 85, 99, 120, 180, 75, 205, 16, 22, 99, 16 };

    return quartiles(someInts);
}
