#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::copy;

int main()
{
    vector<int> u(10, 100);
    copy(u.begin(), u.end(), std::ostream_iterator<int, char>(cout, " "));
    cout << endl;
    vector<int> v;
    copy (u.begin(), u.end(), back_inserter(v));
    copy(v.begin(), v.end(), std::ostream_iterator<int, char>(cout, ","));
    cout << endl;
    return 0;
}
