#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int product = 1;

    for (int i = product + 1; i < 10; i++)
    {
        product *= i;
    }

    cout << product << endl;

    return 0;
}
