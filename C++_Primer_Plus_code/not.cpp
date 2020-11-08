#include <iostream>
#include <climits>

using namespace std;

bool is_int(double x);

int main()
{
    double num;

    cout << "Please enter an integer value: ";
    num = 0;
    cin >> num;
    while (!is_int(num))
    {
        cout << "Out of range, please try again: ";
        num = 0;
        cin >> num;
    }
    int val = int(num);
    cout << "You've entered the integer " << val << "\nDone.\n";

    return 0;
}

bool is_int(double x)
{
    if (x <= INT_MAX && x >= INT_MIN)
    {
        return true;
    }
    else
    {
        return false;
    }
}
