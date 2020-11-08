#include <iostream>

using namespace std;

int main()
{
    int auks, bats, coots;

    auks = 19.99 + 11.99;

    bats = (int) 19.99 + (int) 11.99;
    coots = int(19.99) + int(11.99);
    cout << "auks = " << auks << ", bats = " << bats << ", coots = " << coots << endl;

    char ch = 'Z';
    cout << "The code for " << ch << " is ";
    cout << int(ch) << endl;
    cout << "Yes, the code is " << static_cast<int> (ch) << endl;

    return 0;
}
