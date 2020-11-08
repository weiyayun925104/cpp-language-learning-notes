#include <iostream>

using namespace std;

int main()
{
    double hats, heads;

    cout.setf(ios::fixed, ios::floatfield);
    cout << "Enter number: ";
    cin >> hats;
    cout << "Enter another number: ";
    cin >> heads;
    cout << "hats = " << hats << ", heads = " << heads << endl;
    cout << "hats + heads = " << hats + heads << endl;
    cout << "hats - heads = " << hats - heads << endl;
    cout << "hats * heads = " << hats *heads << endl;
    cout << "hats / heads = " << hats / heads << endl;

    return 0;
}
