#include <iostream>

using namespace std;

template<typename T>
T lesser(T a, T b)
{
    cout << "template lesser\n";
    return a < b ? a : b;
}

int lesser(int a, int b)
{
    a = a < 0 ? -a : a;
    b = b < 0 ? -b : b;
    return a < b ? a : b;
}

int main()
{
    int m = 20;
    int n = -30;
    double x = 15.5;
    double y = 25.9;
    cout << lesser(m, n) << endl;
    cout << lesser(x, y) << endl;
    cout << lesser<>(m, n) << endl;
    cout << lesser<int>(x, y) << endl;

    return 0;
}
