#include <iostream>

using namespace std;

int main ()
{
    int x;
    int *p_int;

    p_int = & x;
    cout << "Please enter a number: ";
    cin >> x;
    cout << *p_int << '\n';
    *p_int = 10;
    cout << x;
}
