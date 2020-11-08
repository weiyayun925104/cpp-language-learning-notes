#include <iostream>

using namespace std;

int main()
{
    const int ArSize = 32;
    char name[ArSize];
    char dessert[ArSize];
    cout << "Enter your name:\n";
    cin.getline(name, ArSize);
    cout << "Enter your favorite dessert:\n";
    cin.getline(dessert, ArSize);
    cout << "I have some delicious " << dessert << " for you, " << name << " .\n";

    return 0;
}