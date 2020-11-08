#include <iostream>

using namespace std;

int main()
{
    const int ArSize = 32;
    char name[ArSize];
    char dessert[ArSize];
    cout << "Enter your name:\n";
    cin >> name;
    cout << "Enter your favorite dessert:\n";
    cin >> dessert;
    cout << "I have some delicious " << dessert << " for you, " << name << " .\n";

    return 0;
}
