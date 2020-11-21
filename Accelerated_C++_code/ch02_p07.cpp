#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int x = 10;

    while (x >= -5)
    {
        cout << x-- << endl;
    }

    return 0;
}