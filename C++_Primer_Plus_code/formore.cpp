#include <iostream>

using namespace std;

const int ArSize = 16;

int main()
{
    long long factorials[ArSize];
    factorials[1] = factorials[0] = 1LL;
    for (int i = 2; i < ArSize; i++)
    {
        factorials[i] = i * factorials[i - 1];
    }
    for (int i = 0; i < ArSize; i++)
    {
        cout << i << " ! = " << factorials[i] << endl;
    }

    return 0;
}
