
#include <iostream>

using namespace std;

void add_multipy(int x, int y, int &sum, int &product)
{
    sum = x + y;
    product = x * y;
}

int main()
{
    int x;
    int y;

    cout << "Enter two numbers to get the sum and product. \n";

    cout << "x: ";
    cin >> x;

    cout << "y: ";
    cin >> y;

    int sum = 0;
    int product = 0;
    add_multipy(x, y, sum, product);

    cout << "x + y = " << x << " + " << y << " = " << sum << '\n';
    cout << "x * y = " << x << " * " << y << " = " << product << '\n';
}
