
#include<iostream>

using namespace std;

int pow(int x, int y)
{
    if (y <= 0)
    {
        return 1;
    }
    else if (y == 1)
    {
        return x;
    }
    else
    {
        return x * pow(x, y - 1);
    }
}

int main()
{
    cout << "Let's calculate x^y\n";

    int x = 0;
    do
    {
        cout << "Enter a positive value for x: ";
        cin >> x;
    }
    while (x < 1);
    cin.clear();
    cin.ignore(80, '\n');

    int y = 0;
    do
    {
        cout << "Enter a positive value for y: ";
        cin >> y;
    }
    while (y < 1);
    cin.clear();
    cin.ignore(80, '\n');

    int result = pow(x, y);
    cout << "x^y = " << x << "^" << y << " = " << result << '\n';
}
